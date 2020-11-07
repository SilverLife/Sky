// ☕ Привет
#pragma once

#include "../../../Sky/Shared/EventGameEngine/FieldData/FieldObjectWithPos.h"
#include "Player.h"

using namespace EventGameEngine::FieldData;

namespace SnakeEvent
{
	namespace FieldData
	{
		class Door : public FieldObject
		{
		public:
			Door()
				: FieldObject(177)
			{}
		};

		class Key : public FieldObject
		{
			Point _door_pos;
		public:
			Key(Point door_pos)
				: FieldObject('K')
				, _door_pos(door_pos)
			{}

			virtual int OnPassiveIntersect(FieldObject* intersected_object)
			{
				if (dynamic_cast<Player*>(intersected_object) != nullptr)
				{
					EventData::PushEvent(new EventData::EventRemoveObject(_door_pos));
					return IntersectResult::IntResIsDead;
				}
				return 0;
			}
		};
	}
}