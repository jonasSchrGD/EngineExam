#pragma once
#include "BaseState.h"
#include <SDL.h>
#include "InputManager.h"
#include "Level.h"

class HorizontalMoveState final : public dae::BaseState
{
public:
	HorizontalMoveState(std::shared_ptr<Level> level);
	~HorizontalMoveState() override = default;

	std::shared_ptr<BaseState> Update(std::shared_ptr<dae::GameObject> gameObject, dae::BaseCommand*& commandOutput, int controller) override;

private:
	std::shared_ptr<Level> m_Level;
	dae::input m_Left{ SDLK_a, 0 };
	dae::input m_Right{ SDLK_d, 0 };
};

