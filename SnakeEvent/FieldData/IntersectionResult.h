// ☕ Привет
#pragma once

namespace SnakeEvent
{
	namespace FieldData
	{
		enum IntersectResult : int
		{
			IntResIsDead = 1,  // Умрет ли объект после пересечения
			IntResIsMove = 2   // Для активного - перемещаться ли на место пассивного
						       // Для пассивного - пускать ли на свое место активного
		};

		bool IsDead(int intersection_result)
		{
			return intersection_result & IntersectResult::IntResIsDead;
		}
		bool IsAlive(int intersection_result)
		{
			return (intersection_result & IntersectResult::IntResIsDead) == 0;
		}
		bool IsMove(int intersection_result)
		{
			return intersection_result & IntersectResult::IntResIsMove;
		}
		bool IsNotMove(int intersection_result)
		{
			return (intersection_result & IntersectResult::IntResIsMove) == 0;
		}
	}
}