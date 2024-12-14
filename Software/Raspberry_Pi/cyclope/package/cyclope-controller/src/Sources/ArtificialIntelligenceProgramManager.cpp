/** @file ArtificialIntelligenceProgramManager.cpp
 * See ArtificialIntelligenceProgramManager.hpp for description.
 * @author Adrien RICCIARDI
 */
#include <ArtificialIntelligenceProgramManager.hpp>
#include <Log.hpp>

// TEST
namespace
{
	class Program1 : public ArtificialIntelligenceProgramBase
	{
		public :
			Program1() : ArtificialIntelligenceProgramBase{"Program number 1"} {}
			virtual void run() {}
	};

	class Program2 : public ArtificialIntelligenceProgramBase
	{
		public:
			Program2() : ArtificialIntelligenceProgramBase{"The second program"} {}
			virtual void run() {}
	};

	class Program3 : public ArtificialIntelligenceProgramBase
	{
		public:
			Program3() : ArtificialIntelligenceProgramBase{"Le troisième"} {}
			virtual void run() {}
	};
}

namespace ArtificialIntelligenceProgramManager
{
	// The statically allocated instances of the programs
	Program1 _p1;
	Program2 _p2;
	Program3 _p3;

	/** List all available programs. */
	ArtificialIntelligenceProgramBase *_artificialIntelligencePrograms[] =
	{
		&_p1,
		&_p2,
		&_p3
	};
	/** The amount of available programs. */
	constexpr unsigned int _artificialIntelligenceProgramsCount = sizeof(_artificialIntelligencePrograms) / sizeof(_artificialIntelligencePrograms[0]);

	ArtificialIntelligenceProgramBase *getProgram(unsigned int index)
	{
		// Make sure that the index is valid
		if (index >= _artificialIntelligenceProgramsCount)
		{
			LOG(LOG_ERR, "Requested an invalid program with index %u.", index);
			return nullptr;
		}
		return _artificialIntelligencePrograms[index];
	}

	unsigned int getProgramsCount()
	{
		return _artificialIntelligenceProgramsCount;
	}
}
