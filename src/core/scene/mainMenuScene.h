#pragma once
#include "pch.h"
#include "scene.h"
#include "core/audio/audio.h"
#include "core/text/text.h"
#include "core/sprites/sprite.h"

class MainMenuScene : public Scene
{
private:

public:
	MainMenuScene();
	~MainMenuScene();

	Sprite *background = nullptr;

	Text *button1;
	Text *button2;
	std::vector<Text *> buttons;

	void CheckMouseHover();

	void Update(float deltaTime) override;
};
