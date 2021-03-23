#include "Data.hpp"

/*****************************************************************************/
/* Palettes                                                                  */
/*****************************************************************************/
const Palette Palettes[] = {
	{
		// 0
		ubvec4(   0,   0,   0,   0),
		ubvec4(  50,  50,  50, 255),
		ubvec4( 200, 200, 200, 255),
		ubvec4( 120, 120, 120, 255),
	},
	{
		// 1
		ubvec4(  50,  50,  50, 255),
		ubvec4( 255,  75,  50, 255),
	},
	{
		// 2
		ubvec4(   0,   0,   0,   0),
		ubvec4(  50,  50,  50, 255),
		ubvec4( 200, 200, 200, 255),
		ubvec4( 120, 120, 120, 255),
	},
	{
		// 3
		ubvec4(  25,  25,  75, 255),
		ubvec4(  50,  50, 150, 255),
	},
	{
		ubvec4(189, 4, 4, 255),
		ubvec4(160, 17, 17, 255),
		ubvec4(0, 0, 0, 255),
	},
};
const unsigned int PaletteCount = sizeof(Palettes) / sizeof(Palettes[0]);

/*****************************************************************************/
/* Sprites                                                                   */
/*****************************************************************************/
const uvec2 SpriteCount(3, 3);
const unsigned char SpriteData[] = {
	  1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
	  1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
	  1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
	  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   1, 1, 1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 2, 2, 2,
	  1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   1, 1, 1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 2, 2, 2,
	  1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1,   0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0,   1, 1, 1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 2, 2, 2,
	  1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1,   0, 0, 0, 0, 0, 0, 1, 3, 3, 1, 0, 0, 0, 0, 0, 0,   1, 1, 1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 2, 2, 2,
	  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 1, 3, 2, 2, 3, 1, 0, 0, 0, 0, 0,   1, 1, 1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 2, 2, 2,
	  1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0,   0, 0, 0, 0, 0, 1, 3, 2, 2, 3, 1, 0, 0, 0, 0, 0,   1, 1, 1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 2, 2, 2,
	  1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0,   0, 0, 0, 0, 0, 0, 1, 3, 3, 1, 0, 0, 0, 0, 0, 0,   1, 1, 1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 2, 2, 2,
	  1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0,   0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0,   1, 1, 1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 2, 2, 2,
	  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   1, 1, 1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 2, 2, 2,
	  1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   1, 1, 1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 2, 2, 2,
	  1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2,
	  1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2,
	  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	  
	  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	  0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0,   0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,   2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
	  0, 2, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 2, 0,   0, 2, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,   3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
	  0, 1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1, 0,   0, 2, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,   3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
	  0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0,   0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,   1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	  
	  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   0, 1, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 0, 1, 0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   0, 1, 0, 2, 2, 2, 2, 2, 2, 2, 1, 1, 0, 0, 1, 0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   0, 1, 0, 2, 2, 2, 2, 2, 2, 1, 0, 0, 1, 0, 1, 0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   0, 1, 0, 2, 2, 2, 2, 1, 1, 0, 1, 1, 2, 0, 1, 0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   0, 1, 0, 2, 2, 2, 1, 0, 0, 1, 2, 2, 2, 0, 1, 0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   0, 1, 0, 2, 1, 1, 0, 1, 1, 2, 2, 2, 2, 0, 1, 0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   0, 1, 0, 1, 0, 1, 1, 2, 2, 2, 2, 2, 2, 0, 1, 0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   0, 1, 0, 0, 1, 2, 2, 2, 2, 2, 2, 2, 2, 0, 1, 0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   0, 1, 0, 0, 1, 2, 2, 2, 2, 2, 2, 2, 2, 0, 1, 0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   0, 1, 0, 1, 0, 1, 1, 2, 2, 2, 2, 2, 2, 0, 1, 0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   0, 1, 0, 2, 1, 1, 0, 1, 2, 2, 2, 2, 2, 0, 1, 0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   0, 1, 0, 2, 2, 2, 1, 0, 1, 1, 2, 2, 2, 0, 1, 0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   0, 1, 0, 2, 2, 2, 2, 1, 1, 0, 1, 1, 2, 0, 1, 0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   0, 1, 0, 2, 2, 2, 2, 2, 2, 1, 0, 0, 1, 0, 1, 0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   0, 1, 0, 2, 2, 2, 2, 2, 2, 2, 1, 1, 0, 0, 1, 0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   0, 1, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 0, 1, 0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
};

/**********************************************************************************/
/* Tileset                                                                        */
/* Collision, sprite, palette, flags, offsetX, offsetY, timeOffsetX, timeOffsetY  */
/**********************************************************************************/
const TileConfig Tiles[] = {
	{CR_NONE,   0,  0, SF_NONE,    0,  0,  0,  0}, //  0, Empty space
	{CR_SOLID,  7,  4, SF_NONE,    0,  0,  0,  0}, //  1, Background brick wall
	{CR_DESTR,  0,  1, SF_NONE,    0,  0,  0,  0}, //  2, Brick wall
	{CR_NONE,   1,  0, SF_NONE,    0,  0,  0,  0}, //  3. Ball
	{CR_NONE,   6,  3, SF_NONE,    0,  0,  0,  0}, //  4. Background sky
	{CR_SOLID,  7,  4, SF_SWAP,    0,  0,  0,  0}, //  1, Background brick wall

};
const unsigned int TileConfigCount = sizeof(Tiles) / sizeof(Tiles[0]);

/*****************************************************************************/
/* Levels                                                                    */
/*****************************************************************************/
GameLevel LEVEL_1 = {
	.tileCountX = 16, 
	.tileCountY = 15,
	.horizontal = false,
	.target = &LEVEL_2,
	.tiles = {
		1, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 1, 0, 0, 0,
		1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 0, 0, 0,
		1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 0, 0, 0,
		1, 4, 2, 2, 2, 2, 2, 2, 2, 2, 2, 4, 1, 0, 0, 0,
		1, 4, 2, 2, 4, 2, 4, 2, 4, 2, 2, 4, 1, 0, 0, 0,
		1, 4, 2, 2, 4, 4, 4, 2, 4, 2, 2, 4, 1, 0, 0, 0,
		1, 4, 2, 2, 4, 2, 4, 2, 4, 2, 2, 4, 1, 0, 0, 0,
		1, 4, 2, 2, 2, 2, 2, 2, 2, 2, 2, 4, 1, 0, 0, 0,
		1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 0, 0, 0,
		1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 0, 0, 0,
		1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 0, 0, 0,
		1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 0, 0, 0,
		1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 0, 0, 0,
		1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 0, 0, 0,
		1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 0, 0, 0,
	}
};

GameLevel LEVEL_2 = {
	.tileCountX = 16, 
	.tileCountY = 15,
	.horizontal = false,
	.target = &LEVEL_3,
	.tiles = {
		1, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 1, 0, 0, 0,
		1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 0, 0, 0,
		1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 0, 0, 0,
		1, 4, 4, 4, 2, 2, 4, 2, 2, 4, 4, 4, 1, 0, 0, 0,
		1, 4, 4, 2, 2, 2, 2, 2, 2, 2, 4, 4, 1, 0, 0, 0,
		1, 4, 4, 2, 2, 2, 2, 2, 2, 2, 4, 4, 1, 0, 0, 0,
		1, 4, 4, 2, 2, 2, 2, 2, 2, 2, 4, 4, 1, 0, 0, 0,
		1, 4, 4, 4, 2, 2, 2, 2, 2, 4, 4, 4, 1, 0, 0, 0,
		1, 4, 4, 4, 4, 2, 2, 2, 4, 4, 4, 4, 1, 0, 0, 0,
		1, 4, 4, 4, 4, 4, 2, 4, 4, 4, 4, 4, 1, 0, 0, 0,
		1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 0, 0, 0,
		1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 0, 0, 0,
		1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 0, 0, 0,
		1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 0, 0, 0,
		1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 0, 0, 0,
	}
};

GameLevel LEVEL_3 = {
	.tileCountX = 16, 
	.tileCountY = 15,
	.horizontal = false,
	.target = &LEVEL_4,
	.tiles = {
		1, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 1, 0, 0, 0,
		1, 4, 4, 4, 2, 2, 2, 4, 4, 4, 4, 4, 1, 0, 0, 0,
		1, 4, 4, 4, 2, 2, 2, 4, 4, 4, 4, 4, 1, 0, 0, 0,
		1, 4, 4, 4, 2, 2, 2, 4, 4, 4, 4, 4, 1, 0, 0, 0,
		1, 4, 4, 4, 2, 2, 2, 4, 4, 4, 4, 4, 1, 0, 0, 0,
		1, 4, 4, 4, 2, 2, 2, 4, 4, 4, 4, 4, 1, 0, 0, 0,
		1, 4, 2, 2, 2, 2, 2, 2, 2, 4, 4, 4, 1, 0, 0, 0,
		1, 4, 2, 2, 2, 4, 2, 2, 2, 4, 4, 4, 1, 0, 0, 0,
		1, 4, 2, 2, 2, 4, 2, 2, 2, 4, 4, 4, 1, 0, 0, 0,
		1, 4, 2, 2, 2, 4, 2, 2, 2, 4, 4, 4, 1, 0, 0, 0,
		1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 0, 0, 0,
		1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 0, 0, 0,
		1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 0, 0, 0,
		1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 0, 0, 0,
		1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 0, 0, 0,
	}
};

GameLevel LEVEL_4 = {
	.tileCountX = 16, 
	.tileCountY = 15,
	.horizontal = false,
	.target = &LEVEL_5,
	.tiles = {
		1, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 1, 0, 0, 0,
		1, 4, 4, 4, 4, 4, 2, 4, 4, 4, 4, 4, 1, 0, 0, 0,
		1, 4, 4, 4, 2, 2, 2, 2, 2, 4, 4, 4, 1, 0, 0, 0,
		1, 4, 4, 2, 2, 2, 2, 2, 2, 2, 4, 4, 1, 0, 0, 0,
		1, 4, 2, 2, 2, 2, 2, 2, 2, 2, 2, 4, 1, 0, 0, 0,
		1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 0, 0, 0,
		1, 4, 4, 4, 4, 4, 2, 4, 4, 4, 4, 4, 1, 0, 0, 0,
		1, 4, 4, 4, 4, 4, 2, 4, 4, 4, 4, 4, 1, 0, 0, 0,
		1, 4, 4, 4, 4, 4, 2, 4, 4, 4, 4, 4, 1, 0, 0, 0,
		1, 4, 4, 4, 2, 4, 2, 4, 4, 4, 4, 4, 1, 0, 0, 0,
		1, 4, 4, 4, 2, 2, 2, 4, 4, 4, 4, 4, 1, 0, 0, 0,
		1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 0, 0, 0,
		1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 0, 0, 0,
		1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 0, 0, 0,
		1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 0, 0, 0,
	}
};

GameLevel LEVEL_5 = {
	.tileCountX = 16, 
	.tileCountY = 15,
	.horizontal = false,
	.target = 0,
	.tiles = {
		1, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 1, 0, 0, 0,
		1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 0, 0, 0,
		1, 2, 2, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 0, 0, 0,
		1, 2, 2, 4, 2, 2, 4, 4, 4, 4, 4, 4, 1, 0, 0, 0,
		1, 2, 2, 4, 2, 2, 4, 2, 2, 4, 4, 4, 1, 0, 0, 0,
		1, 2, 2, 4, 2, 2, 4, 2, 2, 4, 2, 2, 1, 0, 0, 0,
		1, 2, 2, 4, 2, 2, 4, 2, 2, 4, 2, 2, 1, 0, 0, 0,
		1, 2, 2, 4, 2, 2, 4, 2, 2, 4, 2, 2, 1, 0, 0, 0,
		1, 2, 2, 4, 2, 2, 4, 2, 2, 4, 2, 2, 1, 0, 0, 0,
		1, 1, 1, 4, 1, 1, 4, 1, 1, 4, 1, 1, 1, 0, 0, 0,
		1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 0, 0, 0,
		1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 0, 0, 0,
		1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 0, 0, 0,
		1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 0, 0, 0,
		1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 0, 0, 0,
	}
};