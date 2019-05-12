#pragma once
#include "GameObject.h"

namespace dae
{
	class BaseCommand
	{
	public:
		BaseCommand();
		virtual ~BaseCommand() {}

		virtual void Execute(std::shared_ptr<GameObject> gameObject){}
	};
}
