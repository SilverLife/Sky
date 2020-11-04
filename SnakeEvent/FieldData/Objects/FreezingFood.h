// ☕ Привет
#pragma once

#include "../FieldObject.h"
#include "../../EventData/GlobalEventPusher.h"
#include "Player.h"

namespace SnakeEvent
{
	namespace FieldData
	{
		class FreezingFood : public FieldObject
		{
		public:
			FreezingFood()
				: FieldObject('F')
			{}

			int OnPassiveIntersect(FieldObject* intersected_object) override
			{ 
				if (dynamic_cast<Player*>(intersected_object) != nullptr)
				{
					EventData::PushEvent(new EventData::Event(EventData::EventType::FreezeEnemies));
					return IntersectResult::IntResIsDead | IntersectResult::IntResIsMove;
				}
				return 0; 
			}
		};
	}
}