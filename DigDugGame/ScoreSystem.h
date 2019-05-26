#pragma once
#include <BaseComponent.h>
#include "GameObject.h"
#include "TextRenderComponent.h"
#include "ScoreObserver.h"

class ScoreSystem final : public dae::BaseComponent
{
public:
	ScoreSystem();
	~ScoreSystem();

	void SetTextP1(std::shared_ptr<dae::TextRenderComponent> text) { m_ScoreP1Text = text; }
	void SetTextP2(std::shared_ptr<dae::TextRenderComponent> text) { m_ScoreP2Text = text; }

	std::shared_ptr<ScoreObserver> GetBoundObserver() const { return m_ScoreObserver; }

	void ResetPoints() { m_P1Score = 0; m_P2Score = 0; }

protected:
	void Update() override;

private:
	std::shared_ptr<dae::TextRenderComponent> m_ScoreP1Text, m_ScoreP2Text;
	std::shared_ptr<ScoreObserver> m_ScoreObserver;
	int m_P1Score = 0, m_P2Score = 0;
};

