#pragma once

#include "ecs/ecs.h"
#include "math/math.h"

struct BallPhysicsComponent : public Component
{
	// Circle.
	float collisionCircleRadius = 0;

	float upAcceleration = 0;
	float downAcceleration = 0;
	float leftAcceleration = 0;
	float rightAcceleration = 0;

	Vector2 velocity = { 0, 0 };
};
