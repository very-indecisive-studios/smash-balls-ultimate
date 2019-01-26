#pragma once
#include "pch.h"
#include "scene.h"
#include "core/audio/audio.h"
#include "core/text/text.h"
#include "core/sprites/sprite.h"

class GameScene : public Scene
{
private:
	Sprite *background = nullptr;
	Text *pauseText;
	bool isPaused = false;
	bool resetRound = false;

public:
	GameScene(int player1, int player2, int gameMode);
	~GameScene();

	void Update(float deltaTime) override;
};
