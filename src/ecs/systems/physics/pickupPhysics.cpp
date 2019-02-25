#include "pch.h"

#include "pickupPhysics.h"
#include "ecs/components/position.h"
#include "ecs/components/gameEntityPhysics.h"
#include "context/context.h"
#include "constants.h"
#include "game/resources.h"

PickupPhysicsSystem::PickupPhysicsSystem()
{
	
}

CollisionResult PickupPhysicsSystem::TestEntityCollision(std::shared_ptr<Entity> pickup, std::shared_ptr<Entity> player)
{
	CollisionResult result;

	// Get physics component
	const auto pickupPosComp = pickup->GetComponent<PositionComponent>();
	const auto pickupPhysComp = pickup->GetComponent<GameEntityPhysicsComponent>();

	RECT pickupRect = { 0 };
	pickupRect.left = pickupPosComp->pos.x;
	pickupRect.right = pickupPosComp->pos.x + pickupPhysComp->collisionBoxWidth;
	pickupRect.top = pickupPosComp->pos.y;
	pickupRect.bottom = pickupPosComp->pos.y + pickupPhysComp->collisionBoxHeight;

	// Get rectangle of player entity.
	const auto playerPosComp = player->GetComponent<PositionComponent>();
	const auto playerPhysComp = player->GetComponent<GameEntityPhysicsComponent>();

	RECT playerRect = { 0 };
	playerRect.left = playerPosComp->pos.x;
	playerRect.right = playerPosComp->pos.x + playerPhysComp->collisionBoxWidth;
	playerRect.top = playerPosComp->pos.y;
	playerRect.bottom = playerPosComp->pos.y + playerPhysComp->collisionBoxHeight;

	// Collision detection for AABB.
	bool isCollided = !(pickupRect.right <= playerRect.left ||
		pickupRect.left >= playerRect.right ||
		pickupRect.bottom <= playerRect.top ||
		pickupRect.top >= playerRect.bottom);

	// Get the collision location.
	if (isCollided)
	{
		int deltaRight = pickupRect.right - playerRect.left;
		if (deltaRight > 0 && deltaRight < pickupPhysComp->collisionBoxWidth)
		{
			result.set(CollisionLocation::RIGHT);
		}

		int deltaLeft = playerRect.right - pickupRect.left;
		if (deltaLeft > 0 && deltaLeft < pickupPhysComp->collisionBoxWidth)
		{
			result.set(CollisionLocation::LEFT);
		}

		int deltaTop = playerRect.bottom - pickupRect.top;
		if (deltaTop > 0 && deltaTop < pickupPhysComp->collisionBoxHeight)
		{
			result.set(CollisionLocation::TOP);
		}

		int deltaBottom = pickupRect.bottom - playerRect.top;
		if (deltaBottom > 0 && deltaBottom < pickupPhysComp->collisionBoxHeight)
		{
			result.set(CollisionLocation::BOTTOM);
		}

		if (pickupPhysComp->onCollisionCallback)
		{
			pickupPhysComp->onCollisionCallback(player);
		}
	}
	return result;
}

void PickupPhysicsSystem::CollisionDetection()
{
	//for (auto &player: *playerEntities)
	//{
		const auto playerPhysComp = player->GetComponent<GameEntityPhysicsComponent>();
		const auto playerPosComp = player->GetComponent<PositionComponent>();

		for (auto &pickup : *pickupEntities)
		{
			auto result = TestEntityCollision(pickup, player);

			const auto physComp = pickup->GetComponent<GameEntityPhysicsComponent>();
			const auto posComp = pickup->GetComponent<PositionComponent>();
			if (posComp->pos.x < 0)
			{
				physComp->velocity.x = -physComp->velocity.x;
			}
			else if (posComp->pos.x >= Constants::GAME_WIDTH - Resources::PICKUP_LENGTH)
			{
				physComp->velocity.x = -physComp->velocity.x;
			}
			if (posComp->pos.y < 0)
			{
				physComp->velocity.y = -physComp->velocity.y;
			}
			else if (posComp->pos.y >= Constants::GAME_HEIGHT - Resources::GROUND_HEIGHT - Resources::PICKUP_LENGTH)
			{
				physComp->velocity.y = -physComp->velocity.y;
			}

			if (result.test(CollisionLocation::LEFT) || result.test(CollisionLocation::RIGHT) || result.test(CollisionLocation::TOP) || result.test(CollisionLocation::BOTTOM))
			{
				playerPhysComp->velocity.x = Resources::PLAYER_SPEED * 2;
			}
		}
	//}
}

void PickupPhysicsSystem::Simulate(float deltaTime)
{
	for (auto &pickup : *pickupEntities)
	{
		const auto physComp = pickup->GetComponent<GameEntityPhysicsComponent>();
		const auto posComp = pickup->GetComponent<PositionComponent>();
		if (posComp->pos.x + deltaTime * physComp->velocity.x < 0)
		{
			posComp->pos.x = 0; // avoid escape from left wall
		}
		else if (posComp->pos.x + deltaTime * physComp->velocity.x > Constants::GAME_WIDTH - Resources::PICKUP_LENGTH)
		{
			posComp->pos.x = Constants::GAME_WIDTH - Resources::PICKUP_LENGTH; // avoid escape from right wall
		}
		posComp->pos.x += deltaTime * physComp->velocity.x;

		// y-axis
		if (posComp->pos.y + deltaTime * physComp->velocity.y < 0)
		{
			posComp->pos.y = 0; // avoid escape from top wall
		}
		else if (posComp->pos.y + deltaTime * physComp->velocity.y > Constants::GAME_HEIGHT - Resources::GROUND_HEIGHT - Resources::PICKUP_LENGTH)
		{
			posComp->pos.y = Constants::GAME_HEIGHT - Resources::GROUND_HEIGHT - Resources::PICKUP_LENGTH; // avoid escape from bottom wall
		}
		posComp->pos.y += deltaTime * physComp->velocity.y;
	}
}

void PickupPhysicsSystem::Process(float deltaTime)
{
	pickupEntities = Context::ECSEngine()->GetEntities("Pickup");
	player = Context::ECSEngine()->GetTaggedEntity("player");
	if (player == nullptr)
	{
		return;
	}
	for (auto &pickups : *pickupEntities)
	{
		if (pickups == nullptr)
		{
			return;
		}
	}
	CollisionDetection();
	Simulate(deltaTime);
}