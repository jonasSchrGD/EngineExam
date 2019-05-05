#pragma once
#include <BaseCommand.h>

class ChangeSceneCommand final : public dae::BaseCommand
{
public:
	ChangeSceneCommand(int newScene);
	~ChangeSceneCommand();

	void Execute(std::shared_ptr<dae::GameObject> gameObject) override;
private:
	int m_newScene;
};

