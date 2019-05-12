#pragma once
#include <BaseCommand.h>

class MoveLeftCommand final : public dae::BaseCommand
{
public:
	MoveLeftCommand(float movementSpeed);
	~MoveLeftCommand() override = default;
	void Execute(std::shared_ptr<dae::GameObject> gameObject) override;

private:
	float m_MovementSpeed;
};

