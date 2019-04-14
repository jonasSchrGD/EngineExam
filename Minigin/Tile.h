#pragma once
#include "CollisionComponent.h"
#include "RenderComponent.h"

namespace dae
{
	class Tile
	{
	public:
		Tile(float tileWidth = 10, float tileHeight = 10);
		~Tile();

		void DoCollision(std::shared_ptr<CollisionComponent> other) { m_CollisionComponent->DoCollisionCheck(other); }

	private:
		std::shared_ptr<CollisionComponent> m_CollisionComponent;
		std::shared_ptr<RenderComponent> m_RenderComponent;
	};
}
