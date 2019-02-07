#pragma once
#include "ecs/ecs.h"
#include "game/entities/sceneObject.h"
#include "sprites/animatedSprite.h"
#include "ecs/components/position.h"
#include "ecs/components/animator.h"
#include "ecs/components/sprite.h"
#include <memory>
#include <functional>
#include "math/math.h"
#include "game/resources.h"

class CharacterList : public SceneObject
{
private:
	std::shared_ptr<PositionComponent> posComp = std::make_shared<PositionComponent>();
	std::shared_ptr<SpriteComponent> spriteComp = std::make_shared<SpriteComponent>();
	std::shared_ptr<Entity> button = std::make_shared<Entity>();

	Texture *beigeTexture;
	Texture *blueTexture;
	Texture *greenTexture;
	Texture *pinkTexture;
	Texture *yellowTexture;

	std::vector<Texture *> characterListTextures;
	
	int currentCharacterIndex = 0;
public:
	CharacterList(Vector2 pointToDraw);
	void Next();
	void Previous();
	std::string GetCurrentCharacterColor();
	void Update(float deltaTime) override;
};