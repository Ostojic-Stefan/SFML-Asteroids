#pragma once
#include "BaseState.hpp"
#include "SharedContext.hpp"

class StateIntro : public BaseState
{
public:
	StateIntro(StateManager* stateManager);

	// Inherited via BaseState
	virtual void OnCreate() override;
	virtual void OnDestroy() override;
	virtual void Update(const sf::Time& time) override;
	virtual void Draw() override;

private:
	void ChangeToGame(const Event& event);
private:
	sf::Font* m_Font;
	sf::Text m_Text;
};