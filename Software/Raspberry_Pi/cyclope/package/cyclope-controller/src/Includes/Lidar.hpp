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
}

#endif
