#pragma once
#include "GameObject.h"
#include "structs.h"
#include "Level.h"
#include "Prefabs.h"
#include "ScoreObserver.h"

class Spawner
{
public:
	Spawner(float2 spawnPos)
		:m_Position(spawnPos)
	{}
	virtual ~Spawner(){}

	virtual std::shared_ptr<dae::GameObject> Spawn() = 0;

	std::shared_ptr<dae::GameObject> GetSpawnedObject() { return  m_SpawnedObject; }

protected:
	std::shared_ptr<dae::GameObject> m_SpawnedObject;
	float2 m_Position;
};

class DigDugSpawner final : public Spawner
{
public:
	DigDugSpawner(std::shared_ptr<Level> level, float2 characterSize, float2 spawnPos, int playerNr, std::shared_ptr<ScoreObserver> observer)
		:Spawner(spawnPos)
		,m_level(level)
		,m_characterSize(characterSize)
		,m_PlayerNr(playerNr)
		,m_ScoreObserver(observer)
	{
		
	}
	~DigDugSpawner() override {}
	
	std::shared_ptr<dae::GameObject> Spawn()
	{
		m_SpawnedObject = prefabs::GetPrefab(m_characterSize, m_level.lock(), m_PlayerNr);
		m_SpawnedObject->GetComponent<DigDugColllision>()->AddObserver(m_ScoreObserver);
		m_SpawnedObject->GetTransform().lock()->SetPosition(m_Position.x, m_Position.y, 0);
		m_SpawnedObject->GetComponent<DigDugColllision>()->SetSpawner(this);

		return m_SpawnedObject;
	}

private:
	std::weak_ptr<Level> m_level;
	std::shared_ptr<ScoreObserver> m_ScoreObserver;
	float2 m_characterSize;
	int m_PlayerNr;
};

