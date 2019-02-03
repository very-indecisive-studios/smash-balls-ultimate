#pragma once

#include "ecs/ecs.h"
#include "context/context.h"

class PhysicsSystem : public System
{
private:
	ComponentBitset physicsBitset;
	std::shared_ptr<EntityList> physicsEntities;
	std::shared_ptr<EntityList> passivePhysicsEntities;
	std::shared_ptr<EntityList> activePhysicsEntities;

	bool CheckAABBandAABB(int left1, int right1, int top1, int bottom1, int left2, int right2, int top2, int bottom2);
	bool CheckCircleandCircle(float radius1, Vector2 center1, float radius2, Vector2 center2);
	bool CheckAABBandCircle(int left, int top, int height, int width, Vector2 center, float radius);
	void BlockPnA(std::shared_ptr<Entity> passiveEntity, std::shared_ptr<Entity> activeEntity);
	void Block(std::shared_ptr<Entity> e1, std::shared_ptr<Entity> e2);
	void CheckActiveToPassiveCollision();
	void CheckActiveToActiveCollision();

public:
	PhysicsSystem();

	void Process(float deltaTime) override;
};
