/** @file ArtificialIntelligenceProgramManager.hpp
 * Gather all available programs and abstract their usage.
 * @author Adrien RICCIARDI
 */
#ifndef HPP_ARTIFICIAL_INTELLIGENCE_PROGRAM_MANAGER_HPP
#define HPP_ARTIFICIAL_INTELLIGENCE_PROGRAM_MANAGER_HPP

#include <ArtificialIntelligenceProgramBase.hpp>

namespace ArtificialIntelligenceProgramManager
{
	/** Get a pointer on a specific program. This function is mostly used to list the available programs.
	 * @param index The index of the program to retrieve.
	 * @return nullptr if the index is invalid,
	 * @return The requested program if the index is valid.
	 */
	ArtificialIntelligenceProgramBase *getProgram(unsigned int index);

	/** Retrieve the amount of available programs.
	 * @return How many programs can be retrieved with the getProgram() method.
	 */
	unsigned int getProgramsCount();

	/** Block the calling thread until receiving a command to execute a specific program.
	 * @return A pointer on the program to execute.
	 */
	ArtificialIntelligenceProgramBase *waitForProgramExecutionRequest();

	/** Ask the main thread to start executing the specified program.
	 * @param programIndex The program to run.
	 * @return -1 if an error occurred,
	 * @return 0 on success.
	 */
	int startProgramExecution(unsigned int programIndex);

	/** Ask the program returned by waitForProgramExecutionRequest() to stop execution. */
	void stopRunningProgram();
}

#endif
