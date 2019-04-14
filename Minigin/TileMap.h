#pragma once
#include "SceneObject.h"
#include "CollisionComponent.h"

class TiledMap final : public dae::SceneObject
{
public:
	TiledMap(float tileWidth, float tileHeight, int rows, int cols);
	~TiledMap();

	void Update() override {}

	void DoCollisionCheck(std::shared_ptr<dae::CollisionComponent> collisionComp);

private:
	std::vector<std::shared_ptr<dae::CollisionComponent>> m_TileCollisions;

};

