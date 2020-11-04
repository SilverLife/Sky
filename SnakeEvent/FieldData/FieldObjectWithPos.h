// ☕ Привет
#pragma once

#include "FieldObject.h"

namespace SnakeEvent
{
	namespace FieldData
	{
		class FieldObjectWithPos : public FieldObject
		{
		protected:
			Point _pos;
		public:
			FieldObjectWithPos(Point pos)
				: FieldObject()
				, _pos(pos)
			{}

			FieldObjectWithPos(Point pos, char draw_symbol)
				: FieldObject(draw_symbol) 
				, _pos(pos)
			{}

			void OnMove(Point prev_pos, Point new_pos) override
			{
				_pos = new_pos;
			}

			Point Pos() const { return _pos; }
		};
	}
}