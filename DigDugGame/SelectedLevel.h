#pragma once
#include <Singleton.h>

class SelectedLevel final :public dae::Singleton<SelectedLevel>
{
public:
	SelectedLevel() = default;
	~SelectedLevel() = default;

	int selectedLevel = 1;
};

