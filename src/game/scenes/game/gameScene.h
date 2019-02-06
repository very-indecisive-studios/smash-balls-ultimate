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
#include "game/entities/timer/timer.h"
#include "game/entities/wall/wall.h"
#include "game/entities/goalpost/goalpost.h"
#include "game/entities/ball/ball.h"

struct GameMode
{
	bool isTimed = false;
	float limit = 0;
};

class GameScene : public Scene
{
private:
	std::unique_ptr<Background> background;

	std::unique_ptr<Ball> ball;

	std::unique_ptr<Wall> floor;
	std::unique_ptr<Wall> ceiling;
	std::unique_ptr<Wall> leftWall;
	std::unique_ptr<Wall> rightWall;

	std::unique_ptr<Wall> leftGoalpostCeiling;
	std::unique_ptr<Wall> rightGoalpostCeiling;
	std::unique_ptr<Goalpost> leftGoalpost;
	std::unique_ptr<Goalpost> rightGoalpost;

	std::unique_ptr<Player> player1;
	std::unique_ptr<Player> player2;
	std::unique_ptr<Scoreboard> scoreboard;
	std::unique_ptr<Timer> timer;

	std::unique_ptr<TextObject> middleText;

	std::string p1Color;
	std::string p2Color;

	float timeLimit = 0;
	float goalLimit = 0;

	float totalTime = 0;
	bool toReset = false;
	float currentTime = 0;

	int p1Score = 0;
	int p2Score = 0;

public:
	GameScene(std::string p1Color, std::string p2Color, GameMode gm);
	~GameScene();

	void Initialize() override;
	bool P1Score();
	bool P2Score();
	void ResetRound();
	void CheckGameOver();
	void Update(float deltaTime) override;
};
