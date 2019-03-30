#include "MiniginPCH.h"
#include "GameObject.h"
#include "BaseComponent.h"

dae::GameObject::GameObject()
	:m_pTranform(std::make_unique<TransformComponent>())
{}

dae::GameObject::~GameObject()
{
	for (int i = m_pComponents.size() - 1; i > -1; i--)
	{
		m_pComponents.pop_back();
	}
};

void dae::GameObject::Update()
{
	for (auto child : m_pComponents)
	{
		child->Update();
	}
}

void dae::GameObject::Render() const
{
	for(auto child : m_pComponents)
	{
		child->Render();
	}
}

void dae::GameObject::SetPosition(float x, float y)
{
	m_pTranform->SetPosition(x, y, 0.0f);
}

void dae::GameObject::AddComponent(const std::shared_ptr<BaseComponent>& component)
{
	m_pComponents.push_back(component);
	component->m_GameObject = weak_from_this();
	component->GameObjectSet();
}
