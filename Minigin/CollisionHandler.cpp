#include "MiniginPCH.h"
#include "CollisionHandler.h"


void CollisionHandler::Init(std::shared_ptr<BaseMap> map, std::vector<std::shared_ptr<dae::GameObject>> players)
{
	m_Map = map;
	m_Players = players;
}

void CollisionHandler::Update()
{
	for (auto player : m_Players)
	{
		auto collision = player->GetComponent<dae::CollisionComponent>();

		if (collision != nullptr)
			m_Map->DoCollisionCheck(collision);
	}

	//todo: check overlap for player with ai

}
		