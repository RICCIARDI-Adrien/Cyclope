/** @file WebServer.cpp
 * See WebServer.hpp for description.
 * @author Adrien RICCIARDI
 */
#include <cstring>
#include <Log.hpp>
#include <microhttpd.h>
#include <stdexcept>
#include <unordered_map>
#include <WebPageIndex.hpp>
#include <WebPageManualControl.hpp>
#include <WebServer.hpp>

namespace WebServer
{
	/** The server handle. */
	static struct MHD_Daemon *_pointerServerHandle;

	/** Quickly find a page handler from its URL. */
	static std::unordered_map<std::string, WebPageBase *> _pagesMap;

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
			"		<style>\n"
			"			.text-center\n"
			"			{\n"
			"				text-align: center;\n"
			"			}\n"
			"		</style>\n"
			"	</head>\n"
			"	<body>\n";
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
	 */
	static int _processApiCommand(const char *pointerStringCommand)
	{
		// TEST
		LOG(LOG_ERR, "command=%s", pointerStringCommand);

		return 0;
	}

	/** Retrieve the last executed API command result.
	 * @param referenceStringResponse On output, contain the response to provide to the POST request.
	 * @return -1 if an error occurred,
	 * @return 0 on success.
	 */
	static int _getApiCommandResponse(std::string &referenceStringResponse)
	{
		// TEST
		referenceStringResponse = "test";

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
				// Get the command execution result
				std::string stringResponse;
				if (_getApiCommandResponse(stringResponse) != 0)
				{
					LOG(LOG_ERR, "Failed to retrieve the last API request response.");
					return MHD_NO;
				}

				// Send the response
				pointerResponse = MHD_create_response_from_buffer(stringResponse.size(), const_cast<char *>(stringResponse.c_str()), MHD_RESPMEM_MUST_COPY);
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

		return 0;
	}
}
