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
	int GetTunnelEnum(const std::string& startingState);

	void ReadMapInfo(std::ifstream& input);
	void ReadTiles(std::ifstream& input);

	std::shared_ptr<Level> m_Level;
	Level::Spawns m_Spawns;
	int m_Rows, m_Cols;
	float m_TileWidth, m_TileHeight;
	float m_OffsetX, m_OffsetY;
};

