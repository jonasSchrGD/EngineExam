#pragma once

namespace dae
{
	class GameObject;
	class CollisionComponent;

	class BaseComponent
	{
	public:
		std::shared_ptr<GameObject> GetGameObject() const { return m_GameObject.lock(); };

		BaseComponent();
		virtual  ~BaseComponent() = default;

		BaseComponent(const BaseComponent& other) = delete;
		BaseComponent(const BaseComponent&& other) = delete;
		BaseComponent& operator=(const BaseComponent& other) = delete;
		BaseComponent& operator=(BaseComponent&& other) = delete;

	protected:
		virtual void Update(){}
		virtual void GameObjectSet(){}

		//collision
		virtual void OnCollisionEnter(std::shared_ptr<CollisionComponent> other) {}
		virtual void OnCollisionStay(std::shared_ptr<CollisionComponent> other) {}
		virtual void OnCollisionLeave(std::shared_ptr<CollisionComponent> other) {}

		//trigger
		virtual void OnTriggerEnter(std::shared_ptr<CollisionComponent> other) {}
		virtual void OnTriggerStay(std::shared_ptr<CollisionComponent> other) {}
		virtual void OnTriggerLeave(std::shared_ptr<CollisionComponent> other) {}

	private:
		friend GameObject;

		std::weak_ptr<GameObject> m_GameObject;
	};
}
