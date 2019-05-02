#include "pch.h"
#include "DigDug.h"
#include "Renderer.h"
#include "SceneManager.h"
#include "StartScreen.h"

void DigDug::LoadGame() const
{
	dae::SceneManager::GetInstance().AddScene(std::make_shared<StartScreen>());
}
