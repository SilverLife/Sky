// ☕ Привет
#pragma once

#include "../../../Sky/Shared/EventGameEngine/FieldData/FieldObjectWithPos.h"
#include "../../../Sky/Shared/EventGameEngine/EventData/GlobalEventPusher.h"

using namespace EventGameEngine::FieldData;

namespace SnakeEvent
{
	namespace FieldData
	{
		class CannonBullet : public FieldObjectWithPos
		{
			Point _start_pos;
			Point _delta;
			int _speed;
		public:
			CannonBullet(Point start_pos, Point delta, int speed = 30)
				: FieldObjectWithPos(start_pos, '*', Shared::ConsoleHelper::Color::LightCyan)
				, _start_pos(start_pos)
				, _delta(delta)
				, _speed(speed)
			{}

			void OnRemove() override
			{
				_pos = _start_pos;
				EventData::PushEvent(new EventData::EventAddObject(_pos, this));
			}

			void OnPlaceToFieldFailure(Point pos) override
			{
				OnRemove();
			}

			bool OnMoveOutOfField(Point pos) override
			{
				return true;
			}

			void OnTick(int tick_num) override
			{
				if (tick_num % _speed != 0)
				{
					return;
				}

				EventData::PushEvent(new EventData::EventMove(_pos, _pos + _delta));
			}

			int OnActiveIntersect(FieldObject* intersected_object) override
			{
				return IntersectResult::IntResIsDead;
			}
		};
	}
}