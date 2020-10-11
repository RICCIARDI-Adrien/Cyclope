/** @file Main.cpp
 * Cyclope middleware entry point and AI program execution.
 * @author Adrien RICCIARDI
 */
#include <Adc.hpp>
#include <ArtificialIntelligenceProgram.hpp>
#include <cstdlib>
#include <Light.hpp>
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
	if (Motor::initialize() != 0)
	{
		LOG(LOG_ERR, "Motors initialization failed, aborting.");
		return EXIT_FAILURE;
	}
	
	// Configure front board leds
	if (Light::initialize() != 0)
	{
		LOG(LOG_ERR, "Lights initialization failed, aborting.");
		return EXIT_FAILURE;
	}
	
	// Configure analog voltages sampling
	if (Adc::initialize() != 0)
	{
		LOG(LOG_ERR, "ADC initialization failed, aborting.");
		return EXIT_FAILURE;
	}
	
	// Initialize server
	if (Network::initialize() != 0)
	{
		LOG(LOG_ERR, "Communication protocol server initialization failed, aborting.");
		return EXIT_FAILURE;
	}
	
	// Execute AI programs
	while (1)
	{
		// Wait for a program to execute
		LOG(LOG_INFO, "Waiting for an AI program to execute...");
		int programIndex = Network::waitForProgramExecutionRequest(); // TODO cast to an enum type later ?
		
		// Turn off camera streaming to make camera available for AI program
		system("/etc/init.d/S99camera stop");
		
		// Execute the requested program
		LOG(LOG_INFO, "Beginning execution of AI program %d.\n", programIndex); // TODO also display a string with the program name
		switch (programIndex)
		{
			case 0:
				ArtificialIntelligenceProgram::followObject();
				break;
				
			default:
				LOG(LOG_ERR, "Unknown AI program requested, aborting.");
				break;
		}
		
		// Restart camera streaming
		system("/etc/init.d/S99camera start"); // TODO control camera when manual driving mode is enabled ?
	}
	
	return EXIT_SUCCESS;
}
