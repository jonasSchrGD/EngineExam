#pragma once
#include <Scene.h>

class DigDugLevel : public dae::Scene
{
public:
	DigDugLevel(const std::string& name, bool singlePlayer = true);
	~DigDugLevel();

	void Initialize() override;
};

