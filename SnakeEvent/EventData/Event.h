// ☕ Привет
#pragma once


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
			EventMove() { _type = EventType::Move; }

			Point _src_pos;
			Point _dst_pos;
		};
	}
}