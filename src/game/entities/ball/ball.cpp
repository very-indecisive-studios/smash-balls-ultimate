#include "pch.h"

#include "ball.h"
#include "context/context.h"
#include <iostream>

Ball::Ball(float radius)
{
	ball->AttachComponent<PositionComponent>(posComp);
	ball->AttachComponent<SpriteComponent>(spriteComp);
	ball->AttachComponent<PhysicsComponent>(phyComp);
	Context::ECSEngine()->AttachEntity(ball);

	spriteComp->texture = Context::ResourceManager()->GetTexture(Resources::BALL_IMAGE);
	spriteComp->layer = 10;

	posComp->pos = {(Constants::GAME_WIDTH/2) - (Resources::BALL_RADIUS/2), Constants::GAME_HEIGHT - Resources::GROUND_HEIGHT - Resources::BALL_RADIUS*2};

	phyComp->radius = radius;
	phyComp->isPassive = false;
	phyComp->SetCurrentPos(posComp->pos);
	phyComp->center.x = posComp->pos.x + phyComp->radius;
	phyComp->center.y = posComp->pos.y + phyComp->radius;
}

void Ball::Update(float deltaTime)
{
	phyComp->SetCurrentPos(posComp->pos);
	phyComp->center.x = posComp->pos.x + phyComp->radius;
	phyComp->center.y = posComp->pos.y + phyComp->radius;
}