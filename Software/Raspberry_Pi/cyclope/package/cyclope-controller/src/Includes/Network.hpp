/** @file Network.hpp
 * Handle communications with PC application.
 * @author Adrien RICCIARDI
 */
#ifndef HPP_NETWORK_HPP
#define HPP_NETWORK_HPP

namespace Network
{
	/** Create a dedicated thread handling communication protocol.
	 * @return -1 if an error occurred,
	 * @return 0 on success.
	 */
	int initialize();
	
	/** Block calling thread until PC application commands to execute a specific program.
	 * @return The program to execute index.
	 */
	int waitForProgramExecutionRequest();
}

#endif
