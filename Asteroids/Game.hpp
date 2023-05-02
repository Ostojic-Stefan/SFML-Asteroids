#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include <iostream>

#include "Window.hpp"
#include "EventManager.hpp"

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
	Window* m_Window;
	sf::RectangleShape shape;
};