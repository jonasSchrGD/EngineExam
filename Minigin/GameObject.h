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
		void Render() const override;

		void SetPosition(float x, float y);
		void AddComponent(const std::shared_ptr<BaseComponent>& component);

		const glm::vec3& GetPosition()const { return m_pTranform->GetPosition(); };

		GameObject();
		virtual ~GameObject() override;
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

	private:
		std::vector<std::shared_ptr<BaseComponent>> m_pComponents;
		std::unique_ptr<TransformComponent> m_pTranform;
	};
}
