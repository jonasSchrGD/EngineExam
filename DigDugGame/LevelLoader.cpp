#include "pch.h"
#include "LevelLoader.h"
#include <fstream>
#include "CollisionComponent.h"
#include "SpriteRenderer.h"
#include "Animations.h"
#include "TunnelUpdate.h"


LevelLoader::LevelLoader()
	: m_Rows(0)
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
		}

		if (line == "mapInfo:")
			ReadMapInfo(input);
	}

	input.close();

	return m_Level;
}

void LevelLoader::AddEmptyTiles(int startCount, int endCount)
{
	for (int i = startCount; i < endCount; ++i)
	{
		auto tile = std::make_shared<dae::GameObject>();
		AddCollisionComponent(tile, i);
		AddSpriteRenderer(tile, "none");
		AddTunnelUpdate(tile);
		
		m_Level->AddGameObject(tile);
	}
}

void LevelLoader::AddSpriteRenderer(std::shared_ptr<dae::GameObject> tile, const std::string& startingState)
{
	auto spriterenderer = std::make_shared<dae::SpriteRenderer>("Tunnels.png", 0.25f, 4, 4, 16, float2{ m_TileWidth, m_TileHeight });
	tile->AddComponent(spriterenderer);

	if (startingState == "straightVertical")
	{
		spriterenderer->SetAnimation((int)TunnelSprite::straightVertical);
		return;
	}
	if (startingState == "straightHorizontal")
	{
		spriterenderer->SetAnimation((int)TunnelSprite::straightHorizontal);
		return;
	}

	if (startingState == "cornerLU")
	{
		spriterenderer->SetAnimation((int)TunnelSprite::cornerLU);
		return;
	}
	if (startingState == "cornerRU")
	{
		spriterenderer->SetAnimation((int)TunnelSprite::cornerRU);
		return;
	}
	if (startingState == "cornerLD")
	{
		spriterenderer->SetAnimation((int)TunnelSprite::cornerLD);
		return;
	}
	if (startingState == "cornerRD")
	{
		spriterenderer->SetAnimation((int)TunnelSprite::cornerRD);
		return;
	}

	if (startingState == "tUp")
	{
		spriterenderer->SetAnimation((int)TunnelSprite::tUp);
		return;
	}
	if (startingState == "tDown")
	{
		spriterenderer->SetAnimation((int)TunnelSprite::tDown);
		return;
	}
	if (startingState == "tLeft")
	{
		spriterenderer->SetAnimation((int)TunnelSprite::tLeft);
		return;
	}
	if (startingState == "tRight")
	{
		spriterenderer->SetAnimation((int)TunnelSprite::tRight);
		return;
	}

	if (startingState == "left")
	{
		spriterenderer->SetAnimation((int)TunnelSprite::left);
		return;
	}
	if (startingState == "up")
	{
		spriterenderer->SetAnimation((int)TunnelSprite::up);
		return;
	}
	if (startingState == "right")
	{
		spriterenderer->SetAnimation((int)TunnelSprite::right);
		return;
	}
	if (startingState == "down")
	{
		spriterenderer->SetAnimation((int)TunnelSprite::down);
		return;
	}

	if (startingState == "all")
	{
		spriterenderer->SetAnimation((int)TunnelSprite::all);
		return;
	}
	if (startingState == "none")
	{
		spriterenderer->SetAnimation((int)TunnelSprite::none);
	}
}

void LevelLoader::AddCollisionComponent(std::shared_ptr<dae::GameObject> tile, int tileId)
{
	tile->GetTransform().lock()->SetPosition(m_TileWidth * (tileId % m_Cols) + m_OffsetX, m_TileHeight * (tileId / m_Cols) + m_OffsetY, 0);
	auto collider = std::make_shared<dae::CollisionComponent>(m_TileWidth, m_TileHeight, true, true);
	collider->SetTrigger(true);
	tile->AddComponent(collider);
}

void LevelLoader::AddTunnelUpdate(std::shared_ptr<dae::GameObject> tile)
{
	auto comp = std::make_shared<TunnelUpdate>();
	tile->AddComponent(comp);
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

			//add empty tiles until that tile
			AddEmptyTiles(tilesAdded, tileId);

			//read starting state of tile
			std::getline(input, line);
			it = (int)line.find("sprite:");
			it += 8;
			end = (int)line.find(';');
			std::string state = line.substr(it, end - it);

			//add components to new tiles
			AddSpriteRenderer(tile, state);
			AddCollisionComponent(tile, tileId);
			AddTunnelUpdate(tile);

			m_Level->AddGameObject(tile);
			tilesAdded = tileId + 1;
			std::getline(input, line);
		}
	}
	AddEmptyTiles(tilesAdded, m_Cols * m_Rows);
}
