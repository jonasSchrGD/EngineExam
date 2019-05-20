#pragma once
#include <BaseComponent.h>
#include "CollisionComponent.h"
#include "Level.h"
#include "SpriteRenderer.h"

class RockBehaviour final : public dae::BaseComponent
{
public:
	RockBehaviour(std::shared_ptr<Level> level);
	~RockBehaviour();

protected:
	void Initialize() override;
	void Update() override;
	void OnCollisionEnter(std::shared_ptr<dae::CollisionComponent> other) override;
	void OnTriggerEnter(std::shared_ptr<dae::CollisionComponent> other) override;

private:
	std::shared_ptr<dae::SpriteRenderer> m_SpriteRenderer;
	std::shared_ptr<Level> m_Level;
	float m_TriggerTime = 2.0f, m_elapsed = 0, m_BreakTime = 1;
	bool m_Falling = false, m_Trigger = false, m_Break = false;
};

