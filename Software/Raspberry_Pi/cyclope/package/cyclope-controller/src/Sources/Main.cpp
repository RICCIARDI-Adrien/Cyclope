/** @file Main.cpp
 * Cyclope middleware entry point and AI program execution.
 * @author Adrien RICCIARDI
 */
#include <cstdlib>
#include <Log.hpp>
#include <Motor.hpp>

//-------------------------------------------------------------------------------------------------
// Entry point
//-------------------------------------------------------------------------------------------------
int main()
{
	// Initialize logging before everything else
	Log::initialize();
	LOG(LOG_INFO, "Starting Cyclope controller...");
	
	// Configure motor PWMs
	LOG(LOG_INFO, "Initializing motors...");
	if (Motor::initialize() != 0)
	{
		LOG(LOG_ERR, "Motors initialization failed, aborting.");
		return EXIT_FAILURE;
	}
	LOG(LOG_INFO, "Motors successfully initialized.");
	
	return EXIT_SUCCESS;
}
