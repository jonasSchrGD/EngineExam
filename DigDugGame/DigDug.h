#pragma once
#include "Minigin.h"

//all images used are not mine, i got them from other students
class DigDug final : public dae::Minigin
{
protected:
	void LoadGame()const override;
	void InitializeCustomLoaders() override;
};

