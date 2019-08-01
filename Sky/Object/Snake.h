// ☕ Привет
#pragma once

#include "Shared\Container\RoundList.h"
#include "Shared\Geometry\Point.h"
#include "Shared\CommonStructs\Ticker.h"

#include "Common\CommonDefines.h"

using Shared::CommonStructs::TickerByte;

namespace SnakeGame
{
	namespace Object
	{
		class Snake : public TickerByte
		{
			Shared::Containers::RoundList<Point> _snake_parts;
			Point _direction_delta;

		public:
			Snake(Point head_position, uint8_t speed = 20)
				: TickerByte(speed),
				  _direction_delta(-1,0)
			{
				_snake_parts.PushAfterLast(head_position);
			}

			void AddHead(Point head_position)
			{
				_snake_parts.PushBeforeFirst(head_position);
			}

			void AddTail(Point tail_position)
			{
				_snake_parts.PushAfterLast(tail_position);
			}

			Point Move(Point new_head_position)
			{
				const auto tail = _snake_parts.Last();
				_snake_parts.MoveToPrev();
				_snake_parts.First() = new_head_position;
				return tail;
			}

			bool Empty() const { return _snake_parts.Size() == 0; }

			Point HeadPosition() const { return _snake_parts.First(); }
			Point TailPosition() const { return _snake_parts.Last(); }

			Point DirectionDelta() const { return _direction_delta; }
			void SetDirectionDelta(Point direction_delta) { _direction_delta = direction_delta; }

			std::vector<Point> RemoveTail(Point position)
			{
				std::vector<Point> removed_parts;
				removed_parts.reserve(_snake_parts.Size());

				const auto elem_it = _snake_parts.Find(position);
				if (elem_it == _snake_parts.end())
				{
					throw std::logic_error("Cannot find snake point in snake");
				}
				
				for (auto it = elem_it; it != _snake_parts.end(); ++it)
				{
					removed_parts.push_back(*it);
				}
				
				_snake_parts.EraseToLast(elem_it);

				return removed_parts;
			}
		};
	}
}