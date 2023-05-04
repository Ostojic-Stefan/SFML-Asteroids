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
	evMgr->RegisterBinding("MovePlayer", EventType::Keyboard, sf::Keyboard::Right);
	evMgr->RegisterCallback(StateType::Game, "MovePlayer", &StateGame::MovePlayer, this);

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
	std::cout << "Game Running " << time.asSeconds() << std::endl;
}

void StateGame::Draw()
{
	Window* window = m_StateManager->GetContext()->window;
	window->Draw(m_PlayerSprite);
}

void StateGame::MovePlayer(const Event& event)
{
	m_PlayerSprite.move({ 2.0f, 0.0f });
}


