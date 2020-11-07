// ☕ Привет
#pragma once

#include "../EventData/EventManager.h"
#include "../FieldData/Field.h"
#include <memory>
#include <thread>

namespace SnakeEvent
{
	namespace Action
	{
		class ActionManager
		{
			EventData::EventManager* const _event_manager;
			FieldData::Field* const _field;

			std::vector<FieldData::FieldObject*> _tick_subscribers;
			int _tick_counter = 0;

			std::vector<FieldData::FieldObject*> _event_subscribers[static_cast<int>(EventData::EventType::EventsCount)];

			void ProcessTick()
			{
				for (auto sub : _tick_subscribers)
				{
					sub->OnTick(_tick_counter);
				}

				_tick_counter++;
			}

			void ProcessEvent(EventData::Event* event)
			{
				if (event->_type == EventData::EventType::Move)
				{
					const auto event_move = static_cast<EventData::EventMove*>(event);
					_field->MoveObject(event_move->_src_pos, event_move->_dst_pos);
				}
				else if (event->_type == EventData::EventType::AddObject)
				{
					const auto event_add_object = static_cast<EventData::EventAddObject*>(event);
					_field->AddObject(event_add_object->_pos, event_add_object->_object);
				}
				else if (event->_type == EventData::EventType::GameOver)
				{
					Shared::ConsoleHelper::Console().PrintString({ 10,10 }, "Game over");
					std::system("pause");
					exit(0);
				}
				else if (event->_type == EventData::EventType::Win)
				{
					Shared::ConsoleHelper::Console().PrintString({ 10,10 }, "You win");
					std::system("pause");
					exit(0);
				}
				else if (event->_type == EventData::EventType::RemoveObject)
				{
					const auto event_remove_object = static_cast<EventData::EventRemoveObject*>(event);
					_field->KillObject(event_remove_object->_pos);
				}
				else
				{
					for (auto sub : _event_subscribers[static_cast<int>(event->_type)])
					{
						sub->OnEvent(event);
					}
				}
			}

			void ProcessEvents()
			{
				auto events_count = _event_manager->EventsCount();

				while (events_count > 0)
				{
					const auto event = _event_manager->PopEvent();

					ProcessEvent(event);
					--events_count;
				}
			}

		public:
			ActionManager(EventData::EventManager* event_manager,
				          FieldData::Field* field)
				: _event_manager(event_manager)
				, _field(field)
			{}

			void SubscribeToTick(FieldData::FieldObject* field_object)
			{
				_tick_subscribers.push_back(field_object);
			}

			void SubscribeToEvent(FieldData::FieldObject* field_object, EventData::EventType event_type)
			{
				_event_subscribers[static_cast<int>(event_type)].push_back(field_object);
			}

			void Run()
			{
				while (true)
				{
					ProcessTick();

					ProcessEvents();

					std::this_thread::sleep_for(std::chrono::microseconds(5));
				}
			}
		};
	}
}