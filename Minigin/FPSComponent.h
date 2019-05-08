#pragma once
#include "BaseComponent.h"
#include "TextRenderComponent.h"
#include <deque>

namespace dae
{
	class FPSComponent final : public BaseComponent
	{
	public:
		FPSComponent();
		~FPSComponent();

	protected:
		void Update() override;
		void Initialize() override;

	private:
		std::weak_ptr<TextRenderComponent> m_Text;
		std::deque<unsigned int> m_FpsCatches; //keep track of multiple frame fps calculations

		unsigned int m_LastFpsUpdate, m_FpsSum;
	};
}
