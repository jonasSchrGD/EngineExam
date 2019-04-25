#pragma once

namespace dae
{
	class SceneObject;
	class Scene
	{
	public:
		void Add(const std::shared_ptr<SceneObject>& object);

		void Update();
		void Render() const;

		Scene(const std::string& name);
		virtual ~Scene();
		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;

	protected:
		void AddFpsComponent();
		virtual void Initialize() = 0;

	private: 
		std::string mName{};
		std::vector <std::shared_ptr<SceneObject>> mObjects{};

		static unsigned int idCounter; 
	};

}
