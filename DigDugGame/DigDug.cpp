#include "pch.h"
#include "DigDug.h"
#include "Renderer.h"
#include "SceneManager.h"
#include "DemoScene.h"

void DigDug::LoadGame() const
{
	dae::SceneManager::GetInstance().AddScene(std::make_shared<dae::DemoScene>("demo"));
}
