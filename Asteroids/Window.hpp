#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <string_view>

#include "EventManager.hpp"

class Window
{
public:
	Window(const std::string& title, const sf::Vector2i& = { 1280, 720 });
	bool ShouldClose() const;
	void UpdateEvents();
	void BeginDraw();
	void Draw(const sf::Drawable& drawable);
	void EndDraw();
	const sf::RenderWindow& GetRenderWindow() const {
		return m_Window;
	}
	sf::Vector2u GetSize() const;
	void SetFullScreen(const Event& ev);
private:
	void CloseWindow(const Event& ev);
private:
	EventManager m_EventManager;
	sf::RenderWindow m_Window;
	bool m_ShouldClose = false;
};
