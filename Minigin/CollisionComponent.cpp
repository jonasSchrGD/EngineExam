#include "MiniginPCH.h"
#include "CollisionComponent.h"
#include "GameObject.h"
#include "CollisionHandler.h"

dae::CollisionComponent::CollisionComponent(float width, float height, bool fixedRotation)
	:m_Width(width)
	,m_Height(height)
{
	m_Idx = CollisionHandler::GetInstance().AddCollisionComp(shared_from_this());

	b2BodyDef bodydef;
	bodydef.type = b2_dynamicBody;
	bodydef.fixedRotation = fixedRotation;

	m_pCollision = CollisionHandler::GetInstance().GetWorld().CreateBody(&bodydef);
	m_pCollision->SetUserData(this);

	b2PolygonShape box;
	box.SetAsBox(width / 2, height / 2);

	b2FixtureDef fixture;
	fixture.shape = &box;
	fixture.isSensor = false;
	fixture.density = 1;
	fixture.friction = 0.f;

	m_pCollision->CreateFixture(&fixture);
}

dae::CollisionComponent::~CollisionComponent()
{
	CollisionHandler::GetInstance().RemoveCollisionComp(m_Idx);
}

void dae::CollisionComponent::Update()
{
	m_IsOverlappingOld = m_IsOverlapping;

	if (m_pColliding)
		InvokeCorrespondingFunction();
}

void dae::CollisionComponent::InvokeCorrespondingFunction()
{
	auto gameObject = GetGameObject();
	auto other = CollisionHandler::GetInstance().GetSharedPtr(m_Idx);

	if(m_IsTrigger)
	{
		if(m_IsOverlappingOld)
		{
			if (m_IsOverlapping)
				gameObject->OnTriggerStay(other);
			else
			{
				gameObject->OnTriggerLeave(other);
				m_pColliding = nullptr;
			}
		}
		else if(m_IsOverlapping)
			gameObject->OnTriggerEnter(other);
	}
	else
	{
		if (m_IsOverlappingOld)
		{
			if (m_IsOverlapping)
				gameObject->OnCollisionStay(other);
			else
			{
				gameObject->OnCollisionLeave(other);
				m_pColliding = nullptr;
			}
		}
		else if (m_IsOverlapping)
			gameObject->OnCollisionEnter(other);
	}
}
