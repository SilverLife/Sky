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

			FieldObjectWithPos(Point pos, char draw_symbol, Shared::ConsoleHelper::Color color)
				: FieldObject(draw_symbol, color) 
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