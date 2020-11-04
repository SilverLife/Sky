// ☕ Привет
#pragma once

#include "../FieldObjectWithPos.h"
#include "../../EventData/GlobalEventPusher.h"
#include "Enemy.h"

namespace SnakeEvent
{
	namespace FieldData
	{
		class Player : public FieldObjectWithPos
		{
			Point _movement_delta{ 0,0 };
		public:
			Player(Point pos)
				: FieldObjectWithPos(pos, '#', Shared::ConsoleHelper::Color::Yellow)
			{}

			void OnRemove() override
			{	
				//throw "Game Over";
			}

			void OnTick(int tick_num) override
			{
				if (tick_num % 40 != 0)
				{
					return;
				}

				if (_movement_delta == Point{0, 0})
				{
					return;
				}

				EventData::PushEvent(new EventData::EventMove( _pos, _pos + _movement_delta ));
			}

			int OnActiveIntersect(FieldObject* intersected_object) override
			{
				if (dynamic_cast<Enemy*>(intersected_object) != nullptr)
				{
					// Наткнулись на врага
					return IntersectResult::IntResIsDead;
				}
				return 0; 
			}

			int OnPassiveIntersect(FieldObject* intersected_object) override
			{ 
				if (dynamic_cast<Enemy*>(intersected_object) != nullptr)
				{
					// Враг наступил на нас
					return IntersectResult::IntResIsDead;
				}
				return 0; 
			}

			void SetMovementDelta(Point point) { _movement_delta = point; }
		};
	}
}