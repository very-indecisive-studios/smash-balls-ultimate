#pragma once

#include "ecs/ecs.h"
#include "game/components/position.h"
#include "game/components/text.h"
#include "game/components/sprite.h"
#include "game/entities/sceneObject.h"

class Scoreboard : public SceneObject
{
private:
	class Score : public SceneObject
	{
	private:
		std::shared_ptr<PositionComponent> scorePosComp;
		std::shared_ptr<TextComponent> scoreTextComp;
		std::shared_ptr<Entity> scoreEntity;

		std::shared_ptr<PositionComponent> badgePosComp;
		std::shared_ptr<SpriteComponent> badgeSprComp;
		std::shared_ptr<Entity> badgeEntity;
	public:
		Score(const std::string &playerColour, bool alignLeft);

		void SetScore(uint8_t score);

		void Update(float deltaTime) override { };
	};

private:
	Score leftPlayerScore;
	Score rightPlayerScore;

public:
	Scoreboard(const std::string &leftPlayerColour, const std::string &rightPlayerColour);

	void Update(float deltaTime) override { };

	void SetLeftPlayerScore(uint8_t score);
	void SetRightPlayerScore(uint8_t score);
};
