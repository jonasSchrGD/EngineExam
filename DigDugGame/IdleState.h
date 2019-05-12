#pragma once
#include <BaseState.h>
#include "Level.h"
#include <SDL.h>
#include "InputManager.h"

class IdleState final : public dae::BaseState
{
public:
	IdleState(std::shared_ptr<Level> level);
	~IdleState() override = default;

	std::shared_ptr<BaseState> Update(std::shared_ptr<dae::GameObject> gameObject, dae::BaseCommand*& commandOutput) override;

private:
	std::shared_ptr<Level> m_Level;

	dae::input m_Left{ SDLK_a, 0 };
	dae::input m_Right{ SDLK_d, 0 };

	dae::input m_Up{ SDLK_w, 0 };
	dae::input m_Down{ SDLK_s, 0 };
};

