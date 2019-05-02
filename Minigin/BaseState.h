#pragma once
#include "GameObject.h"

namespace dae
{
	class BaseState
	{
	public:
		virtual ~BaseState() = default;

		virtual std::shared_ptr<BaseState> Update(std::shared_ptr<GameObject> gameObject) { return; }
	};
}
