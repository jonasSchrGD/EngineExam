#include "MiniginPCH.h"
#include "TiledMap.h"
#include  "GameObject.h"

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
	auto otherTransform = collisionComp->GetGameObject()->GetTransform().lock();
	float2 bottomLeft{};
	bottomLeft.x = otherTransform->GetPosition().x;
	bottomLeft.y = otherTransform->GetPosition().y;

	float height = collisionComp->GetHeight();
	float width = collisionComp->GetWidth();

	//bottomleft
	int row = int(bottomLeft.y / m_TileHeight);
	int col = int(bottomLeft.x / m_TileWidth);
	if(row > 0 && row < m_Rows && col > 0 && col < m_Cols)
	{
		m_Tiles[row * m_Cols + col]->DoCollision(collisionComp);
	}

	//bottomright
	row = int(bottomLeft.y / m_TileHeight);
	col = int((bottomLeft.x + width) / m_TileWidth);
	if (row > 0 && row < m_Rows && col > 0 && col < m_Cols)
	{
		m_Tiles[row * m_Cols + col]->DoCollision(collisionComp);
	}

	//topleft
	row = int((bottomLeft.y + height) / m_TileHeight);
	col = int((bottomLeft.x) / m_TileWidth);
	if (row > 0 && row < m_Rows && col > 0 && col < m_Cols)
	{
		m_Tiles[row * m_Cols + col]->DoCollision(collisionComp);
	}

	//topright
	row = int((bottomLeft.y + height) / m_TileHeight);
	col = int((bottomLeft.x + width) / m_TileWidth);
	if (row > 0 && row < m_Rows && col > 0 && col < m_Cols)
	{
		m_Tiles[row * m_Cols + col]->DoCollision(collisionComp);
	}
}
