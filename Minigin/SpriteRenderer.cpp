#include "MiniginPCH.h"
#include "SpriteRenderer.h"
#include "Time.h"
#include "Renderer.h"
#include "GameObject.h"
#include "ContentManager.h"

dae::SpriteRenderer::SpriteRenderer(const std::string& filename, float frameTime, int cols, int rows, int nrOfAnimations, float2 drawSize)
	:m_Texture(ContentManager::GetInstance().Load<Texture2D>(filename))
	,m_BottomLeft({0,0})
	,m_Cols(cols)
	,m_Rows(rows)
	,m_FrameTime(frameTime)
	, m_NrOfAnimations(nrOfAnimations)
	,m_CurrentFrame(0)
	,m_ElapsedFrameTime(0)
	,m_Animation(0)
	,m_AnimationChanged(false)
	,m_loop(true)
{
	int w, h;
	SDL_QueryTexture(m_Texture->GetSDLTexture(), nullptr, nullptr, &w, &h);
	m_SrcRect.x = w / (float)cols;
	m_SrcRect.y = h / (float)rows;

	if(drawSize.x == 0 && drawSize.y == 0)
		m_DrwRect = m_SrcRect;
	else
		m_DrwRect = drawSize;

	if(nrOfAnimations == 1)
	{
		m_FramesPerAnim.push_back(cols * rows);
	}
	else
	{
		for (int i = 0; i < nrOfAnimations; i++)
		{
			m_FramesPerAnim.push_back((cols * rows) / nrOfAnimations);
		}
	}
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
	if (m_AnimationChanged || m_FramesPerAnim[m_Animation] > 1)
	{
		m_ElapsedFrameTime += Time::GetInstance().DeltaTime();
		bool updateAnim{true};

		if (!m_loop)
		{
			int localframe = m_CurrentFrame;
			for (int i = 0; i < m_Animation; ++i)
			{
				localframe -= m_FramesPerAnim[i];
			}
			updateAnim = localframe != m_FramesPerAnim[m_Animation] - 1;
		}

		if (m_AnimationChanged || m_ElapsedFrameTime >= m_FrameTime && updateAnim)
		{
			const int AnimFrames = m_FramesPerAnim[m_Animation];
			m_CurrentFrame = (m_CurrentFrame + 1) % AnimFrames;
			for (int i = 0; i < m_Animation; ++i)
			{
				m_CurrentFrame += m_FramesPerAnim[i];
			}

			m_BottomLeft.x = (m_CurrentFrame % m_Cols) * m_SrcRect.x;
			m_BottomLeft.y = (m_CurrentFrame / m_Cols) * m_SrcRect.y;

			m_ElapsedFrameTime -= m_FrameTime;
		}
		m_AnimationChanged = false;
	}
}
