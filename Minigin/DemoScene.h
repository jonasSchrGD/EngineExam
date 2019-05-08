#pragma once
#include "Scene.h"
namespace dae
{
	class DemoScene final : public Scene
	{
	public:
		DemoScene(const std::string& name);
		~DemoScene() = default;

		void LoadScene() override;
	};
}
