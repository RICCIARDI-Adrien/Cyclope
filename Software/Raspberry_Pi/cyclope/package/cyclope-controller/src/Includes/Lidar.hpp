/** @file Lidar.hpp
 * Retrieve distance measurements from a RPLIDAR A1M8.
 * @author Adrien RICCIARDI
 */
#ifndef HPP_LIDAR_HPP
#define HPP_LIDAR_HPP

namespace Lidar
{
	/** Initialize the lidar serial port and driving GPIO.
	 * @return -1 if an error occurred,
	 * @return 0 on success.
	 */
	int initialize();
}

#endif
