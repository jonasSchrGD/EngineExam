#pragma once
#include "BaseComponent.h"
#include "Texture2D.h"
#include "BaseRenderComponent.h"

namespace dae
{
	class RenderComponent final :	public BaseRenderComponent
	{
	public:
		RenderComponent();
		virtual ~RenderComponent() override = default;

		void SetTexture(const std::string& filename);
		virtual void Render() const;

	protected:
		void Update() override { AddToRenderer(); }

	private:
		std::shared_ptr<Texture2D> mTexture;
		bool m_AddedToRenderer;
	};
}
