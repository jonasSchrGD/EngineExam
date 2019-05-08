#include "pch.h"
#include "DigDugLevel.h"
#include "GameObject.h"
#include "RenderComponent.h"
#include "TextRenderComponent.h"
#include "ResourceManager.h"
#include "SpriteRenderer.h"
#include "DigDugAnimationHandler.h"


DigDugLevel::DigDugLevel(const std::string& name, bool singlePlayer)
	:Scene(name)
{
	UNREFERENCED_PARAMETER(singlePlayer);
}


DigDugLevel::~DigDugLevel()
{
}

void DigDugLevel::LoadScene()
{
	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 24);
	
	std::shared_ptr<dae::GameObject> level{ std::make_shared<dae::GameObject>() };
	auto renderComp = std::make_shared<dae::RenderComponent>(560, 680);
	renderComp->SetTexture("level1.png");
	level->AddComponent(renderComp);
	Add(level);

	std::shared_ptr<dae::GameObject> singlePlayer{ std::make_shared<dae::GameObject>() };
	singlePlayer->SetPosition(200, 10);
	auto comp = std::make_shared<dae::TextRenderComponent>("SinglePlayer", font);
	singlePlayer->AddComponent(comp);
	Add(singlePlayer);

	std::shared_ptr<dae::GameObject> Player(std::make_shared<dae::GameObject>());
	auto spriterenderer = std::make_shared<dae::SpriteRenderer>("DigDugRun.png", 0.1f, 4, 2, 4, float2{32, 32});
	auto movement = std::make_shared<DigDugAnimationHandler>();
	Player->AddComponent(spriterenderer);
	Player->AddComponent(movement);
	Add(Player);
}
