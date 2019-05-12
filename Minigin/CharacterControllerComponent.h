#pragma once
#include "BaseComponent.h"
#include "BaseState.h"

namespace dae
{
	class CharacterControllerComponent final : public BaseComponent
	{
	public:
		CharacterControllerComponent(std::shared_ptr<BaseState> startState);
		~CharacterControllerComponent() override = default;

	protected:
		void Update() override;

	private:
		std::shared_ptr<BaseState> m_CurrentState;
	};
}
