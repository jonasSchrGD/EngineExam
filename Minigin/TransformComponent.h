#pragma once
#include "BaseComponent.h"
#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/glm/vec3.hpp>
#pragma warning(pop)

namespace dae
{
	class TransformComponent final : public BaseComponent
	{
		glm::vec3 mPosition;
	public:
		const glm::vec3& GetPosition() const { return mPosition; }
		void SetPosition(float x, float y, float z);

		~TransformComponent() override;
	};
}
