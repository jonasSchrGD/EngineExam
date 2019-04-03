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
		void Update() override;

		void SetPosition(float x, float y);
		void AddComponent(const std::shared_ptr<BaseComponent>& component);

		GameObject();
		virtual ~GameObject() override;
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

		const std::weak_ptr<TransformComponent> GetTransform() const { return m_pTranform; };

	private:
		std::vector<std::shared_ptr<BaseComponent>> m_pComponents;
		std::shared_ptr<TransformComponent> m_pTranform;
	};
}
