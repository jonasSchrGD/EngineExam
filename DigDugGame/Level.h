#pragma once
#include "GameObject.h"
#include "structs.h"

class Level final
{
public:
	Level();
	~Level();

	void Initialize(float2 characterSize, float centerRange);

	void AddGameObject(std::shared_ptr<dae::GameObject> object);

	void AddToScene(std::shared_ptr<dae::Scene> scene);

	void SetOffset(float x, float y) { m_Offset = { x, y }; }
	void SetTileSize(float width, float height) { m_TileSize = {width, height}; }

	bool Center(std::shared_ptr<dae::GameObject> object, bool CenterX);

private:
	std::vector<std::shared_ptr<dae::GameObject>> m_LevelObjects;
	float2 m_Offset;
	float2 m_TileSize;
	float2 m_CharacterSize;
	float m_CenterRange;
};

