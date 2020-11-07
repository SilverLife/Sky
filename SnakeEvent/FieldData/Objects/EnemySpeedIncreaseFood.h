// ☕ Привет
#pragma once

#include "../../../Sky/Shared/EventGameEngine/FieldData/FieldObjectWithPos.h"
#include "../../../Sky/Shared/EventGameEngine/EventData/GlobalEventPusher.h"

#include "Enemy.h"
#include "Player.h"

using namespace EventGameEngine::FieldData;

namespace SnakeEvent
{
	namespace FieldData
	{
		class EnemySpeedIncreaseFood : public FieldObject
		{
		public:
			EnemySpeedIncreaseFood()
				: FieldObject('I')
			{}

			int OnPassiveIntersect(FieldObject* intersected_object) override
			{
				if (dynamic_cast<Enemy*>(intersected_object) != nullptr)
				{
					EventData::PushEvent(new EventData::Event(CustomEventType::EnemySpeedIncrease));
					return IntersectResult::IntResIsDead | IntersectResult::IntResIsMove;
				}
				if (dynamic_cast<Player*>(intersected_object) != nullptr)
				{
					return IntersectResult::IntResIsDead | IntersectResult::IntResIsMove;
				}

				return 0;
			}
		};
	}
}