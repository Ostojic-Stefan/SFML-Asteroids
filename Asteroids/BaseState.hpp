#pragma once
#include <SFML/Graphics.hpp>

class StateManager;

class BaseState
{
public:
	BaseState(StateManager* stateManager) : m_StateManager(stateManager) {}
	virtual ~BaseState() = default;

	virtual void OnCreate() = 0;
	virtual void OnDestroy() = 0;

	virtual void Update(const sf::Time& time) = 0;
	virtual void Draw() = 0;
protected:
	StateManager* m_StateManager;
};