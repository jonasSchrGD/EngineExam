#include "pch.h"
#include "InflatedState.h"
#include "EnemyCollisionHandler.h"
#include "Time.h"
#include "SpriteRenderer.h"
#include "Animations.h"
#include "WanderState.h"
#include "ContentManager.h"
#include "IdleCommand.h"
#include "SelectedLevel.h"


InflatedState::InflatedState(std::shared_ptr<Level> level)
	:m_Level(level)
{
}


InflatedState::~InflatedState()
{
}

std::shared_ptr<dae::BaseState> InflatedState::Update(std::shared_ptr<dae::GameObject> gameObject, dae::BaseCommand*& commandOutput, int controller)
{
	UNREFERENCED_PARAMETER(controller);
	commandOutput = new IdleCommand();
	std::shared_ptr<BaseState> returnstate{};

	auto collision = gameObject->GetComponent<EnemyCollisionHandler>();

	if (collision->GetPumpCollisionState() == 0)
	{
		m_Elapsed += dae::Time::GetInstance().DeltaTime();
		if(m_Elapsed >= 2 * m_TimePerStep)
		{
			m_Progress--;
			if (m_Progress > -1)
				gameObject->GetComponent<dae::SpriteRenderer>()->SetAnimation(int(PookaAnimation::inflate1) + m_Progress);

			if (m_Progress == -1)
			{
				gameObject->GetComponent<dae::SpriteRenderer>()->SetAnimation(int(PookaAnimation::left));
				returnstate = std::make_shared<WanderState>(m_Level);
			}

			m_Elapsed = 0;
		}
	}
	if (collision->GetPumpCollisionState() == 1)
	{
		m_Elapsed = 0;
		m_Progress++;
		gameObject->GetComponent<dae::SpriteRenderer>()->SetAnimation(int(PookaAnimation::inflate1) + m_Progress);

		if (m_Progress == 4)
			gameObject->GetComponent<EnemyCollisionHandler>()->Die();
	}
	if (collision->GetPumpCollisionState() == 2)
	{
		m_Elapsed -= dae::Time::GetInstance().DeltaTime();
		if(m_Elapsed <= 0)
		{
			m_Progress++;
			gameObject->GetComponent<dae::SpriteRenderer>()->SetAnimation(int(PookaAnimation::inflate1) + m_Progress);
			m_Elapsed = 2 * m_TimePerStep;

			if (m_Progress == 4)
				gameObject->GetComponent<EnemyCollisionHandler>()->Die();
		}
	}

	return returnstate;
}
