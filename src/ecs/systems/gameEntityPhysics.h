#pragma once

#include <bitset>
#include "ecs/ecs.h"
#include "ecs/components/gameEntityPhysics.h"

namespace CollisionLocation
{
	constexpr uint8_t LEFT = 0, RIGHT = 1, TOP = 2, BOTTOM = 3;
};

class GameEntityPhysicsSystem : public System
{
private:
	typedef std::bitset<4> CollisionResult;

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