#ifndef __UTIL_HPP__
#define __UTIL_HPP__

enum CollisionResponse {
	CR_NONE,
	CR_SOLID,
	CR_DESTR,
	CR_SCORE,
	CR_DIE
};

enum TileType {
	ETT_EMPTY = 0,
	ETT_BACKGROUND_BRICK = 1,
	ETT_BRICK = 2,
	
	ETT_COUNT
};

struct GameLevel {
	unsigned int tileCountX;
	unsigned int tileCountY;
	unsigned char horizontal;
	GameLevel* target;
	unsigned char tiles[];
	/* Enemy array */
};

#endif // __UTIL_HPP__