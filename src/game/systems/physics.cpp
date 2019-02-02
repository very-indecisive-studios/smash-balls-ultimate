#include "pch.h"

#include "physics.h"
#include "game/components/position.h"
#include "game/components/physics.h"
#include "context/context.h"

PhysicsSystem::PhysicsSystem()
{
	physicsBitset.set(Component::GetComponentId<PhysicsComponent>());
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
	
	int totalRadius = (radius1 + radius2) * (radius1 + radius2);

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

bool PhysicsSystem::CheckActiveToPassiveCollision()
{
	for (auto &activeEntity : *activePhysicsEntities) 
	{
		const auto activePhysicsComp = activeEntity->GetComponent<PhysicsComponent>();

		for (auto &passiveEntity : *passivePhysicsEntities)
		{
			const auto passivePhysicsComp = passiveEntity->GetComponent<PhysicsComponent>();

			if (activePhysicsComp->radius == 0 && passivePhysicsComp->radius == 0) // both entities AABB
			{
				CheckAABBandAABB(activePhysicsComp->left, activePhysicsComp->right, activePhysicsComp->top, activePhysicsComp->bottom, 
					passivePhysicsComp->left, passivePhysicsComp->right, passivePhysicsComp->top, passivePhysicsComp->bottom);
			}

			if (activePhysicsComp->radius != 0 && passivePhysicsComp->radius != 0) // both entities Circle
			{
				CheckCircleandCircle(activePhysicsComp->radius, activePhysicsComp->center, 
					passivePhysicsComp->radius, passivePhysicsComp->center);
			}

			else // one AABB one Circle
			{
				if (activePhysicsComp->radius == 0)  // active = AABB, passive = Circle
				{
					CheckAABBandCircle(activePhysicsComp->left, activePhysicsComp->right, activePhysicsComp->top, activePhysicsComp->bottom,
						passivePhysicsComp->center, passivePhysicsComp->radius);
				}
				else // active = Circle, passive = AABB
				{
					CheckAABBandCircle(passivePhysicsComp->left, passivePhysicsComp->right, passivePhysicsComp->top, passivePhysicsComp->bottom,
						activePhysicsComp->center, activePhysicsComp->radius);
				}
			}
		}
	}
	return false;
}

bool PhysicsSystem::CheckActiveToActiveCollision()
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
					CheckAABBandAABB(currentActivePhysicsComp->left, currentActivePhysicsComp->right, currentActivePhysicsComp->top, currentActivePhysicsComp->bottom,
						activePhysicsComp->left, activePhysicsComp->right, activePhysicsComp->top, activePhysicsComp->bottom);
				}

				if (currentActivePhysicsComp->radius != 0 && activePhysicsComp->radius != 0) // both entities Circle
				{
					CheckCircleandCircle(currentActivePhysicsComp->radius, currentActivePhysicsComp->center,
						activePhysicsComp->radius, activePhysicsComp->center);
				}

				else // one AABB one Circle
				{
					if (currentActivePhysicsComp->radius == 0)  // currentActive = AABB, active = Circle
					{
						CheckAABBandCircle(currentActivePhysicsComp->left, currentActivePhysicsComp->right, currentActivePhysicsComp->top, currentActivePhysicsComp->bottom,
							activePhysicsComp->center, activePhysicsComp->radius);
					}
					else // currentActive = Circle, active = AABB
					{
						CheckAABBandCircle(activePhysicsComp->left, activePhysicsComp->right, activePhysicsComp->top, activePhysicsComp->bottom,
							currentActivePhysicsComp->center, currentActivePhysicsComp->radius);
					}
				}
			}
		}
	}
	return false;
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

	CheckActiveToPassiveCollision();
	CheckActiveToActiveCollision();
}
