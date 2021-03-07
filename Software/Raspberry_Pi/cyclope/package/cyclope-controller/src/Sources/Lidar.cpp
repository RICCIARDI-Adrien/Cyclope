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

namespace Lidar
{
	/** Make the thread sleep until distance sampling is enabled. */
	static pthread_cond_t _waitConditionDistanceSampling = PTHREAD_COND_INITIALIZER;
	/** The wait condition mutex. */
	static pthread_mutex_t _mutexWaitConditionDistanceSampling = PTHREAD_MUTEX_INITIALIZER;
	/** Tell whether the wait condition is still blocking. */
	static bool _isDistanceSamplingEnabled = false;
	
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
	
	/** The distance sampling thread. */
	static void *_threadDistanceSampling(void *)
	{
		int gpioChipFileDescriptor, gpioFileDescriptor = -1, serialPortFileDescriptor;
		struct gpiohandle_request gpioRequest;
		struct gpiohandle_data gpioData;
		unsigned char communicationBuffer[22];
		
		// Configure the serial port used to communicate with the lidar
		serialPortFileDescriptor = _configureSerialPort();
		if (serialPortFileDescriptor < 0)
		{
			LOG(LOG_ERR, "Failed to configure serial port (%s).", strerror(errno));
			return NULL;
		}
		
		// Get access to GPIO controller
		gpioChipFileDescriptor = open("/dev/gpiochip0", O_RDONLY);
		if (gpioChipFileDescriptor == -1)
		{
			LOG(LOG_ERR, "Failed to open GPIO chip device (%s).", strerror(errno));
			return NULL;
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
			
			// Sample data until lidar is disabled
			do
			{
				// TEST
				communicationBuffer[0] = 0xA5;
				communicationBuffer[1] = 0x50;
				if (write(serialPortFileDescriptor, communicationBuffer, 2) != 2) printf("WRITE ERROR\n");
				for (int i = 0; i < 27; i++)
				{
					if (read(serialPortFileDescriptor, &communicationBuffer[0], 1) != 1) printf("READ ERROR %d\n", i);
					printf("READ BYTE %d = %d 0x%02X %c\n", i, communicationBuffer[0], communicationBuffer[0], communicationBuffer[0]);
				}
				usleep(1000000);
				
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
		
		// Create the communication thread
		if (pthread_create(&threadId, NULL, _threadDistanceSampling, NULL) != 0)
		{
			LOG(LOG_ERR, "Error : failed to create lidar thread (%s).", strerror(errno));
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
