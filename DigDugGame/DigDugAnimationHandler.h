#pragma once
#include <BaseComponent.h>
#include "InputManager.h"
#include "SpriteRenderer.h"

class DigDugAnimationHandler final : public dae::BaseComponent
{
	enum class DigDugAnimation
	{
		
	};

public:
	DigDugAnimationHandler();
	~DigDugAnimationHandler();

protected:
	void Initialize() override;
	void Update() override;

private:
	dae::input m_Left{ SDLK_a, 0 };
	dae::input m_Right{ SDLK_d, 0 };
	dae::input m_Up{ SDLK_w, 0 };
	dae::input m_Down{ SDLK_s, 0 };

	std::shared_ptr<dae::SpriteRenderer> m_pSpriteRenderer;

	float m_MovementSpeed;
};

