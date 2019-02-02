#include "pch.h"

#include "wall.h"
#include "context/context.h"
#include <iostream>

Wall::Wall(float x, float y, float height, float width)
{
	wall->AttachComponent<PositionComponent>(posComp);
	wall->AttachComponent<PhysicsComponent>(phyComp);
	Context::ECSEngine()->AttachEntity(wall);

	posComp->pos.x = x;
	posComp->pos.y = y;

	phyComp->left = posComp->pos.x;
	phyComp->right = posComp->pos.x + width;
	phyComp->top = posComp->pos.y;
	phyComp->bottom = posComp->pos.y + height;
	phyComp->isPassive = true;
}

void Wall::Update(float deltaTime)
{
}