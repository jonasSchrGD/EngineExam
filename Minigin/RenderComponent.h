#pragma once
#include "BaseComponent.h"
#include "Texture2D.h"

namespace dae
{
	class RenderComponent :	public BaseComponent
	{
	public:
		RenderComponent();
		virtual ~RenderComponent() override;

		void SetTexture(const std::string& filename);

	protected:
		void Update() override;
		void Render() const override;
		void GameObjectSet() override {};

	private:
		std::shared_ptr<Texture2D> mTexture;
	};
}
