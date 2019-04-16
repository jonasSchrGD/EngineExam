#pragma once
#include "SceneObject.h"
namespace dae
{
	class BoundingBox :	public SceneObject
	{
	public:
		BoundingBox();
		~BoundingBox() = default;
	};
}
