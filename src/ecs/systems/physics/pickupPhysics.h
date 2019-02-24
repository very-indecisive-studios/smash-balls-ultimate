#pragma once
#include <bitset>
#include "collision.h"
#include "ecs/ecs.h"
#include "ecs/components/gameEntityPhysics.h"

class PickupPhysicsSystem : public System
{
private:
	
	CollisionResult TestEntityCollision(std::shared_ptr<Entity> target, std::shared_ptr<Entity> other);
	void CollisionDetection();
	void Simulate(float deltaTime);

public:
	PickupPhysicsSystem();
	void Process(float deltaTime) override;
};