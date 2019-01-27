#include "pch.h"

#include <windows.h>
#include <Mmsystem.h>
#include <iostream>
#include <string>
#include "game.h"
#include "sprites/sprite.h"
#include "context/context.h"
#include "game/resources.h"
#include "game/resources.h"
#include "game/systems/rendering.h"
#include "game/components/position.h"
#include "game/components/sprite.h"
#include "game/systems/rendering.h"
#include "scene/sceneManager.h"

Game::Game()
{}

Game::~Game()
{}

void Game::Initialize()
{
	QueryPerformanceFrequency(&timerFreq);
	QueryPerformanceCounter(&timeStart);

	Context::SceneManager()->Initialize();
}

void Game::Run()
{
	/*
		Calculate delta time + limit frame rate.
	*/

	// Calculate elapsed time of last frame, save in frameTime.
	QueryPerformanceCounter(&timeEnd);
	deltaTime = (float) (timeEnd.QuadPart - timeStart.QuadPart) / (float) timerFreq.QuadPart;

	// Power saving code; if not enough time has elapsed for desired frame rate.
	if (deltaTime < MIN_FRAME_TIME)
	{
		float sleepTime = (float) ((MIN_FRAME_TIME - deltaTime) * 1000);
		timeBeginPeriod(1);         // Request 1mS resolution for windows timer
		Sleep(sleepTime);           // release cpu for sleepTime
		timeEndPeriod(1);           // End 1mS timer resolution
		return;
	}

	// If frame rate is very slow.
	if (deltaTime > MAX_FRAME_TIME)
	{
		// Limit maximum frameTime.
		deltaTime = MAX_FRAME_TIME;
	}

	timeStart = timeEnd;

	/*
		Update ECS engine.
	*/
	Context::ECSEngine()->Update(deltaTime);

	/*
		Update current scene.
	*/
	Context::SceneManager()->Update(deltaTime);

	/*
		Render game.
	*/
	auto gR = Context::GraphicsRenderer();
	gR->Render();
	gR->HandleLostDevice();
}

float Game::GetDeltaTime()
{
	return deltaTime;
}
