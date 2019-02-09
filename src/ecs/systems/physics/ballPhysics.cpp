#include "pch.h"

#include <cmath>
#include "ballPhysics.h"
#include "ecs/components/ballPhysics.h"
#include "ecs/components/gameEntityPhysics.h"
#include "ecs/components/position.h"
#include "context/context.h"
#include "constants.h"
#include "game/resources.h"

void BallPhysicsSystem::ApplyGravity()
{
	const auto physicsComp = ballEntity->GetComponent<BallPhysicsComponent>();
	physicsComp->downAcceleration = 100;
}

// To slow down ball x-axis velocity
void BallPhysicsSystem::AirResistance()
{
	const auto physicsComp = ballEntity->GetComponent<BallPhysicsComponent>();

	if (physicsComp->velocity.x >= 0)
	{
		physicsComp->velocity.x -= 0.25f;
	}
	else
	{
		physicsComp->velocity.x += 0.25f;
	}
}

CollisionResult BallPhysicsSystem::TestEntityCollision(std::shared_ptr<Entity> gameEntity)
{
	CollisionResult result;

	const auto ballPhyComp = ballEntity->GetComponent<BallPhysicsComponent>();
	const auto ballPosComp = ballEntity->GetComponent<PositionComponent>();

	const auto gameEntityPhyComp = gameEntity->GetComponent<GameEntityPhysicsComponent>();
	const auto gameEntityPosComp = gameEntity->GetComponent<PositionComponent>();

	// Center of ball.
	float ballCenterX = ballPosComp->pos.x + ballPhyComp->collisionCircleRadius;
	float ballCenterY = ballPosComp->pos.y + ballPhyComp->collisionCircleRadius;

	// Rectangle of game entity.
	RECT gameEntityRect = { 0 };
	gameEntityRect.left = gameEntityPosComp->pos.x;
	gameEntityRect.right = gameEntityPosComp->pos.x + gameEntityPhyComp->collisionBoxWidth;
	gameEntityRect.top = gameEntityPosComp->pos.y;
	gameEntityRect.bottom = gameEntityPosComp->pos.y + gameEntityPhyComp->collisionBoxHeight;

	// Collision detection for AABB & Circle.
	float closeX = ballCenterX;
	float closeY = ballCenterY;

	// check left
	if (ballCenterX < gameEntityRect.left)
	{
		closeX = gameEntityRect.left;
	}
	// check right
	if (ballCenterX > gameEntityRect.right)
	{
		closeX = gameEntityRect.right;
	}
	// check top
	if (ballCenterY < gameEntityRect.top)
	{
		closeY = gameEntityRect.top;
	}
	// check bottom
	if (ballCenterY > gameEntityRect.bottom)
	{
		closeY = gameEntityRect.bottom;
	}

	float distanceSquared = std::powf(closeX - ballCenterX, 2) + std::powf(closeY - ballCenterY, 2);
	bool collided = distanceSquared < std::powf(ballPhyComp->collisionCircleRadius, 2);

	// Get the collision location.
	if (collided)
	{
		int deltaRight = gameEntityRect.left - ballCenterX;
		if (deltaRight >= 0 && deltaRight < ballPhyComp->collisionCircleRadius)
		{
			//Ciricle --><-- AABB 
			result.set(RIGHT);
		}

		int deltaLeft = ballCenterX - gameEntityRect.right;
		if (deltaLeft >= 0 && deltaLeft < ballPhyComp->collisionCircleRadius)
		{
			//AABB --><-- Circle
			result.set(LEFT);
		}

		int deltaBottom = gameEntityRect.top - ballCenterY;
		if (deltaBottom >= 0 && deltaBottom < ballPhyComp->collisionCircleRadius)
		{
			/*
			Circle
			-----
			AABB
			*/
			result.set(BOTTOM);
		}
		
		int deltaTop = ballCenterY - gameEntityRect.bottom;
		if (deltaTop >= 0 && deltaTop < ballPhyComp->collisionCircleRadius)
		{
			/*
			AABB
			-----
			Circle
			*/
			result.set(TOP);
		}

		if (ballPhyComp->onCollisionCallback)
		{
			ballPhyComp->onCollisionCallback(gameEntity);
		}
	}

	return result;
}

void BallPhysicsSystem::KickBall(std::shared_ptr<Entity> player, CollisionResult result)
{
	const auto physicsComp = ballEntity->GetComponent<BallPhysicsComponent>();
	const auto posComp = ballEntity->GetComponent<PositionComponent>();
	
	if (result.test(LEFT) || result.test(RIGHT)) 
	{
		if (result.test(LEFT))
		{
			/*Knockback player - to ensure ball will not get 'eaten' (only for x-axis)*/
			player->GetComponent<PositionComponent>()->pos.x = posComp->pos.x - Resources::PLAYER_WIDTH;

			/*Kick the ball by giving adding velocity*/
			physicsComp->velocity.x += 50;
		}

		if (result.test(RIGHT))
		{
			player->GetComponent<PositionComponent>()->pos.x = posComp->pos.x + Resources::BALL_WIDTH;
			physicsComp->velocity.x -= 50;
		}

		/*Angle the ball slightly to simulate a kick*/
		if (physicsComp->velocity.y >= 0)
		{
			// ball coming downwards
			physicsComp->velocity.y -= 225;
		}
		else
		{
			// ball coming upwards
			physicsComp->velocity.y += 225;
		}
	}

	if (result.test(TOP))
	{
		physicsComp->velocity.y += 50;
	}

	if (result.test(BOTTOM))
	{
		physicsComp->velocity.y -= 50;
	}
}

void BallPhysicsSystem::CollisionDetection()
{
	const auto physicsComp = ballEntity->GetComponent<BallPhysicsComponent>();
	const auto posComp = ballEntity->GetComponent<PositionComponent>();

	for (auto gameEntity : *gameEntities)
	{
		CollisionResult result = TestEntityCollision(gameEntity);

		/* Collision responses. */
		if (!gameEntity->GetComponent<GameEntityPhysicsComponent>()->isCollidable) // For goalposts.
		{
			continue;
		}

		// Negate the x and y respectively.
		if (result.test(LEFT))
		{
			if (physicsComp->velocity.x < 0)
			{
				physicsComp->velocity.x = -physicsComp->velocity.x;
			}

			if (!gameEntity->GetComponent<GameEntityPhysicsComponent>()->isPassive) // If ball hit player
			{
				KickBall(gameEntity, result);
			}
		}
		
		if (result.test(RIGHT))
		{
			if (physicsComp->velocity.x >= 0)
			{
				physicsComp->velocity.x = -physicsComp->velocity.x;
			}

			if (!gameEntity->GetComponent<GameEntityPhysicsComponent>()->isPassive) // If ball hit player
			{
				KickBall(gameEntity, result);
			}
		}

		if (result.test(TOP))
		{
			if (physicsComp->velocity.y < 0)
			{
				physicsComp->velocity.y = -physicsComp->velocity.y;
			}

			if (!gameEntity->GetComponent<GameEntityPhysicsComponent>()->isPassive) // If ball hit player
			{
				KickBall(gameEntity, result);
			}
		}
		
		if (result.test(BOTTOM))
		{
			if (physicsComp->velocity.y >= 0)
			{
				physicsComp->velocity.y = -physicsComp->velocity.y;
			}

			if (!gameEntity->GetComponent<GameEntityPhysicsComponent>()->isPassive) // If ball hit player
			{
				KickBall(gameEntity, result);
			}
		}
	}
}

void BallPhysicsSystem::Simulate(float deltaTime)
{
	const auto physicsComp = ballEntity->GetComponent<BallPhysicsComponent>();
	const auto posComp = ballEntity->GetComponent<PositionComponent>();

	// Update acceleration and then velocity.
	Vector2 effectiveAccel = {
		physicsComp->rightAcceleration - physicsComp->leftAcceleration,
		physicsComp->downAcceleration - physicsComp->upAcceleration // flipped because of downwards is +ve 
	};

	physicsComp->velocity.x += effectiveAccel.x * deltaTime;
	physicsComp->velocity.y += effectiveAccel.y * deltaTime;

	/*Limit ball's velocity*/
	if (physicsComp->velocity.x > 0 && physicsComp->velocity.x > physicsComp->maxVelocity.x)
	{
		physicsComp->velocity.x = physicsComp->maxVelocity.x; // Limit right
	}

	if (physicsComp->velocity.x < 0 && physicsComp->velocity.x < -physicsComp->maxVelocity.x)
	{
		physicsComp->velocity.x = -physicsComp->maxVelocity.x; // Limit left
	}

	if (physicsComp->velocity.y < 0 && physicsComp->velocity.y < -physicsComp->maxVelocity.y)
	{
		physicsComp->velocity.y = -physicsComp->maxVelocity.y; // Limit up
	}

	if (physicsComp->velocity.y > 0 && physicsComp->velocity.y > physicsComp->maxVelocity.y)
	{
		physicsComp->velocity.y = physicsComp->maxVelocity.y; // Limit down
	}

	/*Update position component from velocity*/

	// x-axis
	if (posComp->pos.x + deltaTime * physicsComp->velocity.x < 0) 
	{
		posComp->pos.x = 0; // avoid ball to escape from left wall
	}
	else if (posComp->pos.x + deltaTime * physicsComp->velocity.x > Constants::GAME_WIDTH - Resources::BALL_WIDTH) 
	{
		posComp->pos.x = Constants::GAME_WIDTH - Resources::BALL_WIDTH; // avoid ball to escape from right wall
	}
	posComp->pos.x += deltaTime * physicsComp->velocity.x;

	// y-axis
	if (posComp->pos.y + deltaTime * physicsComp->velocity.y < 0)
	{
		posComp->pos.y = 0; // avoid ball to escape from top wall
	}
	else if (posComp->pos.y + deltaTime * physicsComp->velocity.y > Constants::GAME_HEIGHT - Resources::GROUND_HEIGHT - Resources::BALL_WIDTH)
	{
		posComp->pos.y = Constants::GAME_HEIGHT - Resources::GROUND_HEIGHT - Resources::BALL_WIDTH; // avoid ball to escape from bottom wall
	}
	posComp->pos.y += deltaTime * physicsComp->velocity.y;
	
}

BallPhysicsSystem::BallPhysicsSystem()
{
	gameEntityPhyBitset.set(Component::GetComponentId<GameEntityPhysicsComponent>());
}

void BallPhysicsSystem::Process(float deltaTime)
{
	gameEntities = Context::ECSEngine()->GetEntities(gameEntityPhyBitset);

	ballEntity = Context::ECSEngine()->GetTaggedEntity("ball");
	
	// No balls to process
	if (ballEntity == nullptr)
	{
		return;
	}
	ApplyGravity();

	AirResistance();
	
	CollisionDetection();
	
	Simulate(deltaTime);
}