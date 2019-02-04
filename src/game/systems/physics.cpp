#include "pch.h"

#include "physics.h"
#include "game/components/position.h"
#include "game/components/physics.h"
#include "context/context.h"
#include <iostream>

PhysicsSystem::PhysicsSystem()
{
	physicsBitset.set(Component::GetComponentId<PhysicsComponent>());
}

CollisionResult PhysicsSystem::TestAABBandAABB(std::shared_ptr<PhysicsComponent> target, std::shared_ptr<PhysicsComponent> other)
{
	CollisionResult result;

	if (target->right > other->left)
	{
		result.location = CollisionResult::CollisionLocation::RIGHT;
		result.isCollided = true;
	}

	if (target->left < other->right)
	{
		result.location = CollisionResult::CollisionLocation::LEFT;
		result.isCollided = true;
	}

	if (target->top < other->bottom)
	{
		result.location = CollisionResult::CollisionLocation::TOP;
		result.isCollided = true;
	}

	if (target->bottom > other->top)
	{
		result.location = CollisionResult::CollisionLocation::BOTTOM;
		result.isCollided = true;
	}

	return result;
}

bool PhysicsSystem::CheckAABBandAABB(int left1, int right1, int top1, int bottom1, int left2, int right2, int top2, int bottom2)
{
	if ((right1 < left2) || (left1 > right2) || (bottom1 < top2) || (top1 > bottom2))
	{
		return false;
	}

	return true;
}

bool PhysicsSystem::CheckCircleandCircle(float radius1, Vector2 center1, float radius2, Vector2 center2)
{
	Vector2 distance = center1 - center2;
	distance.x = distance.x * distance.x;
	distance.y = distance.y * distance.y;
	
	float totalRadius = (radius1 + radius2) * (radius1 + radius2);

	if (distance.x + distance.y < totalRadius) 
	{
		return true;
	}

	return false;
}

bool PhysicsSystem::CheckAABBandCircle(int left, int right, int top, int bottom, Vector2 center, float radius)
{
	int closeX = center.x;
	int closeY = center.y;

	// check left
	if (center.x < left) 
	{
		closeX = left;
	}
	// check right
	if (center.x > right)
	{
		closeX = right;
	}
	// check top
	if (center.y < top)
	{
		closeY = top;
	}
	// check bottom
	if (center.y > bottom)
	{
		closeY = bottom;
	}

	int distanceSquared = ((closeX - center.x) * (closeX - center.x)) 
		+ ((closeY - center.y) *(closeY - center.y));

	if (distanceSquared < (radius * radius)) { return true; }

	return false;
}

void PhysicsSystem::CheckActiveToPassiveCollision()
{
	for (auto &activeEntity : *activePhysicsEntities) 
	{
		const auto activePhysicsComp = activeEntity->GetComponent<PhysicsComponent>();

		for (auto &passiveEntity : *passivePhysicsEntities)
		{
			const auto passivePhysicsComp = passiveEntity->GetComponent<PhysicsComponent>();

			if (activePhysicsComp->radius == 0 && passivePhysicsComp->radius == 0) // both entities AABB
			{
				auto result = TestAABBandAABB(activePhysicsComp, passivePhysicsComp);
				if (result.isCollided)
				{
					if (result.location == CollisionResult::CollisionLocation::LEFT)
					{
						passivePhysicsComp->leftwardForce = activePhysicsComp->rightwardForce;
					}
					else if (result.location == CollisionResult::CollisionLocation::RIGHT)
					{
						passivePhysicsComp->rightwardForce = activePhysicsComp->leftwardForce;
					}
					else if (result.location == CollisionResult::CollisionLocation::TOP)
					{
						passivePhysicsComp->downwardForce = activePhysicsComp->upwardForce;
					}
					else if (result.location == CollisionResult::CollisionLocation::BOTTOM)
					{
						passivePhysicsComp->upwardForce = activePhysicsComp->downwardForce;
					}
				}
			}

			else // one AABB one Circle
			{
				if (activePhysicsComp->radius == 0)  // active = AABB, passive = Circle
				{
					if (CheckAABBandCircle(activePhysicsComp->left, activePhysicsComp->right, activePhysicsComp->top, activePhysicsComp->bottom,
						passivePhysicsComp->center, passivePhysicsComp->radius))
					{
						/*activePhysicsComp->collided = true;
						activePhysicsComp->handleCollision(passiveEntity);
						activePhysicsComp->collided = false;*/
					}
				}
				else // active = Circle, passive = AABB
				{
					if (CheckAABBandCircle(passivePhysicsComp->left, passivePhysicsComp->right, passivePhysicsComp->top, passivePhysicsComp->bottom,
						activePhysicsComp->center, activePhysicsComp->radius))
					{
						/*activePhysicsComp->collided = true;
						activePhysicsComp->handleCollision(passiveEntity);
						activePhysicsComp->collided = false;*/
					}
				}
			}
		}
	}
}

void PhysicsSystem::CheckActiveToActiveCollision()
{
	for (auto &currentActiveEntity : *activePhysicsEntities)
	{
		const auto currentActivePhysicsComp = currentActiveEntity->GetComponent<PhysicsComponent>();

		for (auto &activeEntity : *activePhysicsEntities)
		{
			if (currentActiveEntity != activeEntity)
			{
				const auto activePhysicsComp = activeEntity->GetComponent<PhysicsComponent>();

				if (currentActivePhysicsComp->radius == 0 && activePhysicsComp->radius == 0) // both entities AABB
				{
					auto result = TestAABBandAABB(currentActivePhysicsComp, activePhysicsComp);
					if (result.isCollided)
					{
						if (result.location == CollisionResult::CollisionLocation::LEFT)
						{
							activePhysicsComp->leftwardForce = currentActivePhysicsComp->rightwardForce;
						}
						else if (result.location == CollisionResult::CollisionLocation::RIGHT)
						{
							activePhysicsComp->rightwardForce = currentActivePhysicsComp->leftwardForce;
						}
						else if (result.location == CollisionResult::CollisionLocation::TOP)
						{
							activePhysicsComp->downwardForce = currentActivePhysicsComp->upwardForce;
						}
						else if (result.location == CollisionResult::CollisionLocation::BOTTOM)
						{
							activePhysicsComp->upwardForce = currentActivePhysicsComp->downwardForce;
						}
					}
				}

				else // one AABB one Circle
				{
					if (currentActivePhysicsComp->radius == 0)  // currentActive = AABB, active = Circle
					{
						if (CheckAABBandCircle(currentActivePhysicsComp->left, currentActivePhysicsComp->right, currentActivePhysicsComp->top, currentActivePhysicsComp->bottom,
							activePhysicsComp->center, activePhysicsComp->radius))
						{
							currentActivePhysicsComp->collided = true;
							activePhysicsComp->collided = true;
							//currentActivePhysicsComp->handleCollision(activeEntity);
							//activePhysicsComp->handleCollision(currentActiveEntity);
							currentActivePhysicsComp->collided = false;
							activePhysicsComp->collided = false;
						}
					}
					else // currentActive = Circle, active = AABB
					{
						if (CheckAABBandCircle(activePhysicsComp->left, activePhysicsComp->right, activePhysicsComp->top, activePhysicsComp->bottom,
							currentActivePhysicsComp->center, currentActivePhysicsComp->radius))
						{
							currentActivePhysicsComp->collided = true;
							activePhysicsComp->collided = true;
							//currentActivePhysicsComp->handleCollision(activeEntity);
							//activePhysicsComp->handleCollision(currentActiveEntity);
							currentActivePhysicsComp->collided = false;
							activePhysicsComp->collided = false;
						}
					}
				}
			}
		}
	}
}

void PhysicsSystem::ApplyGravityForce()
{
	for (auto &entity : *activePhysicsEntities)
	{
		const auto physicsComp = entity->GetComponent<PhysicsComponent>();
		physicsComp->SetAcceleration(Vector2(physicsComp->acceleration.x, physicsComp->acceleration.y + 10));
	}
}

void PhysicsSystem::RecalculateActiveComponents() 
{
	for (auto &entity : *activePhysicsEntities)
	{
		const auto physicsComp = entity->GetComponent<PhysicsComponent>();
		if (physicsComp->isForcesModified) 
		{
			if (physicsComp->leftwardForce > physicsComp->rightwardForce)
			{
				physicsComp->acceleration.x = (physicsComp->leftwardForce - physicsComp->rightwardForce) / physicsComp->mass;
			}
			else 
			{
				physicsComp->acceleration.x = (physicsComp->rightwardForce - physicsComp->leftwardForce) / physicsComp->mass;
			}

			if (physicsComp->upwardForce > physicsComp->downwardForce)
			{
				physicsComp->acceleration.y = (physicsComp->upwardForce - physicsComp->downwardForce) / physicsComp->mass;
			}
			else
			{
				physicsComp->acceleration.y = (physicsComp->downwardForce - physicsComp->upwardForce) / physicsComp->mass;
			}

			physicsComp->isForcesModified = false;
		}

		if (physicsComp->isAccelerationModified)
		{
			// how would i modify the force :thinking:
			physicsComp->isAccelerationModified = false;
		}

		if (physicsComp->isVelocityModified)
		{
			// dont think need to?
			physicsComp->isVelocityModified = false;
		}
	}
}

//this is to iterate all active and update: 
// 1) velocity based on acceleration
// 2) pos based on velocity
// 3) velcity/oacceleratin based on force?
void PhysicsSystem::Simulate(float deltaTime)
{
	for (auto &entity : *activePhysicsEntities)
	{
		const auto posComp = entity->GetComponent<PositionComponent>();
		const auto physicsComp = entity->GetComponent<PhysicsComponent>();

		// probably wrong?
		physicsComp->xVelocity = physicsComp->acceleration.x * deltaTime;
		physicsComp->yVelocity = physicsComp->acceleration.y * deltaTime;

		posComp->pos.x += deltaTime * physicsComp->xVelocity;
		posComp->pos.y += deltaTime * physicsComp->yVelocity;
	}
}

void PhysicsSystem::Process(float deltaTime)
{
	physicsEntities = Context::ECSEngine()->GetEntities(physicsBitset);
	passivePhysicsEntities = std::make_shared<EntityList>();
	activePhysicsEntities = std::make_shared<EntityList>();

	for (auto &entity : *physicsEntities)
	{
		if (entity->GetComponent<PhysicsComponent>()->isPassive)
		{
			passivePhysicsEntities->push_back(entity);
		}
		else
		{
			activePhysicsEntities->push_back(entity);
		}
	}

	ApplyGravityForce();
	RecalculateActiveComponents();

	CheckActiveToPassiveCollision();
	CheckActiveToActiveCollision();

	Simulate(deltaTime); 

	passivePhysicsEntities->clear();
	activePhysicsEntities->clear();
}