#include "Game.hpp"
#include <functional>

Game::Game()
	: 
	m_Window(new Window("Asteroids")),
	m_TextureManager("textures.cfg"),
	m_FontManager("fonts.cfg"),
	m_StateManager(&m_SharedContext)
{
	m_SharedContext.window = m_Window;
	m_SharedContext.eventManager = m_Window->GetEventManager();
	m_SharedContext.textureManager = &m_TextureManager;
	m_SharedContext.fontManager= &m_FontManager;

	m_StateManager.SwitchTo(StateType::Intro);
}

Game::~Game()
{
	delete m_Window;
}

void Game::Update()
{
	m_Window->UpdateEvents();
	m_StateManager.Update(m_Elapsed);
	m_Elapsed = m_Clock.restart();
}

void Game::Render()
{
	m_Window->BeginDraw();
	m_StateManager.Draw();
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
}

