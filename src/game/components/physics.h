#pragma once

#include "ecs/ecs.h"
#include "math/math.h"

struct PhysicsComponent : public Component
{
public:
	int height;
	int width;
	float radius;
	float mass;
	float gravity;
	int speed;
	Vector2 velocity{ speed, -speed };
	bool isPassive;
	bool collidable;
};
