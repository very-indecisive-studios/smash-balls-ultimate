#include "pch.h"
#include "pickup.h"
#include "context/context.h"

Pickup::Pickup(int type)
{
	body->AttachComponent<PositionComponent>(posComp);
	body->AttachComponent<SpriteComponent>(spriteComp);
	Context::ECSEngine->AttachEntity(body);

	pickupTexture = Context::ResourceManager()->GetTexture(Resources::PLAYER_LEFT_OFF_FOLDER + color + ".png");
}

void Pickup::Update(float deltaTime)
{

}