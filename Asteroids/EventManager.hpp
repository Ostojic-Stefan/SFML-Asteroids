#pragma once
#include <SFML/Graphics.hpp>

#include <unordered_map>
#include <string>
#include <iostream>
#include <functional>

enum class EventType
{
	KeyDown = sf::Event::KeyPressed,
	KeyUp = sf::Event::KeyReleased,
	MButtonDown = sf::Event::MouseButtonPressed,
	MButtonUp = sf::Event::MouseButtonReleased,
	GainedFocus = sf::Event::GainedFocus,
	LostFocus = sf::Event::LostFocus,
	MouseEntered = sf::Event::MouseEntered,
	MouseLeft = sf::Event::MouseLeft,
	Closed = sf::Event::Closed,
	TextEntered = sf::Event::TextEntered,

	Keyboard = sf::Event::Count + 1,
	Mouse,
};

struct Binding 
{
	EventType eventType;
	int keyCode;
};

struct Event
{
	sf::Vector2i mousePos;
	int keyCode;
};

using CallbackType = std::function<void(const Event&)>;

class EventManager
{
public:
	EventManager();
	void RegisterBinding(const std::string& name, EventType type, int keyCode);
	
	template<class T>
	void RegisterCallback(const std::string& name, void(T::*func)(const Event&), T* instance)
	{
		CallbackType callback = std::bind(func, instance, std::placeholders::_1);
		m_Callbacks[name] = callback;
	}

	void UpdateRealTime();
	void UpdatePoll(const sf::Event& event);
private:
	//Window& m_Window;
	std::unordered_map<std::string, Binding> m_Bindings;
	std::unordered_map<std::string, CallbackType> m_Callbacks;
};