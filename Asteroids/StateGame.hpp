#pragma once
#include "BaseState.hpp"

class StateGame : public BaseState
{
public:
	StateGame(StateManager* context);

	// Inherited via BaseState
	virtual void OnCreate() override;

	virtual void OnDestroy() override;

	virtual void Update(const sf::Time& time) override;

	virtual void Draw() override;

};