#include "pch.h"
#include "DigDugLevel.h"
#include "GameObject.h"
#include "RenderComponent.h"
#include "HorizontalMoveState.h"
#include "ContentManager.h"
#include "CollisionComponent.h"
#include "Prefabs.h"
#include "Spawner.h"


DigDugLevel::DigDugLevel(const std::string& name, bool singlePlayer, bool coop)
	: Scene(name)
	, m_characterSize({28, 28})
	, m_SinglePlayer(singlePlayer)
	, m_Coop(coop)
	, m_DigDugSpawn1(nullptr)
	, m_DigDugSpawn2(nullptr)
{
}

DigDugLevel::~DigDugLevel()
{
	if (m_DigDugSpawn1 != nullptr)
		delete m_DigDugSpawn1;

	if (m_DigDugSpawn2 != nullptr)
		delete m_DigDugSpawn2;
}

void DigDugLevel::SetupScene()
{
	auto font = dae::ContentManager::GetInstance().LoadFont("Lingua.otf", 24);
	
	std::shared_ptr<dae::GameObject> level{ std::make_shared<dae::GameObject>() };
	auto renderComp = std::make_shared<dae::RenderComponent>(560, 680);
	renderComp->SetTexture("DigDugBackGround.png");
	level->AddComponent(renderComp);
	Add(level);

	m_level = dae::ContentManager::GetInstance().Load<Level>("MapLayout.txt");
	m_level->Initialize(m_characterSize, 10);
	m_level->AddToScene(shared_from_this());

	SpawnCharacters();
}

void DigDugLevel::SpawnCharacters()
{
	auto pookaSpawns = m_level->GetPookaSpawns(!m_Coop);
	for (float2 spawn : pookaSpawns)
	{
		std::shared_ptr<dae::GameObject> pooka(prefabs::GetPrefab(m_characterSize, m_level, false));
		Add(pooka);
		pooka->GetTransform().lock()->SetPosition(spawn.x, spawn.y, 0);
	}

	auto fygarSpawns = m_level->GetFygarSpawns(!m_Coop);
	for (float2 spawn : fygarSpawns)
	{
		std::shared_ptr<dae::GameObject> fygar(prefabs::GetPrefab(m_characterSize, m_level, false, -1, false));
		Add(fygar);
		fygar->GetTransform().lock()->SetPosition(spawn.x, spawn.y, 0);
	}

	if(m_SinglePlayer)
	{
		auto spawn = m_level->GetDigDugSpawn();
		m_DigDugSpawn1 = new DigDugSpawner(m_level, m_characterSize, spawn, 0);
		Add(m_DigDugSpawn1->Spawn());
	}
	else if(m_Coop)
	{
		auto spawn = m_level->GetCoopSpawn(true);
		m_DigDugSpawn1 = new DigDugSpawner(m_level, m_characterSize, spawn, 0);
		Add(m_DigDugSpawn1->Spawn());

		spawn = m_level->GetCoopSpawn(false);
		m_DigDugSpawn2 = new DigDugSpawner(m_level, m_characterSize, spawn, 1);
		Add(m_DigDugSpawn2->Spawn());
	}
	else
	{
		auto spawn = m_level->GetVersusSpawn();
		m_DigDugSpawn1 = new DigDugSpawner(m_level, m_characterSize, spawn, 0);
		Add(m_DigDugSpawn1->Spawn());

		std::shared_ptr<dae::GameObject> Player2(prefabs::GetPrefab(m_characterSize, m_level, true, 1, false));
		Add(Player2);
		spawn = m_level->GetVersusSpawn();
		Player2->GetTransform().lock()->SetPosition(spawn.x, spawn.y, 0);
	}
}
