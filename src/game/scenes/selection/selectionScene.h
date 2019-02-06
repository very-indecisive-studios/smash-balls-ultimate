#pragma once

#include "scene/scene.h"
#include "audio/audio.h"
#include "text/text.h"
#include "sprites/sprite.h"
#include "constants.h"
#include "game/entities/background/background.h"
#include "game/entities/button/button.h"
#include "game/entities/characterList/characterList.h"
#include "game/entities/text/textObject.h"
#include "game/scenes/game/gameScene.h"

class SelectionScene : public Scene
{
private:
	std::unique_ptr<Background> background;
	std::unique_ptr<Button> p1LeftButton;
	std::unique_ptr<Button> p1RightButton;

	std::unique_ptr<Button> p2LeftButton;
	std::unique_ptr<Button> p2RightButton;
	
	std::unique_ptr<Button> gmLeftButton;
	std::unique_ptr<Button> gmRightButton;
	
	std::unique_ptr<Button> exitLeftButton;
	std::unique_ptr<Button> exitRightButton;

	std::unique_ptr<CharacterList> p1characterList;
	std::unique_ptr<CharacterList> p2characterList;

	std::unique_ptr<TextObject> gameModesText;
	std::vector<std::string> gameModesList;
	int gameModeCounter = 0;

	GameMode currentGM;

public:
	SelectionScene();
	~SelectionScene();

	void NextGameMode();
	void PreviousGameMode();
	void Initialize() override;
	void Update(float deltaTime) override;
};
