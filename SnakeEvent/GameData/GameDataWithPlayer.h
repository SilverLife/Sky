// ☕ Привет
#pragma once

#include "../../Sky/Shared/EventGameEngine/GameData/GameData.h"
#include "../EventData/EventType.h"
#include "../FieldData/Objects/Player.h"

using namespace EventGameEngine;

namespace SnakeEvent
{
	class GameWithPlayer : public GameData<CustomEventType::EventsCount>
	{
	public:
		FieldData::Player* _player;

		GameWithPlayer(Size field_size)
			: GameData(field_size)
		{}
	};
}