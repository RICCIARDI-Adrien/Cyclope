/** @file ArtificialIntelligenceProgramBase.hpp
 * The base class from which all AI programs are derived.
 * @author Adrien RICCIARDI
 */
#ifndef HPP_ARTIFICIAL_INTELLIGENCE_PROGRAM_BASE_HPP
#define HPP_ARTIFICIAL_INTELLIGENCE_PROGRAM_BASE_HPP

class ArtificialIntelligenceProgramBase
{
	public:
		/** Create the program.
		 * @param pointerStringDescriptiveName A human-friendly description name for the program. The name string must be statically allocated, or at least valid for the whole program life.
		 */
		ArtificialIntelligenceProgramBase(const char *pointerStringDescriptiveName) : _pointerStringDescriptiveName{pointerStringDescriptiveName} {};

		/** Retrieve the name of the program.
		 * @return The program name.
		 */
		inline const char *getDescriptiveName()
		{
			return _pointerStringDescriptiveName;
		}

		/** Ask the program to exit at its next loop iteration.
		 * @param isExitRequested Set to true to make the program exit, set to false to reset the flag.
		 */
		void setExitRequest(bool isExitRequested)
		{
			_isExitRequested = isExitRequested;
		}

		/** The AI program code.
		 * @note This method must exit when the exit flag is set.
		 */
		virtual void run() = 0;

	protected:
		/** The program name. */
		const char *_pointerStringDescriptiveName;

		/** When set to true, the run() method must exit as soon as possible. */
		volatile bool _isExitRequested = false;
};

#endif
