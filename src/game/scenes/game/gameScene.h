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
#include "game/entities/background/background.h"

class GameScene : public Scene
{
private:
	std::unique_ptr<Background> background = std::make_unique<Background>(Resources::BACKGROUND_IMAGE);
	std::unique_ptr<Player> player1;
	std::unique_ptr<Player> player2;
	Text *pauseText;
	bool isPaused = false;
	bool resetRound = false;
public:
	GameScene(int player1, int player2, int gameMode);
	~GameScene();

	void Update(float deltaTime) override;
};
