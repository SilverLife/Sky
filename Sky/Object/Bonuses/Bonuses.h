// ☕ Привет
#pragma once

#include "Object\PickupedObject.h"

namespace SnakeGame
{
	namespace Object
	{
		namespace Bonus
		{
			namespace BonusesPictures
			{
				static constexpr auto r = Shared::ConsoleHelper::Color::Red;
				static constexpr auto g = Shared::ConsoleHelper::Color::Green;
				static constexpr auto b = Shared::ConsoleHelper::Color::Blue;
				static constexpr auto y = Shared::ConsoleHelper::Color::Yellow;

				static constexpr Shared::ConsoleHelper::ColoredChar kFS{ static_cast<unsigned char>(176), y }; // Frame symbol

				static const PickupedObjectPicture kAddTail =
				{
					{ kFS,     kFS, kFS },
					{ kFS, {'T',b}, kFS },
					{ kFS,     kFS, kFS }
				};
			}

			class AddTailBonus : public PickupedObject
			{
			public:
				AddTailBonus(Point start_position)
				: PickupedObject(start_position, BonusesPictures::kAddTail)
				{}
			};

		}
	}
}