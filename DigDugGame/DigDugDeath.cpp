#include "pch.h"
#include "DigDugDeath.h"
#include "SpriteRenderer.h"
#include "Animations.h"
#include "CharacterControllerComponent.h"


DigDugDeath::DigDugDeath()
{
}


DigDugDeath::~DigDugDeath()
{
}

std::shared_ptr<dae::BaseState> DigDugDeath::Update(std::shared_ptr<dae::GameObject> gameObject, dae::BaseCommand*& commandOutput, int controller)
{
	UNREFERENCED_PARAMETER(commandOutput);
	UNREFERENCED_PARAMETER(controller);

	auto spriterenderer = gameObject->GetComponent<dae::SpriteRenderer>();

	if(spriterenderer->GetAnimation() == (int)DigDugAnimation::right || spriterenderer->GetAnimation() == (int)DigDugAnimation::left ||
		spriterenderer->GetAnimation() == (int)DigDugAnimation::digRight || spriterenderer->GetAnimation() == (int)DigDugAnimation::digLeft)
		spriterenderer->SetAnimation((int)DigDugAnimation::flatV);

	if (spriterenderer->GetAnimation() == (int)DigDugAnimation::up || spriterenderer->GetAnimation() == (int)DigDugAnimation::down ||
		spriterenderer->GetAnimation() == (int)DigDugAnimation::digUp || spriterenderer->GetAnimation() == (int)DigDugAnimation::digDown)
		spriterenderer->SetAnimation((int)DigDugAnimation::flatH);

	return std::make_shared<BaseState>();
}
