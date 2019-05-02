#include "pch.h"
#include "StartScreen.h"
#include "GameObject.h"
#include "TextRenderComponent.h"
#include "ResourceManager.h"
#include "MenuInputHandler.h"

StartScreen::StartScreen()
	:Scene("DigDug StartScreen")
{
}
StartScreen::~StartScreen()
{
}

void StartScreen::Initialize()
{
	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	std::vector<std::shared_ptr<dae::GameObject>> buttons{};
	std::vector<std::shared_ptr<dae::Command>> commands{};

	std::shared_ptr<dae::GameObject> StartButton{ std::make_shared<dae::GameObject>() };
	StartButton->SetPosition(30, 30);
	auto comp = std::make_shared<dae::TextRenderComponent>("Start", font);
	StartButton->AddComponent(comp);
	Add(StartButton);
	buttons.push_back(StartButton);

	std::shared_ptr<dae::GameObject> optionsButton{ std::make_shared<dae::GameObject>() };
	optionsButton->SetPosition(30, 80);
	comp = std::make_shared<dae::TextRenderComponent>("options", font);
	optionsButton->AddComponent(comp);
	Add(optionsButton);
	buttons.push_back(optionsButton);

	std::shared_ptr<dae::GameObject> inputHandler{ std::make_shared<dae::GameObject>() };
	auto inputHandling = std::make_shared<MenuInputHandler>(buttons, commands);
	inputHandler->AddComponent(inputHandling);
	Add(inputHandler);
}
