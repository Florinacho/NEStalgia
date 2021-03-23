#ifndef __TILE_H__
#define __TILE_H__

enum CollisionResponse {
	CR_NONE,
	CR_SOLID,
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

struct AnimationConfig {
	unsigned char beginFrame;
	unsigned char frameCount;
	unsigned char flags;
	unsigned char delay;
};

struct CharacterConfig {
	unsigned char speed;
	const AnimationConfig* animations[];
};

struct GameLevel {
	unsigned int playerStartX;
	unsigned int playerStartY;
	unsigned int tileCountX;
	unsigned int tileCountY;
	unsigned char horizontal;
	unsigned int targetX;
	unsigned int targetY;
	GameLevel* target;
	unsigned char tiles[];
	/* Enemy array */
};

#endif // __TILE_H__