#pragma once

#include "scene.h"
#include "audio/audio.h"
#include "text/text.h"
#include "sprites/sprite.h"

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
