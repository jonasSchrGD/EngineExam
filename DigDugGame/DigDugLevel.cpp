#include "pch.h"
#include "DigDugLevel.h"
#include "GameObject.h"
#include "RenderComponent.h"
#include "HorizontalMoveState.h"
#include "ContentManager.h"
#include "CollisionComponent.h"
#include "Prefabs.h"
#include "Spawner.h"
#include "RockBehaviour.h"
#include "TextRenderComponent.h"
#include "ScoreSystem.h"
#include "SelectedLevel.h"


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
	std::shared_ptr<dae::GameObject> level{ std::make_shared<dae::GameObject>() };
	auto renderComp = std::make_shared<dae::RenderComponent>(560, 680);
	renderComp->SetTexture("DigDugBackGround.png");
	level->AddComponent(renderComp);
	Add(level);

	AddUi();
}

void DigDugLevel::LoadScene()
{
	Scene::LoadScene();
	m_level = dae::ContentManager::GetInstance().Load<Level>("MapLayout" + std::to_string(SelectedLevel::GetInstance().selectedLevel) + ".txt");
	m_level->Initialize(m_characterSize, 10);
	m_level->AddToScene(shared_from_this());

	SpawnCharacters();
	m_ScoreSystem->ResetPoints();
}

void DigDugLevel::UnloadScene()
{
	Scene::UnloadScene();
	m_level->RemoveFromScene(shared_from_this());

	for (auto fygar : m_Fygars)
	{
		if(!fygar.expired())
			Remove(fygar.lock());
	}
	m_Fygars.clear();
	for (auto pooka : m_Pookas)
	{
		if (!pooka.expired())
			Remove(pooka.lock());
	}
	m_Pookas.clear();
	for (auto rock : m_Rocks)
	{
		if (!rock.expired())
			Remove(rock.lock());
	}
	m_Rocks.clear();

	if (m_DigDugSpawn1 != nullptr)
	{
		Remove(m_DigDugSpawn1->GetSpawnedObject());
		delete m_DigDugSpawn1;
		m_DigDugSpawn1 = nullptr;
	}

	if (m_DigDugSpawn2 != nullptr)
	{
		Remove(m_DigDugSpawn2->GetSpawnedObject());
		delete m_DigDugSpawn2;
		m_DigDugSpawn2 = nullptr;
	}
}

void DigDugLevel::SpawnCharacters()
{
	auto pookaSpawns = m_level->GetPookaSpawns();
	int enemyCount{};
	for (float2 spawn : pookaSpawns)
	{
		std::shared_ptr<dae::GameObject> pooka(prefabs::GetPrefab(m_characterSize, m_level, false));
		pooka->GetTransform().lock()->SetPosition(spawn.x, spawn.y, 0);
		pooka->GetComponent<EnemyCollisionHandler>()->AddObserver(m_ScoreObserver);
		m_Pookas.push_back(pooka);
		Add(pooka);
		enemyCount++;
	}

	auto fygarSpawns = m_level->GetFygarSpawns(!m_Coop);
	for (float2 spawn : fygarSpawns)
	{
		std::shared_ptr<dae::GameObject> fygar(prefabs::GetPrefab(m_characterSize, m_level, false, -1, false));
		fygar->GetTransform().lock()->SetPosition(spawn.x, spawn.y, 0);
		fygar->GetComponent<EnemyCollisionHandler>()->AddObserver(m_ScoreObserver);
		m_Fygars.push_back(fygar);
		Add(fygar);
		enemyCount++;
	}
	m_ScoreObserver->SetEnemyCount(enemyCount);

	auto rockSpawns = m_level->GetRockSpawns();
	for (float2 spawn : rockSpawns)
	{
		std::shared_ptr<dae::GameObject> rock = std::make_shared<dae::GameObject>();
		rock->GetTransform().lock()->SetPosition(spawn.x, spawn.y, 0);

		auto spriterenderer = std::make_shared<dae::SpriteRenderer>("Rock.png", 0.2f, 5, 1, 3, float2{30,30});
		spriterenderer->SetFramesPerAnim(std::vector<int>{2, 1, 2});
		spriterenderer->SetAnimation((int)RockAnimation::Idle, false);
		rock->AddComponent(spriterenderer);
	
		auto behavior = std::make_shared<RockBehaviour>(m_level);
		rock->AddComponent(behavior);

		auto collision = std::make_shared<dae::CollisionComponent>(30.f ,30.f, true);
		collision->SetTrigger(true);
		rock->AddComponent(collision);

		m_Rocks.push_back(rock);
		Add(rock);
	}

	if(m_SinglePlayer)
	{
		auto spawn = m_level->GetDigDugSpawn();
		m_DigDugSpawn1 = new DigDugSpawner(m_level, m_characterSize, spawn, 0, m_ScoreObserver);
		Add(m_DigDugSpawn1->Spawn());
	}
	else if(m_Coop)
	{
		auto spawn = m_level->GetCoopSpawn(true);
		m_DigDugSpawn1 = new DigDugSpawner(m_level, m_characterSize, spawn, 0, m_ScoreObserver);
		Add(m_DigDugSpawn1->Spawn());

		spawn = m_level->GetCoopSpawn(false);
		m_DigDugSpawn2 = new DigDugSpawner(m_level, m_characterSize, spawn, 1, m_ScoreObserver);
		Add(m_DigDugSpawn2->Spawn());
	}
	else
	{
		auto spawn = m_level->GetVersusSpawn();
		m_DigDugSpawn1 = new DigDugSpawner(m_level, m_characterSize, spawn, 0, m_ScoreObserver);
		Add(m_DigDugSpawn1->Spawn());

		std::shared_ptr<dae::GameObject> Player2(prefabs::GetPrefab(m_characterSize, m_level, true, 1, false));
		Player2->GetComponent<EnemyCollisionHandler>()->AddObserver(m_ScoreObserver);
		Add(Player2);
		spawn = m_level->GetVersusSpawn(true);
		Player2->GetTransform().lock()->SetPosition(spawn.x, spawn.y, 0);
	}
}

void DigDugLevel::AddUi()
{
	std::shared_ptr<dae::GameObject> scoreSystem{ std::make_shared<dae::GameObject>() };
	m_ScoreSystem = std::make_shared<ScoreSystem>();
	m_ScoreObserver = m_ScoreSystem->GetBoundObserver();
	scoreSystem->AddComponent(m_ScoreSystem);
	Add(scoreSystem);

	auto font = dae::ContentManager::GetInstance().LoadFont("Lingua.otf", 24);

	std::shared_ptr<dae::GameObject> scoreText{ std::make_shared<dae::GameObject>() };
	auto textRenderer = std::make_shared<dae::TextRenderComponent>("Score: p1", font);
	scoreText->AddComponent(textRenderer);
	scoreText->SetPosition(10, 20);
	Add(scoreText);

	std::shared_ptr<dae::GameObject> score{ std::make_shared<dae::GameObject>() };
	textRenderer = std::make_shared<dae::TextRenderComponent>("0", font);
	score->AddComponent(textRenderer);
	score->SetPosition(10, 40);
	Add(score);
	m_ScoreSystem->SetTextP1(textRenderer);

	if (!m_SinglePlayer)
	{
		scoreText = std::make_shared<dae::GameObject>();
		textRenderer = std::make_shared<dae::TextRenderComponent>("Score: p2", font);
		scoreText->AddComponent(textRenderer);
		scoreText->GetTransform().lock()->SetPosition(450, 20, 0);
		Add(scoreText);

		score = std::make_shared<dae::GameObject>();
		textRenderer = std::make_shared<dae::TextRenderComponent>("0", font);
		m_ScoreSystem->SetTextP2(textRenderer);
		score->AddComponent(textRenderer);
		score->GetTransform().lock()->SetPosition(450, 40, 0);
		Add(score);
	}
}
