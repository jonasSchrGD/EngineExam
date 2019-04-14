#pragma once
#include "SceneObject.h"
#include "CollisionComponent.h"

class BaseMap : public dae::SceneObject
{
public:
	BaseMap() = default;
	~BaseMap() = default;

	void Update() override = 0;
	virtual void DoCollisionCheck(std::shared_ptr<dae::CollisionComponent> collisionComp) const = 0;
};

