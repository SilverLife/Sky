#pragma once

#include "../GameData/GameData.h"
#include "../FieldData/FieldObject.h"
#include "../FieldData/Objects/Wall.h"

#include <memory>

namespace SnakeEvent
{
	namespace Level
	{
		std::unique_ptr<GameData::GameWithPlayer> GenerateLevel(PointCoordsType w, PointCoordsType h, int walls_count)
		{
			auto game_data = std::make_unique<GameData::GameWithPlayer>(Size{ w, h });

			for (int i = 0; i < walls_count; i++)
			{
				const Point pos = { std::rand() % w, std::rand() % h };

				if (game_data->_field.IsEmpty(pos))
				{
					game_data->_field.AddObject(pos, new FieldData::Wall);
				}
			}

			const Point player_pos = { std::rand() % w, std::rand() % h };
			if (!game_data->_field.IsEmpty(player_pos))
			{
				game_data->_field.KillObject(player_pos);
			}

			game_data->_player = new FieldData::Player(player_pos);
			game_data->_field.AddObject(player_pos, game_data->_player);

			return std::move(game_data);
		}
	}
}