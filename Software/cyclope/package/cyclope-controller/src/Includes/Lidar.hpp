/** @file Lidar.hpp
 * Retrieve distance measurements from a RPLIDAR A1M8.
 * @author Adrien RICCIARDI
 */
#ifndef HPP_LIDAR_HPP
#define HPP_LIDAR_HPP

/** How many angles can be sampled by this lidar. */
#define LIDAR_ANGLES_COUNT 360

namespace Lidar
{
	/** Initialize the lidar serial port and driving GPIO.
	 * @return -1 if an error occurred,
	 * @return 0 on success.
	 */
	int initialize();
	
	/** Turn lidar on or off.
	 * @param isEnabled Set to false to turn lidar off, set to true to turn lidar on.
	 */
	void setEnabled(bool isEnabled);
	
	/** Get the last sampled distances.
	 * @param pointerDistanceFromAngles On output, contain a copy of the last sampled distances. The pointed buffer must have at least LIDAR_ANGLES_COUNT elements count. Distances unit is millimeter.
	 */
	void getLastDistances(int *pointerDistanceFromAngles);
	
	/** Determine the minimum and maximum distances of a specific angles range of measured distances. Starting angle can be greater than ending angle, for instance startingAngle=350 and endingAngle=10 to measure a 20 degree range in front of the robot.
	 * @param startingAngle The angle to start considering distance from. Angle unit is degree, value 0 is in front of the robot, angle values increment clockwise.
	 * @param endingAngle The angle to end considering distance from. Angle unit is degree, value 0 is in front of the robot, angle values increment clockwise.
	 * @param pointerMinimumDistance On output, contain the minimum distance found in the specified range (in millimeter). Set this pointer to NULL if you don't want minimum distance reporting.
	 * @param pointerMaximumDistance On output, contain the maximum distance found in the specified range (in millimeter). Set this pointer to NULL if you don't want minimum distance reporting.
	 */
	void getDistanceRangeLimits(int *pointerDistanceFromAngles, int startingAngle, int endingAngle, int *pointerMinimumDistance, int *pointerMaximumDistance);
}

#endif
