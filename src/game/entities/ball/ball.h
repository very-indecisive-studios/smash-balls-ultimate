#pragma once
#include "ecs/ecs.h"
#include "game/entities/sceneObject.h"
#include "sprites/animatedSprite.h"
#include "game/components/position.h"
#include "game/components/animator.h"
#include "game/components/sprite.h"
#include "game/components/ballPhysics.h"
#include <memory>
#include "math/math.h"
#include "game/resources.h"

class Ball : public SceneObject
{
private:
	std::shared_ptr<PositionComponent> posComp = std::make_shared<PositionComponent>();
	std::shared_ptr<SpriteComponent> spriteComp = std::make_shared<SpriteComponent>();
	std::shared_ptr<BallPhysicsComponent> phyComp = std::make_shared<BallPhysicsComponent>();
	std::shared_ptr<Entity> ball = std::make_shared<Entity>();

public:
	Ball(float radius);
	void SetX(float newX) { posComp->pos.x = newX; }
	void SetY(float newY) { posComp->pos.y = newY; }
	void Reset();
	Vector2 GetPos() { return posComp->pos; }
	void Update(float deltaTime) override;
};