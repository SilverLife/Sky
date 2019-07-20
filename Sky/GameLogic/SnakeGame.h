// ☕ Привет
#pragma once

#include "Shared\BmpHelper\Bmp.h"
#include "Shared\FieldData\Field.h"
#include "Shared\FieldData\WavePathFinder.h"
#include "Object\Snake.h"
#include "Object\MovableWall.h"

#include "Shared\ConsoleHelper\Form.h"

#include <filesystem>

namespace fs = std::filesystem;

namespace SnakeGame
{
	namespace GameLogic
	{
		// Основной класс игры. Вся игра осуществляется через интерфейс этого класса.
		class SnakeGame
		{
			enum class FieldObjectType : unsigned char
			{
				Empty = 0,
				Snake,
				Wall,
				Count
			};

			using PathFinder = Shared::FieldData::WavePathFinder<FieldObjectType, short>;

			Shared::FieldData::Field<FieldObjectType, PointCoordsType> _field;

			std::vector<PathFinder> _wave_path_finders;
			Object::Snake _snake;

			std::vector<Object::MoveableWall> _moveable_walls;

			bool _is_game_active = true;

			std::unique_ptr<Shared::ConsoleHelper::Form> _info_form;

			inline void PrintObject(Point position, FieldObjectType object_type);

			void MoveObject(Point position_from, Point position_to);
			void SetObject(Point position, FieldObjectType object_type);

			void GenerateWalls(uint walls_count);

			void GenerateMoveableWalls(uint walls_count);

			void MoveMoveableWalls();

			void MoveSnake();

			void SplitSnake(Point position);

		public:
			SnakeGame(PointCoordsType width, PointCoordsType height, uint snake_length);
			SnakeGame(Shared::BmpHelper::Bmp bmp);
			
			void Init();

			~SnakeGame();

			void PrintField() const;

			void Action();

			void ChangeSnakeDirection(Point new_direction_delta);

			void Stop() { _is_game_active = false; }
			bool IsGameActive() const { return _is_game_active; }
		};
	}
}