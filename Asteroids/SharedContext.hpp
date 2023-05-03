#pragma once
#include "Window.hpp"
#include "EventManager.hpp"

struct SharedContext
{
	Window* window = nullptr;
	EventManager* eventManager = nullptr;
};