// ☕ Привет
#pragma once

#include "../../../Sky/Shared/EventGameEngine/FieldData/FieldObjectWithPos.h"
#include "../../../Sky/Shared/EventGameEngine/EventData/GlobalEventPusher.h"
#include "../../EventData/EventType.h"

using namespace EventGameEngine::FieldData;

namespace SnakeEvent
{
	namespace FieldData
	{
		class Enemy : public FieldObjectWithPos
		{
			int _freeze_counter = 0;
			int _speed = 100;
		public:
			Enemy(Point pos)
				: FieldObjectWithPos(pos, '@', Shared::ConsoleHelper::Color::LightRed)
			{}

			void OnTick(int tick_num) override
			{
				if (tick_num % _speed != 0)
				{
					return;
				}

				if (_freeze_counter > 0)
				{
					--_freeze_counter;
					return;
				}
				
				const auto delta_num = std::rand() % std::size(kDeltas);
				EventData::PushEvent(new EventData::EventMoveObject(_pos, _pos + kDeltas[delta_num]));
			}

			void OnEvent(EventData::Event* event) override
			{
				if (event->_type == CustomEventType::FreezeEnemies)
				{
					_freeze_counter = 50;
				}
				else if (event->_type == CustomEventType::EnemySpeedIncrease)
				{
					_speed /= 2;
				}
			}
		};
	}
}