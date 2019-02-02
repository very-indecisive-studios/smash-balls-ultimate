#pragma once
#include "ecs/ecs.h"
#include "game/entities/sceneObject.h"
#include "sprites/animatedSprite.h"
#include "game/components/position.h"
#include "game/components/sprite.h"
#include "game/components/physics.h"
#include <memory>
#include "math/math.h"
#include "game/resources.h"

class Goalpost : public SceneObject
{
private:
	std::shared_ptr<PositionComponent> posComp = std::make_shared<PositionComponent>();
	std::shared_ptr<SpriteComponent> spriteComp = std::make_shared<SpriteComponent>();
	std::shared_ptr<PhysicsComponent> phyComp = std::make_shared<PhysicsComponent>();
	std::shared_ptr<Entity> goalpost = std::make_shared<Entity>();

	int height = Resources::GOALPOST_HEIGHT;
	int width = Resources::GOALPOST_WIDTH;

public:
	Goalpost(std::string pathToImage, float x, float y);
	void Update(float deltaTime) override;
};