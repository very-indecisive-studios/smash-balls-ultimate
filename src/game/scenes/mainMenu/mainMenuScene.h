#pragma once

#include "scene/scene.h"
#include "audio/audio.h"
#include "game/entities/background/background.h"
#include "game/entities/button/button.h"
#include "game/entities/text/textObject.h"

class MainMenuScene : public Scene
{
private:
	std::unique_ptr<Background> background;

	std::unique_ptr<Button> playButton;
	std::unique_ptr<Button> creditsButton;

	std::unique_ptr<TextObject> playText;
	std::unique_ptr<TextObject> creditsText;

public:
	MainMenuScene();
	~MainMenuScene();

	void Initialize() override;
	void HandleButtonHover();
	void Update(float deltaTime) override;
};
