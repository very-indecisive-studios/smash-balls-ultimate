#pragma once

#include <bitset>
#include <memory>
#include "ecs/ecs.h"
#include "gameEntityPhysics.h"
#include "ballPhysics.h"

class PhysicsSystem : public System
{
private:
	std::shared_ptr<GameEntityPhysicsSystem> gameEntityPhySubSystem = std::make_shared<GameEntityPhysicsSystem>();
	std::shared_ptr<BallPhysicsSystem> ballPhySubSystem = std::make_shared<BallPhysicsSystem>();
public:
	void Process(float deltaTime) override
	{
		gameEntityPhySubSystem->Process(deltaTime);
		ballPhySubSystem->Process(deltaTime);
	}
};
