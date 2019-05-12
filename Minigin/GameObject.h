#pragma once
#include <memory>

#include "SceneObject.h"
#include "TransformComponent.h"
#include "Observer.h"
#include "Subject.h"

namespace dae
{
	class BaseComponent;
	class GameObject final : public SceneObject, public std::enable_shared_from_this<GameObject>
	{
	public:
		friend CollisionComponent;

		void Update() override;
		void Initialize() override;

		void Load() override;
		void Unload() override;

		void SetPosition(float x, float y);
		void AddComponent(const std::shared_ptr<BaseComponent>& component);
		std::weak_ptr<TransformComponent> GetTransform() const { return m_pTranform; };

		void AddObServer(std::shared_ptr<Observer> observer);
		void RemoveObserver(std::shared_ptr<Observer> observer);

		template<class  T>
		std::shared_ptr<T> GetComponent()
		{
			for (auto component : m_pComponents)
			{
				auto raw = component.get();
				if (typeid(raw) == typeid(T))
					return std::static_pointer_cast<T>(component);

				if (dynamic_cast<T*>(raw))
					return std::static_pointer_cast<T>(component);
			}

			return std::shared_ptr<T>();
		}

		GameObject();
		~GameObject() override;
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

	private:
		std::vector<std::shared_ptr<BaseComponent>> m_pComponents;
		std::shared_ptr<TransformComponent> m_pTranform;
		Subject m_Subject;
		bool m_IsInitialized;

		//collision
		void OnCollisionEnter(std::shared_ptr<CollisionComponent> other);
		void OnCollisionStay(std::shared_ptr<CollisionComponent> other);
		void OnCollisionLeave(std::shared_ptr<CollisionComponent> other);

		//trigger
		void OnTriggerEnter(std::shared_ptr<CollisionComponent> other);
		void OnTriggerStay(std::shared_ptr<CollisionComponent> other);
		void OnTriggerLeave(std::shared_ptr<CollisionComponent> other);
	};
}
