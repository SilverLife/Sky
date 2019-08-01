// ☕ Привет
#pragma once

#include "Shared\Geometry\Point.h"
#include "Shared\CommonStructs\Ticker.h"
#include "Common\CommonDefines.h"

#include <vector>

using Shared::CommonStructs::TickerByte;

namespace SnakeGame
{
	namespace Object
	{
		namespace MoveableWallActions
		{
			struct MoveAction
			{
				uint _count;
				Point _move_delta;
			};

			template <int Count>
			static const std::vector<MoveableWallActions::MoveAction>& UpDown()
			{
				static const std::vector<MoveableWallActions::MoveAction> instance =
				{
					{ Count, { 0, -1} },
					{ Count, { 0,  1} }
				};
				return instance;
			}

			template <int Count>
			static const std::vector<MoveableWallActions::MoveAction>& Rectangle()
			{
				static const std::vector<MoveableWallActions::MoveAction> instance =
				{
					{ Count,{  0, -1 } },
				    { Count,{  1,  0 } },
				    { Count,{  0,  1 } },
				    { Count,{ -1,  0 } }
				};
				return instance;
			}

			template <int Count>
			static const std::vector<MoveableWallActions::MoveAction>& RightLeft()
			{
				static const std::vector<MoveableWallActions::MoveAction> instance =
				{
					{ Count,{  1, 0 } },
					{ Count,{ -1, 0 } }
				};
				return instance;
			}
		}

		// Движущаяся стена. Двигается по определенному алгоритму, заданному массивом actions
		class MoveableWall : public TickerByte
		{
			Point _start_position;
			Point _cur_position;

			uint _cur_action_id = 0;
			uint _cur_action_subid = 0;

			const std::vector<MoveableWallActions::MoveAction>& _actions;

			//std::pair<int, int> GetNextActionIdAndSubId() const
			//{
			//	const auto incremented_sub_id = _cur_action_subid + 1;
			//	const auto cur_action_count = _actions[_cur_action_id]._count;
			//	const auto next_action_id = (_cur_action_id + (incremented_sub_id / cur_action_count)) % _actions.size();
			//	const auto next_action_subid = incremented_sub_id % cur_action_count;
			//
			//	return { next_action_id, next_action_subid };
			//}

		public:
			MoveableWall(std::vector<MoveableWallActions::MoveAction>&& actions) = delete;

			MoveableWall(Point position, uint ticks_to_move, const std::vector<MoveableWallActions::MoveAction>& actions)
				: TickerByte(ticks_to_move),
				  _start_position(position),
				  _cur_position(position),
				  _actions(actions)
			{}
			
			void Move()
			{
				_cur_position += _actions[_cur_action_id]._move_delta;
				if (_cur_action_subid >= _actions[_cur_action_id]._count)
				{
					_cur_action_subid = 0;
					_cur_action_id = (_cur_action_id + 1) % _actions.size();
				}
				else
				{
					++_cur_action_subid;
				}
			}
			
			Point NextPosition() const
			{
				return _cur_position + _actions[_cur_action_id]._move_delta;
			}

			Point Position() const { return _cur_position; }

			void Reset()
			{
				_cur_action_id = 0;
				_cur_action_subid = 0;
				_cur_position = _start_position;
			}
		};
	}
}