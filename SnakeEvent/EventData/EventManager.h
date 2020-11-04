// ☕ Привет
#pragma once

#include "Event.h"

#include "GlobalEventPusher.h"
#include <queue>

namespace SnakeEvent
{
	namespace EventData
	{
		class EventManager
		{
			std::queue<Event*> _events;
		public:
			EventManager()
			{
				SetEventManager(this);
			}

			bool HasEvents() const { return !_events.empty(); }

			int EventsCount() const { return _events.size(); }

			Event* PopEvent() 
			{
				const auto event = _events.front();
				_events.pop();
				return event;
			}

			void PushEvent(Event* event)
			{
				_events.push(event);
			}
		};
	}
}