/** @file ArtificialIntelligenceProgramWanderWithNoGoal.cpp
 * See ArtificialIntelligenceProgram.hpp for description.
 * @author Adrien RICCIARDI
 */
#include <ArtificialIntelligenceProgram.hpp>
#include <cstdio>
#include <cstring>
#include <Lidar.hpp>
#include <Light.hpp>
#include <Motor.hpp>
#include <Network.hpp>
#include <unistd.h>

/** TODO */
#define MOTORS_DELAY_TICK_MILLISECONDS 100

/** TODO */
#define WANDER_WITH_NO_GOAL_MOTORS_DELAY() usleep(MOTORS_DELAY_TICK_MILLISECONDS * 1000)

namespace ArtificialIntelligenceProgram
{
	typedef enum
	{
		WANDER_WITH_NO_GOAL_STATE_DETERMINE_FORWARD_DISTANCE,
		WANDER_WITH_NO_GOAL_STATE_GO_FORWARD,
		WANDER_WITH_NO_GOAL_STATE_DETERMINE_OBSTACLE_AVOIDANCE_DIRECTION,
		WANDER_WITH_NO_GOAL_STATE_DETERMINE_BACKWARD_DISTANCE,
		WANDER_WITH_NO_GOAL_STATE_TERMINATE_BACKWARD_SEQUENCE
	} WanderWithNoGoalState;
	
	void wanderWithNoGoal()
	{
		const int MAXIMUM_DISTANCE_MILLIMETER = 800; // The maximum distance taken into account by the robot
		const int OBSTACLE_AVOIDANCE_DISTANCE_MILLIMETER = 400; // The distance at which the robot will change its direction to avoid the object
		const int VERY_CLOSE_OBSTACLE_DISTANCE_MILLIMETER = 200; // The distance preventing the robot to go further, it must go back or it will collide something
		const int BACKWARD_DIRECTION_DELAY = 60; // How many "motor ticks" the robot will go backward (assuming a tick is 100ms)
		int distanceFromAngles[LIDAR_ANGLES_COUNT] = {0}, distance, leftDistance, rightDistance, backwardDirectionRemainingCounts = 0; // Prevent the robot from running until some valid data was processed by clearing distanceFromAngles array
		WanderWithNoGoalState state = WANDER_WITH_NO_GOAL_STATE_DETERMINE_FORWARD_DISTANCE;
		
		// Reset robot state
		Motor::setRobotMotion(Motor::ROBOT_MOTION_STOP);
		Light::setEnabled(false);
		
		// Start measuring distances
		Lidar::setEnabled(true);
		
		// Wait for lidar to return meaningful information
		do
		{
			Lidar::getLastDistances(distanceFromAngles);
			Lidar::getDistanceRangeLimits(distanceFromAngles, 315, 45, &distance, nullptr);
		} while (distance < 40); // Distance can't be less than 40mm, as this is the clearance from the lidar sensor to the chassis edge
		
		while (Network::isProgramRunning())
		{
			Lidar::getLastDistances(distanceFromAngles);
			
			switch (state)
			{
				case WANDER_WITH_NO_GOAL_STATE_DETERMINE_FORWARD_DISTANCE:
				{
					// Search for the longest obstacle-free distance in front of the robot (using a field of view of 90°)
					Lidar::getDistanceRangeLimits(distanceFromAngles, 315, 45, &distance, nullptr);
					if (distance > MAXIMUM_DISTANCE_MILLIMETER) distance = MAXIMUM_DISTANCE_MILLIMETER; // Clamp the distance to the maximum taken into account here
					
					// Is an obstacle very close ?
					if (distance <= VERY_CLOSE_OBSTACLE_DISTANCE_MILLIMETER)
					{
						backwardDirectionRemainingCounts = BACKWARD_DIRECTION_DELAY; // This state is not reached until the robot terminates the backward sequence, so counter can be safely initialized here
						state = WANDER_WITH_NO_GOAL_STATE_DETERMINE_BACKWARD_DISTANCE;
					}
					// Is an obstacle becoming close ?
					else if (distance <= OBSTACLE_AVOIDANCE_DISTANCE_MILLIMETER) state = WANDER_WITH_NO_GOAL_STATE_DETERMINE_OBSTACLE_AVOIDANCE_DIRECTION;
					// No obstacle at sight, go straight
					else state = WANDER_WITH_NO_GOAL_STATE_GO_FORWARD;
					break;
				}
				
				case WANDER_WITH_NO_GOAL_STATE_GO_FORWARD:
				{
					// No obstacle at sight, turn leds off
					Light::setEnabled(false);
					
					Motor::setRobotMotion(Motor::ROBOT_MOTION_FORWARD);
					WANDER_WITH_NO_GOAL_MOTORS_DELAY();
					
					state = WANDER_WITH_NO_GOAL_STATE_DETERMINE_FORWARD_DISTANCE;
					break;
				}
				
				case WANDER_WITH_NO_GOAL_STATE_DETERMINE_OBSTACLE_AVOIDANCE_DIRECTION:
				{
					// Obstacle detected, turn leds on
					Light::setEnabled(true);
				
					// Is there more room to go on the left or on the right (keep 5° each side as hysteresis) ?
					Lidar::getDistanceRangeLimits(distanceFromAngles, 300, 355, &leftDistance, nullptr); // 55° on the top left side
					Lidar::getDistanceRangeLimits(distanceFromAngles, 5, 60, &rightDistance, nullptr); // 55° on the top right side
					
					// Turn to the location with the less close obstacle
					if (leftDistance > rightDistance) Motor::setRobotMotion(Motor::ROBOT_MOTION_FORWARD_LEFT);
					else Motor::setRobotMotion(Motor::ROBOT_MOTION_FORWARD_RIGHT);
					WANDER_WITH_NO_GOAL_MOTORS_DELAY();
					
					state = WANDER_WITH_NO_GOAL_STATE_DETERMINE_FORWARD_DISTANCE;
					break;
				}
				
				case WANDER_WITH_NO_GOAL_STATE_DETERMINE_BACKWARD_DISTANCE:
				{
					// Turn leds on until the robot terminates the escaping sequence
					Light::setEnabled(true);
					
					// Can the robot go straight backward ?
					Lidar::getDistanceRangeLimits(distanceFromAngles, 135, 225, &distance, nullptr);
					if (distance > OBSTACLE_AVOIDANCE_DISTANCE_MILLIMETER) Motor::setRobotMotion(Motor::ROBOT_MOTION_BACKWARD);
					else
					{
						// Is there more room to go on the left or on the right in the backward direction (keep 5° each side as hysteresis) ?
						Lidar::getDistanceRangeLimits(distanceFromAngles, 185, 240, &leftDistance, nullptr); // 60° on the bottom left side
						Lidar::getDistanceRangeLimits(distanceFromAngles, 120, 175, &rightDistance, nullptr); // 60° on the bottom right side
						
						// Turn to the location with the less close obstacle
						if (leftDistance > rightDistance) Motor::setRobotMotion(Motor::ROBOT_MOTION_BACKWARD_LEFT);
						else Motor::setRobotMotion(Motor::ROBOT_MOTION_BACKWARD_RIGHT);
					}
					WANDER_WITH_NO_GOAL_MOTORS_DELAY();
					
					// Continue going in reverse until the counter time has elapsed
					if (backwardDirectionRemainingCounts > 0) backwardDirectionRemainingCounts--;
					else state = WANDER_WITH_NO_GOAL_STATE_TERMINATE_BACKWARD_SEQUENCE;
					
					break;
				}
				
				case WANDER_WITH_NO_GOAL_STATE_TERMINATE_BACKWARD_SEQUENCE:
				{
					// Determine which direction has the more clearance
					Lidar::getDistanceRangeLimits(distanceFromAngles, 185, 240, &leftDistance, nullptr); // 60° on the bottom left side
					Lidar::getDistanceRangeLimits(distanceFromAngles, 120, 175, &rightDistance, nullptr); // 60° on the bottom right side
					
					// Turn to the location with the less close obstacle
					if (leftDistance > rightDistance) Motor::setRobotMotion(Motor::ROBOT_MOTION_BACKWARD_LEFT);
					else Motor::setRobotMotion(Motor::ROBOT_MOTION_BACKWARD_RIGHT);
					WANDER_WITH_NO_GOAL_MOTORS_DELAY();
					WANDER_WITH_NO_GOAL_MOTORS_DELAY();
					WANDER_WITH_NO_GOAL_MOTORS_DELAY();
					
					state = WANDER_WITH_NO_GOAL_STATE_DETERMINE_FORWARD_DISTANCE;
					break;
				}
			}
		}
		
		// Stop measuring distances
		Lidar::setEnabled(false);
	}
}
