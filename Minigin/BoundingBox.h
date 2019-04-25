#pragma once
#include "SceneObject.h"
namespace dae
{
	class BoundingBox :	public SceneObject
	{
	public:
		BoundingBox(float width, float height);
		~BoundingBox() = default;

		void Update() override;

	private:
		const float m_Width, m_height;
	};
}
