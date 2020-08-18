/** @file Light.cpp
 * See Light.hpp for description.
 * @author Adrien RICCIARDI
 */
#include <cstdlib>
#include <cstring>
#include <errno.h>
#include <fcntl.h>
#include <Light.hpp>
#include <linux/gpio.h>
#include <Log.hpp>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

namespace Light
{
	/** The file descriptor used to access to the leds GPIO. */
	static int _gpioFileDescriptor = -1;
	
	/** Automatically called on application exit to release resources. */
	static void _applicationExit()
	{
		if (_gpioFileDescriptor != -1) close(_gpioFileDescriptor);
		LOG(LOG_ERR, "caca");
	}
	
	int initialize()
	{
		// Get access to GPIO controller
		int gpioChipFileDescriptor = open("/dev/gpiochip0", O_RDONLY);
		if (gpioChipFileDescriptor == -1)
		{
			LOG(LOG_ERR, "Failed to open GPIO chip device (%s).", strerror(errno));
			return -1;
		}
		
		// Configure leds GPIO as output
		struct gpiohandle_request gpioRequest;
		memset(&gpioRequest, 0, sizeof(gpioRequest));
		gpioRequest.lineoffsets[0] = 24; // Pin 18 is GPIO 24
		gpioRequest.flags = GPIOHANDLE_REQUEST_OUTPUT;
		gpioRequest.lines = 1;
		
		// Get a file descriptor to access the GPIO
		if (ioctl(gpioChipFileDescriptor, GPIO_GET_LINEHANDLE_IOCTL, &gpioRequest) < 0)
		{
			LOG(LOG_ERR, "Could not retrieve leds GPIO handle (%s).\n", strerror(errno));
			close(gpioChipFileDescriptor);
			return -1;
		}
		_gpioFileDescriptor = gpioRequest.fd;
		
		// GPIO chip access is no more needed
		close(gpioChipFileDescriptor);
		
		// Automatically release resources on application exit
		atexit(_applicationExit);
		
		return 0;
	}
}
