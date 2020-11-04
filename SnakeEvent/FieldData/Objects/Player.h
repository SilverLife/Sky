// ☕ Привет
#pragma once

#include "../FieldObject.h"

namespace SnakeEvent
{
	namespace FieldData
	{
		class Player : public FieldObject
		{
			Point _pos;
		public:
			Player(Point pos)
				: FieldObject('#')
				, _pos(pos)
			{}

			virtual void OnMove(Point prev_pos, Point new_pos)
			{
				_pos = new_pos;
			}

			void OnRemove() override
			{	
				throw "Game Over";
			}

			Point Pos() const { return _pos; }
		};
	}
}