#pragma once
#include "BaseRenderComponent.h"
#include "Texture2D.h"
#include "structs.h"

namespace dae
{
	class SpriteRenderer final : public BaseRenderComponent
	{
	public:
		//if drawSize is {0,0} the size of a sprite will be used
		SpriteRenderer(const std::string& filename, float frameTime, int cols = 1, int rows = 1, int nrOfAnimations = 1, float2 drawSize = {0,0});
		~SpriteRenderer() = default;

		//can be used with an enum
		void SetAnimation(int animationNr, bool loop = true)
		{
			if(m_Animation != animationNr && animationNr < m_NrOfAnimations && animationNr >= 0)
			{
				m_Animation = animationNr;
				m_AnimationChanged = true;
				m_loop = loop;
			}
		}
		int GetAnimation() const { return m_Animation; }
		void SetFramesPerAnim(const std::vector<int>& framesPerAnim) { m_FramesPerAnim = framesPerAnim; }

		void Render() const override;

	protected:
		void Update() override;

	private:
		//member variables
		std::vector<int> m_FramesPerAnim;
		std::shared_ptr<Texture2D> m_Texture;

		float2 m_SrcRect, m_DrwRect;
		float2 m_BottomLeft;

		const float m_FrameTime; 
		float m_ElapsedFrameTime;

		const int m_Cols, m_Rows, m_NrOfAnimations;
		int m_Animation, m_CurrentFrame;
		bool m_AnimationChanged, m_loop;
	};
}
