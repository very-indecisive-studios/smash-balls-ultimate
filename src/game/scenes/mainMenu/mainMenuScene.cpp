#include "pch.h"
#include <iostream>
#include "mainMenuScene.h"
#include "context/context.h"
#include "constants.h"
#include "game/resources.h"

MainMenuScene::MainMenuScene()
{
	buttonText = Text::Create("PLAY", Resources::FONT_TYPE, Resources::FONT_COLOR_BLACK, Resources::FONT_SIZE, 100, false, false);
	buttons.push_back(buttonText);

	buttonText = Text::Create("CREDITS", Resources::FONT_TYPE, Resources::FONT_COLOR_BLACK, Resources::FONT_SIZE, 100, false, false);
	buttons.push_back(buttonText);

	playButton = std::make_unique<Button>(
		Resources::BUTTON_IMAGE,
		Vector2((Constants::GAME_WIDTH * 0.5f) - (Resources::BUTTON_WIDTH * 0.5f), (Constants::GAME_HEIGHT * 0.5f) - (Resources::BUTTON_HEIGHT * 0.5f)),
		Resources::BUTTON_HEIGHT,
		Resources::BUTTON_WIDTH,
		[this]() { Context::SceneManager()->LoadScene<SelectionScene>(); }
	);

	creditsButton = std::make_unique<Button>(
		Resources::BUTTON_IMAGE,
		Vector2((Constants::GAME_WIDTH * 0.5f) - (Resources::BUTTON_WIDTH * 0.5f), (Constants::GAME_HEIGHT * 0.5f) - (Resources::BUTTON_HEIGHT * 0.5f) + Resources::BUTTON_HEIGHT + 10),
		Resources::BUTTON_HEIGHT,
		Resources::BUTTON_WIDTH,
		[this]() { Context::SceneManager()->LoadScene<SelectionScene>(); }
	);
}

MainMenuScene::~MainMenuScene()
{
}

void MainMenuScene::Update(float deltaTime)
{
	playButton->Update(deltaTime);
	creditsButton->Update(deltaTime);
}