#include "pch.h"

#include "gameOverScene.h"
#include "game/scenes/selection/selectionScene.h"
#include "context/context.h"
#include "constants.h"
#include "game/resources.h"

GameOverScene::GameOverScene(int winnerPlayerNo) 
	: winnerPlayerNo(winnerPlayerNo)
{ }

GameOverScene::~GameOverScene()
{ }

void GameOverScene::Initialize()
{
	if (winnerPlayerNo == 0) 
	{
		winnerString = "DRAW";
	}
	else 
	{
		winnerString = "PLAYER " + std::to_string(winnerPlayerNo) + " WINS";
	}

	background = std::make_unique<Background>(Resources::BACKGROUND_IMAGE_GAME_OVER);

	winnerText = std::make_unique<TextObject>(
		Resources::FONT_TYPE,
		Vector2(0, Constants::GAME_HEIGHT / 2 - (Resources::FONT_SIZE * 3 / 2)),
		winnerString,
		Constants::GAME_HEIGHT,
		Constants::GAME_WIDTH,
		TextAlignPosition::H_CENTER,
		Resources::FONT_SIZE * 3,
		Resources::FONT_COLOR_BLACK,
		false,
		[this]() {}
	);

	playAgainButton = std::make_unique<Button>(
		Resources::BUTTON_IMAGE,
		Vector2((Constants::GAME_WIDTH * 0.5f) - (Resources::BUTTON_WIDTH * 0.5f), Constants::GAME_HEIGHT - Resources::BUTTON_HEIGHT - Resources::GROUND_HEIGHT * 1.5f),
		Resources::BUTTON_HEIGHT,
		Resources::BUTTON_WIDTH,
		[this]() { Context::SceneManager()->LoadScene<SelectionScene>(); }
	);

	playAgainText = std::make_unique<TextObject>(
		Resources::FONT_TYPE,
		Vector2(0, Constants::GAME_HEIGHT - Resources::BUTTON_HEIGHT - Resources::GROUND_HEIGHT * 1.5f + (Resources::BUTTON_HEIGHT * 0.25f)),
		"PLAY AGAIN",
		Constants::GAME_HEIGHT - Resources::BUTTON_HEIGHT - Resources::GROUND_HEIGHT * 1.5f,
		Constants::GAME_WIDTH,
		TextAlignPosition::H_CENTER,
		Resources::FONT_SIZE,
		Resources::FONT_COLOR_BLACK,
		true,
		[this]() { this->HandleButtonHover(); }
	);
}

void GameOverScene::HandleButtonHover()
{
	if (playAgainButton->MouseOverButton())
	{
		playAgainText->ChangeColor(Resources::FONT_COLOR_RED);
	}
	else
	{
		playAgainText->ChangeColor(Resources::FONT_COLOR_BLACK);
	}
}

void GameOverScene::Update(float deltaTime)
{
	playAgainButton->Update(deltaTime);
	playAgainText->Update(deltaTime);
}