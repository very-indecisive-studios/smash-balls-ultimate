#pragma once
#include "ecs/ecs.h"
#include "game/entities/gameEntity.h"
#include "ecs/components/position.h"
#include "ecs/components/animator.h"
#include "ecs/components/sprite.h"
#include <memory>
#include <functional>
#include "math/math.h"
#include "game/resources.h"

class Button : public GameEntity
{
private:
	std::shared_ptr<PositionComponent> posComp = std::make_shared<PositionComponent>();
	std::shared_ptr<SpriteComponent> spriteComp = std::make_shared<SpriteComponent>();
	std::shared_ptr<Entity> button = std::make_shared<Entity>();

	std::shared_ptr<AudioPlayer> buttonClickAudioPlayer;

	int height;
	int width;
	bool mouseDown = false;
	bool mouseClicked = false;
	std::function<void()> callbackClicked;

public:
	Button(std::string pathToTexture, Vector2 pointToDraw, int height, int width, std::function<void()> callbackClicked);
	bool MouseOverButton();
	void PerformMouseAction();
	void Update(float deltaTime) override;
};