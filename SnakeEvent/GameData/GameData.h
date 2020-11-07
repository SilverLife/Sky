// ☕ Привет
#pragma once

#include "../../Sky/Shared/EventGameEngine/FieldData/Field.h"
#include "../../Sky/Shared/EventGameEngine/ActionData/ActionManager.h"
#include "../../Sky/Shared/EventGameEngine/EventData/EventManager.h"
#include "../FieldData/Objects/Player.h"

using namespace EventGameEngine;

namespace SnakeEvent
{
	namespace GameData
	{
		class GameData
		{
		public:
			EventGameEngine::FieldData::Field _field;
			Action::ActionManager<CustomEventType::EventsCount> _action_manager;
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