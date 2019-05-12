#include "MiniginPCH.h"
#include "GameObject.h"
#include "BaseComponent.h"
#include "BaseRenderComponent.h"

dae::GameObject::GameObject()
	: m_pTranform(std::make_unique<TransformComponent>())
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
		child->Update();
	}
}

void dae::GameObject::Initialize()
{
	for (auto child : m_pComponents)
	{
		child->Initialize();
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

void dae::GameObject::AddComponent(const std::shared_ptr<BaseComponent>& component)
{
	m_pComponents.push_back(component);
	component->m_GameObject = weak_from_this();

	auto raw = component.get();
	if (dynamic_cast<BaseRenderComponent*>(raw))
		m_Subject.Notify(shared_from_this(), 0);

	if (m_IsInitialized)
		component->Initialize();
}

void dae::GameObject::AddObServer(std::shared_ptr<Observer> observer)
{
	m_Subject.AddObserver(observer);
}

void dae::GameObject::RemoveObserver(std::shared_ptr<Observer> observer)
{
	m_Subject.RemoveObserver(observer);
}