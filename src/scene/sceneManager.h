#pragma once

#include "scene.h"

class SceneManager
{
private:
	Scene *currentScene = nullptr;
	Scene *pendingSceneToLoad = nullptr;

public:
	SceneManager();
	~SceneManager();

	template <typename T, class... Args>
	void LoadScene(Args&&... args)
	{
		Scene *sceneToLoad = new T(std::forward<Args>(args)...);

		pendingSceneToLoad = sceneToLoad;
	}

	void Update(float deltaTime);
};
