/** @file Motor.hpp
 * Control each motor speed and direction.
 * @author Adrien RICCIARDI
 */
#ifndef HPP_MOTOR_HPP
#define HPP_MOTOR_HPP

namespace Motor
{
	/** How many time is needed (approximately) for the robot to make a 90° turn (one motor is stopped and the other one is running). */
	const int TURNING_TIME_90_DEGREES_MILLISECONDS = 1600;
	/** How many time is needed (approximately) for the robot to make a 180° turn (one motor is stopped and the other one is running). */
	const int TURNING_TIME_180_DEGREES_MILLISECONDS = 3200;

	/** All possible motions the robot can perform. */
	typedef enum
	{
		ROBOT_MOTION_STOP,
		ROBOT_MOTION_FORWARD,
		ROBOT_MOTION_BACKWARD,
		ROBOT_MOTION_FORWARD_LEFT,
		ROBOT_MOTION_FORWARD_RIGHT,
		ROBOT_MOTION_BACKWARD_LEFT,
		ROBOT_MOTION_BACKWARD_RIGHT
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
