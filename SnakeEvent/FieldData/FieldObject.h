﻿// ☕ Привет
#pragma once

#include "../Common/Common.h"
#include "../../Sky/Shared/ConsoleHelper/ConsoleHelper.h"
#include "IntersectionResult.h"

namespace SnakeEvent
{
	namespace FieldData
	{
		class FieldObject
		{
			char _draw_symbol = ' ';
		public:
			FieldObject() = default;
			FieldObject(char draw_symbol) : _draw_symbol(draw_symbol) {}

			// ???
			virtual void OnTick(int tick_num) {};

			// Вызывается, когда надо нарисовать данный объект в указанной точке
			virtual void OnDraw(Point point_to_draw)
			{
				Shared::ConsoleHelper::Console().Print(point_to_draw, _draw_symbol);
			}

			// Вызывается, когда надо затереть объект в указанной точке
			virtual void OnDrawTrace(Point point_to_draw)
			{
				Shared::ConsoleHelper::Console().Print(point_to_draw, ' ');
			}

			// ???
			virtual void OnMove(Point prev_pos, Point new_pos) {}
			
			// Вызывается когда один объект (Active) при движении пересекается с другим объектом (Passive)
			// По умолчанию при пересечении все выживают и никто никуда не двигается
			virtual int OnActiveIntersect(FieldObject* intersected_object) { return 0; }
			virtual int OnPassiveIntersect(FieldObject* intersected_object) { return 0; }

			// Вызывается, когда поле решает, что объект надо уничтожить
			virtual void OnRemove() {}
		};
	}
}