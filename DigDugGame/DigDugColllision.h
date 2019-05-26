#pragma once
#include <BaseComponent.h>
#include "Subject.h"
#include "Observer.h"

class DigDugSpawner;
class DigDugColllision final : public dae::BaseComponent
{
public:
	DigDugColllision();
	~DigDugColllision();

	void SetSpawner(DigDugSpawner* spawner) { m_Spawner = spawner; }
	void SetDigging(bool digging);
	bool GetDigging() const { return m_IsDigging; }

	bool KilledByPlayer() const { return m_KilledByPlayer; }

	void AddObserver(std::shared_ptr<dae::Observer> observer) { m_Subject.AddObserver(observer); }

protected:
	void Update() override;

	void OnTriggerEnter(std::shared_ptr<dae::CollisionComponent> other) override;

private:
	dae::Subject m_Subject;
	DigDugSpawner* m_Spawner;
	float m_DeathTimer = 0.8f;
	bool m_IsDigging, m_ChangedThisFrame, m_Dead = false, m_KilledByPlayer = false;
};

