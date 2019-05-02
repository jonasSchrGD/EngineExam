#pragma once
#include "BaseComponent.h"
#include "Box2D/Box2D.h"

namespace dae
{
	class CollisionComponent final : public BaseComponent, std::enable_shared_from_this<CollisionComponent>
	{
	public:
		CollisionComponent(float width, float height, bool fixedRotation = false);
		~CollisionComponent();

		float GetHeight() const { return  m_Height; }
		float GetWidth() const { return  m_Width; }

		void SetTrigger(bool isTrigger) { m_pCollision->GetFixtureList()->SetSensor(isTrigger); }

		void SetOverlapping(bool isoverlapping, CollisionComponent* other)
		{
			m_IsOverlapping = isoverlapping;
			m_pColliding = other;
		}

	protected:
		void Update() override;

	private:
		float m_Width, m_Height;
		int m_Idx;
		bool m_IsOverlapping = false, m_IsOverlappingOld, m_IsTrigger;

		b2Body* m_pCollision;
		CollisionComponent* m_pColliding = nullptr;

		void InvokeCorrespondingFunction();
	};
}
			