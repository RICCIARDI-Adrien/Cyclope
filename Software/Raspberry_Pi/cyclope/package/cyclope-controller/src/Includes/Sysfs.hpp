/** @file Sysfs.hpp
 * Helper functions to access sysfs files.
 * @author Adrien RICCIARDI
 */
#ifndef HPP_SYSFS_HPP
#define HPP_SYSFS_HPP

namespace Sysfs
{
	/** Write a numeric value converted to a string to the specified sysfs file.
	 * @param pointerStringFileName Full path and name of the sysfs file to write to.
	 * @param value The value to write.
	 * @return -1 if an error occurred,
	 * @return 0 on success.
	 */
	int writeFile(const char *pointerStringFileName, int value);
}

#endif
