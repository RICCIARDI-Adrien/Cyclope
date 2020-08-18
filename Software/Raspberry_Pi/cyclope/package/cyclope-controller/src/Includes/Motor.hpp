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
	
	/** All possible motions the robot can perform. */
	typedef enum
	{
		ROBOT_MOTION_STOP,
		ROBOT_MOTION_FORWARD,
		ROBOT_MOTION_BACKWARD,
		ROBOT_MOTION_LEFT,
		ROBOT_MOTION_RIGHT
	} RobotMotion;
	
	/** Initialize PWM modules and turn motors off.
	 * @return -1 if an error occurred,
	 * @return 0 on success.
	 */
	int initialize();
	
	/** Tell robot to move or to stop.
	 * @param robotMotion The motion to set.
	 * @return -1 if an error occurred,
	 * @return 0 on success.
	 */
	int setRobotMotion(RobotMotion robotMotion);
}

#endif
