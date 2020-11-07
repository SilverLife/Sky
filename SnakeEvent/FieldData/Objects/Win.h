// ☕ Привет
#pragma once

#include "../../../Sky/Shared/EventGameEngine/FieldData/FieldObjectWithPos.h"
#include "Player.h"

using namespace EventGameEngine::FieldData;

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