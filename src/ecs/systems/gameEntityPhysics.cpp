#include "pch.h"

#include "gameEntityPhysics.h"
#include "context/context.h"

GameEntityPhysicsSystem::GameEntityPhysicsSystem()
{
	physicsBitset.set(Component::GetComponentId<GameEntityPhysicsComponent>());
}

void GameEntityPhysicsSystem::ApplyGravity()
{
	for (auto &entity : *activePhysicsEntities)
	{
		const auto physicsComp = entity->GetComponent<GameEntityPhysicsComponent>();
		physicsComp->downAcceleration = 100;
	}
}

GameEntityPhysicsSystem::CollisionResult GameEntityPhysicsSystem::TestEntityCollision(std::shared_ptr<Entity> target, std::shared_ptr<Entity> other)
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
	}

	return result;
}

void GameEntityPhysicsSystem::CollisionDetection()
{
	for (auto &activeEntity : *activePhysicsEntities)
	{
		const auto activePhysicsComp = activeEntity->GetComponent<GameEntityPhysicsComponent>();
		const auto activePosComp = activeEntity->GetComponent<PositionComponent>();

		for (auto &otherEntity : *physicsEntities)
		{
			if (activeEntity == otherEntity)
			{
				continue;
			}

			auto result = TestEntityCollision(activeEntity, otherEntity);
			
			const auto otherPhysicsComp = otherEntity->GetComponent<GameEntityPhysicsComponent>();
			
			/* Collision responses. */
			// Don't respond if either is not collidable.
			if (!activePhysicsComp->isCollidable || !otherPhysicsComp->isCollidable)
			{
				continue;
			}

			// Response on the x axis.
			if (result.test(CollisionLocation::LEFT) || result.test(CollisionLocation::RIGHT))
			{
				activePhysicsComp->velocity.x = 0;
				activePhysicsComp->leftAcceleration = 0;
				activePhysicsComp->rightAcceleration = 0;
				
				// Move the x pos so that it wont trigger collision again.
				if (result.test(CollisionLocation::LEFT))
				{
					activePosComp->pos.x += 0.1f;
				}
				else if (result.test(CollisionLocation::RIGHT))
				{
					activePosComp->pos.x -= 0.1f;
				}
			}

			// Response on the y axis.
			if (result.test(CollisionLocation::TOP) || result.test(CollisionLocation::BOTTOM))
			{
				activePhysicsComp->velocity.y = 0;
				activePhysicsComp->upAcceleration = 0;
				activePhysicsComp->downAcceleration = 0;

				// Move the y pos so that it wont trigger collision again.
				if (result.test(CollisionLocation::TOP))
				{
					activePosComp->pos.y += 0.1f;
				}
				else if(result.test(CollisionLocation::BOTTOM))
				{
					activePosComp->pos.y -= 0.1f;
				}
			}
		}
	}
}

void GameEntityPhysicsSystem::Simulate(float deltaTime)
{
	for (auto &entity : *activePhysicsEntities)
	{
		const auto posComp = entity->GetComponent<PositionComponent>();
		const auto physicsComp = entity->GetComponent<GameEntityPhysicsComponent>();

		// Update acceleration and then velocity.
		Vector2 effectiveAccel = {
			physicsComp->rightAcceleration - physicsComp->leftAcceleration,
			physicsComp->downAcceleration - physicsComp->upAcceleration // flipped because of downwards is +ve 
		};

		physicsComp->velocity.x += effectiveAccel.x * deltaTime;
		physicsComp->velocity.y += effectiveAccel.y * deltaTime;

		// Update position component from velocity.
		posComp->pos.x += deltaTime * physicsComp->velocity.x;
		posComp->pos.y += deltaTime * physicsComp->velocity.y;
	}
}

void GameEntityPhysicsSystem::Process(float deltaTime)
{
	physicsEntities = Context::ECSEngine()->GetEntities(physicsBitset);
	activePhysicsEntities = std::make_shared<EntityList>();

	for (auto &entity : *physicsEntities)
	{
		if (!entity->GetComponent<GameEntityPhysicsComponent>()->isPassive)
		{
			activePhysicsEntities->push_back(entity);
		}
	}

	ApplyGravity();

	CollisionDetection();

	Simulate(deltaTime);

	activePhysicsEntities->clear();
}
