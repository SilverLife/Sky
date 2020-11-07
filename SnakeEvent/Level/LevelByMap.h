#pragma once

#include "../GameData/GameData.h"
#include "../../Sky/Shared/EventGameEngine/FieldData/FieldObject.h"
#include "../FieldData/Objects/Wall.h"
#include "../FieldData/Objects/Enemy.h"
#include "../FieldData/Objects/FreezingFood.h"
#include "../FieldData/Objects/EnemySpeedIncreaseFood.h"
#include "../FieldData/Objects/CannonBullet.h"
#include "../FieldData/Objects/Win.h"
#include "../FieldData/Objects/KeyDoor.h"

#include <memory>
#include <string_view>

namespace SnakeEvent
{
	namespace Level
	{

		static constexpr std::string_view kMap[] =
		{
			"P     #                  #                 L#                              L",
			"                       # # #### ####### ####K    ############### ###########",
			"      #                #             L#     #   #                           ",
			"## ###########         ########### ####     #  #                            ",
			"             #    E    #              #  E    #           E                 ",
			" ####### #####         #              #     ##                              ",
			" #          L#                        #######              E                ",
			" #           ###########                                                   K",
			" #R          #         #####################################################",
			" #                       L#                #                               K",
			" ############# ### ###  ###                                      E          ",
			"             # # # # #    #                #                                ",
			" #   E       # # # # # #  #      E         #                                ",
			" #           #U# #U# #U# K#                #    E               E           ",
			" #           ### ### ######                #                                ",
			" ###########             K#                #                                ",
			"            ############### ###############K####### #                      K",
			" #                                               L# ########################",
			"U#                                               L#                 wwwwwwwW"
		};

		std::unique_ptr<GameData::GameWithPlayer> GenerateLevelFromMap()
		{
			const PointCoordsType w = std::size(kMap[0]);
			const PointCoordsType h = std::size(kMap);

			auto game_data = std::make_unique<GameData::GameWithPlayer>(Size{ w, h });

			std::vector<Point> key_positions;
			std::vector<Point> door_positions;

			for (PointCoordsType x = 0; x < w; x++)
			{
				for (PointCoordsType y = 0; y < h; y++)
				{
					const auto symbol = kMap[y][x];
					const Point pos{ x,y };

					if (symbol == ' ')
					{
						continue;
					}
					else if (symbol == 'P')
					{
						game_data->_player = new FieldData::Player(pos);
						game_data->_field.AddObject(pos, game_data->_player);
						game_data->_action_manager.SubscribeToTick(game_data->_player);
					}
					else if (symbol == '#')
					{
						game_data->_field.AddObject(pos, new FieldData::Wall);
					}
					else if (symbol == 'E')
					{
						const auto enemy = new FieldData::Enemy(pos);
						game_data->_field.AddObject(pos, enemy);
						game_data->_action_manager.SubscribeToTick(enemy);
						game_data->_action_manager.SubscribeToEvent(enemy, CustomEventType::FreezeEnemies);
						game_data->_action_manager.SubscribeToEvent(enemy, CustomEventType::EnemySpeedIncrease);
					}
					else if (symbol == 'F')
					{
						game_data->_field.AddObject(pos, new FieldData::FreezingFood);
					}
					else if (symbol == 'I')
					{
						game_data->_field.AddObject(pos, new FieldData::EnemySpeedIncreaseFood);
					}
					else if (symbol == 'L')
					{
						const auto cannon_bullet = new FieldData::CannonBullet(pos, { -1,0 }, std::rand() % 50 + 30);
						game_data->_field.AddObject(pos, cannon_bullet);
						game_data->_action_manager.SubscribeToTick(cannon_bullet);
					}
					else if (symbol == 'D')
					{
						const auto cannon_bullet = new FieldData::CannonBullet(pos, { 0,1 }, std::rand() % 20 + 150);
						game_data->_field.AddObject(pos, cannon_bullet);
						game_data->_action_manager.SubscribeToTick(cannon_bullet);
					}
					else if (symbol == 'U')
					{
						const auto cannon_bullet = new FieldData::CannonBullet(pos, { 0,-1 }, std::rand() % 20 + 150);
						game_data->_field.AddObject(pos, cannon_bullet);
						game_data->_action_manager.SubscribeToTick(cannon_bullet);
					}
					else if (symbol == 'W')
					{
						const auto win = new FieldData::Win();
						game_data->_field.AddObject(pos, win);
					}
					else if (symbol == 'w')
					{
						door_positions.push_back(pos);
					}
					else if (symbol == 'K')
					{
						key_positions.push_back(pos);
					}
				}
			}

			if (key_positions.size() != door_positions.size())
			{
				throw 4;
			}

			for (int i = 0; i < door_positions.size(); i++)
			{
				game_data->_field.AddObject(door_positions[i], new FieldData::Door);
				game_data->_field.AddObject(key_positions[i], new FieldData::Key(door_positions[i]));
			}

			return std::move(game_data);
		}
	}
}