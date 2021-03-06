#pragma once

#include "../GameData/GameDataWithPlayer.h"
#include "../../Sky/Shared/EventGameEngine/FieldData/FieldObject.h"
#include "../FieldData/Objects/Wall.h"
#include "../FieldData/Objects/Enemy.h"
#include "../FieldData/Objects/FreezingFood.h"
#include "../FieldData/Objects/EnemySpeedIncreaseFood.h"
#include "../FieldData/Objects/CannonBullet.h"

#include <memory>

namespace SnakeEvent
{
	namespace Level
	{
		std::unique_ptr<GameWithPlayer> GenerateLevel(PointCoordsType w, PointCoordsType h, int walls_count, int enemies_count, int food_count)
		{
			auto game_data = std::make_unique<GameWithPlayer>(Size{ w, h });

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
				game_data->_action_manager.SubscribeToEvent(enemy, CustomEventType::FreezeEnemies);
				game_data->_action_manager.SubscribeToEvent(enemy, CustomEventType::EnemySpeedIncrease);
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

			for (int i = 0; i < food_count; i++)
			{
				const Point pos = { std::rand() % w, std::rand() % h };

				if (!game_data->_field.IsEmpty(pos))
				{
					continue;
				}

				game_data->_field.AddObject(pos, new FieldData::EnemySpeedIncreaseFood);
			}
			
			for (int i = 0; i < 3; i++)
			{
				const Point pos = { std::rand() % w, std::rand() % h };

				if (!game_data->_field.IsEmpty(pos))
				{
					continue;
				}

				const auto cannon_bullet = new FieldData::CannonBullet(pos, kDeltas[std::rand() % 4]);
				game_data->_field.AddObject(pos, cannon_bullet);
				game_data->_action_manager.SubscribeToTick(cannon_bullet);
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