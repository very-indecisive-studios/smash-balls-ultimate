#include "pch.h"

#include "ball.h"
#include "context/context.h"
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

	posComp->pos = {(Constants::GAME_WIDTH/2) - (Resources::BALL_RADIUS/2), 20};

	phyComp->collisionCircleRadius = radius;
}

void Ball::Update(float deltaTime)
{ }