#pragma once
#include "Singleton.h"

namespace dae
{
	class Minigin;
	class Time final : public Singleton<Time>
	{
	public:
		friend Minigin;

		const float& FrameTime() const { return m_FrameTime; };
		const float& DeltaTime() const { return m_MsPerFrame; };

	private:
		float m_FrameTime;
		const float m_MsPerFrame = 1 / 60.f;
	};
}
