#include "MiniginPCH.h"
#include "FPSComponent.h"
#include "Time.h"
#include "GameObject.h"
#include "ResourceManager.h"

dae::FPSComponent::FPSComponent()
	:m_Text()
	,m_TimePassed()
	,m_Frames()
{
}

dae::FPSComponent::~FPSComponent()
{
}

void dae::FPSComponent::UpdatePerFrame()
{
	m_Frames++;
	m_TimePassed += Time::GetInstance().DeltaTime();

	if (m_TimePassed >= 1.f)
	{
		m_Text.lock()->SetText(std::to_string(m_Frames) + " fps");
		m_TimePassed -= 1.f;
		m_Frames = 0;
	}
}

void dae::FPSComponent::Update()
{
}

void dae::FPSComponent::Render() const
{
}

void dae::FPSComponent::GameObjectSet()
{
	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 24);
	auto text = std::make_shared<TextComponent>("60 fps", font, SDL_Color{ 255,255,0 });
	GetGameObject()->AddComponent(text);
	m_Text = text;
}
