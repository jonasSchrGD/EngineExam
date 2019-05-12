#pragma once
#include <BaseLoader.h>
#include "Level.h"

class LevelLoader final : public dae::ContentLoader<Level>
{
public:
	LevelLoader();
	~LevelLoader();

	std::shared_ptr<Level> LoadContent(const std::string& assetFile) override;
	void Initialize() override{}

private:
	void AddEmptyTiles(int startCount, int endCount);

	void AddSpriteRenderer(std::shared_ptr<dae::GameObject> tile, const std::string& startingState);
	void AddCollisionComponent(std::shared_ptr<dae::GameObject> tile, int tileId);
	void AddTunnelUpdate(std::shared_ptr<dae::GameObject> tile);

	void ReadMapInfo(std::ifstream& input);
	void ReadTiles(std::ifstream& input);

	std::shared_ptr<Level> m_Level;
	int m_Rows, m_Cols;
	float m_TileWidth, m_TileHeight;
	float m_OffsetX, m_OffsetY;
};

