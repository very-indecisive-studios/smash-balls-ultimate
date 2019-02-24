#include "pch.h"
#include "pickupPhysics.h"
#include "ecs/components/position.h"
#include "context/context.h"

PickupPhysicsSystem::PickupPhysicsSystem()
{

}

CollisionResult PickupPhysicsSystem::TestEntityCollision(std::shared_ptr<Entity> target, std::shared_ptr<Entity> other)
{
	CollisionResult result;

	// Get rectangle of target entity.
	const auto targetPosComp = target->GetComponent<PositionComponent>();
	const auto targetPhysicsComp = target->GetComponent<GameEntityPhysicsComponent>();

	RECT targetRect = { 0 };
	targetRect.left = targetPosComp->pos.x;
	targetRect.right = targetPosComp->pos.x + targetPhysicsComp->collisionBoxWidth;
	targetRect.top = targetPosComp->pos.y;
	targetRect.bottom = targetPosComp->pos.y + targetPhysicsComp->collisionBoxHeight;

	// Get rectangle of other entity.
	const auto otherPosComp = other->GetComponent<PositionComponent>();
	const auto otherPhysicsComp = other->GetComponent<GameEntityPhysicsComponent>();

	RECT otherRect = { 0 };
	otherRect.left = otherPosComp->pos.x;
	otherRect.right = otherPosComp->pos.x + otherPhysicsComp->collisionBoxWidth;
	otherRect.top = otherPosComp->pos.y;
	otherRect.bottom = otherPosComp->pos.y + otherPhysicsComp->collisionBoxHeight;

	// Collision detection for AABB.
	bool isCollided = !(targetRect.right <= otherRect.left ||
		targetRect.left >= otherRect.right ||
		targetRect.bottom <= otherRect.top ||
		targetRect.top >= otherRect.bottom);

	// Get the collision location.
	if (isCollided)
	{
		int deltaRight = targetRect.right - otherRect.left;
		if (deltaRight > 0 && deltaRight < targetPhysicsComp->collisionBoxWidth)
		{
			result.set(CollisionLocation::RIGHT);
		}

		int deltaLeft = otherRect.right - targetRect.left;
		if (deltaLeft > 0 && deltaLeft < targetPhysicsComp->collisionBoxWidth)
		{
			result.set(CollisionLocation::LEFT);
		}

		int deltaTop = otherRect.bottom - targetRect.top;
		if (deltaTop > 0 && deltaTop < targetPhysicsComp->collisionBoxHeight)
		{
			result.set(CollisionLocation::TOP);
		}

		int deltaBottom = targetRect.bottom - otherRect.top;
		if (deltaBottom > 0 && deltaBottom < targetPhysicsComp->collisionBoxHeight)
		{
			result.set(CollisionLocation::BOTTOM);
		}

		if (targetPhysicsComp->onCollisionCallback)
		{
			targetPhysicsComp->onCollisionCallback(other);
		}
	}

	return result;
}

void PickupPhysicsSystem::CollisionDetection()
{

}

void PickupPhysicsSystem::Simulate(float deltaTime)
{

}

void PickupPhysicsSystem::Process(float deltaTime)
{
	CollisionDetection();

	Simulate(deltaTime);
}