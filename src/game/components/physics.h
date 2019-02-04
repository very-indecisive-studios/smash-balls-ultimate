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

	bool collided = false;

	std::function<void(std::shared_ptr<Entity> e)> handleCollision;

	bool isCollidable = true;
	bool isPassive = true;

	void SetUpwardForce(float force)
	{
		upwardForce = force;
		isForcesModified = true;
	}
	float GetUpwardForce() { return upwardForce; }

	void SetDownwardForce(float force)
	{
		downwardForce = force;
		isForcesModified = true;
	}
	float GetDownwardForce() { return downwardForce; }

	void SetRightwardForce(float force)
	{
		rightwardForce = force;
		isForcesModified = true;
	}
	float GetRightwardForce() { return rightwardForce; }

	void SetLeftwardForce(float force)
	{
		leftwardForce = force;
		isForcesModified = true;
	}
	float GetLeftwardForce() { return leftwardForce; }

	void SetAcceleration(Vector2 acc)
	{
		acceleration = acc;
		isAccelerationModified = true;
	}
	Vector2 GetAcceleration() { return acceleration; }

	void SetXVelocity(float velocity) 
	{
		xVelocity = velocity;
		isVelocityModified = true;
	}
	float GetXVelocity() { return xVelocity; }

	void SetYVelocity(float velocity)
	{
		yVelocity = velocity;
		isVelocityModified = true;
	}
	float GetYVelocity() { return yVelocity; }

private:
	bool isForcesModified = false;
	float upwardForce = 0;
	float downwardForce = 0;
	float leftwardForce = 0;
	float rightwardForce = 0;

	bool isAccelerationModified = false;
	Vector2 acceleration{ 0, 0 };

	bool isVelocityModified = false;
	float xVelocity = 0;
	float yVelocity = 0;

	friend class PhysicsSystem;
};
