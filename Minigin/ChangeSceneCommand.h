#pragma once
#include "BaseCommand.h"

namespace dae
{
	class ChangeSceneCommand final : public BaseCommand
	{
	public:
		ChangeSceneCommand(int newScene);
		~ChangeSceneCommand();

		void Execute(std::shared_ptr<GameObject> gameObject) override;
	private:
		int m_newScene;
	};
}
