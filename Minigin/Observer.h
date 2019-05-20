#pragma once
#include "GameObject.h"

namespace dae
{
	class Observer : public std::enable_shared_from_this<Observer>
	{
	public:
		Observer() = default;
		virtual ~Observer() = default;

		virtual void Notify(std::shared_ptr<GameObject>) = 0;
	};
}
