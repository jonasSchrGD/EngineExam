#include "MiniginPCH.h"
#include "CollisionHandler.h"
#include "Time.h"

dae::CollisionHandler::CollisionHandler()
	:m_Map(b2Vec2(0, 0))
	,m_ContactListener()
{
	m_Map.SetContactListener(&m_ContactListener);
}

void dae::CollisionHandler::Update()
{
	m_Map.Step(dae::Time::GetInstance().DeltaTime(), 8, 3);
}
		