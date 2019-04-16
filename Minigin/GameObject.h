#pragma once
#include <memory>

#include "SceneObject.h"
#include "TransformComponent.h"

namespace dae
{
	class BaseComponent;
	class GameObject final : public SceneObject, public std::enable_shared_from_this<GameObject>
	{
	public:
		friend CollisionComponent;

		void Update() override;

		void SetPosition(float x, float y);
		void AddComponent(const std::shared_ptr<BaseComponent>& component);
		const std::weak_ptr<TransformComponent> GetTransform() const { return m_pTranform; };

		template<class  T>
		std::shared_ptr<T> GetComponent()
		{
			for (auto component : m_pComponents)
			{
				if (typeid(*component) == typeid(T))
					return std::static_pointer_cast<T>(component);
			}
			return std::shared_ptr<T>();
		}

		GameObject();
		virtual ~GameObject() override;
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

	private:
		std::vector<std::shared_ptr<BaseComponent>> m_pComponents;
		std::shared_ptr<TransformComponent> m_pTranform;

		//collision
		virtual void OnCollisionEnter(std::shared_ptr<CollisionComponent> other) {}
		virtual void OnCollisionStay(std::shared_ptr<CollisionComponent> other) {}
		virtual void OnCollisionLeave(std::shared_ptr<CollisionComponent> other) {}

		//trigger
		virtual void OnTriggerEnter(std::shared_ptr<CollisionComponent> other) {}
		virtual void OnTriggerStay(std::shared_ptr<CollisionComponent> other) {}
		virtual void OnTriggerLeave(std::shared_ptr<CollisionComponent> other) {}
	};
}
