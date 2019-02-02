#include "pch.h"

#include "ball.h"
#include "context/context.h"
#include <iostream>

Ball::Ball()
{
	ball->AttachComponent<PositionComponent>(posComp);
	ball->AttachComponent<SpriteComponent>(spriteComp);
	ball->AttachComponent<PhysicsComponent>(phyComp);
	Context::ECSEngine()->AttachEntity(ball);

	spriteComp->texture = Context::ResourceManager()->GetTexture(Resources::BALL_IMAGE);
	spriteComp->layer = 10;

	posComp->pos = { 100,100 };

	phyComp->isPassive = false;
}

void Ball::Update(float deltaTime)
{
	phyComp->left = posComp->pos.x;
	phyComp->right = posComp->pos.x + Resources::PLAYER_WIDTH;
	phyComp->top = posComp->pos.y;
	phyComp->bottom = posComp->pos.y + Resources::PLAYER_HEIGHT;
}