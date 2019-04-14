#include "MiniginPCH.h"
#include "CollisionHandler.h"


void CollisionHandler::Init(std::shared_ptr<BaseMap> map, std::vector<std::shared_ptr<dae::GameObject>> players)
{
	m_Map = map;
	m_Players = players;
}

void CollisionHandler::Update()
{
	//todo: add characterController

	//check collision for player with the map

	//check overlap for player with ai

}
		