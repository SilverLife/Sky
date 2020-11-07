#pragma once

#include "../GameData/GameData.h"
#include "../FieldData/FieldObject.h"
#include "../FieldData/Objects/Wall.h"
#include "../FieldData/Objects/Enemy.h"
#include "../FieldData/Objects/FreezingFood.h"
#include "../FieldData/Objects/EnemySpeedIncreaseFood.h"
#include "../FieldData/Objects/CannonBullet.h"
#include "../FieldData/Objects/Win.h"

#include <memory>
#include <string_view>

namespace SnakeEvent
{
	namespace Level
	{

		static constexpr std::string_view kMap[] =
		{
			"P     #                  #                 L#                              L",
			"                       # # #### ####### ####     ############### ###########",
			"      #                #             L#     #   #                           ",
			"## ###########         ########### ####     #  #                            ",
			"             #    E    #              #  E    #           E                 ",
			" ####### #####         #              #     ##                              ",
			" #          L#                        #######              E                ",
			" #           ###########                                                    ",
			" #R          #         #####################################################",
			" #                       L#                #                                ",
			" ############# ### ###  ###                                      E          ",
			"             # # # # #    #                #                                ",
			" #   E       # # # # # #  #      E         #                                ",
			" #           #U# #U# #U#  #                #    E               E           ",
			" #           ### ### ######                #                                ",
			" ###########              #                #                                ",
			"            ############### ############### ####### #                       ",
			" #                                               L# ########################",
			"U#                                               L#                        W"
		};

		std::unique_ptr<GameData::GameWithPlayer> GenerateLevelFromMap()
		{
			const PointCoordsType w = std::size(kMap[0]);
			const PointCoordsType h = std::size(kMap);

			auto game_data = std::make_unique<GameData::GameWithPlayer>(Size{ w, h });

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
						game_data->_action_manager.SubscribeToEvent(enemy, EventData::EventType::FreezeEnemies);
						game_data->_action_manager.SubscribeToEvent(enemy, EventData::EventType::EnemySpeedIncrease);
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
				}
			}

			return std::move(game_data);
		}
	}
}