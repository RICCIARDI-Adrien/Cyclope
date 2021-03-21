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

/** The flag starting every lidar command and answer. */
#define LIDAR_COMMUNICATION_PROTOCOL_START_FLAG 0xA5

/** TODO */
#define LIDAR_SCAN_LEGACY_DATA_CABINS_COUNT 16

/** How many measures in a response packet. There are 2 measures per cabin. */
#define LIDAR_SCAN_LEGACY_DATA_MEASURES_COUNT (LIDAR_SCAN_LEGACY_DATA_CABINS_COUNT * 2)

namespace Lidar
{
	/** All used command codes. */
	typedef enum
	{
		COMMAND_CODE_STOP = 0x25,
		COMMAND_CODE_EXPRESS_SCAN = 0x82
	} CommandCode;
	
	/** TODO */
	typedef struct __attribute__((packed))
	{
		unsigned char data[5];
	} ScanLegacyDataCabin;
	
	/** TODO */
	typedef struct __attribute__((packed))
	{
		unsigned char reserved[2];
		unsigned short startAngle;
		ScanLegacyDataCabin cabins[LIDAR_SCAN_LEGACY_DATA_CABINS_COUNT];
	} ScanLegacyResponsePacket;
	
	/** TODO */
	typedef struct
	{
		int distanceMillimeter;
		int angleDelta;
	} Measure;
	
	/** TODO */
	typedef struct
	{
		int startAngle;
		Measure measures[LIDAR_SCAN_LEGACY_DATA_MEASURES_COUNT];
	} ScanLegacyExtractedData;
	
	/** Make the thread sleep until distance sampling is enabled. */
	static pthread_cond_t _waitConditionDistanceSampling = PTHREAD_COND_INITIALIZER;
	/** The wait condition mutex. */
	static pthread_mutex_t _mutexWaitConditionDistanceSampling = PTHREAD_MUTEX_INITIALIZER;
	/** Tell whether the wait condition is still blocking. */
	static bool _isDistanceSamplingEnabled = false;
	
	/** Store latest measured distances for each angle degree. */
	static int _distanceFromAngles[LIDAR_ANGLES_COUNT];
	/** Allow atomic access to angles data. */
	static pthread_mutex_t _mutexDistanceFromAngles = PTHREAD_MUTEX_INITIALIZER;
	
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
		serialPortSettings.c_iflag = IGNBRK | IGNPAR; // Ignore break and parity errors
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
	 * @param pointerPayloadBuffer Contain an optional payload. Payload size and checksum are automatically added. It can be NULL if no payload is provided.
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
	
	/** Receive all the bytes of an expected response.
	 * @param bytesCount How many bytes to receive. This function will block until all bytes are received.
	 * @param pointerOutputBuffer On output, contain the received data. Make sure the provided buffer is large enough.
	 * @return -1 if an error occurred,
	 * @return 0 on success.
	 */
	static int _receiveCommandResponse(int bytesCount, void *pointerOutputBuffer)
	{
		unsigned char *pointerBufferByte = reinterpret_cast<unsigned char *>(pointerOutputBuffer);
		
		while (bytesCount > 0)
		{
			// Try to read the next byte
			if (read(_serialPortFileDescriptor, pointerBufferByte, 1) != 1) return -1;
			
			// Prepare for next one
			pointerBufferByte++;
			bytesCount--;
		}
		
		return 0;
	}
	
	/** Retrieve the relevant data from a raw lidar reponse packet.
	 * @param pointerPacket The raw scan response packet received from the lidar.
	 * @param pointerExtractedData On output, contain the reassembled information. Only relevant information are extracted, they are kept in their original units.
	 */
	static inline void _extractScanLegacyData(ScanLegacyResponsePacket *pointerPacket, ScanLegacyExtractedData *pointerExtractedData)
	{
		int i, measuresIndex = 0;
		ScanLegacyDataCabin *pointerCabin;
		
		// Extract starting angle
		pointerExtractedData->startAngle = pointerPacket->startAngle & 0x7FFF;
		
		// Process each cabin
		for (i = 0; i < LIDAR_SCAN_LEGACY_DATA_CABINS_COUNT; i++)
		{
			// Cache current cabin access
			pointerCabin = &pointerPacket->cabins[i];
			
			// Extract first distance
			pointerExtractedData->measures[measuresIndex].distanceMillimeter = ((pointerCabin->data[1] << 6) | (pointerCabin->data[0] >> 2)) & 0x3FFF;
			// Extract first angle delta
			pointerExtractedData->measures[measuresIndex].angleDelta = ((pointerCabin->data[0] & 0x03) << 4) | (pointerCabin->data[4] & 0x0F);
			measuresIndex++;

			// Extract second distance
			pointerExtractedData->measures[measuresIndex].distanceMillimeter = ((pointerCabin->data[3] << 6) | (pointerCabin->data[2] >> 2)) & 0x3FFF;
			// Extract second angle delta
			pointerExtractedData->measures[measuresIndex].angleDelta = ((pointerCabin->data[2] & 0x03) << 4) | (pointerCabin->data[4] >> 4);
			measuresIndex++;
		}
	}
	
	/** Compute the angles related to each distances from the extracted data.
	 * @param pointerPreviousExtractedData The scan data from the previous lidar frame.
	 * @param pointerCurrentExtractedData The scan data from the current lidar frame.
	 * @param pointerDistanceFromAnglesArray An array where each angle (used as index) corresponds to the sampled distance, relevant distances will be filled by this function.
	 * @note This algorithm is taken from RPLIDAR SDK, original coding style has been kept.
	 */
	static inline void _processScanLegacyData(ScanLegacyExtractedData *pointerPreviousExtractedData, ScanLegacyExtractedData *pointerCurrentExtractedData, int *pointerDistanceFromAnglesArray)
	{
		int angleDegree;
		
		int currentStartAngle_q8 = pointerCurrentExtractedData->startAngle << 2;
		int prevStartAngle_q8 = pointerPreviousExtractedData->startAngle << 2;
		
		int diffAngle_q8 = (currentStartAngle_q8) - (prevStartAngle_q8);
		if (prevStartAngle_q8 >  currentStartAngle_q8) {
			diffAngle_q8 += (360<<8);
		}
		
		int angleInc_q16 = (diffAngle_q8 << 3);
		int currentAngle_raw_q16 = (prevStartAngle_q8 << 8);
		
		for (size_t pos = 0; pos < 16; ++pos)
		{
			int angle_q16[2];

			int angle_offset1_q3 = pointerPreviousExtractedData->measures[pos * 2].angleDelta;
			int angle_offset2_q3 = pointerPreviousExtractedData->measures[pos * 2 + 1].angleDelta;

			angle_q16[0] = (currentAngle_raw_q16 - (angle_offset1_q3<<13));
			currentAngle_raw_q16 += angleInc_q16;

			angle_q16[1] = (currentAngle_raw_q16 - (angle_offset2_q3<<13));
			currentAngle_raw_q16 += angleInc_q16;

			for (int cpos = 0; cpos < 2; ++cpos) {

				if (angle_q16[cpos] < 0) angle_q16[cpos] += (360<<16);
				if (angle_q16[cpos] >= (360<<16)) angle_q16[cpos] -= (360<<16);
				
				// Fill corresponding distance using angle as index
				angleDegree = angle_q16[cpos] >> 16; // Convert angle to degrees
				// Save value only if angle is valid
				if ((angleDegree >= 0) && (angleDegree <= 359)) pointerDistanceFromAnglesArray[angleDegree] = pointerPreviousExtractedData->measures[pos * 2 + cpos].distanceMillimeter;
			}
		}
	}
	
	/** The distance sampling thread. */
	static void *_threadDistanceSampling(void *)
	{
		static unsigned char startExpressScanCommandAnswer[] = { LIDAR_COMMUNICATION_PROTOCOL_START_FLAG, 0x5A, 0x54, 0, 0, 0x40, 0x82 };
		int gpioChipFileDescriptor, gpioFileDescriptor = -1, distanceFromAngles[LIDAR_ANGLES_COUNT] = {0}, updatedMeasuresCount = 0;
		struct gpiohandle_request gpioRequest;
		struct gpiohandle_data gpioData;
		unsigned char commandPayloadBuffer[8]; // No need for more bytes for the used commands
		ScanLegacyResponsePacket packet;
		ScanLegacyExtractedData previousExtractedData, currentExtractedData;
		bool isInitialPacket = true;
		
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
			
			// Wait some time for the motor to spin
			usleep(3000000);
			
			// RPLIDAR A1M8 preferred scan mode is Express one, which has index 1, so start scanning using this mode
			commandPayloadBuffer[0] = 1; // Select mode 1, taking into account that multi-bytes numbers must be sent in little endian
			commandPayloadBuffer[1] = 0;
			commandPayloadBuffer[2] = 0;
			commandPayloadBuffer[3] = 0;
			commandPayloadBuffer[4] = 0;
			if (_sendCommand(COMMAND_CODE_EXPRESS_SCAN, commandPayloadBuffer, 5) != 0) goto Exit;
			
			// Lidar will reply with its firmware version number, discard this data
			while (1)
			{
				// Read each byte until the command answer beginning
				_receiveCommandResponse(1, commandPayloadBuffer); // Recycle "commandPayloadBuffer" variable
				if (commandPayloadBuffer[0] == LIDAR_COMMUNICATION_PROTOCOL_START_FLAG)
				{
					// Get response content
					if (_receiveCommandResponse(sizeof(startExpressScanCommandAnswer) - 1, &commandPayloadBuffer[1]) != 0) LOG(LOG_WARNING, "Warning : failed to read response to express scan command (%s).", strerror(errno)); // Recycle "commandPayloadBuffer" variable
					
					// Is this the expected response ?
					if (memcmp(commandPayloadBuffer, startExpressScanCommandAnswer, sizeof(startExpressScanCommandAnswer)) != 0) LOG(LOG_WARNING, "Warning : bad response to express scan command.");
					
					// In all cases, assume lidar data are good
					break;
				}
			}
			
			// Sample data until lidar is disabled
			do
			{
				// Retrieve next data response packet
				if (_receiveCommandResponse(sizeof(packet), &packet) != 0)
				{
					LOG(LOG_WARNING, "Warning : failed to receive scan data response, trying next one.");
					continue;
				}
				
				// Recompose packet content
				_extractScanLegacyData(&packet, &currentExtractedData);
				
				// Extract measured distances
				if (!isInitialPacket)
				{
					_processScanLegacyData(&previousExtractedData, &currentExtractedData, distanceFromAngles);
					updatedMeasuresCount += LIDAR_SCAN_LEGACY_DATA_MEASURES_COUNT;
					
					// Atomically update global distance array if enough measures have been taken
					if (updatedMeasuresCount >= LIDAR_ANGLES_COUNT)
					{
						pthread_mutex_lock(&_mutexDistanceFromAngles);
						memcpy(_distanceFromAngles, distanceFromAngles, sizeof(distanceFromAngles));
						pthread_mutex_unlock(&_mutexDistanceFromAngles);
						
						updatedMeasuresCount = 0;
					}
				}
				else isInitialPacket = false;
				
				// Keep data for next packet processing
				memcpy(&previousExtractedData, &currentExtractedData, sizeof(currentExtractedData));
			} while (_isDistanceSamplingEnabled);
			
			// Tell lidar to stop
			_sendCommand(COMMAND_CODE_STOP, nullptr, 0); // No need to check result as lidar power will be turned off
			usleep(50000); // Give some time to the lidar to stop
			
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
	
	void getLastDistances(int *pointerDistanceFromAngles)
	{
		// Atomically retrieve the array content
		pthread_mutex_lock(&_mutexDistanceFromAngles);
		memcpy(pointerDistanceFromAngles, _distanceFromAngles, sizeof(_distanceFromAngles));
		pthread_mutex_unlock(&_mutexDistanceFromAngles);
	}
	
	void getDistanceRangeLimits(int *pointerDistanceFromAngles, int startingAngle, int endingAngle, int *pointerMinimumDistance, int *pointerMaximumDistance)
	{
		int distance, minimumDistance = 10000000, maximumDistance = 0; // Initialize values with values that can't exist
		
		// Make sure provided angles are valid
		startingAngle %= 360;
		endingAngle %= 360;
		
		// Process each angle in between the provided range
		while (startingAngle != endingAngle)
		{
			// Determine minimum and maximum distances
			distance = pointerDistanceFromAngles[startingAngle];
			if ((distance > 0) && (distance < minimumDistance)) minimumDistance = distance; // Do not take 0 (which stands for a bad measure) into account
			else if (distance > maximumDistance) maximumDistance = distance;
			
			// Check next angle
			startingAngle++;
			if (startingAngle >= 360) startingAngle = 0;
		}
		
		// Update provided output values
		if (pointerMinimumDistance != nullptr)
		{
			if (minimumDistance == 10000000) minimumDistance = 0; // Force minimum distance to 0 in case all measured distances were bad
			*pointerMinimumDistance = minimumDistance;
		}
		if (pointerMaximumDistance != nullptr) *pointerMaximumDistance = maximumDistance;
	}
}
