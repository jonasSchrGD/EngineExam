#include "pch.h"
#include "DigDug.h"
#include "SceneManager.h"
#include "StartScreen.h"
#include "DigDugLevel.h"
#include "ContentManager.h"
#include "LevelLoader.h"

void DigDug::LoadGame() const
{
	dae::SceneManager::GetInstance().AddScene(std::make_shared<StartScreen>());
	dae::SceneManager::GetInstance().AddScene(std::make_shared<DigDugLevel>("SinglePlayer"));
}

void DigDug::InitializeCustomLoaders()
{
	dae::ContentManager::GetInstance().AddLoader(std::make_shared<LevelLoader>());
}
