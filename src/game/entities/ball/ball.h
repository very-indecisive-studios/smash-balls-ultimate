#pragma once

#include "audio/audio.h"
#include "ecs/ecs.h"
#include "game/entities/gameEntity.h"
#include "ecs/components/position.h"
#include "ecs/components/animator.h"
#include "ecs/components/sprite.h"
#include "ecs/components/ballPhysics.h"
#include <memory>
#include "math/math.h"
#include "game/resources.h"

class Ball : public GameEntity
{
private:
	std::shared_ptr<PositionComponent> posComp = std::make_shared<PositionComponent>();
	std::shared_ptr<SpriteComponent> spriteComp = std::make_shared<SpriteComponent>();
	std::shared_ptr<BallPhysicsComponent> phyComp = std::make_shared<BallPhysicsComponent>();
	std::shared_ptr<Entity> ball = std::make_shared<Entity>();
	std::shared_ptr<AudioPlayer> ballHitAudioPlayer;
public:
	Ball(float radius);
	void SetX(float newX) { posComp->pos.x = newX; }
	void SetY(float newY) { posComp->pos.y = newY; }
	void Reset();
	Vector2 GetPos() { return posComp->pos; }
	void Update(float deltaTime) override;
};