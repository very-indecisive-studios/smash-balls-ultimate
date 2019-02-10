#pragma once
#include "constants.h"
#include "ecs/ecs.h"
#include "game/entities/gameEntity.h"
#include "ecs/components/position.h"
#include "ecs/components/animator.h"
#include "ecs/components/sprite.h"
#include "ecs/components/gameEntityPhysics.h"
#include <memory>
#include "math/math.h"
#include "game/resources.h"

class Pickup : public GameEntity
{
private:
	std::shared_ptr<PositionComponent> posComp = std::make_shared<PositionComponent>();
	std::shared_ptr<SpriteComponent> spriteComp = std::make_shared<SpriteComponent>();
	std::shared_ptr<GameEntityPhysicsComponent> physComp = std::make_shared<GameEntityPhysicsComponent>();
	std::shared_ptr<Entity> pickup = std::make_shared<Entity>();
	
	Vector2 velocity;
	Texture *pickupSpeedTexture;
	int x = rand() % Constants::GAME_WIDTH;

public:
	Pickup(Vector2 spawnpt);
	void Update(float deltaTime) override;
};
