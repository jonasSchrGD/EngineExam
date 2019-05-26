#pragma once

namespace dae
{
	class SceneObject;
	class BaseRenderComponent;
	class RenderCompObserver;
	class Scene : public std::enable_shared_from_this<Scene>
	{
	public:
		void Add(const std::shared_ptr<SceneObject>& object);
		void Remove(const std::shared_ptr<SceneObject>& object);

		void Update();
		void Render() const;

		void Initialize();
		virtual void SetupScene() = 0;

		virtual void LoadScene();
		virtual void UnloadScene();
		void DoRemove();

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
		std::vector<std::shared_ptr<SceneObject>> mObjects{};
		std::vector<std::shared_ptr<SceneObject>> m_ObjectsToAdd;
		std::vector<std::shared_ptr<SceneObject>> m_ObjectsToRemove;
		std::vector<std::shared_ptr<BaseRenderComponent>> m_RenderComponents;

		std::shared_ptr<RenderCompObserver> m_Observer;

		static unsigned int idCounter;

		bool m_IsInitialized;
	};

}
