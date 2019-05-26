#pragma once
#include <BaseComponent.h>
#include "structs.h"
#include "GameObject.h"
#include "CharacterControllerComponent.h"
#include "InputManager.h"

class Projectile final : public dae::BaseComponent
{
public:
	//a normalize direction is expected
	Projectile(int2 direction);
	~Projectile();

	void SetOwner(std::shared_ptr<dae::GameObject> owner) { m_PlayerNr = owner->GetComponent<dae::CharacterControllerComponent>()->GetPlayerNr(); }
	int GetPlayerNr() const { return m_PlayerNr; }

protected:
	void Update() override;

	void Initialize() override;
	void OnTriggerEnter(std::shared_ptr<dae::CollisionComponent> other) override;

private:
	dae::input m_Select{ SDLK_SPACE, (int)dae::ControllerButton::A };
	const float m_MaxDistance, m_velocity;
	bool m_Hit = false;
	float m_Distance;
	int2 m_Direction;

	int m_PlayerNr;
};

