#pragma once

#include "ecs/ecs.h"
#include "math/math.h"

struct PhysicsComponent : public Component
{
public:
	// for AABB
	int left = 0;
	int right = 0;
	int top = 0;
	int bottom = 0;

	// for Circle
	float radius = 0;
	Vector2 center = {0,0};

	bool collided = false;

	bool isCollidable = true;
	bool isPassive = true;

	float upAcceleration = 0;
	float downAcceleration = 0;
	float leftAcceleration = 0;
	float rightAcceleration = 0;

	Vector2 velocity = { 0, 0 };
};
