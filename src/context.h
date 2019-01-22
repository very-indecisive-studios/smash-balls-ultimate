#pragma once

#include "core/graphics/graphicsRenderer.h"
#include "core/resource/resourceManager.h"
#include "core/input/inputManager.h"
#include "core/audio/audio.h"
#include "core/scene/sceneManager.h"
#include "game.h"

class Context 
{
private:
	GraphicsRenderer		*graphicsRenderer;
	ResourceManager			*resourceManager;
	InputManager			*inputManager;
	AudioEngine				*audioEngine;
	SceneManager			*sceneManager;
	Game					*game;

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

	static void ReleaseAll();

	static Context * Get();
	static void Initialize();
};
