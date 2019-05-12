#pragma once
#include <Scene.h>
#include "Level.h"

class DigDugLevel : public dae::Scene
{
public:
	DigDugLevel(const std::string& name, bool singlePlayer = true);
	~DigDugLevel();

	void SetupScene() override;

private:
	std::shared_ptr<Level> m_level;
	bool m_SinglePlayer;
};

