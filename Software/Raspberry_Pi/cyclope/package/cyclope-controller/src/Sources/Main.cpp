/** @file Main.cpp
 * Cyclope middleware entry point and AI program execution.
 * @author Adrien RICCIARDI
 */
#include <cstdlib>
#include <Log.hpp>
#include <Motor.hpp>
#include <Network.hpp>

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
	
	// Initialize server
	if (Network::initialize() != 0)
	{
		LOG(LOG_ERR, "Server initialization failed, aborting.");
		return EXIT_FAILURE;
	}
	
	// Execute AI programs
	while (1)
	{
		// Wait for a program to execute
		LOG(LOG_INFO, "Waiting for an AI program to execute...");
		int programIndex = Network::waitForProgramExecutionRequest(); // TODO cast to an enum type later ?
		
		// Execute the requested program
		LOG(LOG_INFO, "Beginning execution of program %d.\n", programIndex); // TODO also display a string with the program name
		// TODO
	}
	
	return EXIT_SUCCESS;
}
