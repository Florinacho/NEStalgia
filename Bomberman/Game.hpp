#ifndef __GAME_HPP__
#define __GAME_HPP__

#include "Window.h"
#include "TileRenderer.hpp"
#include "Character.hpp"
#include "Data.hpp"

enum PlayerKeys {
	KEY_MOVE_LEFT,
	KEY_MOVE_DOWN,
	KEY_MOVE_RIGHT,
	KEY_MOVE_UP,
	KEY_MOVE_COUNT
};

class Game {
public:
	TileRenderer renderer;
	Character player;
	Character enemy;
	bool keys[KEY_MOVE_COUNT];
	bool jumped;
	
	GameLevel *currentLevel;
	bool isSolid(int x, int y) const;
	
public:
	Game();
	
	~Game();
	
	int loadLevel(GameLevel* level);
	
	int getTile(const unsigned int x, const unsigned int y) const;
	
	bool onEvent(Event& event);
	
	void update(unsigned int deltaTime);
	
	void draw(Image* output, const unsigned long long currentTime);
};

extern Game* GamePtr;

#endif // __GAME_HPP__