#pragma once
#include <Scene.h>

class StartScreen final : public dae::Scene
{
public:
	StartScreen();
	~StartScreen() override;

protected:
	void Initialize() override;
};

