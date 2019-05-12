#pragma once
#include <memory>

#include "Scene.h"

namespace dae
{
	class SceneObject //todo: remove sceneObject, i don't get the point of this
	{
		public:
		virtual void Update() = 0;
		virtual void Initialize() = 0;

		virtual void Load() = 0;
		virtual void Unload() = 0;

		void SetScene(std::shared_ptr<Scene> scene) { m_Scene = scene; }
		std::shared_ptr<Scene> GetScene()
		{
			return m_Scene.lock();
		}
		
		SceneObject() = default;
		virtual ~SceneObject() = default;
		SceneObject(const SceneObject& other) = delete;
		SceneObject(SceneObject&& other) = delete;
		SceneObject& operator=(const SceneObject& other) = delete;
		SceneObject& operator=(SceneObject&& other) = delete;

	private:
		std::weak_ptr<Scene> m_Scene;

	};
}
