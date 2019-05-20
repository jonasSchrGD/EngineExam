#pragma once
#include <BaseState.h>
#include "Level.h"

class WanderState final : public dae::BaseState
{
public:
	WanderState(std::shared_ptr<Level> level);
	~WanderState();

	std::shared_ptr<BaseState> Update(std::shared_ptr<dae::GameObject> gameObject, dae::BaseCommand*& commandOutput) override;

private:
	std::shared_ptr<Level> m_Level;
	float2 m_NewPos;

	bool IsInRange(float2 pos);
};

