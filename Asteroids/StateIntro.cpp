#include "StateIntro.hpp"
#include "StateManager.hpp"
#include <iostream>

StateIntro::StateIntro(StateManager* stateManager)
	: BaseState(stateManager)
{
}

void StateIntro::OnCreate()
{
	EventManager* evMgr = m_StateManager->GetContext()->eventManager;
	evMgr->SetCurrentState(StateType::Intro);
	evMgr->RegisterBinding("ChangeToGame", EventType::KeyDown, sf::Keyboard::Enter);
	evMgr->RegisterCallback(StateType::Intro, "ChangeToGame", &StateIntro::ChangeToGame, this);

	ResourceManager<sf::Font>* fontManager = m_StateManager->GetContext()->fontManager;
	fontManager->RequireResource("Default");
	m_Font = fontManager->GetResource("Default");

	sf::Vector2u windowSize = m_StateManager->GetContext()->window->GetSize();

	m_Text.setFont(*m_Font);
	m_Text.setString("Press Enter To Play");
	sf::FloatRect bounds = m_Text.getLocalBounds();
	m_Text.setOrigin(bounds.left + bounds.width / 2.0f, bounds.top + bounds.height / 2.0f);
	m_Text.setPosition(windowSize.x / 2.0f, windowSize.y / 2.0f);
}

void StateIntro::OnDestroy()
{
	//EventManager* evMgr = m_StateManager->GetContext()->eventManager;
	//evMgr->RemoveCallback();
}

void StateIntro::Update(const sf::Time& time)
{
}

void StateIntro::Draw()
{
	sf::RenderWindow* window = m_StateManager->GetContext()->window->GetRenderWindow();
	window->draw(m_Text);
}

void StateIntro::ChangeToGame(const Event& event)
{
	m_StateManager->SwitchTo(StateType::Game);
}
