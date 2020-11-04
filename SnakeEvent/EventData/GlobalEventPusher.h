// ☕ Привет
#pragma once

#include "Event.h"

namespace SnakeEvent
{
	namespace EventData
	{
		class EventManager;

		void SetEventManager(EventManager* manager);

		void PushEvent(Event* event);
	}
}