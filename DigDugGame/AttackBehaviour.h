#pragma once
#include <BaseComponent.h>
#include "InputManager.h"

class AttackBehaviour final : public dae::BaseComponent
{
public:
	AttackBehaviour();
	~AttackBehaviour();

protected:
	void Update() override;
	void Initialize() override;

private:
	dae::input m_Select{ SDLK_SPACE, (int)dae::ControllerButton::A };
	int m_Controller;
	bool m_IsDigDug;
};

