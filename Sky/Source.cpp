#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <conio.h>
#include "GameLogic\SnakeGame.h"
#include <thread>

#include "Shared\BmpHelper\Bmp.h"

#include "Shared\ConsoleHelper\ConsoleHelper.h"
#include "Shared\ConsoleHelper\Label.h"
#include "Shared\ConsoleHelper\Form.h"

#include "Shared\Container\TrackedVariable.h"

using namespace std;

int main()
{
	SnakeGame::GameLogic::SnakeGame _game(Shared::BmpHelper::Bmp("Maps\\map2.bmp"));
	//SnakeGame::GameLogic::SnakeGame _game(70,40,5);
	_game.Init();

	std::thread input_thread([&_game]()
	{
		char ch;
		do
		{
			ch = _getch();

			switch (ch)
			{
				case 'a': _game.ChangeSnakeDirection({ -1,0 }); break;
				case 'w': _game.ChangeSnakeDirection({ 0,-1 }); break;
				case 's': _game.ChangeSnakeDirection({ 0,1 }); break;
				case 'd': _game.ChangeSnakeDirection({ 1,0 }); break;
			}

		} while (ch != 27 && _game.IsGameActive());
		_game.Stop();
	});

	while (_game.IsGameActive())
	{
		_game.Action();
		//_game.PrintField();
		std::this_thread::sleep_for(std::chrono::microseconds(20000));
	}

	Shared::ConsoleHelper::Console().PrintString({ 10,50 }, "Game over!!! Press key");

	input_thread.join();
	
	return 0;
}


























