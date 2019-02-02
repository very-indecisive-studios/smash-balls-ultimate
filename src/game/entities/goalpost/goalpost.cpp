#include "pch.h"

#include "Goalpost.h"
#include "context/context.h"
#include <iostream>

Goalpost::Goalpost(std::string pathToImage, float x, float y)
{
	goalpost->AttachComponent<PositionComponent>(posComp);
	goalpost->AttachComponent<SpriteComponent>(spriteComp);
	goalpost->AttachComponent<PhysicsComponent>(phyComp);
	Context::ECSEngine()->AttachEntity(goalpost);

	posComp->pos.x = x;
	posComp->pos.y = y;

	spriteComp->texture = Context::ResourceManager()->GetTexture(pathToImage);
	spriteComp->layer = 101;

	phyComp->left = posComp->pos.x;
	phyComp->right = posComp->pos.x + width;
	phyComp->top = posComp->pos.y;
	phyComp->bottom = posComp->pos.y + height;
	phyComp->isPassive = true;
	phyComp->collidable = false;
}

void Goalpost::Update(float deltaTime)
{
}