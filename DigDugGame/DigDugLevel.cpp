#include "pch.h"
#include "DigDugLevel.h"
#include "GameObject.h"
#include "RenderComponent.h"
#include "TextRenderComponent.h"
#include "ResourceManager.h"


DigDugLevel::DigDugLevel(const std::string& name, bool singlePlayer)
	:Scene(name)
{
	UNREFERENCED_PARAMETER(singlePlayer);
}


DigDugLevel::~DigDugLevel()
{
}

void DigDugLevel::Initialize()
{
	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	
	std::shared_ptr<dae::GameObject> level{ std::make_shared<dae::GameObject>() };
	level->SetPosition(30, 30);
	auto renderComp = std::make_shared<dae::RenderComponent>();
	renderComp->SetTexture("logo.png");
	level->AddComponent(renderComp);
	Add(level);

	std::shared_ptr<dae::GameObject> singlePlayer{ std::make_shared<dae::GameObject>() };
	singlePlayer->SetPosition(30, 30);
	auto comp = std::make_shared<dae::TextRenderComponent>("SinglePlayer", font);
	singlePlayer->AddComponent(comp);
	Add(singlePlayer);
}
