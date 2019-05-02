#pragma once
#include <Box2D/Dynamics/b2WorldCallbacks.h>

namespace dae
{
	//https://www.iforce2d.net/b2dtut/collision-callbacks
	class MiniginContactListener final : public b2ContactListener
	{
	public:
		MiniginContactListener() = default;
		~MiniginContactListener() = default;

		void BeginContact(b2Contact* contact) override;
		void EndContact(b2Contact* contact) override;
	};
}
