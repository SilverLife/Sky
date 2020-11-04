// ☕ Привет
#pragma once

#include "../Common/Common.h"

namespace SnakeEvent
{
	namespace FieldData
	{
		class FieldObject;
	}

	namespace EventData
	{
		enum class EventType
		{
			Move = 0,
			FreezeEnemies = 1,
			EnemySpeedIncrease = 2,
			AddObject = 3,

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

		struct EventAddObject : Event
		{
			Point _pos;
			FieldData::FieldObject* _object;

			EventAddObject(Point pos, FieldData::FieldObject* object)
				: Event(EventType::AddObject)
				, _pos(pos)
				, _object(object)
			{}
		};
	}
}