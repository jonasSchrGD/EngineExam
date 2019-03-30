#pragma once
#include "BaseComponent.h"
#include "TextComponent.h"

namespace dae
{
	class FPSComponent : public BaseComponent
	{
	public:
		FPSComponent();
		virtual ~FPSComponent();

		void UpdatePerFrame();

	protected:
		void Update() override;
		void Render() const override;
		void GameObjectSet() override;

	private:
		std::weak_ptr<TextComponent> m_Text;
		float m_TimePassed;
		int m_Frames;
	};
}
