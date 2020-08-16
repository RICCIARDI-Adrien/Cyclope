/** @file Log.hpp
 * Write log messages to syslog daemon.
 * @author Adrien RICCIARDI
 */
#ifndef HPP_LOG_HPP
#define HPP_LOG_HPP

// Provide syslog 'level' constants
#include <syslog.h>

/** Write a log message to syslog daemon.
 * @param syslogLevel Use the same 'level' constants that syslog() function uses. See 'man syslog' for more information.
 * @param pointerStringFormat A printf()-like format string.
 */
#define LOG(syslogLevel, pointerStringFormat, ...) Log::writeLog(syslogLevel, "[%s:%d] " pointerStringFormat, __PRETTY_FUNCTION__, __LINE__, ##__VA_ARGS__)

namespace Log
{
	/** Configure future syslog writes. */
	void initialize();
	
	/** Append a message to the system logger. Each message is prefixed by this program name, PID, function name and line.
	 * @param syslogLevel Use the same 'level' constants that syslog() function uses. See 'man syslog' for more information.
	 * @param pointerStringFormat A printf()-like format string.
	 */
	void writeLog(int syslogLevel, const char *pointerStringFormat, ...);
}

#endif
