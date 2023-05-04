#pragma once
#include "BaseState.hpp"
#include "EventManager.hpp"

#define M_PI 3.14159265f

class StateGame : public BaseState
{
public:
	StateGame(StateManager* context);

	// Inherited via BaseState
	virtual void OnCreate() override;

	virtual void OnDestroy() override;

	virtual void Update(const sf::Time& time) override;

	virtual void Draw() override;

private:
	void MovePlayer(const Event& event);
	void RotatePlayer(const Event& event);
	float DegToRad(float deg)
	{
		return deg * M_PI / 180.0f;
	}
private:
	sf::Sprite m_PlayerSprite;
	sf::Vector2f m_Direction;
	float m_CurrentRotation = 0.0f;
};