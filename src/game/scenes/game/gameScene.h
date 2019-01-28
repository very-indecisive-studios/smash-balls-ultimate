#pragma once

#include "scene/scene.h"
#include "audio/audio.h"
#include "text/text.h"
#include "sprites/sprite.h"
#include "game/components/position.h"
#include "game/components/animator.h"
#include "game/components/sprite.h"
#include <memory>
#include "game/entities/player/player.h"

class GameScene : public Scene
{
private:
	Texture *background;
	Text *pauseText;
	bool isPaused = false;
	bool resetRound = false;
	std::shared_ptr<PositionComponent> posComp = std::make_shared<PositionComponent>();
	std::shared_ptr<SpriteComponent> spriteComp = std::make_shared<SpriteComponent>();
	std::shared_ptr<AnimatorComponent> animComp = std::make_shared<AnimatorComponent>();
	std::shared_ptr<Entity> body = std::make_shared<Entity>();

	Player *p1 = nullptr;
public:
	GameScene(int player1, int player2, int gameMode);
	~GameScene();

	void Update(float deltaTime) override;
};
