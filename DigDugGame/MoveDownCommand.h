#pragma once
#include <BaseCommand.h>
class MoveDownCommand final : public dae::BaseCommand
{
public:
	MoveDownCommand(float movementSpeed);
	~MoveDownCommand() override = default;

	void Execute(std::shared_ptr<dae::GameObject> gameObject) override;

private:
	float m_MovementSpeed;
};

