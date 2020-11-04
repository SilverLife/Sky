#pragma once

#include "../GameData/GameData.h"
#include "../FieldData/FieldObject.h"
#include "../FieldData/Objects/Wall.h"
#include "../FieldData/Objects/Enemy.h"
#include "../FieldData/Objects/FreezingFood.h"

#include <memory>

namespace SnakeEvent
{
	namespace Level
	{
		std::unique_ptr<GameData::GameWithPlayer> GenerateLevel(PointCoordsType w, PointCoordsType h, int walls_count, int enemies_count, int food_count)
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

			
			for (int i = 0; i < enemies_count; i++)
			{
				const Point pos = { std::rand() % w, std::rand() % h };

				if (!game_data->_field.IsEmpty(pos))
				{
					game_data->_field.KillObject(pos);
				}

				const auto enemy = new FieldData::Enemy(pos);
				game_data->_field.AddObject(pos, enemy);
				game_data->_action_manager.SubscribeToTick(enemy);
				game_data->_action_manager.SubscribeToEvent(enemy, EventData::EventType::FreezeEnemies);
			}


			for (int i = 0; i < food_count; i++)
			{
				const Point pos = { std::rand() % w, std::rand() % h };

				if (!game_data->_field.IsEmpty(pos))
				{
					continue;
				}

				game_data->_field.AddObject(pos, new FieldData::FreezingFood);
			}
			
			const Point player_pos = { std::rand() % w, std::rand() % h };
			if (!game_data->_field.IsEmpty(player_pos))
			{
				game_data->_field.KillObject(player_pos);
			}

			game_data->_player = new FieldData::Player(player_pos);
			game_data->_field.AddObject(player_pos, game_data->_player);

			game_data->_action_manager.SubscribeToTick(game_data->_player);


			

			return std::move(game_data);
		}
	}
}