#include "pch.h"

#include "selectionScene.h"
#include <iostream>
#include "context/context.h"
#include "constants.h"
#include "game/resources.h"

SelectionScene::SelectionScene()
{
	p1LeftButton = std::make_unique<Button>(
		Resources::SELECTION_SCENE_LEFT_ARROW_WHITE,
		Vector2(P1_X - Resources::SELECTION_SCENE_CHAR_SIZE, P1_Y),
		Resources::SELECTION_SCENE_ARROW_HEIGHT,
		Resources::SELECTION_SCENE_ARROW_WIDTH,
		[this]() { player1CharacterCounter = this->CycleCharacters(player1CharacterCounter, false); }
	);

	p1RightButton = std::make_unique<Button>(
		Resources::SELECTION_SCENE_RIGHT_ARROW_WHITE,
		Vector2(P1_X + Resources::SELECTION_SCENE_CHAR_SIZE, P1_Y),
		Resources::SELECTION_SCENE_ARROW_HEIGHT,
		Resources::SELECTION_SCENE_ARROW_WIDTH,
		[this]() { player1CharacterCounter = this->CycleCharacters(player1CharacterCounter, true); }
	);

	p2LeftButton = std::make_unique<Button>(
		Resources::SELECTION_SCENE_LEFT_ARROW_WHITE,
		Vector2(P2_X - Resources::SELECTION_SCENE_CHAR_SIZE, P2_Y),
		Resources::SELECTION_SCENE_ARROW_HEIGHT,
		Resources::SELECTION_SCENE_ARROW_WIDTH,
		[this]() { player2CharacterCounter = this->CycleCharacters(player2CharacterCounter, false); }
	);

	p2RightButton = std::make_unique<Button>(
		Resources::SELECTION_SCENE_RIGHT_ARROW_WHITE,
		Vector2(P2_X + Resources::SELECTION_SCENE_CHAR_SIZE, P2_Y),
		Resources::SELECTION_SCENE_ARROW_HEIGHT,
		Resources::SELECTION_SCENE_ARROW_WIDTH,
		[this]() { player2CharacterCounter = this->CycleCharacters(player2CharacterCounter, true); }
	);

	gmLeftButton = std::make_unique<Button>(
		Resources::SELECTION_SCENE_LEFT_ARROW_WHITE,
		Vector2((Constants::GAME_WIDTH * 0.5f) - 150, Constants::GAME_HEIGHT * 0.5f - Resources::SELECTION_SCENE_ARROW_HEIGHT / 2),
		Resources::SELECTION_SCENE_ARROW_HEIGHT,
		Resources::SELECTION_SCENE_ARROW_WIDTH,
		[this]() { gameModeCounter = CycleGameModes(gameModeCounter, false); }
	);

	gmRightButton = std::make_unique<Button>(
		Resources::SELECTION_SCENE_RIGHT_ARROW_WHITE,
		Vector2((Constants::GAME_WIDTH * 0.5f) + 100, Constants::GAME_HEIGHT * 0.5f - Resources::SELECTION_SCENE_ARROW_HEIGHT / 2),
		Resources::SELECTION_SCENE_ARROW_HEIGHT,
		Resources::SELECTION_SCENE_ARROW_WIDTH,
		[this]() { gameModeCounter = CycleGameModes(gameModeCounter, true); }
	);

	exitLeftButton = std::make_unique<Button>(
		Resources::SELECTION_SCENE_LEFT_EXIT_WHITE,
		Vector2(Constants::GAME_WIDTH / 5, ((Constants::GAME_HEIGHT / 5) * 4) - Resources::SELECTION_SCENE_EXIT_HEIGHT),
		Resources::SELECTION_SCENE_ARROW_HEIGHT,
		Resources::SELECTION_SCENE_ARROW_WIDTH,
		[this]() { Context::SceneManager()->LoadScene<MainMenuScene>(); }
	);

	exitRightButton = std::make_unique<Button>(
		Resources::SELECTION_SCENE_RIGHT_EXIT_WHITE,
		Vector2((((Constants::GAME_WIDTH / 5) * 4) - Resources::SELECTION_SCENE_EXIT_WIDTH), ((Constants::GAME_HEIGHT / 5) * 4) - Resources::SELECTION_SCENE_EXIT_HEIGHT),
		Resources::SELECTION_SCENE_ARROW_HEIGHT,
		Resources::SELECTION_SCENE_ARROW_WIDTH,
		[this]() { Context::SceneManager()->LoadScene<GameScene>(player1CharacterCounter, player2CharacterCounter, gameModeCounter); }
	);

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
	int mouseX = Context::InputManager()->GetMouseX();
	int mouseY = Context::InputManager()->GetMouseY();

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

void SelectionScene::Update(float deltaTime)
{
	p1LeftButton->Update(deltaTime);
	p1RightButton->Update(deltaTime);

	p2LeftButton->Update(deltaTime);
	p2RightButton->Update(deltaTime);

	gmLeftButton->Update(deltaTime);
	gmRightButton->Update(deltaTime);

	exitLeftButton->Update(deltaTime);
	exitRightButton->Update(deltaTime);

	background->Draw(Vector2(0, 0));

	characters[player1CharacterCounter]->Draw(Vector2(P1_X, P1_Y));
	characters[player2CharacterCounter]->Draw(Vector2(P2_X, P2_Y));

	currentGameModeText->SetText(gameModes[gameModeCounter]);
	currentGameModeText->Draw(Vector2(0, Constants::GAME_HEIGHT / 2 - Resources::FONT_SIZE / 2));
}
