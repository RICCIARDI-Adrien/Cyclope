/** @file Sysfs.cpp
 * See Sysfs.hpp for description.
 * @author Adrien RICCIARDI
 */
#include <cstdio>
#include <cstring>
#include <errno.h>
#include <fcntl.h>
#include <Log.hpp>
#include <sys/stat.h>
#include <sys/types.h>
#include <Sysfs.hpp>
#include <unistd.h>

namespace Sysfs
{
	int writeFile(const char *pointerStringFileName, int value)
	{
		// Try to open sysfs file
		int fileDescriptor = open(pointerStringFileName, O_WRONLY);
		if (fileDescriptor == -1)
		{
			LOG(LOG_ERR, "Failed to open file \"%s\" (%s).", pointerStringFileName, strerror(errno));
			return -1;
		}
		
		// Convert data to string
		char stringValue[64]; // Should be enough for this program usage
		snprintf(stringValue, sizeof(stringValue), "%d", value);
		stringValue[sizeof(stringValue) - 1] = 0; // Make sure string is always terminated
		ssize_t length = strlen(stringValue);
		
		// Write data
		int returnValue;
		if (write(fileDescriptor, stringValue, length) != length)
		{
			LOG(LOG_ERR, "Failed to write string value \"%s\" to file \"%s\" (%s).", stringValue, pointerStringFileName, strerror(errno));
			returnValue = -1;
		}
		else returnValue = 0;
		
		close(fileDescriptor);
		return returnValue;
	}
}
