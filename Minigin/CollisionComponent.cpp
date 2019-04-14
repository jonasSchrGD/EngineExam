#include "MiniginPCH.h"
#include "CollisionComponent.h"
#include "GameObject.h"

dae::CollisionComponent::CollisionComponent(float witdth, float height)
{
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

	if(XOverlapping && YOverlapping)
	{
		if(xDistance > yDistance)
		{
			int sign = 1 - 2 * xDistance < 0;
			other->GetGameObject()->GetTransform().lock()->SetPosition(pos.x - m_Height / 2, otherPos.y, otherPos.z);
		}
		else
		{
			int sign = 1 - 2 * yDistance < 0;
			other->GetGameObject()->GetTransform().lock()->SetPosition(otherPos.x, pos.y + m_Width / 2 * sign, otherPos.z);
		}
	}
}

float2 dae::CollisionComponent::GetBottomLeft()
{
	auto pos = GetGameObject()->GetTransform().lock()->GetPosition();
	float2 bottomLeft{};
	bottomLeft.x = pos.x - m_Width / 2;
	bottomLeft.y = pos.y - m_Height / 2;

	return  bottomLeft;
}

void dae::CollisionComponent::Update()
{

}
