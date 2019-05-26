#include "pch.h"
#include "AttackBehaviour.h"
#include <GameObject.h>
#include "DigDugColllision.h"
#include "CharacterControllerComponent.h"
#include "Prefabs.h"

AttackBehaviour::AttackBehaviour()
	:m_IsDigDug()
	,m_Controller()
{
}


AttackBehaviour::~AttackBehaviour()
{
}

void AttackBehaviour::Update()
{
	if(dae::InputManager::GetInstance().IsPressed(m_Select, m_Controller))
	{
 		if(m_IsDigDug)
		{
			int animation = GetGameObject()->GetComponent<dae::SpriteRenderer>()->GetAnimation();
		
 			if (animation == int(DigDugAnimation::up) || animation == int(DigDugAnimation::digUp))
 			{
				auto pos = GetGameObject()->GetTransform().lock()->GetPosition();
				auto pump = prefabs::GetPrefab(int2{ 0, -1 });

				pump->GetComponent<Projectile>()->SetOwner(GetGameObject());

				pump->SetPosition(pos.x, pos.y - 28);
				GetGameObject()->GetScene()->Add(pump);
			}
			else if(animation == int(DigDugAnimation::down) || animation == int(DigDugAnimation::digDown))
			{
				auto pos = GetGameObject()->GetTransform().lock()->GetPosition();
				auto pump = prefabs::GetPrefab(int2{ 0, 1 });

				pump->SetPosition(pos.x, pos.y + 28);
				GetGameObject()->GetScene()->Add(pump);
			}
			else if (animation == int(DigDugAnimation::digLeft) || animation == int(DigDugAnimation::left))
			{
				auto pos = GetGameObject()->GetTransform().lock()->GetPosition();
				auto pump = prefabs::GetPrefab(int2{ -1, 0 });

				pump->SetPosition(pos.x - 28, pos.y);
				GetGameObject()->GetScene()->Add(pump);
			}
			else if (animation == int(DigDugAnimation::right) || animation == int(DigDugAnimation::digRight))
			{
				auto pos = GetGameObject()->GetTransform().lock()->GetPosition();
				auto pump = prefabs::GetPrefab(int2{ 1, 0 });

				pump->SetPosition(pos.x + 28, pos.y);
				GetGameObject()->GetScene()->Add(pump);
			}
		}
		else
		{
			if(GetGameObject()->GetComponent<dae::SpriteRenderer>()->GetAnimation() == (int)FygarAnimation::left)
			{
				auto pos = GetGameObject()->GetTransform().lock()->GetPosition();
				auto fire = prefabs::GetPrefab(true);
				GetGameObject()->GetScene()->Add(fire);

				fire->AddComponent(std::make_shared<dae::CharacterControllerComponent>(std::make_shared<dae::BaseState>(), GetGameObject()->GetComponent<dae::CharacterControllerComponent>()->GetPlayerNr()));

				fire->SetPosition(pos.x - 80, pos.y);
			}
			else if(GetGameObject()->GetComponent<dae::SpriteRenderer>()->GetAnimation() == (int)FygarAnimation::right)
			{
				auto pos = GetGameObject()->GetTransform().lock()->GetPosition();
				auto fire = prefabs::GetPrefab(false);
				fire->AddComponent(std::make_shared<dae::CharacterControllerComponent>(std::make_shared<dae::BaseState>(), GetGameObject()->GetComponent<dae::CharacterControllerComponent>()->GetPlayerNr()));
				GetGameObject()->GetScene()->Add(fire);

				fire->SetPosition(pos.x + 40, pos.y);
			}
		}
	}
}

void AttackBehaviour::Initialize()
{
	if (GetGameObject()->GetComponent<DigDugColllision>())
		m_IsDigDug = true;

	m_Controller = GetGameObject()->GetComponent<dae::CharacterControllerComponent>()->GetPlayerNr();
}
