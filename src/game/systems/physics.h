#pragma once

#include "ecs/ecs.h"
#include "context/context.h"

struct CollisionResult
{
	enum class CollisionLocation { LEFT, RIGHT, TOP, BOTTOM };

	bool isCollided = false;
	CollisionLocation location;
};

class PhysicsSystem : public System
{
private:
	ComponentBitset physicsBitset;
	std::shared_ptr<EntityList> physicsEntities;
	std::shared_ptr<EntityList> passivePhysicsEntities;
	std::shared_ptr<EntityList> activePhysicsEntities;

	CollisionResult TestAABBandAABB(std::shared_ptr<PhysicsComponent> target, std::shared_ptr<PhysicsComponent> other);
	bool CheckAABBandAABB(int left1, int right1, int top1, int bottom1, int left2, int right2, int top2, int bottom2);
	bool CheckCircleandCircle(float radius1, Vector2 center1, float radius2, Vector2 center2);
	bool CheckAABBandCircle(int left, int top, int height, int width, Vector2 center, float radius);

	void CheckActiveToPassiveCollision(); 
	void CheckActiveToActiveCollision();

	void ApplyGravityForce();
	void RecalculateActiveComponents();
	void Simulate(float deltaTime);
public:
	PhysicsSystem();
	void Process(float deltaTime) override;
};
