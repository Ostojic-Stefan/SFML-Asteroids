#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include <iostream>

#include "Window.hpp"
#include "EventManager.hpp"
#include "ResourceManager.hpp"
#include "StateManager.hpp"
#include "SharedContext.hpp"

class Game
{
public:
	Game();
	~Game();
	void Update();
	void Render();
	const Window& GetWindow() const;
private:
	void MoveShape(const Event& event);
	void MoveShapeMouse(const Event& event);
private:
	sf::Clock m_Clock;
	sf::Time m_Elapsed;

	SharedContext m_SharedContext;
	StateManager m_StateManager;
	Window* m_Window;
	ResourceManager<sf::Texture> m_TextureManager;
	ResourceManager<sf::Font> m_FontManager;
};