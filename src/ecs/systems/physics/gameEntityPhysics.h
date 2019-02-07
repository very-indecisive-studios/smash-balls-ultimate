#pragma once

#include <bitset>
#include "collision.h"
#include "ecs/ecs.h"
#include "ecs/components/gameEntityPhysics.h"

class GameEntityPhysicsSystem : public System
{
private:
	ComponentBitset physicsBitset;
	std::shared_ptr<EntityList> physicsEntities;
	std::shared_ptr<EntityList> activePhysicsEntities;

	void ApplyGravity();

	CollisionResult TestEntityCollision(std::shared_ptr<Entity> target, std::shared_ptr<Entity> other);
	void CollisionDetection();

	void Simulate(float deltaTime);

public:
	GameEntityPhysicsSystem();
	void Process(float deltaTime) override;
};