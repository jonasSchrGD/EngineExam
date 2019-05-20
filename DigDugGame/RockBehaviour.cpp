#include "pch.h"
#include "RockBehaviour.h"
#include "GameObject.h"
#include "TunnelUpdate.h"
#include "Time.h"

RockBehaviour::RockBehaviour(std::shared_ptr<Level> level)
	:m_Level(level)
{
}

RockBehaviour::~RockBehaviour()
{
}

void RockBehaviour::Initialize()
{
	m_SpriteRenderer = GetGameObject()->GetComponent<dae::SpriteRenderer>();
}

void RockBehaviour::Update()
{
	//todo: states
	if (m_Falling)
		GetGameObject()->GetTransform().lock()->Translate(0, -9.81f * dae::Time::GetInstance().DeltaTime(), 0);
	else if (m_Trigger)
	{
		//todo: spriterederer => shakeanimation
		m_elapsed += dae::Time::GetInstance().DeltaTime();
		if (m_elapsed > m_TriggerTime)
		{
			m_Falling = true;
			m_elapsed = 0;
		}
	}
	else if (m_Break)
	{
		//todo: spriterederer => breakanimation
		m_elapsed += dae::Time::GetInstance().DeltaTime();
		if (m_elapsed > m_TriggerTime)
		{
			GetGameObject()->GetScene()->Remove(GetGameObject());
		}
		else
		{
			auto startpos = GetGameObject()->GetTransform().lock()->GetPosition();
			float2 pos{ startpos.x, startpos.y - m_Level->GetTileSize().y };
			if (m_Level->IsTunnel(pos))
				m_Trigger = true;
		}
	}
}

void RockBehaviour::OnCollisionEnter(std::shared_ptr<dae::CollisionComponent> other)
{
	m_Falling = false;
	m_Break = true;
}

void RockBehaviour::OnTriggerEnter(std::shared_ptr<dae::CollisionComponent> other)
{
	auto tunnel = other->GetGameObject()->GetComponent<dae::SpriteRenderer>();

	if (tunnel->GetAnimation() == int(TunnelSprite::none))
		m_Falling = false;

	//todo: enemy check
}

