/** @file ArtificialIntelligenceProgramWanderWithNoGoal.cpp
 * See ArtificialIntelligenceProgram.hpp for description.
 * @author Adrien RICCIARDI
 */
#include <ArtificialIntelligenceProgram.hpp>
#include <cstdio>
#include <Lidar.hpp>
#include <Network.hpp>
#include <unistd.h>

namespace ArtificialIntelligenceProgram
{
	void wanderWithNoGoal()
	{
		int distanceFromAngles[LIDAR_ANGLES_COUNT], minimumDistance, maximumDistance;
		
		// Start measuring distances
		Lidar::setEnabled(true);
		
		while (Network::isProgramRunning())
		{
			Lidar::getLastDistances(distanceFromAngles);
			
			// TEST
			Lidar::getDistanceRangeLimits(distanceFromAngles, 350, 10, &minimumDistance, &maximumDistance);
			printf("min=%d, max=%d\n", minimumDistance, maximumDistance);
			if ((minimumDistance > 300) && (maximumDistance < 1000)) printf("OBSTACLE !!!\n");
			usleep(100000);
		}
		
		// Stop measuring distances
		Lidar::setEnabled(false);
	}
}
