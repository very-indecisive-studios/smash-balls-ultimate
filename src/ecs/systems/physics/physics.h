#pragma once

#include <bitset>
#include <memory>
#include "ecs/ecs.h"
#include "gameEntityPhysics.h"
#include "ballPhysics.h"
#include "pickupPhysics.h"

class PhysicsSystem : public System
{
private:
	std::shared_ptr<GameEntityPhysicsSystem> gameEntityPhySubSystem = std::make_shared<GameEntityPhysicsSystem>();
	std::shared_ptr<BallPhysicsSystem> ballPhySubSystem = std::make_shared<BallPhysicsSystem>();
	std::shared_ptr<PickupPhysicsSystem> pickupPhySubSystem = std::make_shared<PickupPhysicsSystem>();
public:
	void Process(float deltaTime) override
	{
		gameEntityPhySubSystem->Process(deltaTime);
		ballPhySubSystem->Process(deltaTime);
		pickupPhySubSystem->Process(deltaTime);
	}
};
