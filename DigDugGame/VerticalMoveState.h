#pragma once
#include <BaseState.h>
#include "Level.h"
#include <SDL.h>
#include "InputManager.h"

class VerticalMoveState final : public dae::BaseState
{
public:
	VerticalMoveState(std::shared_ptr<Level> level);
	~VerticalMoveState() override = default;

	std::shared_ptr<BaseState> Update(std::shared_ptr<dae::GameObject> gameObject, dae::BaseCommand*& commandOutput, int controller) override;

private:
	std::shared_ptr<Level> m_Level;

	dae::input m_Up{ SDLK_w, 0 };
	dae::input m_Down{ SDLK_s, 0 };
};

