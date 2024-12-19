/** @file WebServer.hpp
 * Allow to control the robot through a web interface.
 * @author Adrien RICCIARDI
 */
#ifndef HPP_WEB_SERVER_HPP
#define HPP_WEB_SERVER_HPP

namespace WebServer
{
	/** The watchdog will fire if it is not cleared for this amount of time. */
	constexpr unsigned int WATCHDOG_TIMEOUT_SECONDS = 2;
	/** The watchdog is cleared at this rate, granting that it will never fire. */
	constexpr unsigned int WATCHDOG_CLEAR_PERIOD = WATCHDOG_TIMEOUT_SECONDS / 2;
	
	/** Spawn the server and make it ready for processing requests.
	 * @return -1 if an error occurred,
	 * @return 0 on success.
	 */
	int initialize();
}

#endif
