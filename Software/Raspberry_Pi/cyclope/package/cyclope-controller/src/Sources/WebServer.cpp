/** @file WebServer.cpp
 * See WebServer.hpp for description.
 * @author Adrien RICCIARDI
 */
#include <Log.hpp>
#include <microhttpd.h>
#include <WebServer.hpp>

namespace WebServer
{
	/** The server handle. */
	static struct MHD_Daemon *_pointerServerHandle;

	/** Called every time a clients sends a request to the web server.
	 * @param pointerCustomData Custom data provided to MHD_start_daemon().
	 * @param pointerConnection The connection handle used to build the response.
	 * @param pointerStringURL The URL requested by the client.
	 * @param pointerStringMethod The HTTP method (GET, POST...) used to send the query.
	 * @param pointerStringVersion HTTP protocol version.
	 * @param pointerStringUploadData The data to upload to POST request.
	 * @param pointerUploadDataSize How many bytes of data to upload to a POST request.
	 * @param pointerPersistentConnectionCustomData A custom data pointer that won't change across callback calls (for the same connection).
	 * @return MHD_NO to close the connection,
	 * @return MHD_YES to continue servicing the client request.
	 */
	static enum MHD_Result _accessHandlerCallback(void __attribute__((unused)) *pointerCustomData, struct MHD_Connection *pointerConnection, const char __attribute__((unused)) *pointerStringURL, const char *pointerStringMethod, const char __attribute__((unused)) *pointerStringVersion, const char *pointerStringUploadData, size_t *pointerUploadDataSize, void __attribute__((unused)) **pointerPersistentConnectionCustomData)
	{
		// TODO
		LOG(LOG_ERR, "CALLBACK");

		return MHD_NO;
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

		return 0;
	}
}
