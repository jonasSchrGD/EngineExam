#include "pch.h"
#include "TunnelUpdate.h"
#include "GameObject.h"
#include "CollisionComponent.h"
#include "Animations.h"
#include "DigDugColllision.h"

TunnelUpdate::TunnelUpdate()
	: m_Center()
{
}

void TunnelUpdate::OnTriggerEnter(std::shared_ptr<dae::CollisionComponent> other)
{
	if (other->GetGameObject()->GetComponent<DigDugColllision>())
	{
		TunnelSprite animation = TunnelSprite(m_SpriteRenderer->GetAnimation());
		if (animation != TunnelSprite::all)
		{
			auto& pos = other->GetGameObject()->GetTransform().lock()->GetPosition();
			float2 charCenter{ float(pos.x + other->GetWidth() / 2), float(pos.y + other->GetHeight() / 2) };
			auto gameobject = other->GetGameObject();

			if (charCenter.y > m_Center.y)
				UpdateDown(gameobject, animation, charCenter.y - m_Center.y);
			else if (charCenter.y < m_Center.y)
				UpdateUp(gameobject, animation, m_Center.y - charCenter.y);
			else if (charCenter.x > m_Center.x)
				UpdateRight(gameobject, animation, charCenter.x - m_Center.x);
			else if (charCenter.x < m_Center.x)
				UpdateLeft(gameobject, animation, m_Center.x - charCenter.x);
		}
	}
}

void TunnelUpdate::OnTriggerStay(std::shared_ptr<dae::CollisionComponent> other)
{
	if (other->GetGameObject()->GetComponent<DigDugColllision>())
	{
		TunnelSprite animation = TunnelSprite(m_SpriteRenderer->GetAnimation());
		if (animation != TunnelSprite::all)
		{
			auto& pos = other->GetGameObject()->GetTransform().lock()->GetPosition();
			float2 charCenter{ float(pos.x + other->GetWidth() / 2), float(pos.y + other->GetHeight() / 2) };
			auto gameobject = other->GetGameObject();

			if (charCenter.y > m_Center.y)
				UpdateDown(gameobject, animation, charCenter.y - m_Center.y);
			else if (charCenter.y < m_Center.y)
				UpdateUp(gameobject, animation, m_Center.y - charCenter.y);
			else if (charCenter.x > m_Center.x)
				UpdateRight(gameobject, animation, charCenter.x - m_Center.x);
			else if (charCenter.x < m_Center.x)
				UpdateLeft(gameobject, animation, m_Center.x - charCenter.x);
		}
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

void TunnelUpdate::UpdateDown(std::shared_ptr<dae::GameObject> other, const TunnelSprite& currentSprite, float distanceToCenter)
{
	TunnelSprite animation = TunnelSprite::none;
	bool digging{ true };

	switch (currentSprite)
	{
	case TunnelSprite::straightHorizontal:
		if (distanceToCenter > 10)
			animation = TunnelSprite::tDown;
		break;
	case TunnelSprite::cornerLU:
		if (distanceToCenter > 10)
			animation = TunnelSprite::tLeft;
		break;
	case TunnelSprite::cornerRU:
		if (distanceToCenter > 10)
			animation = TunnelSprite::tRight;
		break;
	case TunnelSprite::tUp:
		if (distanceToCenter > 10)
			animation = TunnelSprite::all;
		break;
	case TunnelSprite::left:
		if (distanceToCenter > 10)
			animation = TunnelSprite::cornerLD;
		break;
	case TunnelSprite::up:
		if (distanceToCenter > 10)
			animation = TunnelSprite::straightVertical;
		break;
	case TunnelSprite::right:
		if (distanceToCenter > 10)
			animation = TunnelSprite::cornerRD;
		break;
	case TunnelSprite::none:
		if (distanceToCenter < 10)
			animation = TunnelSprite::down;
		break;
	default:
		digging = false;
		break;
	}

	auto digdug = other->GetComponent<DigDugColllision>();
	if (digdug)
	{
		digdug->SetDigging(digging);
	}

	if (animation != TunnelSprite::none)
		m_SpriteRenderer->SetAnimation(int(animation));
}

void TunnelUpdate::UpdateUp(std::shared_ptr<dae::GameObject> other, const TunnelSprite& currentSprite, float distanceToCenter)
{
	TunnelSprite animation = TunnelSprite::none;
	bool digging{ true };

	switch (currentSprite)
	{
	case TunnelSprite::straightHorizontal:
		if (distanceToCenter > 10)
			animation = TunnelSprite::tUp;
		break;
	case TunnelSprite::cornerLD:
		if (distanceToCenter > 10)
			animation = TunnelSprite::tLeft;
		break;
	case TunnelSprite::cornerRD:
		if (distanceToCenter > 10)
			animation = TunnelSprite::tRight;
		break;
	case TunnelSprite::tDown:
		if (distanceToCenter > 10)
			animation = TunnelSprite::all;
		break;
	case TunnelSprite::left:
		if (distanceToCenter > 10)
			animation = TunnelSprite::cornerLU;
		break;
	case TunnelSprite::right:
		if (distanceToCenter > 10)
			animation = TunnelSprite::cornerRU;
		break;
	case TunnelSprite::down:
		if (distanceToCenter > 10)
			animation = TunnelSprite::straightVertical;
		break;
	case TunnelSprite::none:
		if (distanceToCenter < 10)
			animation = TunnelSprite::up;
		break;
	default:
		digging = false;
		break;
	}

	auto digdug = other->GetComponent<DigDugColllision>();
	if (digdug)
	{
		digdug->SetDigging(digging);
	}

	if (animation != TunnelSprite::none)
		m_SpriteRenderer->SetAnimation(int(animation));
}

void TunnelUpdate::UpdateLeft(std::shared_ptr<dae::GameObject> other, const TunnelSprite& currentSprite, float distanceToCenter)
{
	TunnelSprite animation = TunnelSprite::none;
	bool digging{ true };

	switch (currentSprite)
	{
	case TunnelSprite::straightVertical: 
		if (distanceToCenter > 10)
			animation = TunnelSprite::tLeft;
		break;
	case TunnelSprite::cornerRU:
		if (distanceToCenter > 10)
			animation = TunnelSprite::tUp;
		break;
	case TunnelSprite::cornerRD: 
		if (distanceToCenter > 10)
			animation = TunnelSprite::tDown;
		break;
	case TunnelSprite::tRight: 
		if (distanceToCenter > 10)
			animation = TunnelSprite::all;
		break;
	case TunnelSprite::up: 
		if (distanceToCenter > 10)
			animation = TunnelSprite::cornerLU;
		break;
	case TunnelSprite::right: 		
		if (distanceToCenter > 10)
			animation = TunnelSprite::straightHorizontal;
		break;
	case TunnelSprite::down: 
		if (distanceToCenter > 10)
			animation = TunnelSprite::cornerLD;
		break;
	case TunnelSprite::none: 
		if (distanceToCenter < 10)
			animation = TunnelSprite::left;
		break;
	default:
		digging = false;
		break;
	}

	auto digdug = other->GetComponent<DigDugColllision>();
	if (digdug)
	{
		digdug->SetDigging(digging);
	}

	if (animation != TunnelSprite::none)
		m_SpriteRenderer->SetAnimation(int(animation));
}

void TunnelUpdate::UpdateRight(std::shared_ptr<dae::GameObject> other, const TunnelSprite& currentSprite, float distanceToCenter)
{
	TunnelSprite animation = TunnelSprite::none;
	bool digging{ true };

	switch (currentSprite)
	{
	case TunnelSprite::straightVertical: 
		if (distanceToCenter > 10)
			animation = TunnelSprite::tRight;
		break;
	case TunnelSprite::cornerLU: 
		if (distanceToCenter > 10)
			animation = TunnelSprite::tUp;
		break;
	case TunnelSprite::cornerLD: 
		if (distanceToCenter > 10)
			animation = TunnelSprite::tDown;
		break;
	case TunnelSprite::tLeft: 
		if (distanceToCenter > 10)
			animation = TunnelSprite::all;
		break;
	case TunnelSprite::left: 
		if (distanceToCenter > 10)
			animation = TunnelSprite::straightHorizontal;
		break;
	case TunnelSprite::up: 
		if (distanceToCenter > 10)
			animation = TunnelSprite::cornerRU;
		break;
	case TunnelSprite::down: 
		if (distanceToCenter > 10)
			animation = TunnelSprite::cornerRD;
		break;
	case TunnelSprite::none: 
		if (distanceToCenter < 10)
			animation = TunnelSprite::right;
		break;
	default:
		digging = false;
		break;
	}

	auto digdug = other->GetComponent<DigDugColllision>();
	if (digdug)
	{
		digdug->SetDigging(digging);
	}

	if (animation != TunnelSprite::none)
		m_SpriteRenderer->SetAnimation(int(animation));
}

