#include "StateManager.hpp"

StateManager::StateManager(SharedContext* context)
	: m_SharedContext(context)
{
	RegisterState<StateIntro>(StateType::Intro);
	RegisterState<StateGame>(StateType::Game);
}

void StateManager::Update(const sf::Time& dt)
{
	if (m_States.empty()) return;
	std::unique_ptr<BaseState>& stateToUpdate = m_States.back().second;
	stateToUpdate->Update(sf::Time());
}

void StateManager::Draw()
{
	if (m_States.empty()) return;
	std::unique_ptr<BaseState>& stateToUpdate = m_States.back().second;
	stateToUpdate->Draw();
}

bool StateManager::RemoveState(StateType stateType)
{
	return std::erase_if(m_States, [stateType](const auto& state)
		{
			return stateType == state.first;
		}) > 0;
}

void StateManager::SwitchTo(StateType stateType)
{
	if (m_States.back().first == stateType)
		return;

	for (auto itr = m_States.begin(); itr != m_States.end(); ++itr)
	{
		if (itr->first == stateType)
		{
			StateType tmpType = itr->first;
			std::unique_ptr<BaseState> tmpState = std::move(itr->second);
			m_States.erase(itr);
			m_States.emplace_back(tmpType, std::move(tmpState));
			//m_States.back().second->Activate();
			return;
		}
	}
}
