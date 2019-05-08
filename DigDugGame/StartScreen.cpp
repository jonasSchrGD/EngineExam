#include "pch.h"
#include "StartScreen.h"
#include "GameObject.h"
#include "TextRenderComponent.h"
#include "ResourceManager.h"
#include "MenuInputHandler.h"
#include "ChangeSceneCommand.h"
#include "ExitCommand.h"

StartScreen::StartScreen()
	:Scene("DigDug StartScreen")
{
}
StartScreen::~StartScreen()
{
}

void StartScreen::LoadScene()
{
	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	std::vector<std::shared_ptr<dae::GameObject>> buttons{};
	std::vector<std::shared_ptr<dae::BaseCommand>> commands{};

	std::shared_ptr<dae::GameObject> singlePlayer{ std::make_shared<dae::GameObject>() };
	singlePlayer->SetPosition(30, 30);
	auto comp = std::make_shared<dae::TextRenderComponent>("SinglePlayer", font);
	singlePlayer->AddComponent(comp);
	Add(singlePlayer);
	buttons.push_back(singlePlayer);
	commands.push_back(std::make_shared<dae::ChangeSceneCommand>(1));

	std::shared_ptr<dae::GameObject> coop{ std::make_shared<dae::GameObject>() };
	coop->SetPosition(30, 80);
	comp = std::make_shared<dae::TextRenderComponent>("Coop", font);
	coop->AddComponent(comp);
	Add(coop);
	buttons.push_back(coop);
	commands.push_back(std::make_shared<dae::ChangeSceneCommand>(0));

	std::shared_ptr<dae::GameObject> versus{ std::make_shared<dae::GameObject>() };
	versus->SetPosition(30, 130);
	comp = std::make_shared<dae::TextRenderComponent>("Versus", font);
	versus->AddComponent(comp);
	Add(versus);
	buttons.push_back(versus);
	commands.push_back(std::make_shared<dae::ChangeSceneCommand>(0));

	std::shared_ptr<dae::GameObject> exitButton{ std::make_shared<dae::GameObject>() };
	exitButton->SetPosition(30, 180);
	comp = std::make_shared<dae::TextRenderComponent>("exit", font);
	exitButton->AddComponent(comp);
	Add(exitButton);
	buttons.push_back(exitButton);
	commands.push_back(std::make_shared<dae::ExitCommand>());

	std::shared_ptr<dae::GameObject> inputHandler{ std::make_shared<dae::GameObject>() };
	SDL_Color unselected{255,0,0, 255}, selected{255,255,0, 255};
	auto inputHandling = std::make_shared<MenuInputHandler>(buttons, commands, unselected, selected);
	inputHandler->AddComponent(inputHandling);
	Add(inputHandler);
}
