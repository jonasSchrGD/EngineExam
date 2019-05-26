#include "pch.h"
#include "EnemyCollisionHandler.h"
#include "CollisionComponent.h"
#include "GameObject.h"
#include "Projectile.h"
#include "CharacterControllerComponent.h"
#include "InflatedState.h"
#include "DigDugLevel.h"
#include "RockBehaviour.h"

EnemyCollisionHandler::EnemyCollisionHandler(bool isFygar)
	:m_IsFygar(isFygar)
{
}


EnemyCollisionHandler::~EnemyCollisionHandler()
{
}

void EnemyCollisionHandler::Die()
{
	m_ScoreSystem.Notify(GetGameObject());
	GetGameObject()->GetScene()->Remove(GetGameObject());
}

void EnemyCollisionHandler::OnTriggerEnter(std::shared_ptr<dae::CollisionComponent> other)
{
	if(other->GetGameObject()->GetComponent<Projectile>())
	{
		GetGameObject()->GetComponent<dae::CharacterControllerComponent>()->SetState(std::make_shared<InflatedState>(std::static_pointer_cast<DigDugLevel>(GetGameObject()->GetScene())->GetLevel()));

		m_PlayerKiller = other->GetGameObject()->GetComponent<Projectile>()->GetPlayerNr();

		m_PumpCollisionState = 1;
	}
	auto rock = other->GetGameObject()->GetComponent<RockBehaviour>();
	if(rock)
	{
		m_KilledByRock = true;
		m_PlayerKiller = rock->GetInteractedPlayer();
		Die();
	}
}

void EnemyCollisionHandler::OnTriggerStay(std::shared_ptr<dae::CollisionComponent> other)
{
	if (other->GetGameObject()->GetComponent<Projectile>())
	{
		m_PlayerKiller = other->GetGameObject()->GetComponent<Projectile>()->GetPlayerNr();
		m_PumpCollisionState = 2;
	}
}

void EnemyCollisionHandler::OnTriggerLeave(std::shared_ptr<dae::CollisionComponent> other)
{
	if (m_PumpCollisionState == 2)
	{
		m_PumpCollisionState = 0;
	}
}
