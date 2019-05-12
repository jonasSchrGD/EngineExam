#pragma once
#include "BaseComponent.h"
#include "Box2D/Box2D.h"

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
		bool m_IsOverlapping, m_IsOverlappingOld, m_IsTrigger, m_FixedRotation, m_IsStatic;

		b2Body* m_pCollision;
		CollisionComponent* m_pColliding;

		void InvokeCorrespondingFunction();

	protected:
		void Initialize() override;
	};
}
			