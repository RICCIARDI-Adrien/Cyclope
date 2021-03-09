/** @file Lidar.cpp
 * See Lidar.hpp for description.
 * @author Adrien RICCIARDI
 */
#include <cstdlib>
#include <cstring>
#include <errno.h>
#include <fcntl.h>
#include <Lidar.hpp>
#include <linux/gpio.h>
#include <Log.hpp>
#include <pthread.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <termios.h>
#include <unistd.h>

#include <stdio.h>

/** TODO */
#define LIDAR_COMMUNICATION_PROTOCOL_START_FLAG 0xA5

namespace Lidar
{
	/** All used command codes. */
	typedef enum
	{
		COMMAND_CODE_EXPRESS_SCAN = 0x82
	} CommandCode;
	
	/** Make the thread sleep until distance sampling is enabled. */
	static pthread_cond_t _waitConditionDistanceSampling = PTHREAD_COND_INITIALIZER;
	/** The wait condition mutex. */
	static pthread_mutex_t _mutexWaitConditionDistanceSampling = PTHREAD_MUTEX_INITIALIZER;
	/** Tell whether the wait condition is still blocking. */
	static bool _isDistanceSamplingEnabled = false;
	
	/** The serial port used to communicate with the lidar. */
	static int _serialPortFileDescriptor;
	
	/** Configure the serial port connected to the lidar.
	 * @return -1 if an error occurred,
	 * @return A positive number on success corresponding to the serial port file descriptor.
	 */
	static int _configureSerialPort()
	{
		int fileDescriptorSerialPort = -1;
		struct termios serialPortSettings;
		
		// Initialize serial port at 115200 8N1
		// Try to open device file
		fileDescriptorSerialPort = open("/dev/ttyAMA0", O_RDWR);
		if (fileDescriptorSerialPort == -1)
		{
			LOG(LOG_ERR, "Error : failed to open lidar serial port file (%s).\n", strerror(errno));
			goto Exit_Error;
		}
		
		// Configure new parameters
		memset(&serialPortSettings, 0, sizeof(serialPortSettings));
		serialPortSettings.c_iflag = IGNBRK | IGNPAR | ISTRIP | ICRNL; // Ignore break and parity errors
		serialPortSettings.c_oflag = 0;
		serialPortSettings.c_cflag = CS8 | CREAD | CLOCAL; // 8 data bits, receiver enabled, ignore modem control lines
		serialPortSettings.c_lflag = 0; // Use raw mode
		serialPortSettings.c_cc[VMIN] = 1; // Make read() block until at least one byte is received
		
		// Set read and write speeds
		if (cfsetispeed(&serialPortSettings, B115200) == -1)
		{
			LOG(LOG_ERR, "Error : failed to set serial port reception speed (%s).\n", strerror(errno));
			goto Exit_Error;
		}
		if (cfsetospeed(&serialPortSettings, B115200) == -1)
		{
			LOG(LOG_ERR, "Error : failed to set serial port transmission speed (%s).\n", strerror(errno));
			goto Exit_Error;
		}
		
		// Apply serial port settings
		if (tcsetattr(fileDescriptorSerialPort, TCSANOW, &serialPortSettings) == -1)
		{
			LOG(LOG_ERR, "Error : failed to set serial port settings (%s).\n", strerror(errno));
			goto Exit_Error;
		}
		
		// Everything went fine
		return fileDescriptorSerialPort;
		
	Exit_Error:
		if (fileDescriptorSerialPort != -1) close(fileDescriptorSerialPort);
		return -1;
	}
	
	/** Send a command to the lidar.
	 * @param commandCode The command code. Command start flag is automatically added.
	 * @param pointerPayloadBuffer Contain an optional payload. Payload size and checksum are automatically added.
	 * @param payloadBufferSize The payload size in bytes. Set to 0 if there is no payload.
	 * @return -1 if an error occurred,
	 * @return 0 on success.
	 */
	static int _sendCommand(CommandCode commandCode, unsigned char *pointerPayloadBuffer, int payloadBufferSize)
	{
		unsigned char checksum, commandBuffer[64]; // Should be enough for all existing commands
		int i;
		ssize_t commandBufferSize;
		
		// Prepare command header
		commandBuffer[0] = LIDAR_COMMUNICATION_PROTOCOL_START_FLAG;
		commandBuffer[1] = commandCode;
		commandBufferSize = 2;
		
		// Is there some payload to append ?
		if (payloadBufferSize > 0)
		{
			// Will the whole payload fit in the transmission buffer ?
			if (payloadBufferSize > static_cast<int>(sizeof(commandBuffer) - 4)) // Remove 2 bytes from the command header, 1 byte for payload size and 1 byte for the checksum
			{
				LOG(LOG_ERR, "Error : command payload for command %d is too large (payload size is %d bytes).", commandCode, payloadBufferSize);
				return -1;
			}
			
			// Append payload size
			commandBuffer[2] = payloadBufferSize;
			
			// Append payload
			memcpy(&commandBuffer[3], pointerPayloadBuffer, payloadBufferSize);
			
			// Compute checksum
			checksum = 0;
			for (i = 0; i < payloadBufferSize + 3; i++) checksum ^= commandBuffer[i];
			commandBuffer[payloadBufferSize + 3] = checksum;
			
			// Adjust command total size with payload size, payload size byte and checksum
			commandBufferSize += payloadBufferSize + 2;
		}
		
		// Transmit command
		if (write(_serialPortFileDescriptor, commandBuffer, commandBufferSize) != commandBufferSize)
		{
			LOG(LOG_ERR, "Error : failed to transmit command %d (%s).", commandCode, strerror(errno));
			return -1;
		}
		
		return 0;
	}
	
	/** The distance sampling thread. */
	static void *_threadDistanceSampling(void *)
	{
		int gpioChipFileDescriptor, gpioFileDescriptor = -1;
		struct gpiohandle_request gpioRequest;
		struct gpiohandle_data gpioData;
		unsigned char commandPayloadBuffer[8]; // No need for more bytes for the used commands
		
		// Get access to GPIO controller
		gpioChipFileDescriptor = open("/dev/gpiochip0", O_RDONLY);
		if (gpioChipFileDescriptor == -1)
		{
			LOG(LOG_ERR, "Failed to open GPIO chip device (%s).", strerror(errno));
			goto Exit;
		}
		
		// Configure lidar GPIO as output
		memset(&gpioRequest, 0, sizeof(gpioRequest));
		gpioRequest.lineoffsets[0] = 23; // Pin 16 is GPIO 23
		gpioRequest.flags = GPIOHANDLE_REQUEST_OUTPUT;
		gpioRequest.lines = 1;
		
		// Get a file descriptor to access the GPIO
		if (ioctl(gpioChipFileDescriptor, GPIO_GET_LINEHANDLE_IOCTL, &gpioRequest) < 0)
		{
			LOG(LOG_ERR, "Could not retrieve lidar GPIO handle (%s).", strerror(errno));
			goto Exit;
		}
		gpioFileDescriptor = gpioRequest.fd;
		close(gpioChipFileDescriptor);
		gpioChipFileDescriptor = -1;
		
		// Make sure lidar is disabled
		gpioData.values[0] = 0;
		if (ioctl(gpioFileDescriptor, GPIOHANDLE_SET_LINE_VALUES_IOCTL, &gpioData) < 0)
		{
			LOG(LOG_ERR, "Could not disable lidar power (%s).", strerror(errno));
			goto Exit;
		}
		
		while (1)
		{
			// Wait for the lidar to be enabled
			pthread_mutex_lock(&_mutexWaitConditionDistanceSampling);
			while (!_isDistanceSamplingEnabled) pthread_cond_wait(&_waitConditionDistanceSampling, &_mutexWaitConditionDistanceSampling); // Wait for a wake-up signal, avoiding spurious ones by checking the condition variable
			pthread_mutex_unlock(&_mutexWaitConditionDistanceSampling);
			
			// Enable lidar power
			gpioData.values[0] = 1;
			if (ioctl(gpioFileDescriptor, GPIOHANDLE_SET_LINE_VALUES_IOCTL, &gpioData) < 0)
			{
				LOG(LOG_ERR, "Could not enable lidar power (%s).", strerror(errno));
				goto Exit;
			}
			
			// Wait 3 seconds for the motor to spin
			usleep(3000000);
			
			// RPLIDAR A1M8 preferred scan mode is Express one, which has index 1, so start scanning using this mode
			/*commandPayloadBuffer[0] = 1; // Select mode 1, taking into account that multi-bytes numbers must be sent in little endian
			commandPayloadBuffer[1] = 0;
			commandPayloadBuffer[2] = 0;
			commandPayloadBuffer[3] = 0;
			commandPayloadBuffer[4] = 0;
			if (_sendCommand(COMMAND_CODE_EXPRESS_SCAN, commandPayloadBuffer, 5) != 0) goto Exit;*/
			
			// TEST
			commandPayloadBuffer[0] = 0x7F;
			commandPayloadBuffer[1] = 0;
			commandPayloadBuffer[2] = 0;
			commandPayloadBuffer[3] = 0;
			commandPayloadBuffer[4] = 0;
			commandPayloadBuffer[5] = 0;
			if (_sendCommand((CommandCode) 0x84, commandPayloadBuffer, 6) != 0) goto Exit;
			
			// Sample data until lidar is disabled
			do
			{
				unsigned char byte;
				// TEST
				if (read(_serialPortFileDescriptor, &byte, 1) != 1) printf("READ ERROR\n");
				printf("READ BYTE %d 0x%02X %c\n", byte, byte, byte);
				
				// TODO
			} while (_isDistanceSamplingEnabled);
			
			// Disable lidar power
			gpioData.values[0] = 0;
			if (ioctl(gpioFileDescriptor, GPIOHANDLE_SET_LINE_VALUES_IOCTL, &gpioData) < 0)
			{
				LOG(LOG_ERR, "Could not disable lidar power (%s).", strerror(errno));
				goto Exit;
			}
		}
		
	Exit:
		if (gpioChipFileDescriptor != -1) close(gpioChipFileDescriptor);
		if (gpioFileDescriptor != -1) close(gpioFileDescriptor);
		return NULL;
	}
	
	int initialize()
	{
		pthread_t threadId;
		
		// Configure the serial port used to communicate with the lidar
		_serialPortFileDescriptor = _configureSerialPort();
		if (_serialPortFileDescriptor < 0)
		{
			LOG(LOG_ERR, "Failed to configure serial port (%s).", strerror(errno));
			return -1;
		}
		
		// Create the communication thread
		if (pthread_create(&threadId, NULL, _threadDistanceSampling, NULL) != 0)
		{
			LOG(LOG_ERR, "Error : failed to create lidar thread (%s).", strerror(errno));
			close(_serialPortFileDescriptor);
			return -1;
		}
		
		return 0;
	}
	
	void setEnabled(bool isEnabled)
	{
		if (isEnabled)
		{
			pthread_mutex_lock(&_mutexWaitConditionDistanceSampling);
			_isDistanceSamplingEnabled = isEnabled;
			pthread_cond_signal(&_waitConditionDistanceSampling);
			pthread_mutex_unlock(&_mutexWaitConditionDistanceSampling);
		}
		else _isDistanceSamplingEnabled = false;
	}
}
