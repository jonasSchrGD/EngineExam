#pragma once
#include <Scene.h>
#include "Level.h"
#include "Spawner.h"

class DigDugLevel : public dae::Scene
{
public:
	DigDugLevel(const std::string& name, bool singlePlayer = true, bool coop = true);
	~DigDugLevel();

	void SetupScene() override;

private:
	std::shared_ptr<Level> m_level;
	float2 m_characterSize;
	bool m_SinglePlayer, m_Coop;

	DigDugSpawner *m_DigDugSpawn1, *m_DigDugSpawn2;

	void SpawnCharacters();
};

