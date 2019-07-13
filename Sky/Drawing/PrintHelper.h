// ☕ Привет
#pragma once

#include "Shared\ConsoleHelper\ConsoleHelper.h"

namespace SnakeGame
{
	namespace Drawing
	{
		using Shared::ConsoleHelper::Console;
		using Shared::ConsoleHelper::Color;

		static void DrawBorder(short width, short height)
		{
			static const unsigned char    left_up = 201;
			static const unsigned char    up_down = 205;
			static const unsigned char   right_up = 187;
			static const unsigned char right_down = 188;
			static const unsigned char  left_down = 200;
			static const unsigned char left_right = 186;
			
			Console().Print({ 0,              0 },    left_up, Color::Red);
			Console().Print({ 0,     height - 1 },  left_down, Color::Red);
			Console().Print({ width,          0 },   right_up, Color::Red);
			Console().Print({ width, height - 1 }, right_down, Color::Red);

			std::string upper_lower_bound(width - 1, up_down);
			Console().PrintString({ 1,0 }, upper_lower_bound, Color::Red);
			for (short y = 1; y < height - 1; y++)
			{
				Console().Print({     0, y }, left_right, Color::Red);
				Console().Print({ width, y }, left_right, Color::Red);
			}
			Console().PrintString({ 1, height - 1 }, upper_lower_bound, Color::Red);
		}

	}
}