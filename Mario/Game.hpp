#ifndef __GAME_HPP__
#define __GAME_HPP__

#include "Window.h"
#include "TileRenderer.hpp"
#include "Character.hpp"
#include "Graphics.hpp"

enum PlayerKeys {
	KEY_MOVE_LEFT,
	KEY_MOVE_DOWN,
	KEY_MOVE_RIGHT,
	KEY_MOVE_UP,
	KEY_JUMP,
	KEY_ACTION,
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

	int getTile(int x, int y) const;

	bool onEvent(Event& event);

	void update(uint32_t deltaTime);

	void draw(Image* output, uint64_t currentTime);
};

extern Game* GamePtr;

#endif // __GAME_HPP__