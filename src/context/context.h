#pragma once

#include "graphics/graphicsRenderer.h"
#include "resource/resourceManager.h"
#include "input/inputManager.h"
#include "audio/audio.h"
#include "scene/sceneManager.h"
#include "game/game.h"
#include "ecs/engine.h"

class Context 
{
private:
	GraphicsRenderer	*graphicsRenderer	= nullptr;
	ResourceManager		*resourceManager	= nullptr;
	InputManager		*inputManager		= nullptr;
	AudioEngine			*audioEngine		= nullptr;
	SceneManager		*sceneManager		= nullptr;
	Game				*game				= nullptr;
	ECSEngine			*ecsEngine			= nullptr;

	Context();
	~Context();
		
	static Context			*instance;
public:
	static GraphicsRenderer	* GraphicsRenderer();
	static ResourceManager	* ResourceManager();
	static InputManager		* InputManager();
	static AudioEngine		* AudioEngine();
	static SceneManager		* SceneManager();
	static Game				* Game();
	static ECSEngine		* ECSEngine();

	static void ReleaseAll();
	static void Initialize();

	static bool IsInitialized();
};
