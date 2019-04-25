#include "MiniginPCH.h"
#include "CollisionComponent.h"
#include "GameObject.h"

dae::CollisionComponent::CollisionComponent(float width, float height)
	:m_Width(width)
	,m_Height(height)
	,m_IsTrigger(false)
{
}

void dae::CollisionComponent::Update()
{
	m_IsOverlappingOld = m_IsOverlapping;
}

void dae::CollisionComponent::DoCollisionCheck(std::shared_ptr<CollisionComponent> other)
{
	auto pos = GetGameObject()->GetTransform().lock()->GetPosition();
	auto otherPos = other->GetGameObject()->GetTransform().lock()->GetPosition();
	bool XOverlapping = false;
	bool YOverlapping = false;

	float xDistance = pos.x - otherPos.x;
	float xMaxOverlappingDist = m_Height / 2 + other->m_Height / 2;
	if (xDistance < xMaxOverlappingDist && xDistance > -xMaxOverlappingDist)
		XOverlapping = true;

	float yDistance = pos.y - otherPos.y;
	float yMaxOverlappingDist = m_Width / 2 + other->m_Width / 2;
	if (yDistance < yMaxOverlappingDist && yDistance > -yMaxOverlappingDist)
		YOverlapping = true;

	if (XOverlapping && YOverlapping)
	{
		m_IsOverlapping = true;
		if (!m_IsTrigger)
			HandleCollision(other, xDistance, yDistance);
	}
	else
		m_IsOverlapping = false;

	InvokeCorrespondingFunction(other);
}

void dae::CollisionComponent::HandleCollision(std::shared_ptr<CollisionComponent> other, float xDistance, float yDistance)
{
	auto pos = GetGameObject()->GetTransform().lock()->GetPosition();
	auto otherPos = other->GetGameObject()->GetTransform().lock()->GetPosition();

	if (xDistance > yDistance)
	{
		int sign = 1 - 2 * xDistance < 0;
		other->GetGameObject()->GetTransform().lock()->SetPosition(pos.x - m_Height / 2 * sign, otherPos.y, otherPos.z);
	}
	else
	{
		int sign = 1 - 2 * yDistance < 0;
		other->GetGameObject()->GetTransform().lock()->SetPosition(otherPos.x, pos.y + m_Width / 2 * sign, otherPos.z);
	}
}
void dae::CollisionComponent::InvokeCorrespondingFunction(std::shared_ptr<CollisionComponent> other)
{
	auto gameObject = GetGameObject();

	if(m_IsTrigger)
	{
		if(m_IsOverlappingOld)
		{
			if (m_IsOverlapping)
				gameObject->OnTriggerStay(other);
			else
				gameObject->OnTriggerLeave(other);
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
				gameObject->OnCollisionLeave(other);
		}
		else if (m_IsOverlapping)
			gameObject->OnCollisionEnter(other);
	}
}
