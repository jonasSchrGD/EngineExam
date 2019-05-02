#pragma once
#include "GameObject.h"

namespace dae
{
	class Command
	{
	public:
		Command();
		virtual ~Command() {}

		virtual void Execute(std::shared_ptr<GameObject> gameObject) = 0;
	};
}
