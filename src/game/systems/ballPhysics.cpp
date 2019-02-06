#include "pch.h"

#include <cmath>
#include "ballPhysics.h"
#include "game/components/ballPhysics.h"
#include "game/components/gameEntityPhysics.h"
#include "game/components/position.h"
#include "context/context.h"

void BallPhysicsSystem::ApplyGravity()
{
	const auto physicsComp = ballEntity->GetComponent<BallPhysicsComponent>();
	physicsComp->downAcceleration = 100;
}

BallPhysicsSystem::CollisionResult BallPhysicsSystem::TestEntityCollision(std::shared_ptr<Entity> gameEntity)
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
			std::cout << "right" << std::endl;
			//Ciricle --><-- AABB 
			result.set(RIGHT);
		}

		int deltaLeft = ballCenterX - gameEntityRect.right;
		if (deltaLeft >= 0 && deltaLeft < ballPhyComp->collisionCircleRadius)
		{
			std::cout << "left" << std::endl;
			//AABB --><-- Circle
			result.set(LEFT);
		}

		int deltaBottom = gameEntityRect.top - ballCenterY;
		if (deltaBottom >= 0 && deltaBottom < ballPhyComp->collisionCircleRadius)
		{
			std::cout << "bottom" << std::endl;
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
			std::cout << "top" << std::endl;
			/*
			AABB
			-----
			Circle
			*/
			result.set(TOP);
		}
	}

	return result;
}

void BallPhysicsSystem::CollisionDetection()
{
	const auto physicsComp = ballEntity->GetComponent<BallPhysicsComponent>();

	for (auto gameEntity : *gameEntities)
	{
		CollisionResult result = TestEntityCollision(gameEntity);

		/* Collision responses. */
		if (!gameEntity->GetComponent<GameEntityPhysicsComponent>()->isCollidable) // For goalposts.
		{
			continue;
		}

		if (result.test(LEFT))
		{
			physicsComp->velocity.x = -physicsComp->velocity.x;
			//if (physicsComp->velocity.x < 0) 
			//{
			//	physicsComp->velocity.x = -physicsComp->velocity.x;
			//}
			physicsComp->rightAcceleration = 50;
			physicsComp->leftAcceleration = 0;
			physicsComp->velocity.x += 50;
		}
		else if (result.test(RIGHT))
		{
			physicsComp->velocity.x = -physicsComp->velocity.x;
			/*if (physicsComp->velocity.x >= 0)
			{
				physicsComp->velocity.x = -physicsComp->velocity.x;
			}*/
			physicsComp->leftAcceleration = 50;
			physicsComp->rightAcceleration = 0;
			physicsComp->velocity.x -= 50;

		}
		
		// Negate the x and y respectively.
		//if (result.test(LEFT) || result.test(RIGHT)) // -->| then <--|
		//{ 
		//	physicsComp->velocity.x = -physicsComp->velocity.x;
		//}

		if (result.test(TOP))
		{
			physicsComp->velocity.y = -physicsComp->velocity.y;
			physicsComp->velocity.y += 10;
		}
		
		if (result.test(BOTTOM))
		{
			physicsComp->velocity.y = -physicsComp->velocity.y;
			physicsComp->velocity.y -= 10;
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

	// Update position component from velocity.
	posComp->pos.x += deltaTime * physicsComp->velocity.x;
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
	
	CollisionDetection();
	
	Simulate(deltaTime);
}