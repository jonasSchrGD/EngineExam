#pragma once
#include <BaseCommand.h>
#include "Level.h"

class MoveRightCommand final : public dae::BaseCommand
{
public:
	MoveRightCommand(float movementSpeed, std::shared_ptr<Level> level);
	~MoveRightCommand() override = default;

	void Execute(std::shared_ptr<dae::GameObject> gameObject) override;

private:
	std::shared_ptr<Level> m_Level;
	float m_MovementSpeed;
	float m_TunnelTime;
};

