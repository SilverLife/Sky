// ☕ Привет
#pragma once

#include "../FieldObject.h"
#include "Player.h"

namespace SnakeEvent
{
	namespace FieldData
	{
		class Win : public FieldObject
		{
		public:
			Win()
				: FieldObject('W')
			{}

			virtual int OnPassiveIntersect(FieldObject* intersected_object)
			{
				if (dynamic_cast<Player*>(intersected_object) != nullptr)
				{
					EventData::PushEvent(new EventData::Event(EventData::EventType::Win));
					return IntersectResult::IntResIsDead;
				}
				return 0;
			}
		};
	}
}