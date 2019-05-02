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
