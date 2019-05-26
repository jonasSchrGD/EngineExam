#pragma once
#include <Singleton.h>

class SelectedLevel final :public dae::Singleton<SelectedLevel>
{
public:
	SelectedLevel();
	~SelectedLevel();

	int selectedLevel;
};

