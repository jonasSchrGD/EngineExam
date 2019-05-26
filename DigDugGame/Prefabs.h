#pragma once
#include "GameObject.h"
#include "SpriteRenderer.h"
#include "IdleState.h"
#include "CharacterControllerComponent.h"
#include "CollisionComponent.h"
#include "WanderState.h"
#include "DigDugColllision.h"
#include "EnemyCollisionHandler.h"
#include "AttackBehaviour.h"
#include "LifeTime.h"
#include "Projectile.h"

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

		auto attack = std::make_shared<AttackBehaviour>();
		digdug->AddComponent(attack);
		
		return digdug;
	}

	//pooka / fygar
	static std::shared_ptr<dae::GameObject> GetPrefab(float2 characterSize, std::shared_ptr<Level> level, bool PlayerControlled, int playerNr = 0, bool isPooka = true)
	{
		std::shared_ptr<dae::GameObject> Enemy = std::make_shared<dae::GameObject>();

		if(isPooka)
		{
			auto spriterenderer = std::make_shared<dae::SpriteRenderer>("PookaSheet.png", 0.3f, 4, 3, 7, characterSize);
			spriterenderer->SetFramesPerAnim(std::vector<int>{2, 2, 1, 1, 1, 1, 1});
			Enemy->AddComponent(spriterenderer);
			spriterenderer->SetAnimation(0);
		}
		else
		{
			auto spriterenderer = std::make_shared<dae::SpriteRenderer>("FygarSheet.png", 0.3f, 4, 3, 7, characterSize);
			spriterenderer->SetFramesPerAnim(std::vector<int>{2, 2, 1, 1, 1, 1, 1});
			Enemy->AddComponent(spriterenderer);
		}

		if(PlayerControlled)
		{
			auto movement = std::make_shared<IdleState>(level);

			auto characterController = std::make_shared<dae::CharacterControllerComponent>(movement, playerNr);
			Enemy->AddComponent(characterController);

			auto attack = std::make_shared<AttackBehaviour>();
			Enemy->AddComponent(attack);
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

		auto collisionhandler = std::make_shared<EnemyCollisionHandler>(!isPooka);
		Enemy->AddComponent(collisionhandler);

		return Enemy;
	}

	//fire
	static std::shared_ptr<dae::GameObject> GetPrefab(bool drawLeft)
	{
		std::shared_ptr<dae::GameObject> fire = std::make_shared<dae::GameObject>();

		auto collisioncomponent = std::make_shared<dae::CollisionComponent>(80.f, 40.f, true);
		fire->AddComponent(collisioncomponent);

		if(drawLeft)
		{
			auto spriterenderer = std::make_shared<dae::SpriteRenderer>("fireL.png", 0.2f, 3, 1, 1, float2{ 80, 40 });
			fire->AddComponent(spriterenderer);
		}
		else
		{
			auto spriterenderer = std::make_shared<dae::SpriteRenderer>("fireR.png", 0.2f, 3, 1, 1, float2{ 80, 40 });
			fire->AddComponent(spriterenderer);
		}

		auto lifetime = std::make_shared<dae::LifeTime>(0.6f);
		fire->AddComponent(lifetime);

		return fire;
	}

	//pump
	static std::shared_ptr<dae::GameObject> GetPrefab(int2 direction)
	{
		std::shared_ptr<dae::GameObject> pump = std::make_shared<dae::GameObject>();

		auto collisioncomponent = std::make_shared<dae::CollisionComponent>(30.f, 30.f, true);
		collisioncomponent->SetTrigger(true);
		pump->AddComponent(collisioncomponent);

		auto spriterenderer = std::make_shared<dae::SpriteRenderer>("pump.png", 0.2f, 4, 1, 4, float2{ 30, 30 });
		pump->AddComponent(spriterenderer);

		auto projectile = std::make_shared<Projectile>(direction);
		pump->AddComponent(projectile);

		return pump;
	}

};
