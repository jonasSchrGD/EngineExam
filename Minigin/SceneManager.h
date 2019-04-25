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
		void AddScene(std::shared_ptr<Scene> scene) { m_Scenes.push_back(scene); }
		void SetActiveScene(int sceneId)
		{
			if (sceneId >= 0 && sceneId < (int)m_Scenes.size())
				m_ActiveScene = sceneId;
		}

		void Update();
		void Render();

	private:
		std::vector<std::shared_ptr<Scene>> m_Scenes;
		int m_ActiveScene = 0;
	};

}
