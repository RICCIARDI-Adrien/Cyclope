/** @file Log.cpp
 * See Log.hpp for description.
 * @author Adrien RICCIARDI
 */
#include <Log.hpp>
#include <stdarg.h>

namespace Log
{
	void initialize()
	{
		// Append process PID to each message
		openlog("cyclope-controller", LOG_PID, LOG_USER);
	}
	
	void writeLog(int syslogLevel, const char *pointerStringFormat, ...)
	{
		// Retrieve variable arguments list
		va_list argumentsList;
		va_start(argumentsList, pointerStringFormat);
		
		// Write message to system logger
		vsyslog(syslogLevel, pointerStringFormat, argumentsList);
		
		// Clean stack
		va_end(argumentsList);
	}
}
