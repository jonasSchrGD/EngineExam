#pragma once
#include <BaseCommand.h>
class MoveRightCommand final : public dae::BaseCommand
{
public:
	MoveRightCommand(float movementSpeed);
	~MoveRightCommand() override = default;

	void Execute(std::shared_ptr<dae::GameObject> gameObject) override;

private:
	float m_MovementSpeed;
};

