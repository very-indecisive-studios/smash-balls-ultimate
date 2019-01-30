#pragma once

#include "scene/scene.h"
#include "audio/audio.h"
#include "text/text.h"
#include "sprites/sprite.h"
#include "constants.h"
#include "game/entities/background/background.h"
#include "game/entities/button/button.h"

class SelectionScene : public Scene
{
private:
	Sprite *background = nullptr;
	//std::unique_ptr<Background> background = std::make_unique<Background>(Resources::SELECTION_SCENE_BACKGROUND_IMAGE);
	std::unique_ptr<Button> p1LeftButton;
	std::unique_ptr<Button> p1RightButton;

	std::unique_ptr<Button> p2LeftButton;
	std::unique_ptr<Button> p2RightButton;
	
	std::unique_ptr<Button> gmLeftButton;
	std::unique_ptr<Button> gmRightButton;
	
	std::unique_ptr<Button> exitLeftButton;
	std::unique_ptr<Button> exitRightButton;

	Sprite *characterImage = nullptr;
	std::vector<Sprite *> characters;

	std::vector<std::string> gameModes;
	Text *currentGameModeText;
	int gameModeCounter = 0;

	int player1CharacterCounter = 0;
	int player2CharacterCounter = 1;

	int P1_X = (Constants::GAME_WIDTH * 0.5f) - (Constants::GAME_WIDTH/8);
	int P1_Y = Constants::GAME_WIDTH/6;

	int P2_X = (Constants::GAME_WIDTH * 0.5f) + (Constants::GAME_WIDTH/8);
	int P2_Y = Constants::GAME_WIDTH/6;

	bool mouseDown = false;
	bool mouseClicked = false;

public:
	SelectionScene();
	~SelectionScene();

	bool MouseOverButton(Sprite *currentButton, int left, int right, int top, int bottom);
	int CycleCharacters(int currentPlayerCounter, bool add);
	int CycleGameModes(int currentgameModeCounter, bool add);

	void Update(float deltaTime) override;
};
