#pragma once

#include "ecs/ecs.h"
#include "ecs/components/position.h"
#include "ecs/components/text.h"
#include "ecs/components/sprite.h"
#include "game/entities/gameEntity.h"

class Scoreboard : public GameEntity
{
private:
	class Score
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
