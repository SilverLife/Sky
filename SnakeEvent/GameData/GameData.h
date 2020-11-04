// ☕ Привет
#pragma once

#include "../FieldData/Field.h"
#include "../Action/ActionManager.h"
#include "../EventData/EventManager.h"
#include "../FieldData/Objects/Player.h"

namespace SnakeEvent
{
	namespace GameData
	{
		class GameData
		{
		public:
			FieldData::Field _field;
			Action::ActionManager _action_manager;
			EventData::EventManager _event_manager;

			GameData(Size field_size)
				: _field(field_size)
				, _action_manager(&_event_manager, &_field)
			{}
		};

		class GameWithPlayer : public GameData
		{
		public:
			FieldData::Player* _player;

			GameWithPlayer(Size field_size)
				: GameData(field_size)
			{}
		};
	}
}