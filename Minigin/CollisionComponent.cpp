#include "MiniginPCH.h"
#include "CollisionComponent.h"
#include "GameObject.h"
#include "CollisionHandler.h"

dae::CollisionComponent::CollisionComponent(float width, float height, bool fixedRotation, bool isStatic)
	: m_Width(width)
	, m_Height(height)
	, m_FixedRotation(fixedRotation)
	, m_IsStatic(isStatic)
	, m_Idx(0)
	, m_pCollision(nullptr)
	, m_IsTrigger(false)
{
}

dae::CollisionComponent::~CollisionComponent()
{
	CollisionHandler::GetInstance().RemoveCollisionComp(m_Idx);

	if (m_pCollision)
		CollisionHandler::GetInstance().GetWorld().DestroyBody(m_pCollision);
}

void dae::CollisionComponent::Load()
{
	auto pos = GetGameObject()->GetTransform().lock()->GetPosition();

	b2BodyDef bodydef;
	if (m_IsStatic)
		bodydef.type = b2_staticBody;
	else
		bodydef.type = b2_dynamicBody;

	bodydef.fixedRotation = m_FixedRotation;
	bodydef.position.Set(pos.x / 30, pos.y / 30);
	bodydef.active = true;
	bodydef.allowSleep = false;
	bodydef.awake = true;
	bodydef.gravityScale = 0;

	m_pCollision = CollisionHandler::GetInstance().GetWorld().CreateBody(&bodydef);
	m_pCollision->SetUserData(this);

	b2PolygonShape box;
	box.SetAsBox((m_Width - 4) / 2.f / 30.f, (m_Height - 4) / 2 / 30);

	b2FixtureDef fixture;
	fixture.shape = &box;
	fixture.isSensor = m_IsTrigger;

	m_pCollision->CreateFixture(&fixture);
}

void dae::CollisionComponent::Unload()
{
	CollisionHandler::GetInstance().GetWorld().DestroyBody(m_pCollision);
}

void dae::CollisionComponent::Update()
{
	auto pos = GetGameObject()->GetTransform().lock()->GetPosition();

	if(m_pCollision && !m_IsStatic)
		m_pCollision->SetTransform(b2Vec2(pos.x / 30, pos.y / 30), 0);

	InvokeCorrespondingFunction();

	m_pCollisionEnter.clear();
	m_pCollisionLeave.clear();
}

void dae::CollisionComponent::InvokeCorrespondingFunction()
{
	auto gameObject = GetGameObject();
	auto& collisionhandler = CollisionHandler::GetInstance();

	if (m_IsTrigger)
	{
		for (auto collisions : m_pCollisionStay)
			gameObject->OnTriggerStay(collisionhandler.GetSharedPtr(collisions->m_Idx));

		for (auto collisions : m_pCollisionLeave)
			gameObject->OnTriggerLeave(collisionhandler.GetSharedPtr(collisions->m_Idx));
	
		for (auto collisions : m_pCollisionEnter)
		{
			gameObject->OnTriggerEnter(collisionhandler.GetSharedPtr(collisions->m_Idx));
			m_pCollisionStay.push_back(collisions);
		}
	}
	else
	{
		for (auto collisions : m_pCollisionStay)
			gameObject->OnCollisionStay(collisionhandler.GetSharedPtr(collisions->m_Idx));

		for (auto collisions : m_pCollisionLeave)
			gameObject->OnCollisionLeave(collisionhandler.GetSharedPtr(collisions->m_Idx));

		for (auto collisions : m_pCollisionEnter)
		{
			gameObject->OnCollisionEnter(collisionhandler.GetSharedPtr(collisions->m_Idx));
			m_pCollisionStay.push_back(collisions);
		}
	}
}

void dae::CollisionComponent::Initialize()
{
	auto self = shared_from_this(); //this is why i hate std::shared_ptr, extremely annoying
	m_Idx = CollisionHandler::GetInstance().AddCollisionComp(std::static_pointer_cast<CollisionComponent>(self));
}
