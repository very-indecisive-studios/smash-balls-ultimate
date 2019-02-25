#include "pch.h"
#include "pickup.h"
#include "game/data.h"
#include "context/context.h"
#include "game/resources.h"
#include "game/layers.h"

Pickup::Pickup(Vector2 spawnpt)
{
	pickup->SetListTag("Pickup");
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
	physComp->isCollidable = false;
	physComp->isPickup = true;
	physComp->velocity = { 100, 100 };
	/*physComp->onCollisionCallback = [this](auto e) /
	{
		if (e->GetTag() == "player")
		{
			physicsComp = e->GetComponent<GameEntityPhysicsComponent>(physicsComp);
			this->collidedPlayer = true;
			physComp->velocity.x = Resources::PLAYER_SPEED * 2;
			physComp->upAcceleration = Resources::PLAYER_SPEED * 2;
		};
	};*/
	
}

Pickup::~Pickup()
{
	Context::ECSEngine()->RemoveEntity(pickup);
}

void Pickup::ResetPlayer(bool collided)
{
	/*if (collided == false)
	{
		physComp->onCollisionCallback = [this](auto e)
		{
			if (e->GetTag() == "player")
			{
				physComp = e->GetComponent<GameEntityPhysicsComponent>();
				physComp->velocity.x = Resources::PLAYER_SPEED;
				physComp->upAcceleration = Resources::PLAYER_SPEED;
				this->collidedPlayer = false;
			};
		};
	}*/
}

bool Pickup::CheckCollided()
{
	return collidedPlayer;
}
void Pickup::Update(float deltaTime)
{
	physComp->velocity.x = Resources::PICKUP_SPEED;
}