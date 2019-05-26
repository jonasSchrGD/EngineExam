#pragma once
#include <BaseState.h>
class DigDugDeath :	public dae::BaseState
{
public:
	DigDugDeath();
	~DigDugDeath();

	std::shared_ptr<BaseState> Update(std::shared_ptr<dae::GameObject> gameObject, dae::BaseCommand*& commandOutput, int controller) override;
};

