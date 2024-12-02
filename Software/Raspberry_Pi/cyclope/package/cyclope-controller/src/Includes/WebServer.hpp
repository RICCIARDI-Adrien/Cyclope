/** @file WebServer.hpp
 * Allow to control the robot through a web interface.
 * @author Adrien RICCIARDI
 */
#ifndef HPP_WEB_SERVER_HPP
#define HPP_WEB_SERVER_HPP

namespace WebServer
{
	/** Spawn the server and make it ready for processing requests.
	 * @return -1 if an error occurred,
	 * @return 0 on success.
	 */
	int initialize();
}

#endif
