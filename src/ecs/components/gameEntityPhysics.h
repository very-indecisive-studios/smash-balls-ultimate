#pragma once

#include <functional>
#include <memory>
#include "ecs/ecs.h"
#include "math/math.h"

struct GameEntityPhysicsComponent : public Component
{
	// AABB.
	int collisionBoxHeight = 0;
	int collisionBoxWidth = 0;

	bool isCollidable = true;

	bool isPassive = true;

	float upAcceleration = 0;
	float downAcceleration = 0;
	float leftAcceleration = 0;
	float rightAcceleration = 0;

	Vector2 velocity = { 0, 0 };

	// Callback
	std::function<void(std::shared_ptr<Entity> entity)> onCollisionCallback;
};
