#pragma once
#include "BaseComponent.h"
namespace dae
{
	class CharacterControllerComponent final: public BaseComponent
	{
	public:
		CharacterControllerComponent();
		~CharacterControllerComponent() = default;

	protected:
		void Update() override;
	};
}