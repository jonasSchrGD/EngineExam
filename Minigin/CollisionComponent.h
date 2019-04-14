#pragma once
#include "BaseComponent.h"

namespace dae
{
	class CollisionComponent : public BaseComponent
	{
	public:
		CollisionComponent(float witdth, float height);
		~CollisionComponent() = default;

		void DoCollisionCheck(std::shared_ptr<CollisionComponent> other);

		float2 GetBottomLeft();
		float GetHeight() const { return  m_Height; }
		float GetWidth() const { return  m_Width; }

	protected:
		void Update() override;
		void GameObjectSet() override{};

	private:
		float m_Width, m_Height;
	};
}
			