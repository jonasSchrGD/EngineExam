#pragma once

namespace dae
{
	class GameObject;

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
		virtual void Update() = 0;
		virtual void Render() const = 0;
		virtual void GameObjectSet() = 0;

	private:
		friend GameObject;

		std::weak_ptr<GameObject> m_GameObject;
	};
}
