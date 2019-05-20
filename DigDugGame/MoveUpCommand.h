#pragma once
#include <BaseCommand.h>
#include "Level.h"

class MoveUpCommand final : public dae::BaseCommand
{
public:
	MoveUpCommand(float movementSpeed, std::shared_ptr<Level> level);
	~MoveUpCommand() override = default;

	void Execute(std::shared_ptr<dae::GameObject> gameObject) override;

private:
	std::shared_ptr<Level> m_Level;
	float m_MovementSpeed;
	float m_TunnelTime;
};

