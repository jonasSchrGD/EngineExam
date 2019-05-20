#pragma once
#include "GameObject.h"
#include "SpriteRenderer.h"
#include "IdleState.h"
#include "CharacterControllerComponent.h"
#include "CollisionComponent.h"
#include "WanderState.h"
#include "DigDugColllision.h"
#include "EnemyCollisionHandler.h"

class prefabs final
{
public:
	//digdug
	static std::shared_ptr<dae::GameObject> GetPrefab(float2 characterSize, std::shared_ptr<Level> level, int playerNr)
	{
		std::shared_ptr<dae::GameObject> digdug = std::make_shared<dae::GameObject>();
		
		auto spriterenderer = std::make_shared<dae::SpriteRenderer>("DigDugSheet.png", 0.2f, 4, 6, 12, characterSize);
		spriterenderer->SetFramesPerAnim(std::vector<int>{2,2,2,2,2,2,2,2,2,1,1,4});
		digdug->AddComponent(spriterenderer);

		auto movement = std::make_shared<IdleState>(level);
		auto characterController = std::make_shared<dae::CharacterControllerComponent>(movement, playerNr);
		digdug->AddComponent(characterController);

		auto collision = std::make_shared<dae::CollisionComponent>(characterSize.x, characterSize.y, true);
		collision->SetTrigger(true);
		digdug->AddComponent(collision);

		auto collisionHandler = std::make_shared<DigDugColllision>();
		digdug->AddComponent(collisionHandler);

		return digdug;
	}

	//pooka / fygar
	static std::shared_ptr<dae::GameObject> GetPrefab(float2 characterSize, std::shared_ptr<Level> level, bool PlayerControlled, int playerNr = 0, bool isPooka = true)
	{
		std::shared_ptr<dae::GameObject> Enemy = std::make_shared<dae::GameObject>();

		if(isPooka)
		{
			auto spriterenderer = std::make_shared<dae::SpriteRenderer>("PookaSheet.png", 0.3f, 4, 3, 4, characterSize);
			spriterenderer->SetFramesPerAnim(std::vector<int>{2, 2, 4, 1});
			Enemy->AddComponent(spriterenderer);
			spriterenderer->SetAnimation(0);
		}
		else
		{
			auto spriterenderer = std::make_shared<dae::SpriteRenderer>("FygarRun.png", 0.3f, 2, 1, 1, characterSize);
			Enemy->AddComponent(spriterenderer);
		}

		if(PlayerControlled)
		{
			auto movement = std::make_shared<IdleState>(level);
			auto characterController = std::make_shared<dae::CharacterControllerComponent>(movement, playerNr);
			Enemy->AddComponent(characterController);
		}
		else
		{
			auto movement = std::make_shared<WanderState>(level);
			auto characterController = std::make_shared<dae::CharacterControllerComponent>(movement, -1);
			Enemy->AddComponent(characterController);
		}
		
		auto collision = std::make_shared<dae::CollisionComponent>(characterSize.x, characterSize.y, true);
		collision->SetTrigger(true);
		Enemy->AddComponent(collision);

		auto collisionhandler = std::make_shared<EnemyCollisionHandler>();
		Enemy->AddComponent(collisionhandler);

		return Enemy;
	}

};
