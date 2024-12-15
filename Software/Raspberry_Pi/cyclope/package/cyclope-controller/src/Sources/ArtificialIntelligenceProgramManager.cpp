/** @file ArtificialIntelligenceProgramManager.cpp
 * See ArtificialIntelligenceProgramManager.hpp for description.
 * @author Adrien RICCIARDI
 */
#include <ArtificialIntelligenceProgramManager.hpp>
#include <Log.hpp>
#include <pthread.h>

// TEST
#include <unistd.h>

// TEST
namespace
{
	class Program1 : public ArtificialIntelligenceProgramBase
	{
		public :
			Program1() : ArtificialIntelligenceProgramBase{"Program number 1"} {}
			virtual void run()
			{
				int i = 0;
				while (!_isExitRequested)
				{
					LOG(LOG_INFO, "prog 1 exec %d", i++);
					usleep(500000);
				}
			}
	};

	class Program2 : public ArtificialIntelligenceProgramBase
	{
		public:
			Program2() : ArtificialIntelligenceProgramBase{"The second program"} {}
			virtual void run()
			{
				int i = 0;
				while (!_isExitRequested)
				{
					LOG(LOG_INFO, "second program exec %d", i++);
					usleep(250000);
				}
			}
	};

	class Program3 : public ArtificialIntelligenceProgramBase
	{
		public:
			Program3() : ArtificialIntelligenceProgramBase{"Le troisième"} {}
			virtual void run()
			{
				int i = 0;
				while (!_isExitRequested)
				{
					LOG(LOG_INFO, "le prog num 3 exec %d", i++);
					usleep(1000000);
				}
			}
	};
}

namespace ArtificialIntelligenceProgramManager
{
	// The statically allocated instances of the programs
	Program1 _p1;
	Program2 _p2;
	Program3 _p3;

	/** List all available programs. */
	static ArtificialIntelligenceProgramBase *_pointerArtificialIntelligencePrograms[] =
	{
		&_p1,
		&_p2,
		&_p3
	};
	/** The amount of available programs. */
	static constexpr unsigned int _pointerArtificialIntelligenceProgramsCount = sizeof(_pointerArtificialIntelligencePrograms) / sizeof(_pointerArtificialIntelligencePrograms[0]);

	/** The program that is currently executed. */
	static ArtificialIntelligenceProgramBase *_pointerCurrentlyRunProgram{nullptr};

	/** The wait condition telling when a program execution can begin. */
	static pthread_cond_t _programExecutionWaitCondition = PTHREAD_COND_INITIALIZER;
	/** The mutex used to synchronize the program execution wait condition. */
	static pthread_mutex_t _programExecutionWaitConditionMutex = PTHREAD_MUTEX_INITIALIZER;
	/** The program execution wait condition variable, it holds the program index to execute or -1 if no program must be executed. */
	static volatile int _programToExecuteIndex = -1;

	ArtificialIntelligenceProgramBase *getProgram(unsigned int index)
	{
		// Make sure that the index is valid
		if (index >= _pointerArtificialIntelligenceProgramsCount)
		{
			LOG(LOG_ERR, "Requested an invalid program with index %u.", index);
			return nullptr;
		}
		return _pointerArtificialIntelligencePrograms[index];
	}

	unsigned int getProgramsCount()
	{
		return _pointerArtificialIntelligenceProgramsCount;
	}

	ArtificialIntelligenceProgramBase *waitForProgramExecutionRequest()
	{
		// Wait for the web server telling to begin program execution
		pthread_mutex_lock(&_programExecutionWaitConditionMutex);
		while (_pointerCurrentlyRunProgram == nullptr) pthread_cond_wait(&_programExecutionWaitCondition, &_programExecutionWaitConditionMutex);
		pthread_mutex_unlock(&_programExecutionWaitConditionMutex);

		return _pointerCurrentlyRunProgram;
	}

	int startProgramExecution(unsigned int programIndex)
	{
		// Retrieve the requested program
		ArtificialIntelligenceProgramBase *pointerProgram = getProgram(programIndex);
		if (pointerProgram == nullptr) return -1;

		// Unlock waitForProgramExecutionRequest() in the main thread
		pthread_mutex_lock(&_programExecutionWaitConditionMutex);
		_pointerCurrentlyRunProgram = pointerProgram;
		pthread_cond_signal(&_programExecutionWaitCondition);
		pthread_mutex_unlock(&_programExecutionWaitConditionMutex);

		return 0;
	}

	void stopRunningProgram()
	{
		if (_pointerCurrentlyRunProgram != nullptr) _pointerCurrentlyRunProgram->setExitRequest(true);
		_pointerCurrentlyRunProgram = nullptr;
	}
}
