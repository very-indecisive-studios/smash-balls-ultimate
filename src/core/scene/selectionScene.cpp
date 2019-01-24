#include "pch.h"
#include "selectionScene.h"
#include <iostream>
#include "context.h"
#include "constants.h"
#include "resources.h"

SelectionScene::SelectionScene()
{
	background = Sprite::Create(Resources::SELECTION_SCENE_BACKGROUND_IMAGE, 0);

	characterImage = Sprite::Create(Resources::SELECTION_SCENE_BIEGE_CHAR, 0);
	characters.push_back(characterImage);
	characterImage = Sprite::Create(Resources::SELECTION_SCENE_BLUE_CHAR, 0);
	characters.push_back(characterImage);
	characterImage = Sprite::Create(Resources::SELECTION_SCENE_GREEN_CHAR, 0);
	characters.push_back(characterImage);
	characterImage = Sprite::Create(Resources::SELECTION_SCENE_PINK_CHAR, 0);
	characters.push_back(characterImage);
	characterImage = Sprite::Create(Resources::SELECTION_SCENE_YELLOW_CHAR, 0);
	characters.push_back(characterImage);

	arrowLeftP1 = Sprite::Create(Resources::SELECTION_SCENE_LEFT_ARROW_WHITE, 0);
	buttons.push_back(arrowLeftP1);
	arrowLeftP2 = Sprite::Create(Resources::SELECTION_SCENE_LEFT_ARROW_WHITE, 0);
	buttons.push_back(arrowLeftP2);

	arrowRightP1 = Sprite::Create(Resources::SELECTION_SCENE_RIGHT_ARROW_WHITE, 0);
	buttons.push_back(arrowRightP1);
	arrowRightP2 = Sprite::Create(Resources::SELECTION_SCENE_RIGHT_ARROW_WHITE, 0);
	buttons.push_back(arrowRightP2);

	exitLeft = Sprite::Create(Resources::SELECTION_SCENE_LEFT_EXIT_WHITE, 0);
	buttons.push_back(exitLeft);
	exitRight = Sprite::Create(Resources::SELECTION_SCENE_RIGHT_EXIT_WHITE, 0);
	buttons.push_back(exitRight);

	std::map<int, std::string> gameModes;
	gameModes.insert({ 0, "TIME LIMIT - 3 MINS" });
	gameModes.insert({ 1, "TIME LIMIT - 5 MINS" });
	gameModes.insert({ 2, "FIRST TO 5 GOALS" });
	gameModes.insert({ 3, "FIRST TO 10 GOALS" });
}

SelectionScene::~SelectionScene()
{
}

bool SelectionScene::CheckCollisionWithButton(Sprite *currentButton, int left, int right, int top, int bottom)
{
	int mouseX = Context::Get()->GetInputManager()->GetMouseX();
	int mouseY = Context::Get()->GetInputManager()->GetMouseY();
	
	if (mouseX > left && mouseX < right && mouseY > top && mouseY < bottom)
	{
		return true;
	}
	return false;
}

int SelectionScene::ReturnCharacterNo(int currentPlayerCounter, bool add)
{
	if (add) 
	{
		if (currentPlayerCounter == characters.size() - 1)
		{
			return 0;
		}
		else 
		{
			return currentPlayerCounter + 1;
		}
	}
	else 
	{
		if (currentPlayerCounter == 0)
		{
			return characters.size() - 1;
		}
		else
		{
			return currentPlayerCounter - 1;
		}
	}
}

// perform action when mouse click
void SelectionScene::PerformMouseAction()
{
	int mouseX = Context::Get()->GetInputManager()->GetMouseX();
	int mouseY = Context::Get()->GetInputManager()->GetMouseY();

	if (Context::Get()->GetInputManager()->GetMouseLButton()) 
	{
		mouseDown = true;
	}

	if (mouseDown && !Context::Get()->GetInputManager()->GetMouseLButton())
	{
		mouseClicked = true;
		mouseDown = false;
	}

	if (mouseClicked)
	{
		if (CheckCollisionWithButton(arrowLeftP1, P1_X - Resources::SELECTION_SCENE_CHAR_SIZE, P1_X - Resources::SELECTION_SCENE_CHAR_SIZE + Resources::SELECTION_SCENE_ARROW_WIDTH, P1_Y, P1_Y + Resources::SELECTION_SCENE_ARROW_HEIGHT))
		{
			player1CharacterCounter = ReturnCharacterNo(player1CharacterCounter, false);
		}

		if (CheckCollisionWithButton(arrowRightP1, P1_X + Resources::SELECTION_SCENE_CHAR_SIZE, P1_X + Resources::SELECTION_SCENE_CHAR_SIZE + Resources::SELECTION_SCENE_ARROW_WIDTH, P1_Y, P1_Y + Resources::SELECTION_SCENE_ARROW_HEIGHT))
		{
			player1CharacterCounter = ReturnCharacterNo(player1CharacterCounter, true);
		}

		if (CheckCollisionWithButton(arrowLeftP2, P2_X - Resources::SELECTION_SCENE_CHAR_SIZE, P2_X - Resources::SELECTION_SCENE_CHAR_SIZE + Resources::SELECTION_SCENE_ARROW_WIDTH, P2_Y, P2_Y + Resources::SELECTION_SCENE_ARROW_HEIGHT))
		{
			player2CharacterCounter = ReturnCharacterNo(player2CharacterCounter, false);
		}

		if (CheckCollisionWithButton(arrowRightP2, P2_X + Resources::SELECTION_SCENE_CHAR_SIZE, P2_X + Resources::SELECTION_SCENE_CHAR_SIZE + Resources::SELECTION_SCENE_ARROW_WIDTH, P2_Y, P2_Y + Resources::SELECTION_SCENE_ARROW_HEIGHT))
		{
			player2CharacterCounter = ReturnCharacterNo(player2CharacterCounter, true);
		}

		mouseClicked = false;
	}
}

void SelectionScene::Update(float deltaTime)
{
	background->Draw(Vector2(0, 0));

	arrowLeftP1->Draw(Vector2(P1_X - Resources::SELECTION_SCENE_CHAR_SIZE, P1_Y));
	arrowRightP1->Draw(Vector2(P1_X + Resources::SELECTION_SCENE_CHAR_SIZE, P1_Y));

	arrowLeftP2->Draw(Vector2(P2_X - Resources::SELECTION_SCENE_CHAR_SIZE, P2_Y));
	arrowRightP2->Draw(Vector2(P2_X + Resources::SELECTION_SCENE_CHAR_SIZE, P2_Y));

	characters[player1CharacterCounter]->Draw(Vector2(P1_X, P1_Y));
	characters[player2CharacterCounter]->Draw(Vector2(P2_X, P2_Y));

	PerformMouseAction();
}