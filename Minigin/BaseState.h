#pragma once
#include "GameObject.h"
#include "BaseCommand.h"

namespace dae
{
	class BaseState
	{
	public:
		virtual ~BaseState() = default;

		virtual std::shared_ptr<BaseState> Update(std::shared_ptr<GameObject> gameObject, BaseCommand*& commandOutput, int controller)
		{
			UNREFERENCED_PARAMETER(gameObject);
			UNREFERENCED_PARAMETER(controller);
			commandOutput = new BaseCommand();
			return std::shared_ptr<BaseState>();
		}
	};
}
