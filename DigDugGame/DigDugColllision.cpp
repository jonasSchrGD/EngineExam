#include "pch.h"
#include "DigDugColllision.h"
#include "CollisionComponent.h"
#include "GameObject.h"
#include "EnemyCollisionHandler.h"
#include "TunnelUpdate.h"
#include "CharacterControllerComponent.h"
#include "Spawner.h"
#include "Time.h"

DigDugColllision::DigDugColllision()
	: m_Spawner(nullptr)
	, m_IsDigging(false)
	, m_ChangedThisFrame(false)
{
}


DigDugColllision::~DigDugColllision()
{

}

void DigDugColllision::SetDigging(bool digging)
{
	if (!m_ChangedThisFrame || !m_IsDigging)
	{
		m_IsDigging = digging;
		m_ChangedThisFrame = true;
	}
}

void DigDugColllision::OnTriggerEnter(std::shared_ptr<dae::CollisionComponent> other)
{
	auto enemy = other->GetGameObject()->GetComponent<EnemyCollisionHandler>();

	if (enemy)
	{
		auto spriterenderer = GetGameObject()->GetComponent<dae::SpriteRenderer>();
		spriterenderer->SetAnimation((int)DigDugAnimation::death, false);

		GetGameObject()->RemoveComponent(GetGameObject()->GetComponent<dae::CharacterControllerComponent>());
		GetGameObject()->RemoveComponent(GetGameObject()->GetComponent<dae::CollisionComponent>());

		m_Dead = true;
		return;
	}
}

void DigDugColllision::Update()
{
	m_ChangedThisFrame = false;

	if(m_Dead)
	{
		m_DeathTimer -= dae::Time::GetInstance().DeltaTime();
		if(m_DeathTimer <= 0)
		{
			GetGameObject()->GetScene()->Remove(GetGameObject());
			GetGameObject()->GetScene()->Add(m_Spawner->Spawn());
		}
	}
}
