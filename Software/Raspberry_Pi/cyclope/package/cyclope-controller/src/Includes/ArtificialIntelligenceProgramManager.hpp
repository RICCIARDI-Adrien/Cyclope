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
}

#endif
