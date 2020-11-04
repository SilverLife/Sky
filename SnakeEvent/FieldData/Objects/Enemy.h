// ☕ Привет
#pragma once

#include "../FieldObject.h"
#include "../../EventData/GlobalEventPusher.h"

namespace SnakeEvent
{
	namespace FieldData
	{
		class Enemy : public FieldObject
		{
			Point _pos;

			int _freeze_counter = 0;
		public:
			Enemy(Point pos)
				: FieldObject('@')
				, _pos(pos)
			{}

			void OnMove(Point prev_pos, Point new_pos) override
			{
				_pos = new_pos;
			}

			void OnTick(int tick_num) override
			{
				const auto r = std::rand() % 100;

				if (r > 1)
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
			}
		};
	}
}