// ☕ Привет
#pragma once

#include "../Common/Common.h"

namespace SnakeEvent
{
	namespace EventData
	{
		enum class EventType
		{
			Move
		};

		struct Event
		{
			EventType _type;

			virtual ~Event() = default;
		};

		// ============= //

		struct EventMove : Event
		{
			Point _src_pos;
			Point _dst_pos;

			EventMove(Point src_pos, Point dst_pos)
				: _src_pos(src_pos)
				, _dst_pos(dst_pos)
			{ 
				_type = EventType::Move; 
			}


		};
	}
}