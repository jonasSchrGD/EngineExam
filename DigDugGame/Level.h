#pragma once
#include "GameObject.h"
#include "structs.h"
#include "TunnelUpdate.h"

class Level final
{
public:
	struct Spawns
	{
		int DigDugSinglePlayer;
		int DigDugMultiPlayer1;
		int DigDugMultiPlayer2;
		std::vector<int> PookaSpawns;
		std::vector<int> FygarSpawns;
		std::vector<int> RockSpawns;
	};

	Level();
	~Level();

	void Initialize(float2 characterSize, float centerRange);

	void AddGameObject(std::shared_ptr<dae::GameObject> object);

	void AddToScene(std::shared_ptr<dae::Scene> scene);

	void SetOffset(float x, float y) { m_Offset = { x, y }; }
	void SetTileSize(float width, float height) { m_TileSize = {width, height}; }
	void SetSpawn(Spawns spawns) { m_Spawns = spawns; }
	void SetRowCol(int rows, int cols) { m_RowCol = { rows, cols }; }

	bool IsTunnel(float2 pos);
	bool Center(std::shared_ptr<dae::GameObject> object, bool CenterX);
	bool IsInGrid(float2 pos);

	float2 GetNextPos(float2 currentPos, int2 direction);
	std::vector<int2> GetPossibleDirections(float2 currentPos);

	const float2& GetTileSize() const { return m_TileSize; }
	float2 GetDigDugSpawn();
	float2 GetCoopSpawn(bool FirstPlayer = true);
	float2 GetVersusSpawn(bool isPooka = false);
	std::vector<float2> GetPookaSpawns();
	std::vector<float2> GetFygarSpawns(bool Versus = false);
	std::vector<float2> GetRockSpawns();

private:
	std::vector<std::shared_ptr<dae::GameObject>> m_LevelObjects;
	Spawns m_Spawns;
	int2 m_RowCol;
	float2 m_Offset;
	float2 m_TileSize;
	float2 m_CharacterSize;
	float m_CenterRange;

	bool AreConnected(int tile1, int tile2);
	bool CheckHorizontalConnection(TunnelSprite left, TunnelSprite right);
	bool checkVerticalConnection(TunnelSprite up, TunnelSprite down);
};

