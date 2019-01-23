#include "pch.h"
#include <iostream>
#include "mainMenuScene.h"
#include "context.h"
#include "constants.h"
#include "resources.h"

MainMenuScene::MainMenuScene()
{
	background = Sprite::Create(Resources::BACKGROUND_IMAGE, 0);

	button1 = Text::Create("PLAY", Resources::FONT_TYPE, Resources::FONT_COLOR_BLACK, Resources::FONT_SIZE, 100, false, false);
	button2 = Text::Create("CREDITS", Resources::FONT_TYPE, Resources::FONT_COLOR_BLACK, Resources::FONT_SIZE, 100, false, false);

	buttons.push_back(button1);
	buttons.push_back(button2);
}

MainMenuScene::~MainMenuScene()
{
}

void MainMenuScene::CheckMouseHover() 
{
	int mouseX = Context::Get()->GetInputManager()->GetMouseX();
	int mouseY = Context::Get()->GetInputManager()->GetMouseY();

	int count = 0;
	for (Text *button : buttons)
	{
		int buttonLeft, buttonRight, buttonTop, buttonBottom;

		button->Draw(Vector2(0, (Constants::GAME_HEIGHT - (buttons.size() / 2 * Resources::FONT_SIZE)) + (Resources::FONT_SIZE * count)));
		count++;

		if (mouseX > buttonLeft && mouseX < buttonRight && mouseY > buttonTop && mouseY < buttonBottom)
		{
			button->SetColor(Resources::FONT_COLOR_RED);
		}
		else 
		{
			button->SetColor(Resources::FONT_COLOR_BLACK);
		}
	}

}

void MainMenuScene::Update(float deltaTime)
{
	background->Draw(Vector2(0, 0));

	int count = 0;
	for (Text *button : buttons)
	{
		button->Draw(Vector2(0, (Constants::GAME_HEIGHT * 0.5f - (buttons.size() / 2 * Resources::FONT_SIZE)) + (Resources::FONT_SIZE * count)));
		count++;
	}
}