#include "pch.h"
#include "ScoreObserver.h"
#include "EnemyCollisionHandler.h"
#include "ContentManager.h"
#include "DigDugColllision.h"
#include "SceneManager.h"
#include "AttackBehaviour.h"
#include "SelectedLevel.h"


ScoreObserver::ScoreObserver(int *p1Score, int *p2Score)
	:m_P1Score(p1Score)
	,m_P2Score(p2Score)
{
}

ScoreObserver::~ScoreObserver()
{
}

void ScoreObserver::Notify(std::shared_ptr<dae::GameObject> gameObject)
{
	auto enemy = gameObject->GetComponent<EnemyCollisionHandler>();
	auto level = dae::ContentManager::GetInstance().Load<Level>("MapLayout" + std::to_string(SelectedLevel::GetInstance().selectedLevel) + ".txt");

 	if(enemy && enemy->GetPlayerKiller() == 0)
	{
		int score{};

		if(enemy->IsKilledByRock())
		{
			m_P1KillCount++;
			score = GetKillCountScore(m_P1KillCount);
		}
		else
		{
			int layer{level->GetLayer(gameObject->GetTransform().lock()->GetPosition().y)};
			bool isFygar{ enemy->IsFygar() };

			score = (100 + (100 * layer)) * (1 + isFygar);
		}

		*m_P1Score += score;
		if (!enemy->GetGameObject()->GetComponent<AttackBehaviour>())
			m_EnemyCount--;
		 if(m_EnemyCount == 0)
			 dae::SceneManager::GetInstance().SetActiveScene(0);
	}
	else if(enemy && enemy->GetPlayerKiller() == 1)
	{
		int score{};

		if (enemy->IsKilledByRock())
		{
			m_P2KillCount++;
			score = GetKillCountScore(m_P2KillCount);
		}
		else
		{
			int layer{ level->GetLayer(gameObject->GetTransform().lock()->GetPosition().y) };
			bool isFygar{ enemy->IsFygar() };

			score = (100 + (100 * layer)) * (1 + isFygar);
		}
		
		*m_P2Score += score;
		if (!enemy->GetGameObject()->GetComponent<AttackBehaviour>())
			m_EnemyCount--;
		if (m_EnemyCount == 0)
			dae::SceneManager::GetInstance().SetActiveScene(0);
	}
	else//versus
	{
		if(gameObject->GetComponent<DigDugColllision>() && gameObject->GetComponent<DigDugColllision>()->KilledByPlayer())
			*m_P2Score += 500;
	}
}

int ScoreObserver::GetKillCountScore(int killcount)
{
	if (killcount == 1)
		return 1000;
	if (killcount == 2)
		return 2500;
	if (killcount == 3)
		return 4000;
	if (killcount == 4)
		return 6000;
	if (killcount == 5)
		return 8000;
	if (killcount == 6)
		return 10000;
	if (killcount == 7)
		return 12000;
	if (killcount == 8)
		return 15000;
	return 0;
}
