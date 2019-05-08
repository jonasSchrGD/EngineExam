#pragma once
#include "Singleton.h"
#include "Box2D/Box2D.h"
#include "CollisionComponent.h"
#include <unordered_map>
#include "MiniginContactListener.h"
#include "Subject.h"

namespace dae
{
	//class that handles all the collision in the game, collision in digdug is verry simple
	class CollisionHandler final : public Singleton<CollisionHandler>
	{
	public:
		CollisionHandler();

		void Update();

		b2World GetWorld() const { return m_Map; }

		int AddCollisionComp(std::shared_ptr<CollisionComponent> comp)
		{
			m_collisionComponents.at(m_NewIdx) = comp;
			m_NewIdx++;

			return m_NewIdx - 1;
		}

		void RemoveCollisionComp(int idx)
		{
			m_collisionComponents.erase(idx);
		}

		std::shared_ptr<CollisionComponent> GetSharedPtr(int idx)
		{
			return m_collisionComponents.at(idx);
		}

		MiniginContactListener& GetContactListener() { return  m_ContactListener; }

	private:
		b2World m_Map;
		MiniginContactListener m_ContactListener;

		int m_NewIdx = 0;
		std::unordered_map<int, std::shared_ptr<CollisionComponent>> m_collisionComponents;
		Subject m_subject;
	};
}
