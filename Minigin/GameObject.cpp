#include "MiniginPCH.h"
#include "GameObject.h"
#include "BaseComponent.h"
#include "BaseRenderComponent.h"
#include <algorithm>

dae::GameObject::GameObject()
	: m_pTranform(std::make_shared<TransformComponent>())
	, m_IsInitialized(false)
{
}

dae::GameObject::~GameObject()
{
	for (size_t i = m_pComponents.size() - 1; i > -1; i--)
	{
		m_pComponents.pop_back();
	}
}

void dae::GameObject::OnCollisionEnter(std::shared_ptr<CollisionComponent> other)
{
	for (auto child : m_pComponents)
	{
		child->OnCollisionEnter(other);
	}
}
void dae::GameObject::OnCollisionStay(std::shared_ptr<CollisionComponent> other)
{
	for (auto child : m_pComponents)
	{
		child->OnCollisionStay(other);
	}
}
void dae::GameObject::OnCollisionLeave(std::shared_ptr<CollisionComponent> other)
{
	for (auto child : m_pComponents)
	{
		child->OnCollisionLeave(other);
	}
}

void dae::GameObject::OnTriggerEnter(std::shared_ptr<CollisionComponent> other)
{
	for (auto child : m_pComponents)
	{
		child->OnTriggerEnter(other);
	}
}
void dae::GameObject::OnTriggerStay(std::shared_ptr<CollisionComponent> other)
{
	for (auto child : m_pComponents)
	{
		child->OnTriggerStay(other);
	}
}
void dae::GameObject::OnTriggerLeave(std::shared_ptr<CollisionComponent> other)
{
	for (auto child : m_pComponents)
	{
		child->OnTriggerLeave(other);
	}
}

void dae::GameObject::Update()
{
	//todo: use an allocator for less memory acces
	for (auto child : m_pComponents)
	{
		if (std::find(m_pComponentsToRemove.begin(), m_pComponentsToRemove.end(), child) == m_pComponentsToRemove.end())
			child->Update();
	}

	for (int i = 0; i < (int)m_pComponentsToRemove.size(); ++i)
	{
		m_pComponents.erase(std::remove(m_pComponents.begin(), m_pComponents.end(), m_pComponentsToRemove[i]));
	}
	m_pComponentsToRemove.clear();
}

void dae::GameObject::Initialize()
{
	if (!m_IsInitialized)
	{
		//for (auto child : m_pComponents)//can't handle change in container
		for (int i = 0; i < (int)m_pComponents.size(); ++i)
		{
			auto raw = m_pComponents[i].get();
			if (dynamic_cast<BaseRenderComponent*>(raw))
				m_Subject.Notify(shared_from_this());

			m_pComponents[i]->Initialize();
		}
		m_IsInitialized = true;
	}
}

void dae::GameObject::Load()
{
	for (auto child : m_pComponents)
	{
		child->Load();
	}
}

void dae::GameObject::Unload()
{
	for (auto child : m_pComponents)
	{
		child->Unload();
	}
}

void dae::GameObject::SetPosition(float x, float y)
{
	m_pTranform->SetPosition(x, y, 0.0f);
}

void dae::GameObject::AddComponent(std::shared_ptr<BaseComponent> component)
{
	m_pComponents.push_back(component);
	component->m_GameObject = weak_from_this();

	auto raw = component.get();
	if (dynamic_cast<BaseRenderComponent*>(raw))
		m_Subject.Notify(shared_from_this());

	if (m_IsInitialized)
	{
		component->Initialize();
	}
}

void dae::GameObject::AddObServer(std::shared_ptr<Observer> observer)
{
	m_Subject.AddObserver(observer);
}

void dae::GameObject::RemoveObserver(std::shared_ptr<Observer> observer)
{
	m_Subject.RemoveObserver(observer);
}