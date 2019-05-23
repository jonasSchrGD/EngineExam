#include "pch.h"
#include "Level.h"
#include "SpriteRenderer.h"
#include "TunnelUpdate.h"


Level::Level()
	: m_Spawns()
	, m_RowCol()
	, m_Offset()
	, m_TileSize()
	, m_CharacterSize({30, 30})
	, m_CenterRange(3)
{
}

Level::~Level()
{
}

void Level::Initialize(float2 characterSize, float centerRange)
{
	m_CharacterSize = characterSize;
	m_CenterRange = centerRange;
}

void Level::AddGameObject(std::shared_ptr<dae::GameObject> object)
{
	m_LevelObjects.push_back(object);
}

void Level::AddToScene(std::shared_ptr<dae::Scene> scene)
{
	for (auto object : m_LevelObjects)
	{
		scene->Add(object);
	}
}

bool Level::IsTunnel(float2 pos)
{
	int col = int((pos.x - m_Offset.x) / m_TileSize.x);
	int row = int((pos.y - m_Offset.y) / m_TileSize.y);

	return m_LevelObjects[row * m_RowCol.y + col]->GetComponent<dae::SpriteRenderer>()->GetAnimation() != (int)TunnelSprite::none;
}

bool Level::Center(std::shared_ptr<dae::GameObject> object, bool CenterX)
{
	UNREFERENCED_PARAMETER(object);

	auto transform = object->GetTransform().lock();
	auto pos = transform->GetPosition();

	bool isInCenterArea = false;
	if(CenterX)
	{
		int col = int((pos.x - m_Offset.x + m_CharacterSize.x / 2) / m_TileSize.x);
		float centerx = col * m_TileSize.x + m_TileSize.x / 2 + m_Offset.x;

		float offset = centerx -(pos.x + m_CharacterSize.x / 2);

		isInCenterArea = (offset > -m_CenterRange && offset < m_CenterRange);
		if(isInCenterArea)
		{
			transform->Translate( offset, 0, 0);
		}
	}
	else
	{
		int row = int((pos.y - m_Offset.y + m_CharacterSize.y / 2) / m_TileSize.y);
		float centery = row * m_TileSize.y + m_TileSize.y / 2 + m_Offset.y;
	
		float offset = centery - (pos.y + m_CharacterSize.y / 2);

		isInCenterArea = (offset > -m_CenterRange && offset < m_CenterRange);
		if (isInCenterArea)
		{
			transform->Translate(0, offset, 0);
		}
		else
		{
			offset = 80 - (pos.y + m_CharacterSize.y / 2);
			if((offset > -m_CenterRange && offset < m_CenterRange))
			{
				isInCenterArea = true;
				transform->Translate(0, offset, 0);
			}
		}
	}
	return isInCenterArea;
}

bool Level::IsInGrid(float2 pos)
{
	float2 center{pos.x + m_CharacterSize.x / 2, pos.y + m_CharacterSize.y / 2 };

	//is underground inside boundaries?
	if (center.x <= m_TileSize.x / 2 + (m_RowCol.y - 1) * m_TileSize.x + m_Offset.x && center.x >= m_TileSize.x / 2 + m_Offset.x &&
		center.x <= m_TileSize.y / 2 + (m_RowCol.x - 1) * m_TileSize.y + m_Offset.y && center.y >= m_TileSize.y / 2 + m_Offset.y)
		return true;

	//is in tunnel to go above ground?
	if (center.x == 260 && center.y > 80)
		return true;

	//is above ground?
	if(center.y == 80 && center.x <= m_TileSize.x / 2 + (m_RowCol.y - 1) * m_TileSize.x + m_Offset.x && center.y >= m_TileSize.x / 2 + m_Offset.x)
		return true;

	return false;
}

float2 Level::GetNextPos(float2 currentPos, int2 direction)
{
	int col = int((currentPos.x - m_Offset.x) / m_TileSize.x);
	int row = int((currentPos.y - m_Offset.y) / m_TileSize.y);
	int tile = row * m_RowCol.y + col;

	if (direction.x > 0)
		tile += 1;
	if (direction.x < 0)
		tile -= 1;

	if (direction.y > 0)
		tile += m_RowCol.y;
	if (direction.y < 0)
		tile -= m_RowCol.y;

	float2 spawnPos{};

	spawnPos.x = (tile % m_RowCol.y) * m_TileSize.x + m_Offset.x;
	spawnPos.y = (tile / m_RowCol.y) * m_TileSize.y + m_Offset.y;

	spawnPos.x += (m_TileSize.x - m_CharacterSize.x) / 2;
	spawnPos.y += (m_TileSize.y - m_CharacterSize.y) / 2;

	return spawnPos;
}
std::vector<int2> Level::GetPossibleDirections(float2 currentPos)
{
	std::vector<int2> directions{};

	int col = int((currentPos.x - m_Offset.x + m_CharacterSize.x) / m_TileSize.x);
	int row = int((currentPos.y - m_Offset.y + m_CharacterSize.y) / m_TileSize.y);

	int tile{ col + row * m_RowCol.y };

	if (AreConnected(tile, tile + 1))
		directions.push_back({ 1,0 });

	if (AreConnected(tile, tile - 1))
		directions.push_back({ -1,0 });

	if (AreConnected(tile, tile + m_RowCol.y))
		directions.push_back({ 0,1 });

	if (AreConnected(tile, tile - m_RowCol.y))
		directions.push_back({ 0,-1});

	return directions;
}

float2 Level::GetDigDugSpawn()
{
	float2 spawnPos{};

	spawnPos.x = (m_Spawns.DigDugSinglePlayer % m_RowCol.y) * m_TileSize.x + m_Offset.x;
	spawnPos.y = (m_Spawns.DigDugSinglePlayer / m_RowCol.y) * m_TileSize.y + m_Offset.y;

	spawnPos.x += (m_TileSize.x - m_CharacterSize.x) / 2;
	spawnPos.y += (m_TileSize.y - m_CharacterSize.y) / 2;

	return spawnPos;
}

float2 Level::GetCoopSpawn(bool FirstPlayer)
{
	float2 spawnPos{};
	int tileNr{m_Spawns.DigDugMultiPlayer1 * FirstPlayer + m_Spawns.DigDugMultiPlayer2 * (!FirstPlayer)};

	spawnPos.x = (tileNr % m_RowCol.y) * m_TileSize.x + m_Offset.x;
	spawnPos.y = (tileNr / m_RowCol.y) * m_TileSize.y + m_Offset.y;

	spawnPos.x += (m_TileSize.x - m_CharacterSize.x) / 2;
	spawnPos.y += (m_TileSize.y - m_CharacterSize.y) / 2;

	return spawnPos;
}

float2 Level::GetVersusSpawn(bool isPooka)
{
	if(isPooka)
	{
		float2 spawnPos{};

		spawnPos.x = (m_Spawns.PookaSpawns[0] % m_RowCol.y) * m_TileSize.x + m_Offset.x;
		spawnPos.y = (m_Spawns.PookaSpawns[0] / m_RowCol.y) * m_TileSize.y + m_Offset.y;

		spawnPos.x += (m_TileSize.x - m_CharacterSize.x) / 2;
		spawnPos.y += (m_TileSize.y - m_CharacterSize.y) / 2;

		return spawnPos;
	}
	return GetDigDugSpawn();
}

std::vector<float2> Level::GetPookaSpawns()
{
	std::vector<float2> spawns{};
	for (int i = 0; i < m_Spawns.PookaSpawns.size(); ++i)
	{
		float2 spawnPos{};

		spawnPos.x = (m_Spawns.PookaSpawns[i] % m_RowCol.y) * m_TileSize.x + m_Offset.x;
		spawnPos.y = (m_Spawns.PookaSpawns[i] / m_RowCol.y) * m_TileSize.y + m_Offset.y;

		spawnPos.x += (m_TileSize.x - m_CharacterSize.x) / 2;
		spawnPos.y += (m_TileSize.y - m_CharacterSize.y) / 2;

		spawns.push_back(spawnPos);
	}
	return spawns;
}

std::vector<float2> Level::GetFygarSpawns(bool Versus)
{
	std::vector<float2> spawns{};
	for (int i = Versus; i < m_Spawns.FygarSpawns.size(); ++i)
	{
		float2 spawnPos{};

		spawnPos.x = (m_Spawns.FygarSpawns[i] % m_RowCol.y) * m_TileSize.x + m_Offset.x;
		spawnPos.y = (m_Spawns.FygarSpawns[i] / m_RowCol.y) * m_TileSize.y + m_Offset.y;

		spawns.push_back(spawnPos);
	}
	return spawns;
}

std::vector<float2> Level::GetRockSpawns()
{
	std::vector<float2> spawns{};
	for (int i = 0; i < m_Spawns.RockSpawns.size(); ++i)
	{
		float2 spawnPos{};

		spawnPos.x = (m_Spawns.RockSpawns[i] % m_RowCol.y) * m_TileSize.x + m_Offset.x;
		spawnPos.y = (m_Spawns.RockSpawns[i] / m_RowCol.y) * m_TileSize.y + m_Offset.y;

		spawnPos.x += (m_TileSize.x - m_CharacterSize.x) / 2;
		spawnPos.y += (m_TileSize.y - m_CharacterSize.y) / 2;

		spawns.push_back(spawnPos);
	}
	return spawns;
}

bool Level::AreConnected(int tile1, int tile2)
{
	if (tile2 > 0 && tile2 < m_LevelObjects.size())
	{
		TunnelSprite tile1Sprite = (TunnelSprite)m_LevelObjects[tile1]->GetComponent<dae::SpriteRenderer>()->GetAnimation();
		TunnelSprite tile2Sprite = (TunnelSprite)m_LevelObjects[tile2]->GetComponent<dae::SpriteRenderer>()->GetAnimation();

		if (tile1 == tile2 - 1)
			return CheckHorizontalConnection(tile1Sprite, tile2Sprite);
		if (tile1 == tile2 + 1)
			return CheckHorizontalConnection(tile2Sprite, tile1Sprite);

		if (tile1 == tile2 + m_RowCol.y)
			return checkVerticalConnection(tile2Sprite, tile1Sprite);
		if (tile1 == tile2 - m_RowCol.y)
			return checkVerticalConnection(tile1Sprite, tile2Sprite);
	}
	return false;
}
bool Level::CheckHorizontalConnection(TunnelSprite left, TunnelSprite right)
{
	switch (left)
	{
	case TunnelSprite::straightHorizontal:
	case TunnelSprite::cornerRU:
	case TunnelSprite::cornerRD:
	case TunnelSprite::tUp:
	case TunnelSprite::tRight:
	case TunnelSprite::tDown:
	case TunnelSprite::right:
	case TunnelSprite::all:
		switch (right)
		{
		case TunnelSprite::straightHorizontal:
		case TunnelSprite::cornerLU:
		case TunnelSprite::cornerLD:
		case TunnelSprite::tUp:
		case TunnelSprite::tDown:
		case TunnelSprite::tLeft:
		case TunnelSprite::left:
		case TunnelSprite::all:
			return true;
		default:
			return false;
		}
	default:
		return false;
	}
}
bool Level::checkVerticalConnection(TunnelSprite up, TunnelSprite down)
{
	switch (up)
	{
	case TunnelSprite::straightVertical:
	case TunnelSprite::cornerLD:
	case TunnelSprite::cornerRD:
	case TunnelSprite::tRight:
	case TunnelSprite::tDown:
	case TunnelSprite::tLeft:
	case TunnelSprite::down:
	case TunnelSprite::all:
		switch (down)
		{
		case TunnelSprite::straightVertical:
		case TunnelSprite::cornerLU:
		case TunnelSprite::cornerRU:
		case TunnelSprite::tUp:
		case TunnelSprite::tRight:
		case TunnelSprite::tLeft:
		case TunnelSprite::up:
		case TunnelSprite::all:
			return true;
		default: 
			return false;
		}
	default:
		return false;
	}
}

