#pragma once
#include <BaseComponent.h>
#include "SpriteRenderer.h"
#include "Animations.h"

class TunnelUpdate final : public dae::BaseComponent
{
public:
	TunnelUpdate();
	~TunnelUpdate() override = default;

protected:
	void OnTriggerEnter(std::shared_ptr<dae::CollisionComponent> other) override;
	void OnTriggerStay(std::shared_ptr<dae::CollisionComponent> other) override;

	void Initialize() override;

private:
	std::shared_ptr<dae::SpriteRenderer> m_SpriteRenderer;
	float2 m_Center;

	void UpdateDown(std::shared_ptr<dae::GameObject> other, const TunnelSprite& currentSprite, float distanceToCenter);
	void UpdateUp(std::shared_ptr<dae::GameObject> other, const TunnelSprite& currentSprite, float distanceToCenter);
	void UpdateLeft(std::shared_ptr<dae::GameObject> other, const TunnelSprite& currentSprite, float distanceToCenter);
	void UpdateRight(std::shared_ptr<dae::GameObject> other, const TunnelSprite& currentSprite, float distanceToCenter);
};

