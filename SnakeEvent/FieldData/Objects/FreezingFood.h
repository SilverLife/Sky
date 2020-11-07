// ☕ Привет
#pragma once

#include "../../../Sky/Shared/EventGameEngine/FieldData/FieldObjectWithPos.h"
#include "../../../Sky/Shared/EventGameEngine/EventData/GlobalEventPusher.h"

#include "Player.h"

using namespace EventGameEngine::FieldData;

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