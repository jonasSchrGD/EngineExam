#pragma once
#include  <memory>
#include "BaseComponent.h"

namespace dae
{
	class Renderer;
	class BaseRenderComponent : public BaseComponent, public std::enable_shared_from_this<BaseRenderComponent>
	{
	public:
		BaseRenderComponent();
		~BaseRenderComponent() override;

		virtual void Render() const{}

	protected:
		virtual void Update() = 0;
		void AddToRenderer();

	private:
		bool m_AddedToRenderer;
	};
}
