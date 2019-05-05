#pragma once
#include "BaseRenderComponent.h"

namespace dae
{
	class SceneObject;
	class Scene
	{
	public:
		void Add(const std::shared_ptr<SceneObject>& object);

		void Update();
		void Render() const;

		virtual void Initialize() = 0;

		Scene(const std::string& name);
		virtual ~Scene() = default;
		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;

	protected:
		void AddFpsComponent();

	private: 
		std::string mName{};
		std::vector <std::shared_ptr<SceneObject>> mObjects{};
		std::vector<std::shared_ptr<BaseRenderComponent>> m_RenderComponents;

		static unsigned int idCounter; 
	};

}
