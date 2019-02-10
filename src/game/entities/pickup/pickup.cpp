#include "pch.h"
#include "pickup.h"
#include "game/data.h"
#include "context/context.h"
#include "game/resources.h"
#include "game/layers.h"

Pickup::Pickup(Vector2 spawnpt)
{
	pickup->AttachComponent<PositionComponent>(posComp);
	pickup->AttachComponent<SpriteComponent>(spriteComp);
	pickup->AttachComponent<GameEntityPhysicsComponent>(physComp);
	Context::ECSEngine()->AttachEntity(pickup);

	pickupSpeedTexture = Context::ResourceManager()->GetTexture(Resources::SPEED_PICKUP);

	spriteComp->texture = pickupSpeedTexture;
	spriteComp->layer = Layers::UI_IMAGE;

	posComp->pos = spawnpt;

	physComp->collisionBoxHeight = Resources::PICKUP_LENGTH;
	physComp->collisionBoxWidth = Resources::PICKUP_LENGTH;
	physComp->isPassive = false;
}

void Pickup::Update(float deltaTime)
{
	if (onCollissionCallBack)
	physComp->velocity.x = Resources::PICKUP_SPEED;
}