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
	std::shared_ptr<Entity> body = std::make_shared<Entity>();
	Vector2 velocity;
	Texture pickupTexture;

public:
	Pickup(int type);
	void SetX(float newX) { posComp->pos.x = newX; }
	void SetY(float newY) { posComp->pos.y = newY; }
	void SetVelocity(float speed) { velocity = Vector2(speed, -speed); }
	void Update(float deltaTime) override;
};
