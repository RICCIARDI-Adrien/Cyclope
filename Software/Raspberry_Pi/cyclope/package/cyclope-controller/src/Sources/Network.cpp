/** @file Network.cpp
 * See Network.hpp for description.
 * @author Adrien RICCIARDI
 */
#include <Adc.hpp>
#include <arpa/inet.h>
#include <Configuration.hpp>
#include <cstdlib>
#include <cstring>
#include <errno.h>
#include <Light.hpp>
#include <Log.hpp>
#include <Motor.hpp>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <Network.hpp>
#include <pthread.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

namespace Network
{
	/** All available commands the PC application can send. */
	typedef enum
	{
		NETWORK_COMMUNICATION_PROTOCOL_COMMAND_SET_MOTION,
		NETWORK_COMMUNICATION_PROTOCOL_COMMAND_GET_BATTERY_VOLTAGE,
		NETWORK_COMMUNICATION_PROTOCOL_COMMAND_GET_MOTOR_DUTY_CYCLE,
		NETWORK_COMMUNICATION_PROTOCOL_COMMAND_SET_MOTOR_DUTY_CYCLE,
		NETWORK_COMMUNICATION_PROTOCOL_COMMAND_SET_LIGHT_ENABLED,
		NETWORK_COMMUNICATION_PROTOCOL_COMMAND_POWER_OFF,
		NETWORK_COMMUNICATION_PROTOCOL_COMMAND_LIST_AVAILABLE_AI_PROGRAMS,
		NETWORK_COMMUNICATION_PROTOCOL_COMMAND_START_AI_PROGRAM,
		NETWORK_COMMUNICATION_PROTOCOL_COMMAND_STOP_CURRENT_AI_PROGRAM,
		NETWORK_COMMUNICATION_PROTOCOL_COMMAND_SET_STREAMING_CAMERA_ENABLED,
		NETWORK_COMMUNICATION_PROTOCOL_COMMANDS_COUNT
	} CommunicationProtocolCommand;
	
	/** The wait condition telling when a program execution can begin. */
	static pthread_cond_t _programExecutionWaitCondition = PTHREAD_COND_INITIALIZER;
	/** The mutex used to synchronize the program execution wait condition. */
	static pthread_mutex_t _programExecutionWaitConditionMutex = PTHREAD_MUTEX_INITIALIZER;
	/** The program execution wait condition variable, it holds the program index to execute or -1 if no program must be executed. */
	static volatile int _programToExecuteIndex = -1;
	
	/** Tell whether currently running program must terminate. */
	static volatile bool _isProgramRunning;
	
	/** Network server thread. */
	static void *_serverThread(void *)
	{
		// Declare all variables at the beginning to be able to use goto instruction without triggering "jump to label crosses variable initialization" error
		int serverSocket = -1, isAddressReusingEnabled = 1, clientSocket = -1, i, voltageMillivolts, percentage;
		struct sockaddr_in address;
		socklen_t addressSize;
		bool isErrorExitRequested = true;
		CommunicationProtocolCommand command;
		Motor::RobotMotion robotMotion;
		unsigned char byte, buffer[32];
		unsigned short *pointerWord;
		
		LOG(LOG_INFO, "Network thread started, initializing server...");
		
		// Create server socket
		serverSocket = socket(AF_INET, SOCK_STREAM, 0);
		if (serverSocket == -1)
		{
			LOG(LOG_ERR, "Failed to create server socket, aborting (%s).", strerror(errno));
			goto Exit;
		}
			
		// Allow address to be reused instantly
		setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, &isAddressReusingEnabled, sizeof(isAddressReusingEnabled));
		
		// Bind the server port
		address.sin_family = AF_INET;
		address.sin_port = htons(CONFIGURATION_NETWORK_SERVER_PORT);
		address.sin_addr.s_addr = INADDR_ANY;
		if (bind(serverSocket, reinterpret_cast<const struct sockaddr *>(&address), sizeof(address)) == -1)
		{
			LOG(LOG_ERR, "Failed to bind server socket, aborting (%s).", strerror(errno));
			goto Exit;
		}
		
		// Make robot lights blink three times to tell it is ready
		for (i = 0; i < 3; i++)
		{
			if (Light::setEnabled(true) != 0) LOG(LOG_ERR, "Failed to turn lights on.");
			usleep(250000);
			if (Light::setEnabled(false) != 0) LOG(LOG_ERR, "Failed to turn lights off.");
			usleep(250000);
		}
		LOG(LOG_INFO, "Server is ready.");
		
		// Wait for a client to connect
		while (1)
		{
			// Allow only one client at a time
			if (listen(serverSocket, 1) == -1)
			{
				LOG(LOG_ERR, "Server listen() call failed, aborting (%s).", strerror(errno));
				goto Exit;
			}
			
			// Accept client
			addressSize = sizeof(address);
			clientSocket = accept(serverSocket, reinterpret_cast<struct sockaddr *>(&address), &addressSize);
			if (clientSocket == -1)
			{
				LOG(LOG_ERR, "Failed to accept client, aborting (%s).", strerror(errno));
				goto Exit;
			}
			LOG(LOG_INFO, "A new client has connected. IP address : %s, port : %d.", inet_ntoa(address.sin_addr), ntohs(address.sin_port));
			
			// Process client commands
			while (1)
			{
				// Wait for a command code
				if (recv(clientSocket, &command, 1, MSG_WAITALL) != 1) goto Client_Disconnected; // TODO use select to allow to exit from the thread
				
				// Process command
				switch (command)
				{
					case NETWORK_COMMUNICATION_PROTOCOL_COMMAND_SET_MOTION:
						// Retrieve motion parameter
						if (recv(clientSocket, &robotMotion, 1, MSG_WAITALL) != 1) goto Client_Disconnected;
						// Set new motion
						if (Motor::setRobotMotion(robotMotion) != 0) LOG(LOG_ERR, "Failed to set new robot motion %d.", robotMotion);
						break;
						
					case NETWORK_COMMUNICATION_PROTOCOL_COMMAND_GET_BATTERY_VOLTAGE:
						// Retrieve values
						Adc::getBatteryValues(&voltageMillivolts, &percentage);
						// Create command answer
						// First field is battery voltage in millivolts stored on unsigned 16-bit big-endian integer
						pointerWord = reinterpret_cast<unsigned short *>(buffer);
						*pointerWord = htons(static_cast<unsigned short>(voltageMillivolts));
						// Second field is battery percentage
						buffer[2] = static_cast<unsigned char>(percentage);
						// Send data
						if (send(clientSocket, buffer, 3, 0) != 3) LOG(LOG_ERR, "Failed to send answer to 'get battery voltage' command (%s).", strerror(errno));
						break;
						
					case NETWORK_COMMUNICATION_PROTOCOL_COMMAND_SET_LIGHT_ENABLED:
						// Retrieve enabling state
						if (recv(clientSocket, &byte, 1, MSG_WAITALL) != 1) goto Client_Disconnected;
						// Apply new light state
						if (Light::setEnabled(byte) != 0) LOG(LOG_ERR, "Failed to set new light state %d.", byte);
						break;
						
					case NETWORK_COMMUNICATION_PROTOCOL_COMMAND_POWER_OFF:
						LOG(LOG_INFO, "Received power off command, shutting system down.");
						system("poweroff");
						isErrorExitRequested = false;
						goto Exit;
						
					case NETWORK_COMMUNICATION_PROTOCOL_COMMAND_START_AI_PROGRAM:
						// Retrieve program number
						if (recv(clientSocket, &byte, 1, MSG_WAITALL) != 1) goto Client_Disconnected;
						// Make sure streaming camera is stopped, so AI program can access the camera
						system("/etc/init.d/S99camera stop");
						// Unlock waitForProgramExecutionRequest() in main thread
						pthread_mutex_lock(&_programExecutionWaitConditionMutex);
						_programToExecuteIndex = byte;
						pthread_cond_signal(&_programExecutionWaitCondition);
						pthread_mutex_unlock(&_programExecutionWaitConditionMutex);
						break;
						
					case NETWORK_COMMUNICATION_PROTOCOL_COMMAND_STOP_CURRENT_AI_PROGRAM:
						_isProgramRunning = false;
						break;
						
					case NETWORK_COMMUNICATION_PROTOCOL_COMMAND_SET_STREAMING_CAMERA_ENABLED:
						// Retrieve enabling state
						if (recv(clientSocket, &byte, 1, MSG_WAITALL) != 1) goto Client_Disconnected;
						// Change camera state
						system("/etc/init.d/S99camera stop"); // Always call stop, even when camera must be enabled, to make sure camera is disabled before enabling it
						if (byte != 0) system("/etc/init.d/S99camera start");
						break;
						
					default:
						LOG(LOG_ERR, "Unknown command code received : %d, ignoring it.", command);
						break;
				}
			}
			
		Client_Disconnected:
			// Stop robot to avoid it colliding with something
			Motor::setRobotMotion(Motor::ROBOT_MOTION_STOP); // TODO this implies that PC application must be connected while an AI program is running
			// Connection with client has been lost, wait for a new connection
			close(clientSocket);
			LOG(LOG_INFO, "Could not receive client command code, closing client connection (%s).", strerror(errno));
		}
		
	Exit:
		// Release resources
		if (clientSocket != -1) close(clientSocket);
		if (serverSocket != -1) close(serverSocket);
		
		// Exit program if a fatal error is detected
		if (isErrorExitRequested) exit(EXIT_FAILURE);
		
		// Make compiler happy
		return nullptr;
	}
	
	int initialize()
	{
		// Create server thread, the thread itself will handle network initialization
		pthread_t threadId;
		if (pthread_create(&threadId, nullptr, _serverThread, nullptr) != 0) return -1;
		
		return 0;
	}
	
	int waitForProgramExecutionRequest()
	{
		int programIndex;
		
		// Wait for the communication protocol command telling to begin program execution
		pthread_mutex_lock(&_programExecutionWaitConditionMutex);
		while (_programToExecuteIndex == -1) pthread_cond_wait(&_programExecutionWaitCondition, &_programExecutionWaitConditionMutex);
		
		// Cache program index and reset it, so this method will block the next time it will be called
		programIndex = _programToExecuteIndex;
		_programToExecuteIndex = -1;
		pthread_mutex_unlock(&_programExecutionWaitConditionMutex);
		
		// Tell isProgramRunning() method that program must run
		_isProgramRunning = true;
		
		return programIndex;
	}
	
	bool isProgramRunning()
	{
		return _isProgramRunning;
	}
}
