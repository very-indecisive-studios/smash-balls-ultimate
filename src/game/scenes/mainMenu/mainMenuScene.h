#pragma once

#include "scene/scene.h"
#include "audio/audio.h"
#include "text/text.h"
#include "sprites/sprite.h"
#include "game/entities/background/background.h"
#include "game/entities/button/button.h"

class MainMenuScene : public Scene
{
private:
	std::unique_ptr<Background> background = std::make_unique<Background>(Resources::BACKGROUND_IMAGE);

	std::unique_ptr<Button> playButton;
	std::unique_ptr<Button> creditsButton;

	Text *buttonText;
	std::vector<Text *> buttons;

public:
	MainMenuScene();
	~MainMenuScene();

	void Update(float deltaTime) override;
};
