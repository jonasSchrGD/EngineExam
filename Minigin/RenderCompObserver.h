#pragma once
#include "Observer.h"

#include <vector>
#include <memory>

namespace dae
{
	class GameObject;
	class BaseRenderComponent;
	class RenderCompObserver : public Observer
	{
	public:
		RenderCompObserver(std::vector<std::shared_ptr<BaseRenderComponent>>& renderComponents);

		~RenderCompObserver() override = default;
		void Notify(std::shared_ptr<GameObject>) override;

	private:
		std::vector<std::shared_ptr<BaseRenderComponent>>& m_RenderComponents;
	};
}
