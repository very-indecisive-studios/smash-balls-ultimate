#include "pch.h"

#include "wall.h"
#include "context/context.h"
#include <iostream>

Wall::Wall(float x, float y, float height, float width)
{
	wall->AttachComponent<PositionComponent>(posComp);
	wall->AttachComponent<GameEntityPhysicsComponent>(phyComp);
	Context::ECSEngine()->AttachEntity(wall);

	posComp->pos.x = x;
	posComp->pos.y = y;

	phyComp->collisionBoxWidth = width;
	phyComp->collisionBoxHeight = height;
	phyComp->isPassive = true;
}

void Wall::Update(float deltaTime)
{
}