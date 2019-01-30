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
	std::unique_ptr<Background> background;
	std::unique_ptr<Player> player1;
	std::unique_ptr<Player> player2;
	Text *pauseText;
	bool isPaused = false;
	bool resetRound = false;
	std::string p1Color;
	std::string p2Color;
	int gameMode;
public:
	GameScene(std::string p1Color, std::string p2Color, int gameMode);
	~GameScene();

	void Initialize() override;
	void Update(float deltaTime) override;
};
