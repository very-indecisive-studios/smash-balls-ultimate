#pragma once

#include "scene.h"
#include "game/scenes/game/gameScene.h"
#include "game/scenes/mainMenu/mainMenuScene.h"
#include "game/scenes/selection/selectionScene.h"
#include "game/scenes/gameOver/gameOverScene.h"

class SceneManager
{
private:
	Scene *currentScene = nullptr;
	Scene *pendingSceneToLoad = nullptr;

public:
	SceneManager();
	~SceneManager();

	void Initialize();

	template <typename T, class... Args>
	void LoadScene(Args&&... args)
	{
		Scene *sceneToLoad = new T(std::forward<Args>(args)...);

		pendingSceneToLoad = sceneToLoad;
	}

	void Update(float deltaTime);
};
