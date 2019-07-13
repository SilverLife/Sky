// ☕ Привет

#include "SnakeGame.h"
#include "Drawing\PrintHelper.h"
#include "Shared\ConsoleHelper\ConsoleHelper.h"

#include <fstream>

using Shared::ConsoleHelper::Console;

namespace SnakeGame
{
	namespace GameLogic
	{

		inline void SnakeGame::PrintObject(Point position, FieldObjectType object_type)
		{
			using Color = Shared::ConsoleHelper::Color;
			using SymbolAndColor = std::pair<char, Color>;
			static const SymbolAndColor kSymbolsAndColors[] =
			{
				{ ' ', Color::Black },		 // Empty
				{ (char)177, Color::White }, // Snake
				{ (char)219, Color::Red }	 // Wall
			};

			const auto[symbol, color] = kSymbolsAndColors[static_cast<unsigned char>(object_type)];

			Console().Print(position + Point{ 1, 1 }, symbol, color);
		}

		void SnakeGame::MoveObject(Point position_from, Point position_to)
		{
			const auto object_type = _field.Object(position_from);
			if (object_type == FieldObjectType::Empty)
			{
				throw std::logic_error("Incorrect from object type in move object");
			}

			if (_field.Object(position_to) != FieldObjectType::Empty)
			{
				throw std::logic_error("Incorrect to object type in move object");
			}

			_field.SetObject(position_from, FieldObjectType::Empty);
			_field.SetObject(position_to, object_type);
			
			PrintObject(position_from, FieldObjectType::Empty);
			PrintObject(position_to, object_type);
		}

		void SnakeGame::SetObject(Point position, FieldObjectType object_type)
		{
			if (object_type != FieldObjectType::Empty && _field.Object(position) != FieldObjectType::Empty)
			{
				throw std::logic_error("Incorrect to object type in set object");
			}

			_field.SetObject(position, object_type);

			Shared::ConsoleHelper::Color color = Shared::ConsoleHelper::Color::White;

			if (object_type == FieldObjectType::Wall)
			{
				color = Shared::ConsoleHelper::Color::Red;
			}

			PrintObject(position, object_type);
		}

		void SnakeGame::GenerateWalls(uint walls_count)
		{
			const auto [width, height] = _field.Size();
			for (uint i = 0; i < walls_count; i++)
			{
				const Point pos(std::rand() % width, std::rand() % height);

				if (_field.Object(pos) != FieldObjectType::Empty)
				{
					continue;
				}

				SetObject(pos, FieldObjectType::Wall);
			}
		}

		void SnakeGame::GenerateMoveableWalls(uint walls_count)
		{
			const auto [width, height] = _field.Size();
			for (uint i = 0; i < walls_count; i++)
			{
				const Point pos(std::rand() % width, std::rand() % height);

				if (_field.Object(pos) != FieldObjectType::Empty)
				{
					continue;
				}

				SetObject(pos, FieldObjectType::Wall);
				
				const auto rand_result = std::rand() % 6;

				switch (rand_result)
				{
				case 0: _moveable_walls.emplace_back(pos, 10, Object::MoveableWallActions::UpDown<5>()); break;
				case 1: _moveable_walls.emplace_back(pos, 10, Object::MoveableWallActions::UpDown<15>()); break;
				case 2: _moveable_walls.emplace_back(pos, 10, Object::MoveableWallActions::Rectangle<5>()); break;
				case 3: _moveable_walls.emplace_back(pos, 10, Object::MoveableWallActions::Rectangle<25>()); break;
				case 4: _moveable_walls.emplace_back(pos, 10, Object::MoveableWallActions::RightLeft<5>()); break;
				case 5: _moveable_walls.emplace_back(pos, 10, Object::MoveableWallActions::RightLeft<45>()); break;
				}

			}
		}

		void SnakeGame::MoveMoveableWalls()
		{
			for (auto& wall : _moveable_walls)
			{
				if (!wall.PerformTick())
				{
					continue;
				}

				const auto new_position = wall.NextPosition();
				if (_field.IsOutOfField(new_position))
				{
					continue;
				}

				if (_field.Object(new_position) == FieldObjectType::Snake)
				{
					SplitSnake(new_position);
				}

				if (_field.Object(new_position) != FieldObjectType::Empty)
				{
					continue;
				}

				MoveObject(wall.Position(), new_position);
				wall.Move();
			}
		}

		void SnakeGame::MoveSnake()
		{
			const auto new_snake_head_position = _snake.HeadPosition() + _snake.DirectionDelta();
			if (_field.IsOutOfField(new_snake_head_position))
			{
				return;
			}

			if (_field.Object(new_snake_head_position) != FieldObjectType::Empty)
			{
				return;
			}

			const auto tail_to_remove = _snake.Move(new_snake_head_position);
			MoveObject(tail_to_remove, new_snake_head_position);
		}
		
		void SnakeGame::SplitSnake(Point position)
		{
			const auto point_to_remove = _snake.RemoveTail(position);
			for (auto point : point_to_remove)
			{
				SetObject(point, FieldObjectType::Empty);
			}
		}
		
		SnakeGame::SnakeGame(PointCoordsType width, PointCoordsType height, uint snake_length)
			: _field(width, height),
			  _snake(Point{ width / 2, height / 2 })
		{
			SetObject(_snake.HeadPosition(), FieldObjectType::Snake);

			for (uint i = 1; i < snake_length; i++)
			{
				_snake.AddTail(_snake.TailPosition() + Point{ 1,0 });
				SetObject(_snake.TailPosition(), FieldObjectType::Snake);
			}

			Drawing::DrawBorder(width + 1, height + 2);
			GenerateWalls(1);
			GenerateMoveableWalls(40);
		}

		SnakeGame::SnakeGame(Shared::BmpHelper::Bmp bmp)
			: _field(bmp.Size()._width, bmp.Size()._height),
			  _snake({ 0,0 })
		{
			const auto[width, height] = bmp.Size();

			for (PointCoordsType j = 0; j < height; j++)
			{
				for (PointCoordsType i = 0; i < width; i++)
				{
					auto& pixel = bmp.Pixel({ i,j });
					
					if (pixel == Shared::BmpHelper::PixelColors::Black)
					{
						SetObject({ i,j }, FieldObjectType::Wall);
					}
					else if (pixel == Shared::BmpHelper::PixelColors::Red)
					{
						_snake.Move({ i, j });
						SetObject(_snake.HeadPosition(), FieldObjectType::Snake);
						for (uint i = 1; i < 80; i++)
						{
							_snake.AddTail(_snake.TailPosition() + Point{ 1,0 });
							SetObject(_snake.TailPosition(), FieldObjectType::Snake);
						}
					}
					else  if (pixel == Shared::BmpHelper::PixelColors::White)
					{

					}
					else
					{
						int i = 0;
					}
				}
			}

			Drawing::DrawBorder(width + 1, height + 2);
		}

		SnakeGame::~SnakeGame()
		{
		}

		void SnakeGame::PrintField() const
		{
			//const auto [width, height] = _field.Size();
			//
			//for (short x = 0; x < width; x++)
			//{
			//	for (short y = 0; y < height; y++)
			//	{
			//		Point point{ x, y };
			//		auto obect_type = _field.Object(point);
			//		
			//		point += {1, 1};
			//
			//		switch (obect_type)
			//		{
			//		case FieldObjectType::Empty : Console().Discard(point); break;
			//		case FieldObjectType::Wall : Console().Print(point, kWallSymbol, Shared::ConsoleHelper::Color::Red); break;
			//		case FieldObjectType::Snake : Console().Print(point, (char)177, Shared::ConsoleHelper::Color::Red); break;
			//		default:
			//			break;
			//		}
			//	}
			//}
		}

		void SnakeGame::Action()
		{
			MoveMoveableWalls();

			if (_snake.Empty())
			{
				_is_game_active = false;
				return;
			}

			MoveSnake();

			//SetObject(tail_to_remove, FieldObjectType::Empty);
			//SetObject(new_snake_head_position, FieldObjectType::Snake);
		}

		void SnakeGame::ChangeSnakeDirection(Point new_direction_delta)
		{
			_snake.SetDirectionDelta(new_direction_delta);
		}
	}
}