#pragma once

#include "scene/scene.h"
#include "audio/audio.h"
#include "text/text.h"
#include "sprites/sprite.h"
#include "constants.h"

class SelectionScene : public Scene
{
private:
	Sprite *background = nullptr;

	Sprite *characterImage = nullptr;
	std::vector<Sprite *> characters;

	Sprite *arrowLeftP1 = nullptr;
	Sprite *arrowLeftP2 = nullptr;
	Sprite *arrowLeftGM = nullptr;

	Sprite *arrowRightP1 = nullptr;
	Sprite *arrowRightP2 = nullptr;
	Sprite *arrowRightGM = nullptr;

	Sprite *exitLeft = nullptr;

	Sprite *exitRight = nullptr;
	std::vector<Sprite *> buttons;

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
	void PerformMouseAction();

	void Update(float deltaTime) override;
};
