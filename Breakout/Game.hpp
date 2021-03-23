#ifndef __GAME_HPP__
#define __GAME_HPP__

#include "Window.h"
#include "TileRenderer.hpp"
#include "Data.hpp"

enum PlayerKeys {
	KEY_MOVE_LEFT,
	KEY_MOVE_DOWN,
	KEY_MOVE_RIGHT,
	KEY_MOVE_UP,
	KEY_MOVE_COUNT
};

enum GameState {
	EGS_INITIAL,
	EGS_PAUSE,
	EGS_RUNNING,
	EGS_WON,
	EGS_GAMEOVER
};

class Game {
	TileRenderer renderer;
	GameState state;
	
	bool keys[KEY_MOVE_COUNT];
	
	unsigned int lifeCount;
	unsigned char playerSize;
	ivec2 paddlePosition;
	
	ivec2 ballPosition;
	ivec2 ballVelocity;
	
	unsigned int score;
	unsigned int scoreMultiplier;
	
	GameLevel *currentLevel;
	unsigned int winCondition;
	
public:
	Game();
	
	~Game();
	
	int loadLevel(GameLevel* level);
	
	bool onEvent(Event& event);
	
	void update(unsigned int deltaTime);
	
	void draw(Image* output, const unsigned long long currentTime);
};

extern Game* GamePtr;

#endif // __GAME_HPP__