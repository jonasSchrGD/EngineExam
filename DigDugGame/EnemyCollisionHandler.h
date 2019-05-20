#pragma once
#include <BaseComponent.h>
class EnemyCollisionHandler final : public dae::BaseComponent
{
public:
	EnemyCollisionHandler();
	~EnemyCollisionHandler();

protected:
	void OnTriggerEnter(std::shared_ptr<dae::CollisionComponent> other) override;
};

