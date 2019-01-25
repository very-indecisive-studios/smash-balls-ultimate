#include "pch.h"

#include "selectionScene.h"
#include <iostream>
#include "context/context.h"
#include "constants.h"
#include "resource/resources.h"

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
	arrowLeftGM = Sprite::Create(Resources::SELECTION_SCENE_LEFT_ARROW_WHITE, 0);
	buttons.push_back(arrowLeftGM);

	arrowRightP1 = Sprite::Create(Resources::SELECTION_SCENE_RIGHT_ARROW_WHITE, 0);
	buttons.push_back(arrowRightP1);
	arrowRightP2 = Sprite::Create(Resources::SELECTION_SCENE_RIGHT_ARROW_WHITE, 0);
	buttons.push_back(arrowRightP2);
	arrowRightGM = Sprite::Create(Resources::SELECTION_SCENE_RIGHT_ARROW_WHITE, 0);
	buttons.push_back(arrowRightGM);

	exitLeft = Sprite::Create(Resources::SELECTION_SCENE_LEFT_EXIT_WHITE, 0);
	buttons.push_back(exitLeft);
	exitRight = Sprite::Create(Resources::SELECTION_SCENE_RIGHT_EXIT_WHITE, 0);
	buttons.push_back(exitRight);

	gameModes.push_back(Resources::SELECTION_SCENE_GAMEMODE_1);
	gameModes.push_back(Resources::SELECTION_SCENE_GAMEMODE_2);
	gameModes.push_back(Resources::SELECTION_SCENE_GAMEMODE_3);
	gameModes.push_back(Resources::SELECTION_SCENE_GAMEMODE_4);

	currentGameModeText = Text::Create("", Resources::FONT_TYPE, Resources::FONT_COLOR_BLACK, Resources::FONT_SIZE, 100, false, false);
}

SelectionScene::~SelectionScene()
{
}

// return true if mouse is hovering button
bool SelectionScene::MouseOverButton(Sprite *currentButton, int left, int right, int top, int bottom)
{
	int mouseX = Context::Get()->GetInputManager()->GetMouseX();
	int mouseY = Context::Get()->GetInputManager()->GetMouseY();
	
	if (mouseX > left && mouseX < right && mouseY > top && mouseY < bottom)
	{
		return true;
	}
	return false;
}

// used to cycle through list of characters
int SelectionScene::CycleCharacters(int currentPlayerCounter, bool add)
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

// used to cycle through list of game modes
int SelectionScene::CycleGameModes(int currentgameModeCounter, bool add)
{
	if (add)
	{
		if (currentgameModeCounter == gameModes.size() - 1)
		{
			return 0;
		}
		else
		{
			return currentgameModeCounter + 1;
		}
	}
	else
	{
		if (currentgameModeCounter == 0)
		{
			return gameModes.size() - 1;
		}
		else
		{
			return currentgameModeCounter - 1;
		}
	}
}


// perform action when mouse click
void SelectionScene::PerformMouseAction()
{
	int mouseX = Context::Get()->GetInputManager()->GetMouseX();
	int mouseY = Context::Get()->GetInputManager()->GetMouseY();

	std::cout << "mouseX: " << mouseX << std::endl;
	std::cout << "mouseY: " << mouseY << std::endl;

	// process of checking for mouse click (down then up) - avoid spamming
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
		if (MouseOverButton(arrowLeftP1, P1_X - Resources::SELECTION_SCENE_CHAR_SIZE, P1_X - Resources::SELECTION_SCENE_CHAR_SIZE + Resources::SELECTION_SCENE_ARROW_WIDTH, P1_Y, P1_Y + Resources::SELECTION_SCENE_ARROW_HEIGHT))
		{
			player1CharacterCounter = CycleCharacters(player1CharacterCounter, false);
		}

		if (MouseOverButton(arrowRightP1, P1_X + Resources::SELECTION_SCENE_CHAR_SIZE, P1_X + Resources::SELECTION_SCENE_CHAR_SIZE + Resources::SELECTION_SCENE_ARROW_WIDTH, P1_Y, P1_Y + Resources::SELECTION_SCENE_ARROW_HEIGHT))
		{
			player1CharacterCounter = CycleCharacters(player1CharacterCounter, true);
		}

		if (MouseOverButton(arrowLeftP2, P2_X - Resources::SELECTION_SCENE_CHAR_SIZE, P2_X - Resources::SELECTION_SCENE_CHAR_SIZE + Resources::SELECTION_SCENE_ARROW_WIDTH, P2_Y, P2_Y + Resources::SELECTION_SCENE_ARROW_HEIGHT))
		{
			player2CharacterCounter = CycleCharacters(player2CharacterCounter, false);
		}

		if (MouseOverButton(arrowRightP2, P2_X + Resources::SELECTION_SCENE_CHAR_SIZE, P2_X + Resources::SELECTION_SCENE_CHAR_SIZE + Resources::SELECTION_SCENE_ARROW_WIDTH, P2_Y, P2_Y + Resources::SELECTION_SCENE_ARROW_HEIGHT))
		{
			player2CharacterCounter = CycleCharacters(player2CharacterCounter, true);
		}

		if (MouseOverButton(arrowLeftGM, (Constants::GAME_WIDTH * 0.5f) - 150, ((Constants::GAME_WIDTH * 0.5f) - 150) + Resources::SELECTION_SCENE_ARROW_WIDTH, (Constants::GAME_HEIGHT * 0.5f) - Resources::SELECTION_SCENE_ARROW_HEIGHT / 2, (Constants::GAME_HEIGHT * 0.5f) - Resources::SELECTION_SCENE_ARROW_HEIGHT / 2 + Resources::SELECTION_SCENE_ARROW_HEIGHT))
		{
			gameModeCounter = CycleGameModes(gameModeCounter, false);
		}

		if (MouseOverButton(arrowRightGM, (Constants::GAME_WIDTH * 0.5f) + 100, ((Constants::GAME_WIDTH * 0.5f) + 100) + Resources::SELECTION_SCENE_ARROW_WIDTH, (Constants::GAME_HEIGHT * 0.5f) - Resources::SELECTION_SCENE_ARROW_HEIGHT / 2, (Constants::GAME_HEIGHT * 0.5f) - Resources::SELECTION_SCENE_ARROW_HEIGHT / 2 + Resources::SELECTION_SCENE_ARROW_HEIGHT))
		{
			gameModeCounter = CycleGameModes(gameModeCounter, true);
		}

		if (MouseOverButton(exitLeft, Constants::GAME_WIDTH / 5, ((Constants::GAME_WIDTH / 5) + Resources::SELECTION_SCENE_EXIT_WIDTH), ((Constants::GAME_HEIGHT / 5) * 4) - Resources::SELECTION_SCENE_EXIT_HEIGHT, (Constants::GAME_HEIGHT / 5) * 4))
		{
			Context::Get()->GetSceneManager()->LoadMainMenuScene();
		}

		if (MouseOverButton(exitRight, ((Constants::GAME_WIDTH / 5) * 4) - Resources::SELECTION_SCENE_EXIT_WIDTH, (Constants::GAME_WIDTH / 5) * 4, ((Constants::GAME_HEIGHT / 5) * 4) - Resources::SELECTION_SCENE_EXIT_HEIGHT, (Constants::GAME_HEIGHT / 5) * 4))
		{
			Context::Get()->GetSceneManager()->LoadGameScene(player1CharacterCounter, player2CharacterCounter, gameModeCounter);
		}

		mouseClicked = false;
	}
}

void SelectionScene::Update(float deltaTime)
{
	PerformMouseAction();

	background->Draw(Vector2(0, 0));

	arrowLeftP1->Draw(Vector2(P1_X - Resources::SELECTION_SCENE_CHAR_SIZE, P1_Y));
	arrowRightP1->Draw(Vector2(P1_X + Resources::SELECTION_SCENE_CHAR_SIZE, P1_Y));

	arrowLeftP2->Draw(Vector2(P2_X - Resources::SELECTION_SCENE_CHAR_SIZE, P2_Y));
	arrowRightP2->Draw(Vector2(P2_X + Resources::SELECTION_SCENE_CHAR_SIZE, P2_Y));

	arrowLeftGM->Draw(Vector2((Constants::GAME_WIDTH * 0.5f) - 150, Constants::GAME_HEIGHT * 0.5f - Resources::SELECTION_SCENE_ARROW_HEIGHT / 2));
	arrowRightGM->Draw(Vector2((Constants::GAME_WIDTH * 0.5f) + 100, Constants::GAME_HEIGHT * 0.5f - Resources::SELECTION_SCENE_ARROW_HEIGHT / 2));

	characters[player1CharacterCounter]->Draw(Vector2(P1_X, P1_Y));
	characters[player2CharacterCounter]->Draw(Vector2(P2_X, P2_Y));

	currentGameModeText->SetText(gameModes[gameModeCounter]);
	currentGameModeText->Draw(Vector2(0, Constants::GAME_HEIGHT/2 - Resources::FONT_SIZE/2));
	
	exitLeft->Draw(Vector2(Constants::GAME_WIDTH/5, ((Constants::GAME_HEIGHT/5) * 4 )- Resources::SELECTION_SCENE_EXIT_HEIGHT));
	exitRight->Draw(Vector2((((Constants::GAME_WIDTH/5) * 4 ) - Resources::SELECTION_SCENE_EXIT_WIDTH), ((Constants::GAME_HEIGHT / 5) * 4) - Resources::SELECTION_SCENE_EXIT_HEIGHT));
}