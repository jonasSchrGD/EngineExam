#include "pch.h"
#include "ScoreSystem.h"
#include "InputManager.h"
#include "SceneManager.h"


ScoreSystem::ScoreSystem()
	:m_ScoreObserver(std::make_shared<ScoreObserver>(&m_P1Score, &m_P2Score))
{
}


ScoreSystem::~ScoreSystem()
{
}

void ScoreSystem::Update()
{
	if (m_ScoreP1Text)
		m_ScoreP1Text->SetText(std::to_string(m_P1Score));

	if (m_ScoreP2Text)
		m_ScoreP2Text->SetText(std::to_string(m_P2Score));

	if (dae::InputManager::GetInstance().IsDown(dae::input(SDLK_ESCAPE, int(dae::ControllerButton::Start)), 0))
		dae::SceneManager::GetInstance().SetActiveScene(0);
}
