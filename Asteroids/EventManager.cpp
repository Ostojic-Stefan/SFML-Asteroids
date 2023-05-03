#include "EventManager.hpp"

EventManager::EventManager() 
	: m_CurrentState(StateType(0))
{}

void EventManager::RegisterBinding(const std::string& name, EventType type, int keyCode)
{
	m_Bindings[name] = { type, keyCode };
}

void EventManager::SetCurrentState(StateType stateType)
{
	m_CurrentState = stateType;
}

void EventManager::UpdateRealTime()
{
	for (auto& bItr : m_Bindings)
	{
		Binding& binding = bItr.second;
		if (binding.eventType == EventType::Keyboard)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(binding.keyCode)))
			{
				const auto callbackItr = m_Callbacks.find(bItr.first);
				if (m_CurrentState == callbackItr->second.first || callbackItr->second.first == StateType(0))
				{
					callbackItr->second.second(Event());
				}
			}
		}
		else if (binding.eventType == EventType::Mouse) 
		{
			if (sf::Mouse::isButtonPressed(sf::Mouse::Button(binding.keyCode)))
			{
				const auto callbackItr = m_Callbacks.find(bItr.first);
				if (m_CurrentState == callbackItr->second.first || callbackItr->second.first == StateType(0))
				{
					Event ev;
					//ev.mousePos = sf::Mouse::getPosition(m_Window.GetRenderWindow());
					ev.keyCode = binding.keyCode;
					callbackItr->second.second(ev);
				}
			}
		}
	}
}

void EventManager::UpdatePoll(const sf::Event& event)
{
	for (auto& bItr : m_Bindings)
	{
		Binding& binding = bItr.second;
		EventType sfmlEvent = static_cast<EventType>(event.type);

		if (binding.eventType == sfmlEvent) 
		{
			Event ev;
			if (sfmlEvent == EventType::MButtonDown || sfmlEvent == EventType::MButtonUp)
			{
				ev.mousePos.x = event.mouseButton.x;
				ev.mousePos.y = event.mouseButton.y;
				ev.keyCode = bItr.second.keyCode;
			}
			if (sfmlEvent == EventType::KeyDown || sfmlEvent == EventType::KeyUp)
			{
				ev.keyCode = bItr.second.keyCode;
			}
			const auto callbackItr = m_Callbacks.find(bItr.first);
			if (m_CurrentState == callbackItr->second.first || callbackItr->second.first == StateType(0))
			{
				callbackItr->second.second(ev);
			}
		}
	}
}
