#ifndef __TILE_HPP__
#define __TILE_HPP__

#include "Vector.h"

const unsigned int PaletteLength = 8;
typedef ubvec4 Palette[PaletteLength];

// Sprite flags
const unsigned char SF_NONE = 0;
const unsigned char SF_FLIP_X = 1 << 0;
const unsigned char SF_FLIP_Y = 1 << 1;
const unsigned char SF_SWAP = 1 << 2;
const unsigned char SF_ROT_90  = SF_FLIP_Y | SF_SWAP;
const unsigned char SF_ROT_180 = SF_FLIP_X | SF_FLIP_Y;
const unsigned char SF_ROT_270 = SF_FLIP_X | SF_SWAP;

struct TileConfig {
	unsigned char collision;
	unsigned char spriteIndex;
	unsigned char paletteIndex;
	unsigned char flags;
	unsigned char offsetX;
	unsigned char offsetY;
	  signed char offsetXDelay;
	  signed char offsetYDelay;
};

#endif // __TILE_HPP__