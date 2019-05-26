#include "MiniginPCH.h"
#include "LifeTime.h"
#include "Time.h"
#include "GameObject.h"

dae::LifeTime::LifeTime(float lifeTime)
	:m_LifeTime(lifeTime)
{
}


dae::LifeTime::~LifeTime()
{
}

void dae::LifeTime::Update()
{
	m_LifeTime -= Time::GetInstance().DeltaTime();
	if(m_LifeTime <= 0)
	{
		GetGameObject()->GetScene()->Remove(GetGameObject());
	}
}
