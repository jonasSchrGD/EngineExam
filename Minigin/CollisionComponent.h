#pragma once
#include "BaseComponent.h"
#include "Box2D/Box2D.h"
#include "CollisionHandler.h"

namespace dae
{
	class CollisionComponent final : public BaseComponent
	{
	public:
		CollisionComponent(float width, float height, bool fixedRotation = false, bool isStatic = false);
		~CollisionComponent();

		float GetHeight() const { return  m_Height; }
		float GetWidth() const { return  m_Width; }

		void Load() override;
		void Unload() override;

		void SetTrigger(bool isTrigger)
		{
			m_IsTrigger = isTrigger;

			if (m_pCollision)
				m_pCollision->GetFixtureList()->SetSensor(isTrigger);
		}

		void CollisionEnter(CollisionComponent* other)
		{
			m_pCollisionEnter.push_back(other);
		}
		void CollisionLeave(CollisionComponent* other)
		{
			if (!m_pCollisionStay.empty())
			{
				auto col = std::remove(m_pCollisionStay.begin(), m_pCollisionStay.end(), other);
				if (col != m_pCollisionStay.end())
					m_pCollisionStay.erase(col);
			}
			m_pCollisionLeave.push_back(other);
		}

		std::vector<std::shared_ptr<CollisionComponent>> GetColliders();

	protected:
		void Update() override;

	private:
		float m_Width, m_Height;
		int m_Idx;
		bool m_IsTrigger, m_FixedRotation, m_IsStatic;

		b2Body* m_pCollision;

		void InvokeCorrespondingFunction();

		std::vector<CollisionComponent*> m_pCollisionEnter;
		std::vector<CollisionComponent*> m_pCollisionStay;
		std::vector<CollisionComponent*> m_pCollisionLeave;

	protected:
		void Initialize() override;
	};
}
			