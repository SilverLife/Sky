// ☕ Привет
#pragma once

#include "FieldObject.h"
#include "../../Sky/Shared/FieldData/Field.h"

namespace SnakeEvent
{
	namespace FieldData
	{
		class Field
		{
			using FieldData = Shared::FieldData::Field<FieldObject*>;

			FieldData _field_data;

		public:
			Field(Size size) :_field_data(size._width, size._height) 
			{
				for (PointCoordsType x = 0; x < _field_data.Size()._width; x++)
				{
					for (PointCoordsType y = 0; y < _field_data.Size()._height; y++)
					{
						_field_data.SetObject({ x,y }, nullptr);
					}
				}
			}

			void PrintField()
			{
				for (PointCoordsType x = 0; x < _field_data.Size()._width; x++)
				{
					for (PointCoordsType y = 0; y < _field_data.Size()._height; y++)
					{
						const auto object = _field_data.Object({ x,y });
						if (object == nullptr)
						{
							Shared::ConsoleHelper::Console().Print({ x,y }, ' ');
						}
						else
						{
							object->OnDraw({ x,y });
						}
					}
				}
			}

			bool IsEmpty(Point pos) { return _field_data.Object(pos) == nullptr; }

			void KillObject(Point pos)
			{
				const auto object = _field_data.Object(pos);
			
				object->OnDrawTrace(pos);
				object->OnRemove();
				_field_data.SetObject(pos, nullptr);
			}

			void AddObject(Point pos, FieldObject* object)
			{
				if (_field_data.Object(pos) != nullptr)
				{
					object->OnPlaceToFieldFailure(pos);
					return;
				}

				_field_data.SetObject(pos, object);
				object->OnDraw(pos);
			}

			void MoveObject(Point src_pos, Point dst_pos)
			{
				if (_field_data.IsOutOfField(src_pos))
				{
					throw "Source pos is out of field";
				}

				if (src_pos == dst_pos)
				{
					return;
				}

				const auto src_object = _field_data.Object(src_pos);

				if (src_object == nullptr)
				{
					return;
				}

				if (_field_data.IsOutOfField(dst_pos))
				{
					const bool is_need_remove = src_object->OnMoveOutOfField(dst_pos);
					if (is_need_remove)
					{
						KillObject(src_pos);
					}
					return;
				}

				const auto MoveObject = [this](Point src_pos, Point dst_pos, FieldObject* object)
				{
					object->OnDrawTrace(src_pos);
					object->OnDraw(dst_pos);
					object->OnMove(src_pos, dst_pos);
					_field_data.SetObject(dst_pos, object);
					_field_data.SetObject(src_pos, nullptr);
				};

				const auto dst_object = _field_data.Object(dst_pos);
				if (dst_object == nullptr)
				{
					MoveObject(src_pos, dst_pos, src_object);
					return;
				}

				const auto src_intersect_result = src_object->OnActiveIntersect(dst_object);
				const auto dst_intersect_result = dst_object->OnPassiveIntersect(src_object);

				/* Варианты действий при пересечении 2х объектов (s,d)
				* 1. Все остаются на месте
				* 2. d - остается на месте, s - исчезает
				* 3. d - исчезает, s - остается на месте
				* 4. d - исчезает, s - встает на место d
				* 5. Оба исчезают
				*/

				const auto CheckDeath = [this](Point pos, FieldObject* object, auto intersect_result)
				{
					if (IsDead(intersect_result))
					{
						object->OnDrawTrace(pos);
						object->OnRemove();
						_field_data.SetObject(pos, nullptr);
					}
				};

				CheckDeath(src_pos, src_object, src_intersect_result);
				CheckDeath(dst_pos, dst_object, dst_intersect_result);

				if (IsDead(src_intersect_result))
				{
					return; // Активный объект умер
				}

				if (IsNotMove(src_intersect_result))
				{
					return; // Активный объект не хочет двигаться
				}

				if (IsDead(dst_intersect_result))
				{
					MoveObject(src_pos, dst_pos, src_object);
					return;
				}

				// Активный объект хочет подвинуться, но пассивный жив и не разрешает
				if (IsNotMove(dst_intersect_result))
				{
					throw std::logic_error("Incorrect itersect states. Src - move, dst - don't move");
				}

				// Пассивный жив и разрешает двигаться
				dst_object->OnRemove();
				MoveObject(src_pos, dst_pos, src_object);
			}
		};
	}
}