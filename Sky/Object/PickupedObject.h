// ☕ Привет
#pragma once

#include "Common\CommonDefines.h"
#include "Shared\Geometry\RectangleSize.h"
#include "Shared\FieldData\Field.h"
#include "Shared\ConsoleHelper\ConsoleHelper.h"

namespace SnakeGame
{
	namespace Object
	{
		using PickupedObjectPicture = Shared::FieldData::Field<Shared::ConsoleHelper::ColoredChar, uint8_t>;

		// Подбираемый объект
		// 1) Имеет область заполнения. Имеет рисунок
		// 2) При контакте должен уничтожиться
		// 3) При контакте вызывается функция
		class PickupedObject
		{
			using Size = Shared::Geometry::RectangleSize<char>;

			Point _left_up_position;

			const PickupedObjectPicture& _picture;

		public:
			PickupedObject(Point start_position, const PickupedObjectPicture& picture)
				: _left_up_position(start_position),
				  _picture(picture)
			{}

			void Draw()
			{
				for (uint8_t j = 0; j < _picture.Size()._height; ++j)
				{
					for (uint8_t i = 0; i < _picture.Size()._width; ++i)
					{
						const auto [symbol, color] = _picture.Object({ i,j });
						Shared::ConsoleHelper::Console().Print(_left_up_position + Point{i, j}, symbol, color);
					}
				}
			}
		};
	}
}