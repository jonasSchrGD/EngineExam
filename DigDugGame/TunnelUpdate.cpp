#include "pch.h"
#include "TunnelUpdate.h"
#include "GameObject.h"
#include "CollisionComponent.h"
#include "Animations.h"

TunnelUpdate::TunnelUpdate()
	: m_Center()
{
}

void TunnelUpdate::OnTriggerEnter(std::shared_ptr<dae::CollisionComponent> other)
{
	TunnelSprite animation = TunnelSprite(m_SpriteRenderer->GetAnimation());
	if (animation != TunnelSprite::all)
	{
		auto& pos = other->GetGameObject()->GetTransform().lock()->GetPosition();
		float2 charCenter{ float(pos.x + other->GetWidth() / 2), float(pos.y + other->GetHeight() / 2) };

		if (charCenter.y > m_Center.y)
			UpdateDown(animation);
		else if (charCenter.y < m_Center.y)
			UpdateUp(animation);
		else if (charCenter.x > m_Center.x)
			UpdateRight(animation);
		else if (charCenter.x < m_Center.x)
			UpdateLeft(animation);
	}
}

void TunnelUpdate::OnTriggerStay(std::shared_ptr<dae::CollisionComponent> other)
{
	TunnelSprite animation = TunnelSprite(m_SpriteRenderer->GetAnimation());
	if (animation != TunnelSprite::all)
	{
		auto& pos = other->GetGameObject()->GetTransform().lock()->GetPosition();
		float2 charCenter{ float(pos.x + other->GetWidth() / 2), float(pos.y + other->GetHeight() / 2) };

		if (charCenter.y > m_Center.y)
			UpdateDown(animation);
		else if (charCenter.y < m_Center.y)
			UpdateUp(animation);
		else if (charCenter.x > m_Center.x)
			UpdateRight(animation);
		else if (charCenter.x < m_Center.x)
			UpdateLeft(animation);
	}
}

void TunnelUpdate::Initialize()
{
	m_SpriteRenderer = GetGameObject()->GetComponent<dae::SpriteRenderer>();

	auto pos = GetGameObject()->GetTransform().lock()->GetPosition();
	auto collision = GetGameObject()->GetComponent<dae::CollisionComponent>();
	m_Center.x = float(pos.x + collision->GetWidth() / 2);
	m_Center.y = float(pos.y + collision->GetHeight() / 2);
}

void TunnelUpdate::UpdateDown(const TunnelSprite& currentSprite)
{
	TunnelSprite animation = TunnelSprite::none;

	switch (currentSprite)
	{
	case TunnelSprite::straightHorizontal:
		animation = TunnelSprite::tDown;
		break;
	case TunnelSprite::cornerLU:
		animation = TunnelSprite::tLeft;
		break;
	case TunnelSprite::cornerRU:
		animation = TunnelSprite::tRight;
		break;
	case TunnelSprite::tUp:
		animation = TunnelSprite::all;
		break;
	case TunnelSprite::left:
		animation = TunnelSprite::cornerLD;
		break;
	case TunnelSprite::up:
		animation = TunnelSprite::straightVertical;
		break;
	case TunnelSprite::right:
		animation = TunnelSprite::cornerRD;
		break;
	case TunnelSprite::none:
		animation = TunnelSprite::down;
		break;
	default:
		break;
	}

	if (animation != TunnelSprite::none)
		m_SpriteRenderer->SetAnimation(int(animation));
}

void TunnelUpdate::UpdateUp(const TunnelSprite& currentSprite)
{
	TunnelSprite animation = TunnelSprite::none;

	switch (currentSprite)
	{
	case TunnelSprite::straightHorizontal:
		animation = TunnelSprite::tUp;
		break;
	case TunnelSprite::cornerLD:
		animation = TunnelSprite::tLeft;
		break;
	case TunnelSprite::cornerRD:
		animation = TunnelSprite::tRight;
		break;
	case TunnelSprite::tDown:
		animation = TunnelSprite::all;
		break;
	case TunnelSprite::left:
		animation = TunnelSprite::cornerLU;
		break;
	case TunnelSprite::right:
		animation = TunnelSprite::cornerRU;
		break;
	case TunnelSprite::down:
		animation = TunnelSprite::straightVertical;
		break;
	case TunnelSprite::none:
		animation = TunnelSprite::up;
		break;
	default:
		break;
	}

	if (animation != TunnelSprite::none)
		m_SpriteRenderer->SetAnimation(int(animation));
}

void TunnelUpdate::UpdateLeft(const TunnelSprite& currentSprite)
{
	TunnelSprite animation = TunnelSprite::none;

	switch (currentSprite)
	{
	case TunnelSprite::straightVertical: 
		animation = TunnelSprite::tLeft;
		break;
	case TunnelSprite::cornerRU:
		animation = TunnelSprite::tUp;
		break;
	case TunnelSprite::cornerRD: 
		animation = TunnelSprite::tDown;
		break;
	case TunnelSprite::tRight: 
		animation = TunnelSprite::all;
		break;
	case TunnelSprite::up: 
		animation = TunnelSprite::cornerLU;
		break;
	case TunnelSprite::right: 		
		animation = TunnelSprite::straightHorizontal;
		break;
	case TunnelSprite::down: 
		animation = TunnelSprite::cornerLD;
		break;
	case TunnelSprite::none: 
		animation = TunnelSprite::left;
		break;
	default:
		break;
	}

	if (animation != TunnelSprite::none)
		m_SpriteRenderer->SetAnimation(int(animation));
}

void TunnelUpdate::UpdateRight(const TunnelSprite& currentSprite)
{
	TunnelSprite animation = TunnelSprite::none;

	switch (currentSprite)
	{
	case TunnelSprite::straightVertical: 
		animation = TunnelSprite::tRight;
		break;
	case TunnelSprite::cornerLU: 
		animation = TunnelSprite::tUp;
		break;
	case TunnelSprite::cornerLD: 
		animation = TunnelSprite::tDown;
		break;
	case TunnelSprite::tLeft: 
		animation = TunnelSprite::all;
		break;
	case TunnelSprite::left: 
		animation = TunnelSprite::straightHorizontal;
		break;
	case TunnelSprite::up: 
		animation = TunnelSprite::cornerRU;
		break;
	case TunnelSprite::down: 
		animation = TunnelSprite::cornerRD;
		break;
	case TunnelSprite::none: 
		animation = TunnelSprite::right;
		break;
	default:
		break;
	}

	if (animation != TunnelSprite::none)
		m_SpriteRenderer->SetAnimation(int(animation));
}

