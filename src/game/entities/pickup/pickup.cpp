#include "pch.h"
#include "pickup.h"
#include "game/data.h"
#include "context/context.h"
#include "game/resources.h"

Pickup::Pickup(Vector2 spawnpt)
{
	pickup->AttachComponent<PositionComponent>(posComp);
	pickup->AttachComponent<SpriteComponent>(spriteComp);
	pickup->AttachComponent<GameEntityPhysicsComponent>(physComp);
	Context::ECSEngine()->AttachEntity(pickup);

	pickupSpeedTexture = Context::ResourceManager()->GetTexture(Resources::SPEED_PICKUP);

	spriteComp->texture = pickupSpeedTexture;

	posComp->pos = spawnpt;

	physComp->collisionBoxHeight = Resources::PICKUP_LENGTH;
	physComp->collisionBoxWidth = Resources::PICKUP_LENGTH;
	physComp->isPassive = false;
}

void Pickup::Update(float deltaTime)
{
	physComp->velocity.x = Resources::PICKUP_SPEED;
}