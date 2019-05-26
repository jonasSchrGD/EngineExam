#pragma once
#include "Texture2D.h"
#include "BaseRenderComponent.h"

namespace dae
{
	class RenderComponent final : public BaseRenderComponent
	{
	public:
		RenderComponent(int width = 0, int height = 0);
		~RenderComponent() override = default;

		void SetDimensions(int width, int height) { m_Width = width; m_Height = height; }
		void SetTexture(const std::string& filename);
		virtual void Render() const;

	protected:
		void Update() override {}

	private:
		std::shared_ptr<Texture2D> mTexture;
		int m_Width, m_Height;
	};
}
