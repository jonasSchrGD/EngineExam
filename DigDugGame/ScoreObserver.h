#pragma once
#include "Observer.h"
#include "Level.h"

class ScoreObserver final : public dae::Observer
{
public:
	ScoreObserver(int *p1Score, int *p2Score);
	~ScoreObserver();

	void Notify(std::shared_ptr<dae::GameObject>) override;

	void SetEnemyCount(int enemyCount) { m_EnemyCount = enemyCount; }

private:
	int GetKillCountScore(int killcount);
	int *m_P1Score, *m_P2Score;
	int m_P1KillCount = 0, m_P2KillCount = 0, m_EnemyCount = 0;
};

