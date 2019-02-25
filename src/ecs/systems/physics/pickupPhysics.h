#pragma once
#include <bitset>
#include "collision.h"
#include "ecs/ecs.h"
#include "ecs/components/gameEntityPhysics.h"

class PickupPhysicsSystem : public System
{
private:
	ComponentBitset pickupBitset;
	std::shared_ptr<EntityList> pickupEntities;
	std::shared_ptr<Entity> player;
	

	CollisionResult TestEntityCollision(std::shared_ptr<Entity> pickup, std::shared_ptr<Entity> player);
	void CollisionDetection();

	void Simulate(float deltaTime);

public:
	PickupPhysicsSystem();
	void Process(float deltaTime) override;
};