#include "pch.h"

#include "goalpost.h"
#include "context/context.h"
#include <iostream>

Goalpost::Goalpost(std::string pathToImage, float x, float y)
{
	goalpost->AttachComponent<PositionComponent>(posComp);
	goalpost->AttachComponent<SpriteComponent>(spriteComp);
	goalpost->AttachComponent<GameEntityPhysicsComponent>(phyComp);
	Context::ECSEngine()->AttachEntity(goalpost);

	posComp->pos.x = x;
	posComp->pos.y = y;

	spriteComp->texture = Context::ResourceManager()->GetTexture(pathToImage);
	spriteComp->layer = 101;

	phyComp->collisionBoxHeight = height;
	phyComp->collisionBoxWidth = width;
	phyComp->isPassive = true;
	phyComp->isCollidable = false;
}

void Goalpost::Update(float deltaTime)
{
}