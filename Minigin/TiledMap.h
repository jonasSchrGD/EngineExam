#pragma once
#include "CollisionComponent.h"
#include "Tile.h"
#include "BaseMap.h"

class TiledMap final : public BaseMap
{
public:
	TiledMap(float tileWidth, float tileHeight, int rows, int cols);
	~TiledMap() = default;

	void Update() override {}

	void DoCollisionCheck(std::shared_ptr<dae::CollisionComponent> collisionComp) const override;

private:
	std::vector<std::shared_ptr<dae::Tile>> m_Tiles;
	const float m_TileWidth, m_TileHeight;
	const int m_Cols, m_Rows;
};

