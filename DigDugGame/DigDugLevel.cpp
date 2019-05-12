#include "pch.h"
#include "DigDugLevel.h"
#include "GameObject.h"
#include "RenderComponent.h"
#include "TextRenderComponent.h"
#include "SpriteRenderer.h"
#include "HorizontalMoveState.h"
#include "CharacterControllerComponent.h"
#include "ContentManager.h"
#include "IdleState.h"
#include "CollisionComponent.h"


DigDugLevel::DigDugLevel(const std::string& name, bool singlePlayer)
	:Scene(name)
	,m_SinglePlayer(singlePlayer)
{
}

DigDugLevel::~DigDugLevel()
{
}

void DigDugLevel::SetupScene()
{
	float2 characterSize{ 28, 28 };
	auto font = dae::ContentManager::GetInstance().LoadFont("Lingua.otf", 24);
	
	std::shared_ptr<dae::GameObject> level{ std::make_shared<dae::GameObject>() };
	auto renderComp = std::make_shared<dae::RenderComponent>(560, 680);
	renderComp->SetTexture("level1.png");
	level->AddComponent(renderComp);
	Add(level);

	m_level = dae::ContentManager::GetInstance().Load<Level>("MapLayout.txt");
	m_level->Initialize(characterSize, 10);
	m_level->AddToScene(shared_from_this());

	std::shared_ptr<dae::GameObject> singlePlayer{ std::make_shared<dae::GameObject>() };
	singlePlayer->SetPosition(200, 10);
	auto comp = std::make_shared<dae::TextRenderComponent>("SinglePlayer", font);
	singlePlayer->AddComponent(comp);
	Add(singlePlayer);

	std::shared_ptr<dae::GameObject> Player(std::make_shared<dae::GameObject>());
	auto spriterenderer = std::make_shared<dae::SpriteRenderer>("DigDugRun.png", 0.1f, 4, 2, 4, characterSize);
	Player->AddComponent(spriterenderer);

	auto movement = std::make_shared<IdleState>(m_level);
	auto characterController = std::make_shared<dae::CharacterControllerComponent>(movement);
	Player->AddComponent(characterController);
	auto collision = std::make_shared<dae::CollisionComponent>(characterSize.x, characterSize.y, true);
	Player->AddComponent(collision);
	Add(Player);

	Player->GetTransform().lock()->SetPosition(40 * (118 % 14), 40 * (118 / 14) + 40, 0);
}
