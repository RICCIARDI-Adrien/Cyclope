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

/** PWM period in nanoseconds (Linux expects nanoseconds). */
#define MOTOR_PWM_PERIOD 20000000 // 20ms
/** Duty cycle in nanoseconds to tell the servomotor to immediately stop. */
#define MOTOR_PWM_STOP_DUTY_CYCLE 1500000

namespace Motor
{
	/** Gather motor-specific parameters. */
	typedef struct
	{
		int pwmChannel;
		int forwardPwmPeriodNanoseconds;
		int backwardPwmPeriodNanoseconds;
	} Motor;
	
	/** All possible motions a motor can perform. */
	typedef enum
	{
		MOTOR_MOTION_STOP,
		MOTOR_MOTION_FORWARD,
		MOTOR_MOTION_BACKWARD
	} MotorMotion;
	
	/** Direct access to each motor specific settings. */
	static Motor _motors[] =
	{
		// MOTOR_ID_LEFT
		{
			0,
			2000000,
			1000000
		},
		// MOTOR_ID_RIGHT
		{
			1,
			1000000,
			2000000
		}
	};
	
	/** Write a numeric value converted to a string to the specified sysfs file.
	 * @param pointerStringFileName Full path and name of the sysfs file to write to.
	 * @param value The value to write. It's wide enough for PWM periods in nanoseconds to fit.
	 * @return -1 if an error occurred,
	 * @return 0 on success.
	 */
	int _writeSysfsFile(const char *pointerStringFileName, int value)
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
		snprintf(stringValue, sizeof(stringValue), "%d", value);
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
	
	/** Check whether a specific PWM channel directory is present, if not tell Linux to make it available.
	 * @param pwmChannel The PWM channel number the motor is connected to.
	 * @return -1 if an error occurred,
	 * @return 0 on success.
	 */
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
	
	/** Tell a motor to move or to stop.
	 * @param motorId The motor to set motion.
	 * @param motorMotion The motion to set.
	 * @return -1 if an error occurred,
	 * @return 0 on success.
	 */
	int _setMotorMotion(MotorId motorId, MotorMotion motorMotion)
	{
		// Make sure the specified motor exists
		if (motorId >= MOTOR_IDS_COUNT) return -1;
		
		// Create sysfs file path
		char stringSysfsFile[128];
		sprintf(stringSysfsFile, MOTOR_PWM_CHIP_PATH "/pwm%d/duty_cycle", _motors[motorId].pwmChannel);
		
		// Set desired duty cycle
		switch (motorMotion)
		{
			case MOTOR_MOTION_STOP:
				if (_writeSysfsFile(stringSysfsFile, MOTOR_PWM_STOP_DUTY_CYCLE) != 0) return -1;
				break;
				
			case MOTOR_MOTION_FORWARD:
				if (_writeSysfsFile(stringSysfsFile, _motors[motorId].forwardPwmPeriodNanoseconds) != 0) return -1;
				break;
				
			case MOTOR_MOTION_BACKWARD:
				if (_writeSysfsFile(stringSysfsFile, _motors[motorId].backwardPwmPeriodNanoseconds) != 0) return -1;
				break;
				
			default:
				LOG(LOG_ERR, "Unknown motor motion requested : %d, ignoring command.", motorMotion);
				return -1;
		}
		
		return 0;
	}
	
	int initialize()
	{
		// TODO load motor PWM periods from Configuration module
		
		// Configure each motor
		char stringPwmDirectoryPath[64], stringTemporary[128];
		for (int i = 0; i < MOTOR_IDS_COUNT; i++)
		{
			// Make PWM settings available for this motor
			if (_exportPwmDirectory(_motors[i].pwmChannel)) return -1;
			
			// Cache PWM channel path
			sprintf(stringPwmDirectoryPath, MOTOR_PWM_CHIP_PATH "/pwm%d", _motors[i].pwmChannel);
			
			// Set PWM period (1/50s)
			sprintf(stringTemporary, "%s/period", stringPwmDirectoryPath);
			if (_writeSysfsFile(stringTemporary, MOTOR_PWM_PERIOD) != 0) return -1;
			
			// Make sure motor is stopped
			sprintf(stringTemporary, "%s/duty_cycle", stringPwmDirectoryPath);
			if (_writeSysfsFile(stringTemporary, MOTOR_PWM_STOP_DUTY_CYCLE) != 0) return -1;
			
			// Enable motor signal
			sprintf(stringTemporary, "%s/enable", stringPwmDirectoryPath);
			if (_writeSysfsFile(stringTemporary, 1) != 0) return -1;
		}
		
		return 0;
	}
	
	int setRobotMotion(RobotMotion robotMotion)
	{
		switch (robotMotion)
		{
			case ROBOT_MOTION_STOP:
				if (_setMotorMotion(MOTOR_ID_LEFT, MOTOR_MOTION_STOP) != 0) return -1;
				if (_setMotorMotion(MOTOR_ID_RIGHT, MOTOR_MOTION_STOP) != 0) return -1;
				break;
				
			case ROBOT_MOTION_FORWARD:
				if (_setMotorMotion(MOTOR_ID_LEFT, MOTOR_MOTION_FORWARD) != 0) return -1;
				if (_setMotorMotion(MOTOR_ID_RIGHT, MOTOR_MOTION_FORWARD) != 0) return -1;
				break;
				
			case ROBOT_MOTION_BACKWARD:
				if (_setMotorMotion(MOTOR_ID_LEFT, MOTOR_MOTION_BACKWARD) != 0) return -1;
				if (_setMotorMotion(MOTOR_ID_RIGHT, MOTOR_MOTION_BACKWARD) != 0) return -1;
				break;
				
			case ROBOT_MOTION_LEFT:
				if (_setMotorMotion(MOTOR_ID_LEFT, MOTOR_MOTION_STOP) != 0) return -1;
				if (_setMotorMotion(MOTOR_ID_RIGHT, MOTOR_MOTION_FORWARD) != 0) return -1;
				break;
				
			case ROBOT_MOTION_RIGHT:
				if (_setMotorMotion(MOTOR_ID_LEFT, MOTOR_MOTION_FORWARD) != 0) return -1;
				if (_setMotorMotion(MOTOR_ID_RIGHT, MOTOR_MOTION_STOP) != 0) return -1;
				break;
				
			default:
				LOG(LOG_ERR, "Unknown robot motion : %d, ignoring it.", robotMotion);
				return -1;
		}
		
		return 0;
	}
}
