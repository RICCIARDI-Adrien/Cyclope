/** @file Main.cpp
 * Cyclope middleware entry point and AI program execution.
 * @author Adrien RICCIARDI
 */
#include <cstdlib>
#include <syslog.h>

//-------------------------------------------------------------------------------------------------
// Entry point
//-------------------------------------------------------------------------------------------------
int main()
{
	// Initialize logging
	openlog("cyclope-controller", LOG_PID, LOG_USER);
	syslog(LOG_INFO, "Starting Cyclope controller...");
	
	return EXIT_SUCCESS;
}
