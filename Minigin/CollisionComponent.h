#pragma once
#include "BaseComponent.h"

namespace dae
{
	class CollisionComponent : public BaseComponent
	{
	public:
		CollisionComponent(float width, float height);
		~CollisionComponent() = default;

		void DoCollisionCheck(std::shared_ptr<CollisionComponent> other);

		float2 GetBottomLeft();
		float GetHeight() const { return  m_Height; }
		float GetWidth() const { return  m_Width; }
		void SetTrigger(bool isTrigger) { m_IsTrigger = isTrigger; }

	protected:
		void Update() override;

	private:
		float m_Width, m_Height;
		bool m_IsOverlapping, m_IsOverlappingOld;
		bool m_IsTrigger;

		void HandleCollision(std::shared_ptr<CollisionComponent> other, float xDistance, float yDistance);
		void InvokeCorrespondingFunction(std::shared_ptr<CollisionComponent> other);
	};
}
			