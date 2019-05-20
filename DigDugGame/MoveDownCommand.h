#pragma once
#include <BaseCommand.h>
#include "Level.h"

class MoveDownCommand final : public dae::BaseCommand
{
public:
	MoveDownCommand(float movementSpeed, std::shared_ptr<Level> level);
	~MoveDownCommand() override = default;

	void Execute(std::shared_ptr<dae::GameObject> gameObject) override;

private:
	std::shared_ptr<Level> m_Level;
	float m_MovementSpeed;
	float m_TunnelTime;
};

