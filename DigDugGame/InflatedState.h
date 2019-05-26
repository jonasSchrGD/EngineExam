#pragma once
#include <BaseState.h>
#include "Level.h"

class InflatedState final : public dae::BaseState
{
public:
	InflatedState(std::shared_ptr<Level> level);
	~InflatedState();

	std::shared_ptr<BaseState> Update(std::shared_ptr<dae::GameObject> gameObject, dae::BaseCommand*& commandOutput, int controller) override;
private:
	std::shared_ptr<Level> m_Level;
	const float m_TimePerStep = 0.25f;
	float m_Elapsed = 0;
	int m_Progress = 0;
};

