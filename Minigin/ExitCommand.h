#pragma once
#include "BaseCommand.h"

namespace dae
{
	class ExitCommand final : public BaseCommand
	{
	public:
		ExitCommand(){}
		virtual ~ExitCommand() {}

		void Execute(std::shared_ptr<GameObject> gameObject) override;
	};
}
