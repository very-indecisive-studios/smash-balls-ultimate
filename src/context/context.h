#pragma once

#include "graphics/graphicsRenderer.h"
#include "resource/resourceManager.h"
#include "input/inputManager.h"
#include "audio/audio.h"
#include "scene/sceneManager.h"
#include "ecs/engine.h"
#include "game/game.h"

class Context 
{
private:
	GraphicsRenderer		*graphicsRenderer;
	ResourceManager			*resourceManager;
	InputManager			*inputManager;
	AudioEngine				*audioEngine;
	SceneManager			*sceneManager;
	Game					*game;
	ECSEngine				*ecsEngine;

	Context();
	~Context();
		
	static Context			*instance;
public:
	GraphicsRenderer	* GetGraphicsRenderer();
	ResourceManager		* GetResourceManager();
	InputManager		* GetInputManager();
	AudioEngine			* GetAudioEngine();
	SceneManager		* GetSceneManager();
	Game				* GetGame();
	ECSEngine			* GetECSEngine();

	static void ReleaseAll();

	static Context * Get();
	static void Initialize();
};
