#pragma once
#include <Command.h>

class ChangeSceneCommand final : public dae::Command
{
public:
	ChangeSceneCommand(int newScene);
	~ChangeSceneCommand();

	void Execute(std::shared_ptr<dae::GameObject> gameObject) override;
private:
	int m_newScene;
};

