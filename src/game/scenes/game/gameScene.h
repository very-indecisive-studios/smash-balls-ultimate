#pragma once

#include "scene/scene.h"
#include "audio/audio.h"
#include "text/text.h"
#include "sprites/sprite.h"
#include <memory>
#include "game/entities/player/player.h"
#include "game/entities/background/background.h"
#include "game/entities/text/textObject.h"
#include "game/entities/scoreboard/scoreboard.h"

class GameScene : public Scene
{
private:
	std::unique_ptr<Background> background;
	std::unique_ptr<Player> player1;
	std::unique_ptr<Player> player2;
	std::unique_ptr<Scoreboard> scoreboard;

	std::unique_ptr<TextObject> pauseText;
	bool isPaused = false;

	std::string p1Color;
	std::string p2Color;
	std::string gameMode;

	bool resetRound = false;

public:
	GameScene(std::string p1Color, std::string p2Color, std::string gameMode);
	~GameScene();

	void Initialize() override;
	void Update(float deltaTime) override;
};
