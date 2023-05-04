#pragma once

#include "Window.hpp"
#include "EventManager.hpp"
#include "ResourceManager.hpp"

struct SharedContext
{
	Window* window = nullptr;
	EventManager* eventManager = nullptr;
	ResourceManager<sf::Texture>* textureManager = nullptr;
	ResourceManager<sf::Font>* fontManager = nullptr;
};