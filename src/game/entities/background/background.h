#pragma once
#include "ecs/ecs.h"
#include "game/entities/gameEntity.h"
#include "ecs/components/position.h"
#include "ecs/components/sprite.h"
#include <memory>
#include "math/math.h"
#include "game/resources.h"

class Background : public GameEntity
{
private:
	std::shared_ptr<PositionComponent> posComp = std::make_shared<PositionComponent>();
	std::shared_ptr<SpriteComponent> spriteComp = std::make_shared<SpriteComponent>();
	std::shared_ptr<Entity> background = std::make_shared<Entity>();

public:
	Background(std::string pathToTexture);
	void Update(float deltaTime) override;
};
