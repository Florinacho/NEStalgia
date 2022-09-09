#ifndef __UTIL_HPP__
#define __UTIL_HPP__

#include <stdint.h>

enum CollisionResponse {
	CR_NONE,
	CR_SOLID,
	CR_TOP,
	CR_SWIM,
	CR_CLIMB,
	CR_SCORE,
	CR_DIE
};

enum TileType {
	ETT_EMPTY = 0,
	ETT_BACKGROUND_BRICK = 1,
	ETT_BRICK = 2,
	ETT_WATERFALL_LEFT = 3,
	ETT_WATERFALL_RIGHT = 4,
	ETT_TUBE_LEFT = 5,
	ETT_TUBE_RIGHT = 6,
	ETT_COIN = 7,
	ETT_WATER = 8,
	ETT_LAVA = 9,
	ETT_LADDER = 10,

	ETT_COUNT
};

struct Animation {
	uint8_t beginFrame;
	uint8_t frameCount;
	uint8_t loop;
	uint8_t delay;
};

struct GameLevel {
	uint32_t playerStartX;
	uint32_t playerStartY;
	uint32_t tileCountX;
	uint32_t tileCountY;
	uint8_t horizontal;
	uint32_t targetX;
	uint32_t targetY;
	GameLevel* target;
	uint8_t tiles[];
	/* Enemy array */
};

#endif // __UTIL_HPP__