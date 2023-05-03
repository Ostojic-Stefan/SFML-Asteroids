#include "Window.hpp"
#include "StateManager.hpp"

Window::Window(const std::string& title, const sf::Vector2i& windowSize)
	: m_EventManager()
{
	m_Window.create(
		sf::VideoMode(windowSize.x, windowSize.y, 32), title
	);

	m_EventManager.SetCurrentState(StateType::Intro);

	m_EventManager.RegisterBinding("Close_Window", EventType::Closed, 0);
	m_EventManager.RegisterCallback<Window>(StateType(0), "Close_Window", &Window::CloseWindow, this);
}

void Window::UpdateEvents()
{
	sf::Event event;
	while (m_Window.pollEvent(event))
	{
		m_EventManager.UpdatePoll(event);
	}
	m_EventManager.UpdateRealTime();
}

void Window::BeginDraw()
{
	m_Window.clear();
}

void Window::Draw(const sf::Drawable& drawable)
{
	m_Window.draw(drawable);
}

void Window::EndDraw()
{
	m_Window.display();
}

sf::Vector2u Window::GetSize() const
{
	return m_Window.getSize();
}

void Window::SetFullScreen(const Event& ev)
{
	std::cout << "FullScreen\n";
}

void Window::CloseWindow(const Event& event)
{
	m_ShouldClose = true;
}

bool Window::ShouldClose() const
{
	return m_ShouldClose;
}
