#include "pch.h"

#include "ball.h"
#include "context/context.h"
#include "game/resources.h"
#include <iostream>

Ball::Ball(float radius)
{
	ball->SetTag("ball");

	ball->AttachComponent<PositionComponent>(posComp);
	ball->AttachComponent<SpriteComponent>(spriteComp);
	ball->AttachComponent<BallPhysicsComponent>(phyComp);
	Context::ECSEngine()->AttachEntity(ball);

	spriteComp->texture = Context::ResourceManager()->GetTexture(Resources::BALL_IMAGE);
	spriteComp->layer = 10;

	posComp->pos = {Resources::BALL_SPAWN_X, Resources::BALL_SPAWN_Y};

	phyComp->collisionCircleRadius = radius;
	phyComp->maxVelocity = Resources::BALL_MAX_VEL;

	ballHitAudioPlayer = Context::ResourceManager()->CreateAudioPlayer(Resources::BALL_HIT_AUDIO);
	ballHitAudioPlayer->SetVolume(0.25f);
	phyComp->onCollisionCallback = [&ballHitAudioPlayer = ballHitAudioPlayer](std::shared_ptr<Entity> e)
	{
		ballHitAudioPlayer->Play();
	};
}

void Ball::Reset() 
{
	posComp->pos = { Resources::BALL_SPAWN_X, Resources::BALL_SPAWN_Y };
	phyComp->velocity = { 0,0 };
	phyComp->downAcceleration = 0;
	phyComp->upAcceleration = 0;
	phyComp->leftAcceleration = 0;
	phyComp->rightAcceleration = 0;
}

void Ball::Update(float deltaTime)
{ }