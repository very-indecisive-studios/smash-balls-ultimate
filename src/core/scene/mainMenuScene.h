#pragma once
#include "pch.h"
#include "scene.h"
#include "core/audio/audio.h"
#include "core/text/text.h"
#include "core/sprites/sprite.h"

class MainMenuScene : public Scene
{
private:
	Sprite *background = nullptr;

	Text *buttonText;
	std::vector<Text *> buttons;

	Sprite *buttonImage = nullptr;

public:
	MainMenuScene();
	~MainMenuScene();

	void CheckMouseHover();

	void Update(float deltaTime) override;
};
