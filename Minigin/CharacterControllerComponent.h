#pragma once
#include "BaseComponent.h"
#include "BaseState.h"

namespace dae
{
	class CharacterControllerComponent final : public BaseComponent
	{
	public:
		CharacterControllerComponent(std::shared_ptr<BaseState> startState, int playerNr);
		~CharacterControllerComponent() override {  if(m_pCurrentCommand != nullptr)delete m_pCurrentCommand; }

		int GetPlayerNr() const { return m_PlayerNr; }

		void SetState(std::shared_ptr<BaseState> state) { m_CurrentState = state; }

	protected:
		void Update() override;

	private:
		std::shared_ptr<BaseState> m_CurrentState;
		BaseCommand* m_pCurrentCommand;
		int m_PlayerNr;
	};
}
