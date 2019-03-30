#pragma once
#include "Singleton.h"

namespace dae
{
	class Minigin;
	class Time final : public Singleton<Time>
	{
	public:
		friend Minigin;

		const float& DeltaTime() const { return m_DeltaTime; };

	private:
		float m_DeltaTime;
		const float m_MsPerFrame = 16.f /1000.f; //16 for 60 fps, 33 for 30 fps
	};
}
