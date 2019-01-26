#include "pch.h"
#include <iostream>
#include "gameScene.h"
#include "context.h"
#include "constants.h"
#include "resources.h"

GameScene::GameScene(int player1, int player2, int gameMode)
{
	background = Sprite::Create(Resources::BACKGROUND_IMAGE, 0);
	pauseText = Text::Create("PAUSED", Resources::FONT_TYPE, Resources::FONT_COLOR_BLACK, 64, 100, false, false);
}

GameScene::~GameScene()
{
}

void GameScene::Update(float deltaTime)
{
	background->Draw(Vector2(0, 0));

	if (Context::Get()->GetInputManager()->IsKeyDown(VK_ESCAPE))
	{
		Context::Get()->GetInputManager()->ClearAll();
		isPaused = !isPaused;
	}
	if (isPaused)
	{
		pauseText->Draw(Vector2(0, Constants::GAME_HEIGHT / 2 - 64 / 2));
		return;
	}



}