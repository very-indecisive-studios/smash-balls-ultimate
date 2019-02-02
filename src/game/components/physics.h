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

	float mass;
	float gravity;
	int speed;
	Vector2 velocity{ speed, -speed };
	bool isPassive;
};
