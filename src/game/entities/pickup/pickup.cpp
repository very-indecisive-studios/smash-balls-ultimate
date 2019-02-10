#include "pch.h"
#include "pickup.h"
#include "game/data.h"
#include "context/context.h"

Pickup::Pickup(Vector2 spawnpt)
{
	body->AttachComponent<PositionComponent>(posComp);
	body->AttachComponent<SpriteComponent>(spriteComp);
	body->AttachComponent<AnimatorComponent>(animComp);
	body->AttachComponent<GameEntityPhysicsComponent>(physComp);
	Context::ECSEngine()->AttachEntity(body);

	pickupSpeedTexture = Context::ResourceManager()->GetTexture(Resources::PICKUP_SPEED);

	spriteComp->texture = pickupSpeedTexture;

	animComp->secondsPerFrame = Resources::PICKUP_ANIMATION_DELAY;
	animComp->frameWidth = Resources::PICKUP_LENGTH;
	animComp->frameHeight = Resources::PICKUP_LENGTH;
	animComp->Play();

	posComp->pos = spawnpt;

	physComp->collisionBoxHeight = Resources::PICKUP_LENGTH;
	physComp->collisionBoxWidth = Resources::PICKUP_LENGTH;
	physComp->isPassive = false;
}

void Pickup::Update(float deltaTime)
{

}