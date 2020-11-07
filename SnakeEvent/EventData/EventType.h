// ☕ Привет
#pragma once

#include "../../Sky/Shared/EventGameEngine/Common.h"
#include "../../Sky/Shared/EventGameEngine/EventData/Event.h"

using namespace EventGameEngine;
using namespace EventGameEngine::EventData;

namespace SnakeEvent
{
	enum CustomEventType : EventTypeInt
	{
		FreezeEnemies = 0,
		EnemySpeedIncrease = 1,

		EventsCount
	};
}
