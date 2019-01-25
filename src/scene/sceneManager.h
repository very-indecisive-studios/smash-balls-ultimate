#pragma once

#include "scene.h"
#include "gameScene.h"
#include "game/scenes/mainMenu/mainMenuScene.h"
#include "game/scenes/selection/selectionScene.h"

class SceneManager
{
private:
	Scene *currentScene = nullptr;
	Scene *pendingSceneToLoad = nullptr;

public:
	SceneManager();
	~SceneManager();

	void Initialize();

	void LoadMainMenuScene();
	void LoadSelectionScene();
	void LoadGameScene(int player1, int player2, int gameMode);

	void Update(float deltaTime);
};
