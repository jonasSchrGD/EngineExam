#include "pch.h"
#include "LevelLoader.h"
#include <fstream>
#include "Animations.h"
#include "RockBehaviour.h"

LevelLoader::LevelLoader()
	: m_Spawns()
	, m_Rows(0)
	, m_Cols(0)
	, m_TileWidth(0)
	, m_TileHeight(0)
	, m_OffsetX(0)
	, m_OffsetY(0)
{
}

LevelLoader::~LevelLoader()
{
}

std::shared_ptr<Level> LevelLoader::LoadContent(const std::string& assetFile)
{
	m_Level = std::make_shared<Level>();
	m_Spawns.FygarSpawns.clear();
	m_Spawns.PookaSpawns.clear();
	m_Spawns.RockSpawns.clear();

	std::ifstream input{};
	input.open(assetFile);
	std::string line;

	while (std::getline(input, line))
	{
		if (line == "tileInfo:")
		{
			ReadTiles(input);
			m_Level->SetOffset(m_OffsetX, m_OffsetY);
			m_Level->SetTileSize(m_TileWidth, m_TileHeight);
			m_Level->SetSpawn(m_Spawns);
			m_Level->SetRowCol(m_Rows, m_Cols);
		}

		if (line == "mapInfo:")
			ReadMapInfo(input);
	}

	input.close();

	return m_Level;
}

int LevelLoader::GetTunnelEnum(const std::string& startingState)
{
	if (startingState == "straightVertical")
	{
		return (int)TunnelSprite::straightVertical;
	}
	if (startingState == "straightHorizontal")
	{
		return (int)TunnelSprite::straightHorizontal;
	}

	if (startingState == "cornerLU")
	{
		return (int)TunnelSprite::cornerLU;
	}
	if (startingState == "cornerRU")
	{
		return (int)TunnelSprite::cornerRU;
	}
	if (startingState == "cornerLD")
	{
		return (int)TunnelSprite::cornerLD;
	}
	if (startingState == "cornerRD")
	{
		return (int)TunnelSprite::cornerRD;
	}

	if (startingState == "tUp")
	{
		return (int)TunnelSprite::tUp;
	}
	if (startingState == "tDown")
	{
		return (int)TunnelSprite::tDown;
	}
	if (startingState == "tLeft")
	{
		return (int)TunnelSprite::tLeft;
	}
	if (startingState == "tRight")
	{
		return (int)TunnelSprite::tRight;
	}

	if (startingState == "left")
	{
		return (int)TunnelSprite::left;
	}
	if (startingState == "up")
	{
		return (int)TunnelSprite::up;
	}
	if (startingState == "right")
	{
		return (int)TunnelSprite::right;
	}
	if (startingState == "down")
	{
		return (int)TunnelSprite::down;
	}

	if (startingState == "all")
	{
		return (int)TunnelSprite::all;
	}
	if (startingState == "none")
	{
		return (int)TunnelSprite::none;
	}
	return 15;
}

void LevelLoader::ReadMapInfo(std::ifstream& input)
{
	std::string line;

	std::getline(input, line);
	while (line != "}")
	{
		int pos = (int)line.find("rows:");
		if (pos != std::string::npos)
		{
			pos += 6;
			int end = (int)line.find(";");

			m_Rows = std::stoi(line.substr(pos, end - pos));
			std::getline(input, line);
			continue;
		}

		pos = (int)line.find("cols:");
		if (pos != std::string::npos)
		{
			pos += 6;
			int end = (int)line.find(";");

			m_Cols = std::stoi(line.substr(pos, end - pos));
			std::getline(input, line);
			continue;
		}

		pos = (int)line.find("width:");
		if (pos != std::string::npos)
		{
			pos += 7;
			int end = (int)line.find(";");

			m_TileWidth = std::stof(line.substr(pos, end - pos));
			std::getline(input, line);
			continue;
		}
		
		pos = (int)line.find("height:");
		if (pos != std::string::npos)
		{
			pos += 8;
			int end = (int)line.find(";");

			m_TileHeight = std::stof(line.substr(pos, end - pos));
			std::getline(input, line);
			continue;
		}
		
		pos = (int)line.find("offsetX:");
		if (pos != std::string::npos)
		{
			pos += 9;
			int end = (int)line.find(";");

			m_OffsetX = std::stof(line.substr(pos, end - pos));
			std::getline(input, line);
			continue;
		}
		
		pos = (int)line.find("offsetY:");
		if (pos != std::string::npos)
		{
			pos += 9;
			int end = (int)line.find(";");

			m_OffsetY = std::stof(line.substr(pos, end - pos));
			std::getline(input, line);
			continue;
		}
		
		//template
		//pos = (int)line.find(":");
		//if (pos != std::string::npos)
		//{

		//std::getline(input, line);
		//	continue;
		//}

		std::getline(input, line);
	}
}

void LevelLoader::ReadTiles(std::ifstream& input)
{
	int tilesAdded{};
	std::string line;
	while (std::getline(input, line))
	{
		if (std::find(line.begin(), line.end(), '{') != line.end())
		{
			auto tile = std::make_shared<dae::GameObject>();

			std::getline(input, line);

			//read place where tile is supposed to be
			int it = (int)line.find("tile:");
			it += 6;
			int end = (int)line.find(';');
			int tileId = std::stoi(line.substr(it, end - it));

			//read starting state of tile
			std::getline(input, line);
			it = (int)line.find("sprite:");
			it += 8;
			end = (int)line.find(';');
			std::string state = line.substr(it, end - it);

			m_Level->AddTunnel(std::pair<int, int>(tileId, GetTunnelEnum(state)));
			tilesAdded = tileId + 1;

			std::getline(input, line);

			//read spawn typy if any defined
			if(std::find(line.begin(), line.end(), '}') == line.end())
			{
				it = (int)line.find("spawn:");
				it += 7;
				end = (int)line.find(';');
				std::string spawnType = line.substr(it, end - it);

				if (spawnType == "DigDugS")
					m_Spawns.DigDugSinglePlayer = tileId;

				if (spawnType == "DigDugM1")
					m_Spawns.DigDugMultiPlayer1 = tileId;

				if (spawnType == "DigDugM2")
					m_Spawns.DigDugMultiPlayer2 = tileId;

				if (spawnType == "Pooka")
					m_Spawns.PookaSpawns.push_back(tileId);

				if (spawnType == "Fygar")
					m_Spawns.FygarSpawns.push_back(tileId);

				if (spawnType == "Rock")
					m_Spawns.RockSpawns.push_back(tileId);


				std::getline(input, line);
			}
		}
	}
}
