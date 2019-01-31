#include "pch.h"

#include "selectionScene.h"
#include "context/context.h"
#include "constants.h"
#include "game/resources.h"

SelectionScene::SelectionScene()
{ }

SelectionScene::~SelectionScene()
{ }

void SelectionScene::Initialize()
{
	background = std::make_unique<Background>(Resources::SELECTION_SCENE_BACKGROUND_IMAGE);

	p1LeftButton = std::make_unique<Button>(
		Resources::SELECTION_SCENE_LEFT_ARROW_WHITE,
		Vector2(Resources::SELECTION_SCENE_P1_X - Resources::SELECTION_SCENE_CHAR_SIZE, Resources::SELECTION_SCENE_P1_Y),
		Resources::SELECTION_SCENE_ARROW_HEIGHT,
		Resources::SELECTION_SCENE_ARROW_WIDTH,
		[this]() { p1characterList->Previous(); }
	);

	p1RightButton = std::make_unique<Button>(
		Resources::SELECTION_SCENE_RIGHT_ARROW_WHITE,
		Vector2(Resources::SELECTION_SCENE_P1_X + Resources::SELECTION_SCENE_CHAR_SIZE, Resources::SELECTION_SCENE_P1_Y),
		Resources::SELECTION_SCENE_ARROW_HEIGHT,
		Resources::SELECTION_SCENE_ARROW_WIDTH,
		[this]() { p1characterList->Next(); }
	);

	p2LeftButton = std::make_unique<Button>(
		Resources::SELECTION_SCENE_LEFT_ARROW_WHITE,
		Vector2(Resources::SELECTION_SCENE_P2_X - Resources::SELECTION_SCENE_CHAR_SIZE, Resources::SELECTION_SCENE_P2_Y),
		Resources::SELECTION_SCENE_ARROW_HEIGHT,
		Resources::SELECTION_SCENE_ARROW_WIDTH,
		[this]() { p2characterList->Previous(); }
	);

	p2RightButton = std::make_unique<Button>(
		Resources::SELECTION_SCENE_RIGHT_ARROW_WHITE,
		Vector2(Resources::SELECTION_SCENE_P2_X + Resources::SELECTION_SCENE_CHAR_SIZE, Resources::SELECTION_SCENE_P2_Y),
		Resources::SELECTION_SCENE_ARROW_HEIGHT,
		Resources::SELECTION_SCENE_ARROW_WIDTH,
		[this]() { p2characterList->Next(); }
	);

	gmLeftButton = std::make_unique<Button>(
		Resources::SELECTION_SCENE_LEFT_ARROW_WHITE,
		Vector2((Constants::GAME_WIDTH * 0.5f) - 150, Constants::GAME_HEIGHT * 0.5f - Resources::SELECTION_SCENE_ARROW_HEIGHT / 2),
		Resources::SELECTION_SCENE_ARROW_HEIGHT,
		Resources::SELECTION_SCENE_ARROW_WIDTH,
		[this]() { this->PreviousGameMode(); }
	);

	gmRightButton = std::make_unique<Button>(
		Resources::SELECTION_SCENE_RIGHT_ARROW_WHITE,
		Vector2((Constants::GAME_WIDTH * 0.5f) + 100, Constants::GAME_HEIGHT * 0.5f - Resources::SELECTION_SCENE_ARROW_HEIGHT / 2),
		Resources::SELECTION_SCENE_ARROW_HEIGHT,
		Resources::SELECTION_SCENE_ARROW_WIDTH,
		[this]() { this->NextGameMode(); }
	);

	exitLeftButton = std::make_unique<Button>(
		Resources::SELECTION_SCENE_LEFT_EXIT_WHITE,
		Vector2(Constants::GAME_WIDTH / 5, ((Constants::GAME_HEIGHT / 5) * 4) - Resources::SELECTION_SCENE_EXIT_HEIGHT),
		Resources::SELECTION_SCENE_EXIT_HEIGHT,
		Resources::SELECTION_SCENE_EXIT_WIDTH,
		[this]() { Context::SceneManager()->LoadScene<MainMenuScene>(); }
	);

	exitRightButton = std::make_unique<Button>(
		Resources::SELECTION_SCENE_RIGHT_EXIT_WHITE,
		Vector2((((Constants::GAME_WIDTH / 5) * 4) - Resources::SELECTION_SCENE_EXIT_WIDTH), ((Constants::GAME_HEIGHT / 5) * 4) - Resources::SELECTION_SCENE_EXIT_HEIGHT),
		Resources::SELECTION_SCENE_EXIT_HEIGHT,
		Resources::SELECTION_SCENE_EXIT_WIDTH,
		[this]() { Context::SceneManager()->LoadScene<GameScene>(p1characterList->GetCurrentCharacterColor(), p2characterList->GetCurrentCharacterColor(), gameModesList[gameModeCounter]); }
	);

	p1characterList = std::make_unique<CharacterList>(Vector2(Resources::SELECTION_SCENE_P1_X, Resources::SELECTION_SCENE_P1_Y));
	p2characterList = std::make_unique<CharacterList>(Vector2(Resources::SELECTION_SCENE_P2_X, Resources::SELECTION_SCENE_P2_Y));

	gameModesText = std::make_unique<TextObject>(
		Resources::FONT_TYPE,
		Vector2(0, Constants::GAME_HEIGHT / 2 - Resources::FONT_SIZE / 2),
		"",
		Constants::GAME_HEIGHT,
		Constants::GAME_WIDTH,
		TextAlignPosition::H_CENTER,
		Resources::FONT_SIZE,
		Resources::FONT_COLOR_BLACK,
		false,
		[this]() { Context::SceneManager()->LoadScene<MainMenuScene>(); }
	);

	gameModesList.push_back(Resources::SELECTION_SCENE_GAMEMODE_1);
	gameModesList.push_back(Resources::SELECTION_SCENE_GAMEMODE_2);
	gameModesList.push_back(Resources::SELECTION_SCENE_GAMEMODE_3);
	gameModesList.push_back(Resources::SELECTION_SCENE_GAMEMODE_4);
}

void SelectionScene::NextGameMode()
{
	if (gameModeCounter == gameModesList.size() - 1)
	{
		gameModeCounter = 0;
	}
	else
	{
		gameModeCounter++;
	}
}

void SelectionScene::PreviousGameMode()
{
	if (gameModeCounter == 0)
	{
		gameModeCounter = gameModesList.size() - 1;
	}
	else
	{
		gameModeCounter--;
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

	p1characterList->Update(deltaTime);
	p2characterList->Update(deltaTime);

	gameModesText->SetText(gameModesList[gameModeCounter]);
}
