#include "pch.h"
#include "WanderState.h"
#include "MoveUpCommand.h"
#include "MoveLeftCommand.h"
#include "MoveRightCommand.h"
#include "MoveDownCommand.h"


WanderState::WanderState(std::shared_ptr<Level> level)
	:m_Level(level)
	,m_NewPos()
{
}


WanderState::~WanderState()
{
}

std::shared_ptr<dae::BaseState> WanderState::Update(std::shared_ptr<dae::GameObject> gameObject, dae::BaseCommand*& commandOutput)
{
	std::shared_ptr<BaseState> returnState{};

	auto& pos = gameObject->GetTransform().lock()->GetPosition();
	if ((m_NewPos.x == 0 && m_NewPos.y == 0) || IsInRange({pos.x, pos.y}))
	{
		auto possibleDirections = m_Level->GetPossibleDirections({ pos.x, pos.y });

		int randDirection = std::rand() % possibleDirections.size();

		if (possibleDirections[randDirection].x > 0)
		{
			if (m_Level->Center(gameObject, false))
			{
				commandOutput = new MoveRightCommand(40, m_Level);
				m_NewPos = m_Level->GetNextPos({ pos.x, pos.y }, possibleDirections[randDirection]);
			}
		}
		if (possibleDirections[randDirection].x < 0)
		{
			if (m_Level->Center(gameObject, false))
			{
				commandOutput = new MoveLeftCommand(40, m_Level);
				m_NewPos = m_Level->GetNextPos({ pos.x, pos.y }, possibleDirections[randDirection]);
			}
		}
		if (possibleDirections[randDirection].y > 0)
		{
			if (m_Level->Center(gameObject, true))
			{
				commandOutput = new MoveDownCommand(40, m_Level);
				m_NewPos = m_Level->GetNextPos({ pos.x, pos.y }, possibleDirections[randDirection]);
			}
		}
		if (possibleDirections[randDirection].y < 0)
		{
			if (m_Level->Center(gameObject, true))
			{
				commandOutput = new MoveUpCommand(40, m_Level);
				m_NewPos = m_Level->GetNextPos({ pos.x, pos.y }, possibleDirections[randDirection]);
			}
		}
}

	return returnState;
}

bool WanderState::IsInRange(float2 pos)
{
	int range = 3;
	return pos.x > m_NewPos.x - range && pos.x < m_NewPos.x + range && pos.y > m_NewPos.y - range && pos.y < m_NewPos.y + range;
}
