/** @file Motor.hpp
 * Control each motor speed and direction.
 * @author Adrien RICCIARDI
 */
#ifndef HPP_MOTOR_HPP
#define HPP_MOTOR_HPP

namespace Motor
{
	/** All available motors. */
	typedef enum
	{
		MOTOR_ID_LEFT,
		MOTOR_ID_RIGHT,
		MOTOR_IDS_COUNT
	} MotorId;
	
	/** Initialize PWM modules and turn motors off.
	 * @return -1 if an error occurred,
	 * @return 0 on success.
	 */
	int initialize();
}

#endif
