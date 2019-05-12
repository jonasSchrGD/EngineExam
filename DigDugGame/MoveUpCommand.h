#pragma once
#include <BaseCommand.h>
class MoveUpCommand final : public dae::BaseCommand
{
public:
	MoveUpCommand(float movementSpeed);
	~MoveUpCommand() override = default;

	void Execute(std::shared_ptr<dae::GameObject> gameObject) override;

private:
	float m_MovementSpeed;
};

