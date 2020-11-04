// ☕ Привет
#pragma once

#include "../FieldObjectWithPos.h"
#include "../../EventData/GlobalEventPusher.h"

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
				EventData::PushEvent(new EventData::EventMove(_pos, _pos + kDeltas[delta_num]));
			}

			void OnEvent(EventData::Event* event) override
			{
				if (event->_type == EventData::EventType::FreezeEnemies)
				{
					_freeze_counter = 50;
				}
				else if (event->_type == EventData::EventType::EnemySpeedIncrease)
				{
					_speed /= 2;
				}
			}
		};
	}
}