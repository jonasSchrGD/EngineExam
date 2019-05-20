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

		b2World& GetWorld() { return m_Map; }

		int AddCollisionComp(std::shared_ptr<CollisionComponent> comp)
		{
			m_collisionComponents.insert(std::pair<int, std::shared_ptr<CollisionComponent>>(m_NewIdx, comp));
			m_NewIdx++;

			return m_NewIdx - 1;
		}

		void RemoveCollisionComp(int idx)
		{
			if (m_collisionComponents.find(idx) != m_collisionComponents.end())
			{
				m_collisionComponents.at(idx).reset();
				m_collisionComponents.erase(idx);
			}
		}

		std::shared_ptr<CollisionComponent> GetSharedPtr(int idx)
		{
			if (m_collisionComponents.find(idx) != m_collisionComponents.end())
				return m_collisionComponents.at(idx).lock();
			return std::shared_ptr<CollisionComponent>();
		}

		MiniginContactListener& GetContactListener() { return  m_ContactListener; }

	private:
		b2World m_Map;
		MiniginContactListener m_ContactListener;

		int m_NewIdx = 0;
		std::unordered_map<int, std::weak_ptr<CollisionComponent>> m_collisionComponents;
		Subject m_subject;
	};
}
