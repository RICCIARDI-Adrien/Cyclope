/** @file ArtificialIntelligenceProgramWanderWithNoGoal.cpp
 * See ArtificialIntelligenceProgramWanderWithNoGoal.hpp for description.
 * @author Adrien RICCIARDI
 */
#include <ArtificialIntelligenceProgramWanderWithNoGoal.hpp>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <Lidar.hpp>
#include <Light.hpp>
#include <Motor.hpp>
#include <unistd.h>

/** How many milliseconds to wait between two motors activations (to let the motors reverse voltage dissipate). */
#define MOTORS_DELAY_TICK_MILLISECONDS 100

/** Avoid activating the motors too quickly to prevent damaging them. */
#define WANDER_WITH_NO_GOAL_MOTORS_DELAY() usleep(MOTORS_DELAY_TICK_MILLISECONDS * 1000)

void ArtificialIntelligenceProgramWanderWithNoGoal::run()
{
	const int OBSTACLE_AVOIDANCE_DISTANCE_MILLIMETER = 400; // The distance at which the robot will change its direction to avoid the object
	const int VERY_CLOSE_OBSTACLE_DISTANCE_MILLIMETER = 200; // The distance preventing the robot to go further, it must go back or it will collide something
	int distanceFromAngles[LIDAR_ANGLES_COUNT] = {0}, distance, leftDistance, rightDistance, furtherDistance, distanceFromDirections[WANDER_WITH_NO_GOAL_DIRECTIONS_COUNT], turnRemainingCounts = 0, i; // Prevent the robot from running until some valid data was processed by clearing distanceFromAngles array
	WanderWithNoGoalState state = WANDER_WITH_NO_GOAL_STATE_GO_FORWARD;
	WanderWithNoGoalDirection furtherDistanceDirection;

	// Initialize pseudo-random numbers generator
	srand(time(nullptr));

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

	while (!_isExitRequested)
	{
		Lidar::getLastDistances(distanceFromAngles);

		switch (state)
		{
			case WANDER_WITH_NO_GOAL_STATE_GO_FORWARD:
			{
				// Can the robot go straight backward ?
				Lidar::getDistanceRangeLimits(distanceFromAngles, 330, 30, &distance, nullptr);
				if (distance > OBSTACLE_AVOIDANCE_DISTANCE_MILLIMETER)
				{
					// No obstacle at sight, turn leds off
					Light::setEnabled(false);

					Motor::setRobotMotion(Motor::ROBOT_MOTION_FORWARD);
					WANDER_WITH_NO_GOAL_MOTORS_DELAY();
				}
				else if (distance > VERY_CLOSE_OBSTACLE_DISTANCE_MILLIMETER)
				{
					// One or more obstacles is detected, turn leds on
					Light::setEnabled(true);

					// Is there more room to go on the left or on the right in the forward direction (keep 5° each side as hysteresis) ?
					Lidar::getDistanceRangeLimits(distanceFromAngles, 315, 355, &leftDistance, nullptr); // 60° on the front left side
					Lidar::getDistanceRangeLimits(distanceFromAngles, 5, 60, &rightDistance, nullptr); // 60° on the front right side

					// Turn to the location with the less close obstacle
					if (leftDistance > rightDistance) Motor::setRobotMotion(Motor::ROBOT_MOTION_FORWARD_LEFT);
					else Motor::setRobotMotion(Motor::ROBOT_MOTION_FORWARD_RIGHT);
					WANDER_WITH_NO_GOAL_MOTORS_DELAY();
				}
				else
				{
					// Turn leds on until the robot terminates the escaping sequence
					Light::setEnabled(true);

					state = WANDER_WITH_NO_GOAL_STATE_BACKWARD_SEQUENCE_GO_TO_SAFE_LOCATION;
				}

				break;
			}

			case WANDER_WITH_NO_GOAL_STATE_BACKWARD_SEQUENCE_GO_TO_SAFE_LOCATION:
			{
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

				// Stop only when there is enough clearance all around the robot
				Lidar::getDistanceRangeLimits(distanceFromAngles, 0, 359, &distance, nullptr);
				if (distance >= OBSTACLE_AVOIDANCE_DISTANCE_MILLIMETER) state = WANDER_WITH_NO_GOAL_STATE_BACKWARD_SEQUENCE_DETERMINE_NEXT_DIRECTION;

				break;
			}

			case WANDER_WITH_NO_GOAL_STATE_BACKWARD_SEQUENCE_DETERMINE_NEXT_DIRECTION:
			{
				// Split the lidar values into four 90° windows and determine which one has the most clearance
				Lidar::getDistanceRangeLimits(distanceFromAngles, 315, 45, &distanceFromDirections[WANDER_WITH_NO_GOAL_DIRECTION_FORWARD], nullptr); // Front
				Lidar::getDistanceRangeLimits(distanceFromAngles, 45, 135, &distanceFromDirections[WANDER_WITH_NO_GOAL_DIRECTION_RIGHT], nullptr); // Right
				Lidar::getDistanceRangeLimits(distanceFromAngles, 135, 225, &distanceFromDirections[WANDER_WITH_NO_GOAL_DIRECTION_BACKWARD], nullptr); // Back
				Lidar::getDistanceRangeLimits(distanceFromAngles, 225, 315, &distanceFromDirections[WANDER_WITH_NO_GOAL_DIRECTION_LEFT], nullptr); // Left

				// Determine the further distance and which direction leads to the further distance
				furtherDistance = 0;
				for (i = 0; i < WANDER_WITH_NO_GOAL_DIRECTIONS_COUNT; i++)
				{
					if (distanceFromDirections[i] > furtherDistance)
					{
						furtherDistance = distanceFromDirections[i];
						furtherDistanceDirection = static_cast<WanderWithNoGoalDirection>(i);
					}
				}

				// Start turning the robot nose to that direction
				if (furtherDistanceDirection == WANDER_WITH_NO_GOAL_DIRECTION_FORWARD)
				{
					// Robot is facing the good direction yet, nothing more to do
					state = WANDER_WITH_NO_GOAL_STATE_GO_FORWARD;
					break;
				}

				// Robot needs to turn, determine the quickest path
				if (furtherDistanceDirection == WANDER_WITH_NO_GOAL_DIRECTION_LEFT)
				{
					Motor::setRobotMotion(Motor::ROBOT_MOTION_FORWARD_LEFT);
					turnRemainingCounts = Motor::TURNING_TIME_90_DEGREES_MILLISECONDS / MOTORS_DELAY_TICK_MILLISECONDS;
				}
				else if (furtherDistanceDirection == WANDER_WITH_NO_GOAL_DIRECTION_RIGHT)
				{
					Motor::setRobotMotion(Motor::ROBOT_MOTION_FORWARD_RIGHT);
					turnRemainingCounts = Motor::TURNING_TIME_90_DEGREES_MILLISECONDS / MOTORS_DELAY_TICK_MILLISECONDS;
				}
				else
				{
					// Robot needs to do a half turn, select a random direction to do that
					if (rand() % 2 == 0) Motor::setRobotMotion(Motor::ROBOT_MOTION_BACKWARD_LEFT);
					else Motor::setRobotMotion(Motor::ROBOT_MOTION_BACKWARD_RIGHT);
					turnRemainingCounts = Motor::TURNING_TIME_180_DEGREES_MILLISECONDS / MOTORS_DELAY_TICK_MILLISECONDS;
				}
				WANDER_WITH_NO_GOAL_MOTORS_DELAY();

				state = WANDER_WITH_NO_GOAL_STATE_TURN;
				break;
			}

			case WANDER_WITH_NO_GOAL_STATE_TURN:
			{
				if (turnRemainingCounts > 0)
				{
					turnRemainingCounts--;
					WANDER_WITH_NO_GOAL_MOTORS_DELAY();
				}
				else state = WANDER_WITH_NO_GOAL_STATE_GO_FORWARD;

				break;
			}
		}
	}

	// Stop measuring distances
	Lidar::setEnabled(false);
}
