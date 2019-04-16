#include "MiniginPCH.h"
#include "SpriteRenderer.h"
#include "Time.h"
#include "Renderer.h"
#include "GameObject.h"
#include "ResourceManager.h"

dae::SpriteRenderer::SpriteRenderer(const std::string& filename, float frameTime, int cols, int rows, int nrOfAnimations, float2 drawSize)
	:m_Texture(ResourceManager::GetInstance().LoadTexture(filename))
	,m_BottomLeft({0,0})
	,m_Cols(cols)
	,m_Rows(rows)
	,m_FrameTime(frameTime)
	,m_CurrentFrame(0)
	,m_ElapsedFrameTime(0)
	,m_NrOfAnimations(nrOfAnimations)
{
	AddToRenderer();
	int w, h;
	SDL_QueryTexture(m_Texture->GetSDLTexture(), nullptr, nullptr, &w, &h);
	m_SrcRect.x = w / (float)cols;
	m_SrcRect.y = h / (float)rows;

	if(drawSize.x == 0 && drawSize.y == 0)
		m_DrwRect = m_SrcRect;
	else
		m_DrwRect = drawSize;
}

void dae::SpriteRenderer::Render() const
{
	const auto pos = GetGameObject()->GetTransform().lock()->GetPosition();
	SDL_Rect srcRect, dstRect;
	srcRect.x = static_cast<int>(m_BottomLeft.x);
	srcRect.y = static_cast<int>(m_BottomLeft.y);
	srcRect.w = static_cast<int>(m_SrcRect.x);
	srcRect.h = static_cast<int>(m_SrcRect.y);

	dstRect.x = static_cast<int>(pos.x);
	dstRect.y = static_cast<int>(pos.y);
	dstRect.w = static_cast<int>(m_DrwRect.x);
	dstRect.h = static_cast<int>(m_DrwRect.y);

	Renderer::GetInstance().RenderTexture(*m_Texture, srcRect, dstRect);
}

void dae::SpriteRenderer::Update()
{
	m_ElapsedFrameTime += Time::GetInstance().DeltaTime();

	if (m_ElapsedFrameTime >= m_FrameTime)
	{
		const int framesPerAnim = m_Cols * m_Rows / m_NrOfAnimations;
		m_CurrentFrame = m_CurrentFrame++ % framesPerAnim;
		m_CurrentFrame += framesPerAnim * m_Animation;

		m_BottomLeft.x = (m_CurrentFrame % m_Cols) * m_SrcRect.x;
		m_BottomLeft.y = ((m_CurrentFrame / m_Cols) + 1) * m_SrcRect.y;
	}
}
