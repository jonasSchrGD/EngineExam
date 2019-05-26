#pragma once
#include "BaseComponent.h"
namespace dae
{
	class LifeTime final : public BaseComponent
	{
	public:
		LifeTime(float lifeTime);
		~LifeTime();

	protected:
		void Update() override;

	private:
		float m_LifeTime;
	};
}
