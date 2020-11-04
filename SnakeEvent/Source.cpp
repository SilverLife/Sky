
#include "Level\LevelGenerator.h"
#include "Level\LevelByMap.h"

#include <thread>
#include <conio.h>

int main()
{
	//Shared::ConsoleHelper::Console().SetConsolePositionAndSize(10, 10, 1000, 1800);

	Shared::ConsoleHelper::Console().SetPosition(200, 200);
	//const auto game_data = SnakeEvent::Level::GenerateLevel(50, 30, 10, 4,5);
	const auto game_data = SnakeEvent::Level::GenerateLevelFromMap();

	const auto InputThread = [&game_data]()
	{
		char ch;
		do
		{
			ch = _getch();

			const auto player_pos = game_data->_player->Pos();

			switch (ch)
			{
			case 'a': game_data->_player->SetMovementDelta({-1,  0 });  break;
			case 'w': game_data->_player->SetMovementDelta({ 0, -1 });  break;
			case 's': game_data->_player->SetMovementDelta({ 0,  1 });  break;
			case 'd': game_data->_player->SetMovementDelta({ 1,  0 });  break;
			case ' ': game_data->_player->SetMovementDelta({ 0,  0 });  break;
			}

		} while (ch != 27);

		exit(0);
	};

	std::thread input_thread(InputThread);

	game_data->_action_manager.Run();


	std::system("pause");
}