#pragma once
#include <Scene.h>
#include "Level.h"
#include "Spawner.h"
#include "ScoreObserver.h"
#include "ScoreSystem.h"

class DigDugLevel : public dae::Scene
{
public:
	DigDugLevel(const std::string& name, bool singlePlayer = true, bool coop = true);
	~DigDugLevel();

	void SetupScene() override;

	void LoadScene() override;
	void UnloadScene() override;

	std::shared_ptr<Level> GetLevel() const { return m_level; }

private:
	std::shared_ptr<Level> m_level;
	std::shared_ptr<ScoreSystem> m_ScoreSystem;
	std::shared_ptr<ScoreObserver> m_ScoreObserver;
	std::vector<std::weak_ptr<dae::GameObject>> m_Pookas;
	std::vector<std::weak_ptr<dae::GameObject>> m_Fygars;
	std::vector<std::weak_ptr<dae::GameObject>> m_Rocks;
	float2 m_characterSize;
	bool m_SinglePlayer, m_Coop;

	DigDugSpawner *m_DigDugSpawn1, *m_DigDugSpawn2;

	void SpawnCharacters();
	void AddUi();
};

