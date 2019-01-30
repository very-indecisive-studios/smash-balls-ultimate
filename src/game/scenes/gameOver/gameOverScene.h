#pragma once

#include "scene/scene.h"
#include "audio/audio.h"
#include "text/text.h"
#include "sprites/sprite.h"
#include <memory>
#include "game/entities/background/background.h"
#include "game/entities/button/button.h"
#include "game/entities/text/textObject.h"

class GameOverScene : public Scene
{
private:
	std::unique_ptr<Background> background;

	std::unique_ptr<TextObject> winnerText;

	std::unique_ptr<Button> playAgainButton;
	std::unique_ptr<TextObject> playAgainText;

	int winnerPlayerNo;
public:
	GameOverScene(int winnerPlayerNo);
	~GameOverScene();

	void Initialize() override;
	void HandleButtonHover();
	void Update(float deltaTime) override;
};
