/** @file ArtificialIntelligenceProgramWanderWithNoGoal.cpp
 * See ArtificialIntelligenceProgram.hpp for description.
 * @author Adrien RICCIARDI
 */
#include <ArtificialIntelligenceProgram.hpp>
#include <cstdio>
#include <Lidar.hpp>
#include <Light.hpp>
#include <Motor.hpp>
#include <Network.hpp>
#include <unistd.h>

namespace ArtificialIntelligenceProgram
{
	void wanderWithNoGoal()
	{
		const int MAXIMUM_DISTANCE_MILLIMETER = 800; // The maximum distance taken into account by the robot
		const int OBSTACLE_AVOIDANCE_DISTANCE_MILLIMETER = 400; // The distance at which the robot will change its direction to avoid the object
		int distanceFromAngles[LIDAR_ANGLES_COUNT], distance, leftDistance, rightDistance;
		
		// Reset robot state
		Motor::setRobotMotion(Motor::ROBOT_MOTION_STOP);
		Light::setEnabled(false);
		memset(distanceFromAngles, 0, sizeof(distanceFromAngles)); // Prevent the robot from running until some valid data was processed
		
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
			
			// Search for the longest obstacle-free distance in front of the robot (using a field of view of 90°)
			Lidar::getDistanceRangeLimits(distanceFromAngles, 315, 45, &distance, nullptr);
			
			// Clamp the distance to the maximum taken into account here
			if (distance > MAXIMUM_DISTANCE_MILLIMETER) distance = MAXIMUM_DISTANCE_MILLIMETER;
			
			// Is an obstacle becoming close ?
			if (distance < OBSTACLE_AVOIDANCE_DISTANCE_MILLIMETER)
			{
				Light::setEnabled(true);
				
				// Is there more room to go on the left or on the right (keep 10° each side as hysteresis) ?
				Lidar::getDistanceRangeLimits(distanceFromAngles, 315, 350, &leftDistance, nullptr);
				Lidar::getDistanceRangeLimits(distanceFromAngles, 10, 45, &rightDistance, nullptr);
				
				// Turn the the location with the less close obstacle
				if (leftDistance > rightDistance) Motor::setRobotMotion(Motor::ROBOT_MOTION_FORWARD_LEFT);
				else Motor::setRobotMotion(Motor::ROBOT_MOTION_FORWARD_RIGHT);
			}
			// No obstacle at sight, go straight
			else
			{
				Light::setEnabled(false);
				
				Motor::setRobotMotion(Motor::ROBOT_MOTION_FORWARD);
			}
			
			// React not too fast to avoid creating current bursts with motors
			usleep(100000);
		}
		
		// Stop measuring distances
		Lidar::setEnabled(false);
	}
}
