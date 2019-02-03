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

	Vector2 currentPos;
	bool collided = false;
	void SetCurrentPos(Vector2 pos)
	{
		if (!collided)
		{
			this->currentPos = pos;
		}
	}
	std::function<void(std::shared_ptr<Entity> e)> handleCollision;

	float mass;
	Vector2 velocity{0,-0};

	bool isCollidable = true;
	bool isPassive;
};
