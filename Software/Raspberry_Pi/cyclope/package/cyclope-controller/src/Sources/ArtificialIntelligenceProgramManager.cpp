/** @file ArtificialIntelligenceProgramManager.cpp
 * See ArtificialIntelligenceProgramManager.hpp for description.
 * @author Adrien RICCIARDI
 */
#include <ArtificialIntelligenceProgramManager.hpp>
#include <ArtificialIntelligenceProgramWanderWithNoGoal.hpp>
#include <Log.hpp>
#include <pthread.h>

namespace ArtificialIntelligenceProgramManager
{
	// The statically allocated instances of the programs
	/** Move into the room, simulating a sort of will. */
	static ArtificialIntelligenceProgramWanderWithNoGoal _artificialIntelligenceProgramWanderWithNoGoal{"Wander with no goal"};

	/** List all available programs. */
	static ArtificialIntelligenceProgramBase *_pointerArtificialIntelligencePrograms[] =
	{
		&_artificialIntelligenceProgramWanderWithNoGoal
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
