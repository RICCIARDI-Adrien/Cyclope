/** @file Main.cpp
 * Cyclope middleware entry point and AI program execution.
 * @author Adrien RICCIARDI
 */
#include <Adc.hpp>
#include <ArtificialIntelligenceProgramManager.hpp>
#include <cstdlib>
#include <Lidar.hpp>
#include <Light.hpp>
#include <Log.hpp>
#include <Motor.hpp>
#include <unistd.h>
#include <WebServer.hpp>

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

	// Configure Lidar module
	if (Lidar::initialize() != 0)
	{
		LOG(LOG_ERR, "Lidar initialization failed, aborting.");
		return EXIT_FAILURE;
	}

	// Initialize the server
	if (WebServer::initialize() != 0)
	{
		LOG(LOG_ERR, "Web server initialization failed, aborting.");
		return EXIT_FAILURE;
	}

	// Make the robot lights blink three times to tell it is ready
	for (int i = 0; i < 3; i++)
	{
		if (Light::setEnabled(true) != 0) LOG(LOG_ERR, "Failed to turn lights on.");
		usleep(250000);
		if (Light::setEnabled(false) != 0) LOG(LOG_ERR, "Failed to turn lights off.");
		usleep(250000);
	}
	LOG(LOG_INFO, "Server is ready.");

	// Execute AI programs, exploiting the main thread
	while (1)
	{
		// Wait for a program to execute
		LOG(LOG_INFO, "Waiting for an AI program to execute...");
		ArtificialIntelligenceProgramBase *pointerProgram = ArtificialIntelligenceProgramManager::waitForProgramExecutionRequest();
		if (pointerProgram == nullptr)
		{
			LOG(LOG_ERR, "The selected AI program does not exist.");
			continue;
		}

		// Execute the requested program
		LOG(LOG_INFO, "Beginning execution of the AI program \"%s\".", pointerProgram->getDescriptiveName());
		pointerProgram->setExitRequest(false); // Reset the exit flag to make the program run
		pointerProgram->run();

		// Make sure the robot is stopped
		Motor::setRobotMotion(Motor::ROBOT_MOTION_STOP);
		Lidar::setEnabled(false);
		Light::setEnabled(false);
	}

	return EXIT_SUCCESS;
}
