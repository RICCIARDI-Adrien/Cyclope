/** @file Motor.cpp
 * See Motor.hpp for description.
 * @author Adrien RICCIARDI
 */
#include <cstdio>
#include <cstring>
#include <errno.h>
#include <fcntl.h>
#include <Log.hpp>
#include <Motor.hpp>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

/** The base path of the PWM chip handling the motors PWM channels. */
#define MOTOR_PWM_CHIP_PATH "/sys/class/pwm/pwmchip0"

namespace Motor
{
	/** TODO */
	typedef struct
	{
		int pwmChannel;
		int forwardPwmPeriodMicroseconds;
		int backwardPwmPeriodMicroseconds;
		int stopPwmPeriodMicroseconds;
	} Motor;
	
	/** Direct access to each motor specific settings. */
	static Motor _motors[] =
	{
		// MOTOR_ID_LEFT
		{
			0,
			1000000,
			2000000,
			1500000
		},
		// MOTOR_ID_RIGHT
		{
			1,
			2000000,
			1000000,
			1500000
		}
	};
	
	/** Write a numeric value converted to a string to the specified sysfs file.
	 * @param pointerStringFileName Full path and name of the sysfs file to write to.
	 * @param value The value to write. It's 64-bit wide to for PWM periods in nanoseconds to fit.
	 * @return -1 if an error occurred,
	 * @return 0 on success.
	 */
	int _writeSysfsFile(const char *pointerStringFileName, long long value)
	{
		// Try to open sysfs file
		int fileDescriptor = open(pointerStringFileName, O_WRONLY);
		if (fileDescriptor == -1)
		{
			LOG(LOG_ERR, "Failed to open file \"%s\" (%s).", pointerStringFileName, strerror(errno));
			return -1;
		}
		
		// Convert data to string
		char stringValue[64]; // Should be enough for this program usage
		snprintf(stringValue, sizeof(stringValue), "%lld", value);
		stringValue[sizeof(stringValue) - 1] = 0; // Make sure string is always terminated
		ssize_t length = strlen(stringValue);
		
		// Write data
		int returnValue;
		if (write(fileDescriptor, stringValue, length) != length)
		{
			LOG(LOG_ERR, "Failed to write string value \"%s\" to file \"%s\" (%s).", stringValue, pointerStringFileName, strerror(errno));
			returnValue = -1;
		}
		else returnValue = 0;
		
		close(fileDescriptor);
		return returnValue;
	}
	
	/** TODO */
	int _exportPwmDirectory(int pwmChannel)
	{
		int returnValue = 0;
		
		// Create the requested PWM directory path
		char stringPwmDirectoryPath[64]; // Buffer is big enough to contain all possible PWM channels
		sprintf(stringPwmDirectoryPath, "/sys/class/pwm/pwmchip0/pwm%d", pwmChannel);
		
		// Is the sysfs file exported yet ?
		int fileDescriptor = open(stringPwmDirectoryPath, O_RDONLY);
		if (fileDescriptor == -1) // File is not exported, export it
		{
			// Create the string to write to sysfs export file
			char stringPwmChannel[16];
			sprintf(stringPwmChannel, "%d", pwmChannel);
			
			// Export channel
			if (_writeSysfsFile(MOTOR_PWM_CHIP_PATH "/export", pwmChannel) != 0)
			{
				LOG(LOG_ERR, "Failed to export PWM channel %d.", pwmChannel);
				returnValue = -1;
			}
			close(fileDescriptor);
		}
		
		return returnValue;
	}
	
	int initialize()
	{
		// TODO load motor PWM periods from Configuration module
		
		// Create the first PWM directory path
		/*char stringPwmDirectoryPath[64]; // Buffer is big enough to contain all possible PWM channels
		sprintf(stringPwmDirectoryPath, "/sys/class/pwm/pwmchip0/pwm%d", pwmChannel);*/
		
		// Configure motors
		for (int i = 0; i < MOTOR_IDS_COUNT; i++)
		{
			// Make PWM settings available for this motor
			if (_exportPwmDirectory(_motors[i].pwmChannel)) return -1;
		}
		
		// TODO
		
		return 0;
	}
}
