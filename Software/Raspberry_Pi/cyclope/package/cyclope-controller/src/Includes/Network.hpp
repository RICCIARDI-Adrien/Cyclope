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
	
	/** Tell whether currently running AI program must continue execution or quit.
	 * @return false if AI program execution must terminate,
	 * @return true if AI program must continue execution.
	 */
	bool isProgramRunning();
}

#endif
