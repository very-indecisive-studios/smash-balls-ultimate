#pragma once
#include "constants.h"
#include "ecs/ecs.h"
#include "game/entities/sceneObject.h"
#include "sprites/animatedSprite.h"
#include "game/components/position.h"
#include "game/components/animator.h"
#include "game/components/sprite.h"
#include <memory>
#include "math/math.h"
#include "game/resources.h"
class Pickup : public SceneObject 
{
private:
	std::shared_ptr<PositionComponent> positionComp = std::make_shared<PositionComponent>();
	std::shared_ptr<SpriteComponent> spriteComp = std::make_shared<SpriteComponent>();
	std::shared_ptr<Entity> body = std::make_shared<Entity>();

public:
	Pickup(int type);

};

