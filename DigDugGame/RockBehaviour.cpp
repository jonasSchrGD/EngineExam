#include "pch.h"
#include "RockBehaviour.h"
#include "GameObject.h"
#include "TunnelUpdate.h"
#include "Time.h"
#include "EnemyCollisionHandler.h"
#include "DigDugColllision.h"
#include "CharacterControllerComponent.h"

RockBehaviour::RockBehaviour(std::shared_ptr<Level> level)
	: m_Level(level)
	, m_TileBeneathe()
{
}

RockBehaviour::~RockBehaviour()
{
}

void RockBehaviour::Initialize()
{
	m_SpriteRenderer = GetGameObject()->GetComponent<dae::SpriteRenderer>();

	auto pos = GetGameObject()->GetTransform().lock()->GetPosition();
	m_TileBeneathe = m_Level->GetNextPos({ pos.x, pos.y }, { 0,1 });
}

void RockBehaviour::Update()
{
	if (m_Falling)
		GetGameObject()->GetTransform().lock()->Translate(0, 100 * dae::Time::GetInstance().DeltaTime(), 0);
	else if (m_Trigger)
	{
		GetGameObject()->GetComponent<dae::SpriteRenderer>()->SetAnimation(int(RockAnimation::Shake));
		auto character = m_Level->GetCharacterInTile(m_TileBeneathe);
		if(!character)
		{
			m_elapsed += dae::Time::GetInstance().DeltaTime();
			if (m_elapsed > m_TriggerTime)
			{
				m_Falling = true;
				m_elapsed = 0;
				m_SpriteRenderer->SetAnimation(int(RockAnimation::Idle));
				m_Trigger = false;
			}
		}
		else
			m_PlayerId = character->GetComponent<dae::CharacterControllerComponent>()->GetPlayerNr();
	}
	else if (m_Break)
	{
		GetGameObject()->GetComponent<dae::SpriteRenderer>()->SetAnimation(int(RockAnimation::Break),false);
		m_elapsed += dae::Time::GetInstance().DeltaTime();
		if (m_elapsed > m_TriggerTime)
		{
			GetGameObject()->GetScene()->Remove(GetGameObject());
		}
	}
	else
	{
		if (m_Level->IsTunnel(m_TileBeneathe))
			m_Trigger = true;
	}
}

void RockBehaviour::OnTriggerEnter(std::shared_ptr<dae::CollisionComponent> other)
{
	auto tunnel = other->GetGameObject()->GetComponent<dae::SpriteRenderer>();

	if (other->GetGameObject()->GetComponent<EnemyCollisionHandler>() || other->GetGameObject()->GetComponent<DigDugColllision>() || tunnel->GetAnimation() == int(TunnelSprite::none))
	{
		if (m_Falling)
		{
			m_Break = true;
			m_Falling = false;
		}
	}
}
