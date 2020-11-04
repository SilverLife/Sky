// ☕ Привет

#include "GlobalEventPusher.h"
#include "EventManager.h"

namespace SnakeEvent
{
	namespace EventData
	{
		static EventManager* _manager;

		void SetEventManager(EventManager* manager)
		{
			_manager = manager;
		}

		void PushEvent(Event* event)
		{
			_manager->PushEvent(event);
		}
	}
}