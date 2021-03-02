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
	
	/** The distance sampling thread. */
	static void *_threadDistanceSampling(void *)
	{
		int gpioChipFileDescriptor, gpioFileDescriptor = -1;
		struct gpiohandle_request gpioRequest;
		struct gpiohandle_data gpioData;
		
		// TODO serial port
		
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
				printf("distance sampling thread is running.\n");
				usleep(2000000);
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
