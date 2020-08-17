/** @file Network.cpp
 * See Network.hpp for description.
 * @author Adrien RICCIARDI
 */
#include <Log.hpp>
#include <Network.hpp>
#include <pthread.h>

namespace Network
{
	/** The wait condition telling when a program execution can begin. */
	static pthread_cond_t _programExecutionWaitCondition = PTHREAD_COND_INITIALIZER;
	/** The mutex used to synchronize the program execution wait condition. */
	static pthread_mutex_t _programExecutionWaitConditionMutex = PTHREAD_MUTEX_INITIALIZER;
	/** The program execution wait condition variable, it holds the program index to execute or -1 if no program must be executed. */
	static int _programToExecuteIndex = -1;
	
	/** Network server thread. */
	static void *_serverThread(void *)
	{
		LOG(LOG_INFO, "Network thread started, initializing server...");
		
		// Make compiler happy
		return nullptr;
	}
	
	int initialize()
	{
		// Create server thread, the thread itself will handle network initialization
		pthread_t threadId;
		if (pthread_create(&threadId, nullptr, _serverThread, nullptr) != 0) return -1;
		
		return 0;
	}
	
	int waitForProgramExecutionRequest()
	{
		// Wait for the communication protocol command telling to begin program execution
		pthread_mutex_lock(&_programExecutionWaitConditionMutex);
		while (_programToExecuteIndex == -1) pthread_cond_wait(&_programExecutionWaitCondition, &_programExecutionWaitConditionMutex);
		pthread_mutex_unlock(&_programExecutionWaitConditionMutex);
		
		return _programToExecuteIndex;
	}
}
