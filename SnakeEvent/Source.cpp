
#include "Level\LevelGenerator.h"

#include <thread>
#include <conio.h>

int main()
{
	const auto game_data = SnakeEvent::Level::GenerateLevel(30, 20, 10);

	const auto InputThread = [&game_data]()
	{
		char ch;
		do
		{
			ch = _getch();

			const auto player_pos = game_data->_player->Pos();

			switch (ch)
			{
			case 'a': game_data->_field.MoveObject(player_pos, player_pos + Point{-1,  0 });  break;
			case 'w': game_data->_field.MoveObject(player_pos, player_pos + Point{ 0, -1 });  break;
			case 's': game_data->_field.MoveObject(player_pos, player_pos + Point{ 0,  1 });  break;
			case 'd': game_data->_field.MoveObject(player_pos, player_pos + Point{ 1,  0 });  break;
			}

		} while (ch != 27);

		exit(0);
	};

	std::thread input_thread(InputThread);

	game_data->_action_manager.Run();


	std::system("pause");
}