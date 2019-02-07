#pragma once

#include <string>
#include "constants.h"

namespace Resources
{
	// font name
	const std::string FONT_NAME = "assets\\fonts\\LemonMilk.otf";
	const std::string FONT_NAME_BOLD = "assets\\fonts\\LemonMilk-Bold.otf";
	const std::string FONT_NAME_LIGHT = "assets\\fonts\\LemonMilk-Light.otf";
	const std::string FONT_TYPE = "Lemon/Milk";
	const int FONT_SIZE = 23; 
	const int FONT_COLOR_WHITE = 0xFFFFFFFF; 
	const int FONT_COLOR_RED = 0xFFFF0000; 
	const int FONT_COLOR_BLACK = 0xFF000000; 
	
	// map 
	const std::string GAME_SCENE_IMAGE = "assets\\map\\final_map.png";
	const std::string RIGHT_GOALPOST_IMAGE = "assets\\goalposts\\right.png";
	const std::string LEFT_GOALPOST_IMAGE = "assets\\goalposts\\left.png";
	const int GROUND_HEIGHT = 128;
	const int GOALPOST_WIDTH = 150;
	const int GOALPOST_HEIGHT = 173;
	const int LEFT_GOALPOST_X = 0;
	const int LEFT_GOALPOST_Y = Constants::GAME_HEIGHT - GROUND_HEIGHT - GOALPOST_HEIGHT;
	const int RIGHT_GOALPOST_X = Constants::GAME_WIDTH - GOALPOST_WIDTH;
	const int RIGHT_GOALPOST_Y = Constants::GAME_HEIGHT - GROUND_HEIGHT - GOALPOST_HEIGHT;

	// background
	const std::string BACKGROUND_IMAGE = "assets\\backgrounds\\main.png";
	const std::string BACKGROUND_IMAGE_MAIN_MENU = "assets\\backgrounds\\mainMenu.png";
	const std::string BACKGROUND_IMAGE_GAME_OVER = "assets\\backgrounds\\gameOver.png";

	// buttons
	const std::string BUTTON_IMAGE = "assets\\buttons\\button.png";
	const int BUTTON_HEIGHT = 45;
	const int BUTTON_WIDTH = 190;
	const std::wstring BUTTON_CLICK_AUDIO = L"assets/audio/button_click.wav";

	// selectionScene
	const std::string SELECTION_SCENE_BACKGROUND_IMAGE = "assets\\selectionScene\\background.png";
	const std::string SELECTION_SCENE_RIGHT_ARROW_BLACK = "assets\\selectionScene\\rightArrowBlack.png";
	const std::string SELECTION_SCENE_RIGHT_ARROW_WHITE = "assets\\selectionScene\\rightArrowWhite.png";
	const std::string SELECTION_SCENE_LEFT_ARROW_BLACK = "assets\\selectionScene\\leftArrowBlack.png";
	const std::string SELECTION_SCENE_LEFT_ARROW_WHITE = "assets\\selectionScene\\leftArrowWhite.png";
	const std::string SELECTION_SCENE_BIEGE_CHAR = "assets\\selectionScene\\beige_badge.png";
	const std::string SELECTION_SCENE_BLUE_CHAR = "assets\\selectionScene\\blue_badge.png";
	const std::string SELECTION_SCENE_GREEN_CHAR = "assets\\selectionScene\\green_badge.png";
	const std::string SELECTION_SCENE_PINK_CHAR = "assets\\selectionScene\\pink_badge.png";
	const std::string SELECTION_SCENE_YELLOW_CHAR = "assets\\selectionScene\\yellow_badge.png";
	const std::string SELECTION_SCENE_RIGHT_EXIT_BLACK = "assets\\selectionScene\\exitRightBlack.png";
	const std::string SELECTION_SCENE_RIGHT_EXIT_WHITE = "assets\\selectionScene\\exitRightWhite.png";
	const std::string SELECTION_SCENE_LEFT_EXIT_BLACK = "assets\\selectionScene\\exitLeftBlack.png";
	const std::string SELECTION_SCENE_LEFT_EXIT_WHITE = "assets\\selectionScene\\exitLeftWhite.png";
	const int SELECTION_SCENE_CHAR_SIZE = 50;
	const int SELECTION_SCENE_ARROW_WIDTH = 40;
	const int SELECTION_SCENE_ARROW_HEIGHT = 64;
	const int SELECTION_SCENE_EXIT_WIDTH = 62;
	const int SELECTION_SCENE_EXIT_HEIGHT = 56;
	const std::string SELECTION_SCENE_GAMEMODE_1 = "TIME LIMIT - 3 MINS";
	const std::string SELECTION_SCENE_GAMEMODE_2 = "TIME LIMIT - 5 MINS";
	const std::string SELECTION_SCENE_GAMEMODE_3 = "FIRST TO 5 GOALS";
	const std::string SELECTION_SCENE_GAMEMODE_4 = "FIRST TO 10 GOALS";
	const int SELECTION_SCENE_P1_X = (Constants::GAME_WIDTH * 0.5f) - (Constants::GAME_WIDTH / 8);
	const int SELECTION_SCENE_P1_Y = Constants::GAME_WIDTH / 6;
	const int SELECTION_SCENE_P2_X = (Constants::GAME_WIDTH * 0.5f) + (Constants::GAME_WIDTH / 8);
	const int SELECTION_SCENE_P2_Y = Constants::GAME_WIDTH / 6;

	// player
	const std::string PLAYER_LEFT_OFF_FOLDER = "assets\\players\\left_off\\";
	const std::string PLAYER_LEFT_ON_FOLDER = "assets\\players\\left_on\\";
	const std::string PLAYER_RIGHT_OFF_FOLDER = "assets\\players\\right_off\\";
	const std::string PLAYER_RIGHT_ON_FOLDER = "assets\\players\\right_on\\";

	// hud - scoreboard
	const std::string PLAYER_BADGE_FOLDER = "assets\\players\\badge\\";
	const int PLAYER_BADGE_SIZE = 47;

	const float PLAYER_ANIMATION_DELAY = 0.1f; // time between frames of player animation
	const int  PLAYER_WIDTH = 88;              // width of player image
	const int  PLAYER_HEIGHT = 100;             // height of player image
	const int PLAYER_SPEED= 200;

	// hud - player tag
	const std::string PLAYER_1_TAG = "assets\\players\\tag\\p1.png";
	const std::string PLAYER_2_TAG = "assets\\players\\tag\\p2.png";
	constexpr int PLAYER_1_TAG_COLOUR = 0xFFE86A17;
	constexpr int PLAYER_2_TAG_COLOUR = 0xFF1EA7E1;
	constexpr int PLAYER_TAG_WIDTH = 28;
	constexpr int PLAYER_TAG_HEIGHT = 42;

	// player 1 settings
	const int  P1_SPAWNX = Constants::GAME_WIDTH/2 - (PLAYER_WIDTH * 3);
	const int  P1_SPAWNY = Constants::GAME_HEIGHT - (GROUND_HEIGHT * 2);
	const UCHAR P1_LEFT_KEY = 0x41;
	const UCHAR P1_RIGHT_KEY = 0x44;
	const UCHAR P1_JETPACK_KEY = 0x57;
	const UCHAR P1_POWER_KEY = VK_SPACE;

	// player 2 settings
	const int  P2_SPAWNX = Constants::GAME_WIDTH/2 + (PLAYER_WIDTH * 2);
	const int  P2_SPAWNY = Constants::GAME_HEIGHT - (GROUND_HEIGHT * 2);
	const UCHAR P2_LEFT_KEY = VK_LEFT;
	const UCHAR P2_RIGHT_KEY = VK_RIGHT;
	const UCHAR P2_JETPACK_KEY = VK_UP;
	const UCHAR P2_POWER_KEY = VK_SHIFT;

	// ball
	const std::string BALL_IMAGE = "assets\\ball\\big.png";
	const int BALL_WIDTH = 50;
	const int BALL_RADIUS = BALL_WIDTH / 2;
	const float BALL_SPAWN_X = (Constants::GAME_WIDTH / 2) - (Resources::BALL_RADIUS / 2);
	const float BALL_SPAWN_Y = 100;
}

