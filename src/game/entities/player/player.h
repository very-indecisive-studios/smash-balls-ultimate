#pragma once
#include "ecs/ecs.h"
#include "game/entities/sceneObject.h"
#include "sprites/animatedSprite.h"
#include "game/components/position.h"
#include "game/components/animator.h"
#include "game/components/sprite.h"
#include <memory>
#include "math/math.h"
#include "game/resources.h"

class Player : public SceneObject
{
private:
	std::shared_ptr<PositionComponent> posComp = std::make_shared<PositionComponent>();
	std::shared_ptr<SpriteComponent> spriteComp = std::make_shared<SpriteComponent>();
	std::shared_ptr<AnimatorComponent> animComp = std::make_shared<AnimatorComponent>();
	std::shared_ptr<Entity> body = std::make_shared<Entity>();

	UCHAR leftKey;
	UCHAR rightKey;
	UCHAR jetpackKey;
	UCHAR powerKey;
	Vector2 velocity;

	AnimatedSprite *currentAnimSprite;
	AnimatedSprite *leftOffAnimSprite;
	AnimatedSprite *leftOnAnimSprite;
	AnimatedSprite *rightOffAnimSprite;
	AnimatedSprite *rightOnAnimSprite;
public:
	Player(std::string color, bool isPlayer1);
	void SetLeftKey(UCHAR leftKey) { this->leftKey = leftKey; }
	void SetRightKey(UCHAR rightKey) { this->rightKey = rightKey; }
	void SetJetpackKey(UCHAR jetpackKey) { this->jetpackKey = jetpackKey; }
	void SetPowerKey(UCHAR powerKey) { this->powerKey = powerKey; }
	void SetVelocity(float speed) { velocity = Vector2(speed, -speed); }
	void SetX(float newX) { posComp->pos.x = newX; }
	void SetY(float newY) { posComp->pos.y = newY; }
	void Update(float deltaTime) override;
};