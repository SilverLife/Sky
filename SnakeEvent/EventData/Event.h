// ☕ Привет
#pragma once

#include "../Common/Common.h"

namespace SnakeEvent
{
	namespace EventData
	{
		enum class EventType
		{
			Move = 0,
			FreezeEnemies = 1,
			EnemySpeedIncrease = 2,

			EventsCount
		};

		struct Event
		{
			EventType _type;

			Event(EventType type) : _type(type) {}
			virtual ~Event() = default;
		};

		// ============= //

		struct EventMove : Event
		{
			Point _src_pos;
			Point _dst_pos;

			EventMove(Point src_pos, Point dst_pos)
				: Event(EventType::Move)
				, _src_pos(src_pos)
				, _dst_pos(dst_pos)
			{}
		};
	}
}