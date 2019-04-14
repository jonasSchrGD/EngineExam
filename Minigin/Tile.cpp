#include "MiniginPCH.h"
#include "Tile.h"


dae::Tile::Tile(float tileWidth, float tileHeight)
	:m_CollisionComponent(std::make_shared<CollisionComponent>(tileWidth, tileHeight))
	,m_RenderComponent(std::make_shared<RenderComponent>())
{
}


dae::Tile::~Tile()
{
}
