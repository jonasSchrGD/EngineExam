#include "MiniginPCH.h"
#include "FPSComponent.h"
#include "Time.h"
#include "GameObject.h"
#include "ResourceManager.h"

dae::FPSComponent::FPSComponent()
	:m_Text()
	,m_FpsSum()
{
}

dae::FPSComponent::~FPSComponent()
{
}

void dae::FPSComponent::Update()
{
	if (m_FpsCatches.size() == 30)
	{
		m_FpsSum -= m_FpsCatches[0];
		m_FpsCatches.pop_front();
	}

	m_FpsCatches.push_back(unsigned int(1 / Time::GetInstance().FrameTime()));
	m_FpsSum += m_FpsCatches[m_FpsCatches.size() - 1];

	unsigned int fps{m_FpsSum / (unsigned int)m_FpsCatches.size()};

	if (m_LastFpsUpdate != fps)
		m_Text.lock()->SetText(std::to_string(fps) + " fps");
	m_LastFpsUpdate = fps;
}

void dae::FPSComponent::GameObjectSet()
{
	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 24);
	auto text = std::make_shared<TextRenderComponent>("60 fps", font, SDL_Color{ 255,255,0 });
	GetGameObject()->AddComponent(text);
	m_Text = text;
}
