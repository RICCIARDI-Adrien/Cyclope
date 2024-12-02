/** @file WebServer.cpp
 * See WebServer.hpp for description.
 * @author Adrien RICCIARDI
 */
#include <Log.hpp>
#include <microhttpd.h>
#include <stdexcept>
#include <unordered_map>
#include <WebPageIndex.hpp>
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
			"<!DOCTYPE html>"
			"	<html lang='en'>"
			"	<head>"
			"		<title>Cyclope Controller</title>"
			"	</head>"
			"	<body>";
	}

	/** Append the end of the HTML page to the provided string.
	 * @param referencePageContent On output, the HTML footer is appended to this string.
	 */
	static void _generatePageFooter(std::string &referencePageContent)
	{
		referencePageContent.append(
			"	</body>"
			"</html>");
	}

	/** Called every time a clients sends a request to the web server.
	 * @param pointerCustomData Custom data provided to MHD_start_daemon().
	 * @param pointerConnection The connection handle used to build the response.
	 * @param pointerStringURL The URL requested by the client.
	 * @param pointerStringMethod The HTTP method (GET, POST...) of the request.
	 * @param pointerStringVersion HTTP protocol version.
	 * @param pointerStringUploadData The data to upload to POST request.
	 * @param pointerUploadDataSize How many bytes of data to upload to a POST request.
	 * @param pointerPersistentConnectionCustomData A custom data pointer that won't change across callback calls (for the same connection).
	 * @return MHD_NO to close the connection,
	 * @return MHD_YES to continue servicing the client request.
	 */
	static enum MHD_Result _accessHandlerCallback(void __attribute__((unused)) *pointerCustomData, struct MHD_Connection *pointerConnection, const char __attribute__((unused)) *pointerStringURL, const char *pointerStringMethod, const char __attribute__((unused)) *pointerStringVersion, const char *pointerStringUploadData, size_t *pointerUploadDataSize, void __attribute__((unused)) **pointerPersistentConnectionCustomData)
	{
		// Callback is called when a new connection header is received, and no response must be sent at this time
		if (*pointerPersistentConnectionCustomData == NULL) // This value is always NULL for a new connection
		{
			*pointerPersistentConnectionCustomData = reinterpret_cast<void *>(1); // Set the value to something else to tell that connection first step has been processed
			return MHD_YES; // Continue servicing request
		}

		// Is the page existing ?
		WebPageBase *pointerPage;
		try
		{
			pointerPage = _pagesMap.at(pointerStringURL);
		}
		catch (const std::out_of_range &referenceException)
		{
			LOG(LOG_ERR, "The page with URL \"%s\" does not exist.", pointerStringURL);
			return MHD_NO;
		}

		// Generate the page
		std::string stringPage, stringPageContent;
		_generatePageHeader(stringPage);
		if (pointerPage->generateContent(stringPageContent) != 0)
		{
			LOG(LOG_ERR, "Failed to generate the page content for the URL \"%s\".", pointerStringURL);
			return MHD_NO;
		}
		stringPage.append(stringPageContent);
		_generatePageFooter(stringPage);

		// Generate the HTTP answer containing the page
		struct MHD_Response *pointerResponse = MHD_create_response_from_buffer(stringPage.size(), const_cast<char *>(stringPage.c_str()), MHD_RESPMEM_MUST_COPY);
		if (pointerResponse == NULL)
		{
			LOG(LOG_ERR, "Failed to create the response buffer for the page with URL \"%s\".", pointerStringURL);
			return MHD_NO;
		}

		// Send the response
		MHD_Result returnValue = MHD_queue_response(pointerConnection, MHD_HTTP_OK, pointerResponse);
		MHD_destroy_response(pointerResponse);

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

		// Create all pages
		_pagesMap.insert({"/", new WebPageIndex()});

		return 0;
	}
}
