#include "StateGame.hpp"
#include "StateManager.hpp"
#include <iostream>

StateGame::StateGame(StateManager* context)
	: BaseState(context)
{
}

void StateGame::OnCreate()
{
	EventManager* evMgr = m_StateManager->GetContext()->eventManager;
	evMgr->SetCurrentState(StateType::Game);
	evMgr->RegisterBinding("MovePlayer", EventType::Keyboard, sf::Keyboard::W);
	evMgr->RegisterCallback(StateType::Game, "MovePlayer", &StateGame::MovePlayer, this);
	evMgr->RegisterBinding("RotatePlayer", EventType::Keyboard, sf::Keyboard::R);
	evMgr->RegisterCallback(StateType::Game, "RotatePlayer", &StateGame::RotatePlayer, this);

	ResourceManager<sf::Texture>* textureManager = m_StateManager->GetContext()->textureManager;
	textureManager->RequireResource("PlayerSprite");
	sf::Texture* texture = textureManager->GetResource("PlayerSprite");
	m_PlayerSprite.setTexture(*texture);

	sf::Vector2u windowSize = m_StateManager->GetContext()->window->GetSize();
	sf::FloatRect bounds = m_PlayerSprite.getLocalBounds();

	m_PlayerSprite.setOrigin(bounds.left + bounds.width / 2.0f, bounds.top + bounds.height / 2.0f);
	m_PlayerSprite.setPosition(windowSize.x / 2.0f, windowSize.y / 2.0f);
}

void StateGame::OnDestroy()
{
	//EventManager* evMgr = m_StateManager->GetContext()->eventManager;
	//evMgr->RemoveCallback();
}

void StateGame::Update(const sf::Time& time)
{
}

void StateGame::Draw()
{
	Window* window = m_StateManager->GetContext()->window;
	window->Draw(m_PlayerSprite);
}

void StateGame::MovePlayer(const Event& event)
{
	sf::Vector2f velocity = m_Direction * 0.1f;
	m_PlayerSprite.move(velocity);
}

void StateGame::RotatePlayer(const Event& event)
{
	m_CurrentRotation += DegToRad(1.0f);
	m_PlayerSprite.rotate(1.0f);
	float angle = DegToRad(m_PlayerSprite.getRotation()) - (M_PI / 2.0f);
	m_Direction = sf::Vector2f(std::cos(angle), std::sin(angle));

}


