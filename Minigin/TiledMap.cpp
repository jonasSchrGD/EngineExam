#include "MiniginPCH.h"
#include "TiledMap.h"


TiledMap::TiledMap(float tileWidth, float tileHeight, int rows, int cols)
	:m_TileWidth(tileWidth)
	,m_TileHeight(tileHeight)
	,m_Cols(cols)
	,m_Rows(rows)
{
	for (int col = 0; col < cols; ++col)
	{
		for (int row = 0; row < rows; ++row)
		{
			m_Tiles.push_back(std::make_shared<dae::Tile>());
		}
	}
}

void TiledMap::DoCollisionCheck(std::shared_ptr<dae::CollisionComponent> collisionComp) const
{
	float2 bottomLeft = collisionComp->GetBottomLeft();
	float height = collisionComp->GetHeight();
	float width = collisionComp->GetWidth();

	int row = bottomLeft.y / m_TileHeight;
	int col = bottomLeft.x / m_TileWidth;
	if(row > 0 && row < m_Rows && col > 0 && col < m_Cols)
	{
		m_Tiles[row * m_Cols + col]->DoCollision(collisionComp);
	}//bottomleft

	row = bottomLeft.y / m_TileHeight;
	col = (bottomLeft.x + width) / m_TileWidth;
	if (row > 0 && row < m_Rows && col > 0 && col < m_Cols)
	{
		m_Tiles[row * m_Cols + col]->DoCollision(collisionComp);
	}//bottomright

	row = (bottomLeft.y + height) / m_TileHeight;
	col = (bottomLeft.x) / m_TileWidth;
	if (row > 0 && row < m_Rows && col > 0 && col < m_Cols)
	{
		m_Tiles[row * m_Cols + col]->DoCollision(collisionComp);
	}//topleft

	row = (bottomLeft.y + height) / m_TileHeight;
	col = (bottomLeft.x + width) / m_TileWidth;
	if (row > 0 && row < m_Rows && col > 0 && col < m_Cols)
	{
		m_Tiles[row * m_Cols + col]->DoCollision(collisionComp);
	}//topright
}
