/** @file WebServer.cpp
 * See WebServer.hpp for description.
 * @author Adrien RICCIARDI
 */
#include <Adc.hpp>
#include <cstring>
#include <Light.hpp>
#include <Log.hpp>
#include <microhttpd.h>
#include <Motor.hpp>
#include <stdexcept>
#include <unordered_map>
#include <WebPageIndex.hpp>
#include <WebPageManualControl.hpp>
#include <WebPagePowerOff.hpp>
#include <WebServer.hpp>

namespace WebServer
{
	/** All available commands the user can send. */
	typedef enum
	{
		WEB_SERVER_COMMUNICATION_PROTOCOL_COMMAND_SET_MOTION,
		WEB_SERVER_COMMUNICATION_PROTOCOL_COMMAND_GET_BATTERY_VOLTAGE,
		WEB_SERVER_COMMUNICATION_PROTOCOL_COMMAND_GET_MOTOR_DUTY_CYCLE,
		WEB_SERVER_COMMUNICATION_PROTOCOL_COMMAND_SET_MOTOR_DUTY_CYCLE,
		WEB_SERVER_COMMUNICATION_PROTOCOL_COMMAND_SET_LIGHT_ENABLED,
		WEB_SERVER_COMMUNICATION_PROTOCOL_COMMAND_POWER_OFF,
		WEB_SERVER_COMMUNICATION_PROTOCOL_COMMAND_LIST_AVAILABLE_AI_PROGRAMS,
		WEB_SERVER_COMMUNICATION_PROTOCOL_COMMAND_START_AI_PROGRAM,
		WEB_SERVER_COMMUNICATION_PROTOCOL_COMMAND_STOP_CURRENT_AI_PROGRAM,
		WEB_SERVER_COMMUNICATION_PROTOCOL_COMMAND_SET_STREAMING_CAMERA_ENABLED,
		WEB_SERVER_COMMUNICATION_PROTOCOL_COMMANDS_COUNT
	} WebServerCommunicationProtocolCommand;

	/** The server handle. */
	static struct MHD_Daemon *_pointerServerHandle;

	/** Quickly find a page handler from its URL. */
	static std::unordered_map<std::string, WebPageBase *> _pagesMap;

	/** Store the ASCII response to send for the last executed command. */
	static char _stringLastCommandAnswer[64];

	/** Initialize the provided string with the HTML header of the page.
	 * @param referencePageContent On output, the string will be overwritten by the page header.
	 */
	static void _generatePageHeader(std::string &referencePageContent)
	{
		referencePageContent =
			"<!DOCTYPE html>\n"
			"	<html lang='en'>\n"
			"	<head>\n"
			"		<title>Cyclope Controller</title>\n"
			"		<link rel=\"icon\" href=\"data:,\">\n" // Disable the favicon.ico request from the browser
			"		<meta http-equiv=\"Cache-Control\" content=\"no-cache, no-store, must-revalidate\">\n" // These 3 meta tags should prevent the browser from caching the page
			"		<meta http-equiv=\"Pragma\" content=\"no-cache\">\n"
			"		<meta http-equiv=\"Expires\" content=\"0\">\n"
			"		<style>\n"
			"			.table-center\n"
			"			{\n"
			"				margin: auto;\n" // Center the table (needs the "width" property to be set)
			"				width: 40%;\n"
			"				border-collapse: collapse;\n" // Use a single row around the table
			"			}\n"
			"			.table-center th, .table-center td\n"
			"			{\n"
			"				border: 1px solid;\n"
			"			}\n"
			"			.text-center\n"
			"			{\n"
			"				text-align: center;\n"
			"			}\n"
			"		</style>\n"
			"	</head>\n"
			"	<body>\n"
			"		<script>\n"
			"			const CommunicationProtocol =\n"
			"			{\n"
			"				COMMUNICATION_PROTOCOL_COMMAND_SET_MOTION: '0',\n"
			"				COMMUNICATION_PROTOCOL_COMMAND_GET_BATTERY_VOLTAGE: '1',\n"
			"				COMMUNICATION_PROTOCOL_COMMAND_SET_LIGHT_ENABLED: '4'\n"
			"			}\n"
			"\n"
			"			const RobotMotion =\n"
			"			{\n"
			"				ROBOT_MOTION_STOP: '0',\n"
			"				ROBOT_MOTION_FORWARD: '1',\n"
			"				ROBOT_MOTION_BACKWARD: '2',\n"
			"				ROBOT_MOTION_FORWARD_LEFT: '3',\n"
			"				ROBOT_MOTION_FORWARD_RIGHT: '4',\n"
			"				ROBOT_MOTION_BACKWARD_LEFT: '5',\n"
			"				ROBOT_MOTION_BACKWARD_RIGHT: '6'\n"
			"			}\n"
			"\n"
			"			async function communicationProtocolSendCommand(stringCommand)\n"
			"			{\n"
							// Send the POST request
			"				response = await fetch(\"/api\", { method: \"POST\", body: stringCommand, keepalive: true });\n" // The "keepalive" flag tells the brower to continue the fetch calls even if the calling page is unloaded (this is useful to send commands to the robot in the "beforeunload" event handler)
			"				if (!response.ok) return \"error\";\n"
							// Wait for the server answer
			"				commandAnswer = await response.text();\n"
			"\n"
			"				return commandAnswer;\n"
			"			}\n"
			"		</script>\n";
	}

	/** Append the end of the HTML page to the provided string.
	 * @param referencePageContent On output, the HTML footer is appended to this string.
	 */
	static void _generatePageFooter(std::string &referencePageContent)
	{
		referencePageContent.append(
			"	</body>\n"
			"</html>");
	}

	/** Parse an API request sent by the client and execute the requested command.
	 * @param pointerStringCommand The command to execute.
	 * @return -1 if an error occurred,
	 * @return 0 on success.
	 * @note On output, fill the global _stringLastCommandAnswer string with the value that the user interface should display.
	 */
	static int _processApiCommand(const char *pointerStringCommand)
	{
		// The first character of the string is the command opcode
		switch (pointerStringCommand[0] - '0')
		{
			case WEB_SERVER_COMMUNICATION_PROTOCOL_COMMAND_SET_MOTION:
			{
				Motor::RobotMotion motion = static_cast<Motor::RobotMotion>(pointerStringCommand[1] - '0');
				if (Motor::setRobotMotion(motion) != 0)
				{
					LOG(LOG_ERR, "Failed to set the new robot motion %d.", motion);
					strcpy(_stringLastCommandAnswer, "ERROR");
					return -1;
				}
				else
				{
					// Prepare the answer string for the user interface
					const char *pointerString;
					switch (motion)
					{
						case Motor::ROBOT_MOTION_STOP:
							pointerString = "Stopped";
							break;

						case Motor::ROBOT_MOTION_FORWARD:
							pointerString = "Forward";
							break;

						case Motor::ROBOT_MOTION_BACKWARD:
							pointerString = "Backward";
							break;

						case Motor::ROBOT_MOTION_FORWARD_LEFT:
						case Motor::ROBOT_MOTION_BACKWARD_LEFT:
							pointerString = "Left";
							break;

						case Motor::ROBOT_MOTION_FORWARD_RIGHT:
						case Motor::ROBOT_MOTION_BACKWARD_RIGHT:
							pointerString = "Right";
							break;

						// Should never reach here
						default:
							pointerString = "INVALID DIRECTION";
							break;
					}
					strcpy(_stringLastCommandAnswer, pointerString);
				}
				break;
			}

			case WEB_SERVER_COMMUNICATION_PROTOCOL_COMMAND_GET_BATTERY_VOLTAGE:
			{
				// Execute the command
				int voltageMillivolts, percentage;
				Adc::getBatteryValues(&voltageMillivolts, &percentage);

				// Prepare the answer string for the user interface
				snprintf(_stringLastCommandAnswer, sizeof(_stringLastCommandAnswer), "%d%% (%.2f V)", percentage, voltageMillivolts / 1000.f);
				break;
			}

			case WEB_SERVER_COMMUNICATION_PROTOCOL_COMMAND_SET_LIGHT_ENABLED:
			{
				// The second character is the light state
				bool isEnabled;
				if (pointerStringCommand[1] == '0') isEnabled = false;
				else isEnabled = true;

				// Execute the command
				if (Light::setEnabled(isEnabled) != 0)
				{
					LOG(LOG_ERR, "Failed to set the new light state %d.", isEnabled);
					strcpy(_stringLastCommandAnswer, "ERROR");
					return -1;
				}
				else
				{
					const char *pointerString;
					if (isEnabled) pointerString = "Enabled";
					else pointerString = "Disabled";
					strcpy(_stringLastCommandAnswer, pointerString);
				}
				break;
			}

			default:
				LOG(LOG_ERR, "Unknown command '%c'.", pointerStringCommand[0]);
				return -1;
		}

		return 0;
	}

	/** Called every time a clients sends a request to the web server.
	 * @param pointerCustomData Custom data provided to MHD_start_daemon().
	 * @param pointerConnection The connection handle used to build the response.
	 * @param pointerStringUrl The URL requested by the client.
	 * @param pointerStringMethod The HTTP method (GET, POST...) of the request.
	 * @param pointerStringVersion HTTP protocol version.
	 * @param pointerStringUploadData The data to upload to POST request.
	 * @param pointerUploadDataSize How many bytes of data to upload to a POST request.
	 * @param pointerPersistentConnectionCustomData A custom data pointer that won't change across callback calls (for the same connection).
	 * @return MHD_NO to close the connection,
	 * @return MHD_YES to continue servicing the client request.
	 */
	static enum MHD_Result _accessHandlerCallback(void __attribute__((unused)) *pointerCustomData, struct MHD_Connection *pointerConnection, const char __attribute__((unused)) *pointerStringUrl, const char *pointerStringMethod, const char __attribute__((unused)) *pointerStringVersion, const char *pointerStringUploadData, size_t *pointerUploadDataSize, void __attribute__((unused)) **pointerPersistentConnectionCustomData)
	{
		// Allow only GET and POST requests
		// Check for a GET request
		bool isGetMethod;
		if (strcmp(pointerStringMethod, "GET") == 0) isGetMethod = true;
		else isGetMethod = false;
		// Check for a POST request
		bool isPostMethod;
		if (strcmp(pointerStringMethod, "POST") == 0) isPostMethod = true;
		else isPostMethod = false;

		// Discard other request methods
		if (!isGetMethod && !isPostMethod) return MHD_NO;

		// Callback is called when a new connection header is received, and no response must be sent at this time
		if (*pointerPersistentConnectionCustomData == NULL) // This value is always NULL for a new connection
		{
			*pointerPersistentConnectionCustomData = reinterpret_cast<void *>(1); // Set the value to something else to tell that connection first step has been processed
			return MHD_YES; // Continue servicing request
		}

		// Serve requested pages
		MHD_Result returnValue;
		struct MHD_Response *pointerResponse;
		if (isGetMethod)
		{
			// Is the page existing ?
			WebPageBase *pointerPage;
			try
			{
				pointerPage = _pagesMap.at(pointerStringUrl);
			}
			catch (const std::out_of_range &referenceException)
			{
				LOG(LOG_ERR, "The page with URL \"%s\" does not exist.", pointerStringUrl);
				return MHD_NO;
			}

			// Generate the page
			std::string stringPage, stringPageContent;
			_generatePageHeader(stringPage);
			if (pointerPage->generateContent(stringPageContent) != 0)
			{
				LOG(LOG_ERR, "Failed to generate the page content for the URL \"%s\".", pointerStringUrl);
				return MHD_NO;
			}
			stringPage.append(stringPageContent);
			_generatePageFooter(stringPage);

			// Generate the HTTP answer containing the page
			pointerResponse = MHD_create_response_from_buffer(stringPage.size(), const_cast<char *>(stringPage.c_str()), MHD_RESPMEM_MUST_COPY);
			if (pointerResponse == NULL)
			{
				LOG(LOG_ERR, "Failed to create the response buffer for the page with URL \"%s\".", pointerStringUrl);
				return MHD_NO;
			}

			// Send the response
			returnValue = MHD_queue_response(pointerConnection, MHD_HTTP_OK, pointerResponse);
			MHD_destroy_response(pointerResponse);
		}
		// Execute the sent commands
		else if (isPostMethod)
		{
			// Process the POST data
			if (*pointerUploadDataSize > 0)
			{
				// Execute the requested command
				if (_processApiCommand(pointerStringUploadData) != 0)
				{
					LOG(LOG_ERR, "Failed to execute the last API request.");
					return MHD_NO;
				}

				// Tell that all POST payload bytes have been processed
				*pointerUploadDataSize = 0;
				returnValue = MHD_YES;
			}
			// All the data has been processed, send the response
			else
			{
				// Send the response
				pointerResponse = MHD_create_response_from_buffer(strnlen(_stringLastCommandAnswer, sizeof(_stringLastCommandAnswer)), _stringLastCommandAnswer, MHD_RESPMEM_MUST_COPY);
				if (pointerResponse == NULL)
				{
					LOG(LOG_ERR, "Failed to create the response buffer for the last API request.");
					return MHD_NO;
				}

				// Send the response
				returnValue = MHD_queue_response(pointerConnection, MHD_HTTP_OK, pointerResponse);
				MHD_destroy_response(pointerResponse);
			}
		}

		return returnValue;
	}

	int initialize()
	{
		// Start the web server daemon and configure it to accept connections from any IP
		_pointerServerHandle = MHD_start_daemon(MHD_USE_THREAD_PER_CONNECTION, 80, NULL, NULL, _accessHandlerCallback, NULL, MHD_OPTION_END);
		if (_pointerServerHandle == NULL)
		{
			LOG(LOG_ERR, "Error : failed to start the web server.");
			return -1;
		}

		// Create all pages in alphabetical order
		_pagesMap.insert({webPageIndex.getBaseUrl(), &webPageIndex});
		_pagesMap.insert({webPageManualControl.getBaseUrl(), &webPageManualControl});
		_pagesMap.insert({webPagePowerOff.getBaseUrl(), &webPagePowerOff});

		return 0;
	}
}
