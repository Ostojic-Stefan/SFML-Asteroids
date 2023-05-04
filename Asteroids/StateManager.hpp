#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <stack>
#include <memory>
#include <algorithm>

#include "SharedContext.hpp"
#include "BaseState.hpp"
#include "StateIntro.hpp"
#include "StateGame.hpp"

enum class StateType
{
	Intro = 1, Game, Paused, GameOver
};

class StateManager
{
public:
	StateManager(SharedContext* context);

	void Update(const sf::Time& dt);
	void Draw();

	bool RemoveState(StateType stateType);
	void SwitchTo(StateType stateType);
	SharedContext* GetContext()
	{
		return m_SharedContext;
	}
private:
	template<class T> 
	void RegisterState(StateType stateType)
	{
		auto foundItr = std::find_if(m_States.begin(), m_States.end(), 
			[stateType](std::pair<StateType, std::unique_ptr<BaseState>>& state) {
				return state.first == stateType;
			});

		if (foundItr != m_States.end())
			m_States.erase(foundItr);

		m_States.emplace_back(stateType, std::make_unique<T>(this));
	}
private:
	std::vector<std::pair<StateType, std::unique_ptr<BaseState>>> m_States;
	SharedContext* m_SharedContext;
};