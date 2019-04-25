#pragma once
#include "Singleton.h"

namespace dae
{
	class Minigin;
	class Time final : public Singleton<Time> //is naar mijn mening aangenamer om te gebruiken dan deltatime door te moeten geven
	{
	public:
		friend Minigin;

		float FrameTime() const { return m_FrameTime; };
		float DeltaTime() const { return m_MsPerFrame; };

	private:
		float m_FrameTime; //fps component heeft deze nodig om een juiste waarde te kunnen tonen
		const float m_MsPerFrame = 1 / 60.f; //update gebeurt met deze fixed timestamp, deze word dan ook gebruikt in de updates
	};
}
