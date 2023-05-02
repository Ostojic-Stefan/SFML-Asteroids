#include "Game.hpp"
#include <functional>

Game::Game()
	: m_Window(new Window("Asteroids"))
{
	shape.setFillColor(sf::Color::Green);
	shape.setSize({ 100.0f, 100.0f });

	auto bounds = shape.getLocalBounds();
	shape.setOrigin(bounds.left + bounds.width / 2, bounds.top + bounds.height / 2);
	shape.setPosition(m_Window->GetSize().x / 2.0f, m_Window->GetSize().y / 2.0f);

	//m_EventManager.RegisterBinding("LeftButton", EventType::Keyboard, sf::Keyboard::Left);
	//m_EventManager.RegisterCallback<Game>("LeftButton", &Game::MoveShape, this);

	//m_EventManager.RegisterBinding("MouseLeft", EventType::Mouse, sf::Mouse::Left);
	//m_EventManager.RegisterCallback<Game>("MouseLeft", &Game::MoveShapeMouse, this);
}

Game::~Game()
{
	delete m_Window;
}

void Game::Update()
{
	m_Window->UpdateEvents();
}

void Game::Render()
{
	m_Window->BeginDraw();
	m_Window->Draw(shape);
	m_Window->EndDraw();
}

const Window& Game::GetWindow() const
{
	return *m_Window;
}

void Game::MoveShape(const Event& event)
{
	std::cout << "Moving Shape...\n";
}

void Game::MoveShapeMouse(const Event& event)
{
	std::cout << event.mousePos.x << std::endl;
	std::cout << event.mousePos.y << std::endl;
	shape.setPosition(static_cast<sf::Vector2f>(event.mousePos));
}

