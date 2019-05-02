#include "MiniginPCH.h"
#include "MiniginContactListener.h"
#include "Box2D/Box2D.h"
#include "CollisionComponent.h"

void dae::MiniginContactListener::BeginContact(b2Contact* contact)
{
	CollisionComponent* bodyUserData = static_cast<CollisionComponent*>(contact->GetFixtureA()->GetBody()->GetUserData());
	CollisionComponent* bodyUserData2 = static_cast<CollisionComponent*>(contact->GetFixtureB()->GetBody()->GetUserData());

	if (bodyUserData)
		bodyUserData->SetOverlapping(true, bodyUserData2);

	if (bodyUserData2)
		bodyUserData2->SetOverlapping(true, bodyUserData);
}

void dae::MiniginContactListener::EndContact(b2Contact* contact)
{
	CollisionComponent* bodyUserData = static_cast<CollisionComponent*>(contact->GetFixtureA()->GetBody()->GetUserData());
	CollisionComponent* bodyUserData2 = static_cast<CollisionComponent*>(contact->GetFixtureB()->GetBody()->GetUserData());

	if (bodyUserData)
		bodyUserData->SetOverlapping(false, bodyUserData2);

	if (bodyUserData2)
		bodyUserData2->SetOverlapping(false, bodyUserData);
}
