#ifndef __UTIL_HPP__
#define __UTIL_HPP__

enum CollisionResponse {
	CR_NONE,
	CR_SOLID,
	CR_DESTR,
};

struct GameLevel {
	unsigned int tileCountX;
	unsigned int tileCountY;
	unsigned int startX;
	unsigned int startY;
	unsigned char tiles[];
	/* Enemy array */
};

enum PieceType {
	EPT_O,
	EPT_S,
	EPT_Z,
	EPT_T,
	EPT_L,
	EPT_J,
	EPT_I,
	
	EPT_COUNT
};

struct Piece {
	unsigned char length;
	unsigned char score;
	unsigned char data[16];
};

#endif // __UTIL_HPP__