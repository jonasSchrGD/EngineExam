#pragma once
#include "Singleton.h"

#include <vector>
#include <memory>

namespace dae
{
	class Scene;
	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		void Initialize();

		void AddScene(std::shared_ptr<Scene> scene);
		void SetActiveScene(int sceneId);

		void Update();
		void Render();

		void Clear();

	private:
		std::vector<std::shared_ptr<Scene>> m_Scenes;
		int m_ActiveScene = 0;
	};

}
