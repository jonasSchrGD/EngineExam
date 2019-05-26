#pragma once
#include <BaseComponent.h>
#include "Subject.h"
#include "Observer.h"

class EnemyCollisionHandler final : public dae::BaseComponent
{
public:
	EnemyCollisionHandler(bool isFygar);
	~EnemyCollisionHandler();

	int GetPumpCollisionState()
	{
		if (m_PumpCollisionState == 1)
			m_Reset = true;
		return m_PumpCollisionState;
	}
	int GetPlayerKiller() const { return m_PlayerKiller; }
	bool IsKilledByRock() const { return m_KilledByRock; }
	bool IsFygar() const { return m_IsFygar; }

	void AddObserver(std::shared_ptr<dae::Observer> observer) { m_ScoreSystem.AddObserver(observer); }
	void Die();

protected:
	void OnTriggerEnter(std::shared_ptr<dae::CollisionComponent> other) override;
	void OnTriggerStay(std::shared_ptr<dae::CollisionComponent> other) override;
	void OnTriggerLeave(std::shared_ptr<dae::CollisionComponent> other) override;

	void Update() override
	{
		if (m_Reset)
		{
			m_PumpCollisionState = 0;
			m_Reset = false;
		}
	}
private:
	int m_PumpCollisionState = 0, m_PlayerKiller = -1;
	bool m_KilledByRock = false, m_Reset = false, m_IsFygar = false;

	dae::Subject m_ScoreSystem;
};
