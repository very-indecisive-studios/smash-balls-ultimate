#pragma once

#include "math/math.h"
#include "game/resources.h"
#include "constants.h"

namespace GameSceneData
{
	static const int TILE_SIZE = 16;

	namespace Map
	{
		static const Vector2 BALL_SPAWN = Vector2(1, 1);

		static const Vector2 PLAYER1_SPAWN_LOCATION = Vector2(7, 14);
		static const Vector2 PLAYER2_SPAWN_LOCATION = Vector2(7, 14);

		static const Vector2 GOALPOST1_LOCATION = Vector2(7, 14);
		static const Vector2 GOALPOST2_LOCATION = Vector2(7, 14);
	}

	namespace Scoreboard
	{
		static const Vector2 PADDING_LEFT = Vector2(2.0f, 1.0f) * TILE_SIZE;
		static const Vector2 PADDING_RIGHT = Vector2(-2.0f, 1.0f) * TILE_SIZE;
		
		static const int BADGE_SCALE = 1;
		static const Vector2 BADGE_LOCATION_LEFT = Vector2(0.0f, 0.0f) + PADDING_LEFT;
		static const Vector2 BADGE_LOCATION_RIGHT = Vector2(Constants::GAME_WIDTH, 0.0f) - Vector2(Resources::PLAYER_BADGE_SIZE, 0.0f) + PADDING_RIGHT;
		
		static const int SCORE_FONT_SIZE = TILE_SIZE * 3;
		static const int SCORE_FONT_WIDTH = TILE_SIZE * 4;
		static const Vector2 SCORE_LOCATION_LEFT = BADGE_LOCATION_LEFT + Vector2(Resources::PLAYER_BADGE_SIZE, 0.0f) + Vector2(1.0f, 0.0f) * TILE_SIZE;
		static const Vector2 SCORE_LOCATION_RIGHT = BADGE_LOCATION_RIGHT - Vector2(SCORE_FONT_WIDTH, 0) - Vector2(1.0f, 0.0f) * TILE_SIZE;
	}

	namespace Timer
	{
		static const int TIMER_FONT_SIZE = TILE_SIZE * 3;
	}
}

namespace SelectionSceneData 
{

}