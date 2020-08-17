/** @file Network.cpp
 * See Network.hpp for description.
 * @author Adrien RICCIARDI
 */
#include <Log.hpp>
#include <Network.hpp>
#include <pthread.h>

namespace Network
{
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
}
