#include "pch.h"
#include "Level.h"


Level::Level()
	: m_Offset()
	, m_TileSize()
	, m_CharacterSize({30,30})
	, m_CenterRange(10)
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
	}
	return isInCenterArea;
}

