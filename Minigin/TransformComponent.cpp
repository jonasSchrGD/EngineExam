#include "MiniginPCH.h"
#include "TransformComponent.h"

void dae::TransformComponent::SetPosition(const float x, const float y, const float z)
{
	mPosition.x = x;
	mPosition.y = y;
	mPosition.z = z;
}

dae::TransformComponent::~TransformComponent()
{
}

void dae::TransformComponent::Update()
{
}

