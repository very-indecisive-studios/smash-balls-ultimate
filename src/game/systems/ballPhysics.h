#pragma once

#include <bitset>
#include "ecs/ecs.h"
#include "game/components/gameEntityPhysics.h"

class BallPhysicsSystem : public System
{
private:
	uint8_t LEFT = 0, RIGHT = 1, TOP = 2, BOTTOM = 3;
	typedef std::bitset<4> CollisionResult;

private:
	ComponentBitset gameEntityPhyBitset;
	std::shared_ptr<Entity> ballEntity;
	std::shared_ptr<EntityList> gameEntities;

	void ApplyGravity();

	CollisionResult TestEntityCollision(std::shared_ptr<Entity> other);
	void CollisionDetection();

	void Simulate(float deltaTime);

public:
	BallPhysicsSystem();
	void Process(float deltaTime) override;
};
