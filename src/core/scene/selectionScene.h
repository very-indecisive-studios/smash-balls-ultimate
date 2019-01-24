#pragma once
#include "pch.h"
#include "scene.h"
#include "core/audio/audio.h"
#include "core/text/text.h"
#include "core/sprites/sprite.h"
#include "constants.h"

class SelectionScene : public Scene
{
private:
	Sprite *background = nullptr;

	Sprite *characterImage = nullptr;
	std::vector<Sprite *> characters;

	Sprite *arrowLeftP1 = nullptr;
	Sprite *arrowLeftP2 = nullptr;

	Sprite *arrowRightP1 = nullptr;
	Sprite *arrowRightP2 = nullptr;

	Sprite *exitLeft = nullptr;

	Sprite *exitRight = nullptr;
	std::vector<Sprite *> buttons;

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

	bool CheckCollisionWithButton(Sprite *currentButton, int left, int right, int top, int bottom);
	int ReturnCharacterNo(int currentPlayerCounter, bool add);
	void PerformMouseAction();

	void Update(float deltaTime) override;
};
