#include "pch.h"
#include <iostream>
#include "mainMenuScene.h"
#include "context/context.h"
#include "constants.h"
#include "game/resources.h"

MainMenuScene::MainMenuScene()
{
	background = Sprite::Create(Resources::BACKGROUND_IMAGE, 0);

	buttonText = Text::Create("PLAY", Resources::FONT_TYPE, Resources::FONT_COLOR_BLACK, Resources::FONT_SIZE, 100, false, false);
	buttons.push_back(buttonText);

	buttonText = Text::Create("CREDITS", Resources::FONT_TYPE, Resources::FONT_COLOR_BLACK, Resources::FONT_SIZE, 100, false, false);
	buttons.push_back(buttonText);

	buttonImage = Sprite::Create(Resources::BUTTON_IMAGE, 0);
}

MainMenuScene::~MainMenuScene()
{
}

void MainMenuScene::CheckMouseHover() 
{
	int mouseX = Context::InputManager()->GetMouseX();
	int mouseY = Context::InputManager()->GetMouseY();
	
	int count = 0;

	for (Text *button : buttons)
	{
		int buttonLeft, buttonRight, buttonTop, buttonBottom;
		buttonLeft = (Constants::GAME_WIDTH * 0.5f) - (Resources::BUTTON_WIDTH * 0.5f);
		buttonRight = buttonLeft + Resources::BUTTON_WIDTH;
		buttonTop = (Constants::GAME_HEIGHT * 0.5f) - (Resources::BUTTON_HEIGHT * 0.5f) + ((Resources::BUTTON_HEIGHT + 10) * count);
		buttonBottom = buttonTop + Resources::BUTTON_HEIGHT;
		count++;

		if (mouseX > buttonLeft && mouseX < buttonRight && mouseY > buttonTop && mouseY < buttonBottom)
		{
			button->SetColor(Resources::FONT_COLOR_RED);
			if (Context::InputManager()->GetMouseLButton() && button->GetText() == "PLAY")
			{
				Context::SceneManager()->LoadSelectionScene();
			}
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
		buttonImage->Draw(Vector2((Constants::GAME_WIDTH * 0.5f) - (Resources::BUTTON_WIDTH * 0.5f), (Constants::GAME_HEIGHT * 0.5f) - (Resources::BUTTON_HEIGHT * 0.5f) + ((Resources::BUTTON_HEIGHT + 10) * count)));
		button->Draw(Vector2(0, (Constants::GAME_HEIGHT * 0.5f) - (Resources::BUTTON_HEIGHT * 0.25f) + ((Resources::BUTTON_HEIGHT + 10) * count)));
		count++;
	}

	CheckMouseHover();
}