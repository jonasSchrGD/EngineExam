#pragma once
#include "BaseMap.h"
#include "Singleton.h"
#include "GameObject.h"

//class that handles all the collision in the game, collision in digdug is verry simple
class CollisionHandler final : public dae::Singleton<CollisionHandler>
{
public:
	void Init(std::shared_ptr<BaseMap> map, std::vector<std::shared_ptr<dae::GameObject>> players = std::vector<std::shared_ptr<dae::GameObject>>());
	void Update();

private:
	std::shared_ptr<BaseMap> m_Map;

	//players will only be set during gamemode selection, no need for a objectpool or something related
	std::vector<std::shared_ptr<dae::GameObject>> m_Players;
};

