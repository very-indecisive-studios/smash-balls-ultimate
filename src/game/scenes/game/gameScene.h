#pragma once

#include "scene/scene.h"
#include "audio/audio.h"
#include "text/text.h"
#include "sprites/sprite.h"
#include "game/components/position.h"
#include "game/components/animator.h"
#include "game/components/sprite.h"
#include <memory>

class GameScene : public Scene
{
private:
	Sprite *background = nullptr;
	Text *pauseText;
	bool isPaused = false;
	bool resetRound = false;
	std::shared_ptr<PositionComponent> posComp = std::make_shared<PositionComponent>();
	std::shared_ptr<SpriteComponent> spriteComp = std::make_shared<SpriteComponent>();
	std::shared_ptr<AnimatorComponent> animComp = std::make_shared<AnimatorComponent>();

public:
	GameScene(int player1, int player2, int gameMode);
	~GameScene();

	void Update(float deltaTime) override;
};
