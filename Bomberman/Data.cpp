#include "Data.hpp"

/*****************************************************************************/
/* Palettes                                                                  */
/*****************************************************************************/
const Palette Palettes[] = {
	{
		// 0
		ubvec4(0, 0, 0, 0),
		ubvec4(0, 0, 0, 255),
		ubvec4(174, 38, 51, 255),
		ubvec4(212, 113, 88, 255),
		ubvec4(239, 182, 129, 255),
		ubvec4(32, 99, 72, 255),
		ubvec4(66, 173, 55, 255),
		ubvec4(255, 255, 255, 255),
//		ubvec4(103, 97, 95, 255),
//		ubvec4(177, 177, 177, 255),
	},
	{
		// 1
		ubvec4(  50,  50,  50, 255),
		ubvec4( 130, 130, 130, 255),
		ubvec4( 180, 180, 180, 255),
	},
	{
		// 2
		ubvec4(  50, 100,  50, 255),
		ubvec4( 150, 255, 150, 255),
	},
	{
		// 3
		ubvec4(  50, 100,  50, 255),
		ubvec4(  50,  50,  50, 255),
		ubvec4( 143,  86,  59, 255),
		ubvec4(  26,  26,  26, 255),
	},
	{
		// 4
		ubvec4(   0,   0,   0, 255),
		ubvec4(   0,  35,  40, 255),
		ubvec4( 255, 255,  50, 255),
	},
	{
		// 5
		ubvec4(   0,  35,  40, 255),
		ubvec4( 255, 140,   0, 255),
		ubvec4( 255, 100,   0, 255),
		ubvec4( 255, 200,   0, 255),
	},
	{
		// 6
		ubvec4(   0,   0,   0,   0),
		ubvec4( 51,  51,  51, 255),
		ubvec4( 24, 119, 101, 255),
		ubvec4( 31, 153, 131, 255),
	},
};
const unsigned int PaletteCount = sizeof(Palettes) / sizeof(Palettes[0]);

/*****************************************************************************/
/* Sprites                                                                   */
/*****************************************************************************/
const uvec2 SpriteCount(3, 6);
const unsigned char SpriteData[] = {
	  0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	  0, 0, 0, 0, 1, 2, 2, 2, 2, 2, 2, 1, 0, 0, 0, 0,   0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0,
	  0, 0, 0, 1, 2, 2, 2, 2, 2, 2, 2, 2, 1, 0, 0, 0,   0, 0, 0, 0, 1, 2, 2, 2, 2, 2, 2, 1, 0, 0, 0, 0,   0, 0, 0, 0, 1, 2, 2, 2, 2, 2, 2, 1, 0, 0, 0, 0,
	  0, 0, 0, 1, 2, 2, 3, 2, 2, 2, 3, 2, 1, 0, 0, 0,   0, 0, 0, 1, 2, 2, 2, 2, 2, 2, 2, 2, 1, 0, 0, 0,   0, 0, 0, 1, 2, 2, 2, 2, 2, 2, 2, 2, 1, 0, 0, 0,
	  0, 0, 0, 1, 2, 3, 4, 2, 2, 3, 4, 2, 1, 0, 0, 0,   0, 0, 0, 1, 2, 2, 3, 2, 2, 2, 3, 2, 1, 0, 0, 0,   0, 0, 0, 1, 2, 2, 3, 2, 2, 2, 3, 2, 1, 0, 0, 0,
	  0, 0, 0, 1, 2, 4, 1, 4, 4, 1, 4, 2, 1, 0, 0, 0,   0, 0, 0, 1, 2, 3, 4, 2, 2, 3, 4, 2, 1, 0, 0, 0,   0, 0, 0, 1, 2, 3, 4, 2, 2, 3, 4, 2, 1, 0, 0, 0,
	  0, 0, 0, 1, 3, 4, 1, 4, 4, 1, 4, 3, 1, 0, 0, 0,   0, 0, 0, 1, 2, 4, 1, 4, 4, 1, 4, 2, 1, 0, 0, 0,   0, 0, 0, 1, 2, 4, 1, 4, 4, 1, 4, 2, 1, 0, 0, 0,
	  0, 0, 0, 0, 1, 3, 4, 4, 4, 4, 3, 1, 0, 0, 0, 0,   0, 0, 0, 1, 3, 4, 1, 4, 4, 1, 4, 3, 1, 0, 0, 0,   0, 0, 0, 1, 3, 4, 1, 4, 4, 1, 4, 3, 1, 0, 0, 0,
	  0, 0, 0, 0, 0, 1, 3, 4, 4, 3, 1, 0, 0, 0, 0, 0,   0, 0, 0, 0, 1, 3, 4, 4, 4, 4, 3, 1, 0, 0, 0, 0,   0, 0, 0, 0, 1, 3, 4, 4, 4, 4, 3, 1, 0, 0, 0, 0,
	  0, 0, 0, 1, 1, 5, 6, 7, 7, 6, 5, 1, 1, 0, 0, 0,   0, 0, 0, 0, 1, 1, 3, 4, 4, 3, 1, 1, 0, 0, 0, 0,   0, 0, 0, 0, 1, 1, 3, 4, 4, 3, 1, 1, 0, 0, 0, 0,
	  0, 0, 1, 4, 4, 6, 6, 6, 6, 6, 6, 4, 4, 1, 0, 0,   0, 0, 0, 1, 4, 4, 6, 7, 7, 6, 5, 3, 1, 0, 0, 0,   0, 0, 0, 1, 3, 5, 6, 7, 7, 6, 4, 4, 1, 0, 0, 0,
	  0, 0, 1, 4, 4, 5, 6, 6, 6, 6, 5, 4, 4, 1, 0, 0,   0, 0, 0, 1, 4, 4, 5, 6, 6, 6, 5, 3, 1, 0, 0, 0,   0, 0, 0, 1, 3, 5, 6, 6, 6, 5, 4, 4, 1, 0, 0, 0,
	  0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0,   0, 0, 0, 0, 1, 5, 6, 6, 0, 7, 7, 1, 0, 0, 0, 0,   0, 0, 0, 0, 1, 7, 7, 0, 6, 6, 5, 1, 0, 0, 0, 0,
	  0, 0, 0, 0, 1, 7, 7, 1, 1, 7, 7, 1, 0, 0, 0, 0,   0, 0, 0, 0, 0, 1, 0, 0, 1, 7, 7, 1, 0, 0, 0, 0,   0, 0, 0, 0, 1, 7, 7, 1, 0, 0, 1, 0, 0, 0, 0, 0,
	  0, 0, 0, 0, 1, 1, 1, 0, 0, 1, 1, 1, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0,   0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0,
	  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0,


	  0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	  0, 0, 0, 0, 1, 2, 2, 2, 2, 2, 2, 1, 0, 0, 0, 0,   0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0,
	  0, 0, 0, 1, 2, 2, 2, 2, 2, 2, 2, 2, 1, 0, 0, 0,   0, 0, 0, 0, 1, 2, 2, 2, 2, 2, 2, 1, 0, 0, 0, 0,   0, 0, 0, 0, 1, 2, 2, 2, 2, 2, 2, 1, 0, 0, 0, 0,
	  0, 0, 0, 1, 2, 2, 2, 2, 2, 3, 2, 2, 1, 0, 0, 0,   0, 0, 0, 1, 2, 2, 2, 2, 2, 2, 2, 2, 1, 0, 0, 0,   0, 0, 0, 1, 2, 2, 2, 2, 2, 2, 2, 2, 1, 0, 0, 0,
	  0, 0, 0, 1, 2, 2, 2, 2, 3, 4, 2, 2, 1, 0, 0, 0,   0, 0, 0, 1, 2, 2, 2, 2, 2, 3, 2, 2, 1, 0, 0, 0,   0, 0, 0, 1, 2, 2, 2, 2, 2, 3, 2, 2, 1, 0, 0, 0,
	  0, 0, 0, 1, 2, 2, 2, 3, 4, 1, 4, 1, 0, 0, 0, 0,   0, 0, 0, 1, 2, 2, 2, 2, 3, 4, 2, 2, 1, 0, 0, 0,   0, 0, 0, 1, 2, 2, 2, 2, 3, 4, 2, 2, 1, 0, 0, 0,
	  0, 0, 0, 1, 2, 2, 3, 4, 4, 1, 4, 1, 0, 0, 0, 0,   0, 0, 0, 1, 2, 2, 2, 3, 4, 1, 4, 1, 0, 0, 0, 0,   0, 0, 0, 1, 2, 2, 2, 3, 4, 1, 4, 1, 0, 0, 0, 0,
	  0, 0, 0, 0, 1, 2, 4, 4, 4, 4, 3, 1, 0, 0, 0, 0,   0, 0, 0, 1, 2, 2, 3, 4, 4, 1, 4, 1, 0, 0, 0, 0,   0, 0, 0, 1, 2, 2, 3, 4, 4, 1, 4, 1, 0, 0, 0, 0,
	  0, 0, 0, 0, 0, 1, 3, 4, 4, 3, 1, 0, 0, 0, 0, 0,   0, 0, 0, 0, 1, 2, 4, 4, 4, 4, 3, 1, 0, 0, 0, 0,   0, 0, 0, 0, 1, 2, 4, 4, 4, 4, 3, 1, 0, 0, 0, 0,
	  0, 0, 0, 0, 1, 6, 6, 6, 6, 6, 1, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 1, 3, 4, 4, 3, 1, 1, 0, 0, 0, 0,   0, 0, 0, 0, 0, 1, 3, 4, 4, 3, 1, 1, 0, 0, 0, 0,
	  0, 0, 0, 0, 1, 6, 6, 4, 4, 6, 6, 1, 0, 0, 0, 0,   0, 0, 0, 0, 1, 4, 4, 6, 6, 6, 4, 4, 1, 0, 0, 0,   0, 0, 0, 0, 1, 4, 4, 6, 6, 6, 4, 4, 1, 0, 0, 0,
	  0, 0, 0, 0, 1, 5, 6, 4, 4, 6, 5, 1, 0, 0, 0, 0,   0, 0, 0, 0, 1, 4, 4, 5, 6, 6, 6, 3, 1, 0, 0, 0,   0, 0, 0, 0, 1, 4, 4, 5, 6, 6, 6, 3, 1, 0, 0, 0,
	  0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0,   0, 0, 0, 0, 1, 5, 5, 6, 6, 6, 5, 1, 0, 0, 0, 0,   0, 0, 0, 0, 1, 5, 5, 6, 6, 6, 5, 1, 0, 0, 0, 0,
	  0, 0, 0, 0, 0, 0, 1, 1, 7, 1, 0, 0, 0, 0, 0, 0,   0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 7, 1, 0, 0, 0,   0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 7, 1, 0, 0, 0,
	  0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 1, 7, 7, 1, 1, 1, 7, 1, 0, 0, 0, 0,   0, 0, 0, 0, 1, 7, 7, 1, 1, 1, 7, 1, 0, 0, 0, 0,
	  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0,


	  0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	  0, 0, 0, 0, 1, 2, 2, 2, 2, 2, 2, 1, 0, 0, 0, 0,   0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0,
	  0, 0, 0, 1, 2, 2, 2, 2, 2, 2, 2, 2, 1, 0, 0, 0,   0, 0, 0, 0, 1, 2, 2, 2, 2, 2, 2, 1, 0, 0, 0, 0,   0, 0, 0, 0, 1, 2, 2, 2, 2, 2, 2, 1, 0, 0, 0, 0,
	  0, 0, 0, 1, 2, 2, 2, 2, 2, 2, 2, 2, 1, 0, 0, 0,   0, 0, 0, 1, 2, 2, 2, 2, 2, 2, 2, 2, 1, 0, 0, 0,   0, 0, 0, 1, 2, 2, 2, 2, 2, 2, 2, 2, 1, 0, 0, 0,
	  0, 0, 0, 1, 2, 2, 2, 2, 2, 2, 2, 2, 1, 0, 0, 0,   0, 0, 0, 1, 2, 2, 2, 2, 2, 2, 2, 2, 1, 0, 0, 0,   0, 0, 0, 1, 2, 2, 2, 2, 2, 2, 2, 2, 1, 0, 0, 0,
	  0, 0, 0, 1, 2, 2, 2, 2, 2, 2, 2, 2, 1, 0, 0, 0,   0, 0, 0, 1, 2, 2, 2, 2, 2, 2, 2, 2, 1, 0, 0, 0,   0, 0, 0, 1, 2, 2, 2, 2, 2, 2, 2, 2, 1, 0, 0, 0,
	  0, 0, 0, 1, 2, 2, 2, 2, 2, 2, 2, 2, 1, 0, 0, 0,   0, 0, 0, 1, 2, 2, 2, 2, 2, 2, 2, 2, 1, 0, 0, 0,   0, 0, 0, 1, 2, 2, 2, 2, 2, 2, 2, 2, 1, 0, 0, 0,
	  0, 0, 0, 0, 1, 2, 2, 2, 2, 2, 2, 1, 0, 0, 0, 0,   0, 0, 0, 1, 2, 2, 2, 2, 2, 2, 2, 2, 1, 0, 0, 0,   0, 0, 0, 1, 2, 2, 2, 2, 2, 2, 2, 2, 1, 0, 0, 0,
	  0, 0, 0, 0, 0, 1, 3, 3, 3, 3, 1, 0, 0, 0, 0, 0,   0, 0, 0, 0, 1, 2, 2, 2, 2, 2, 2, 1, 0, 0, 0, 0,   0, 0, 0, 0, 1, 2, 2, 2, 2, 2, 2, 1, 0, 0, 0, 0,
	  0, 0, 0, 1, 1, 5, 6, 6, 6, 6, 5, 1, 1, 0, 0, 0,   0, 0, 0, 0, 1, 1, 3, 3, 3, 3, 1, 1, 0, 0, 0, 0,   0, 0, 0, 0, 1, 1, 3, 3, 3, 3, 1, 1, 0, 0, 0, 0,
	  0, 0, 1, 3, 5, 6, 6, 6, 6, 6, 6, 5, 3, 1, 0, 0,   0, 0, 0, 1, 3, 5, 6, 6, 6, 6, 4, 4, 1, 0, 0, 0,   0, 0, 0, 1, 4, 4, 6, 6, 6, 6, 5, 3, 1, 0, 0, 0,
	  0, 0, 1, 3, 5, 5, 6, 6, 6, 6, 5, 5, 3, 1, 0, 0,   0, 0, 0, 1, 3, 5, 6, 6, 6, 5, 4, 4, 1, 0, 0, 0,   0, 0, 0, 1, 4, 4, 5, 6, 6, 6, 5, 3, 1, 0, 0, 0,
	  0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0,   0, 0, 0, 0, 1, 7, 7, 0, 6, 6, 5, 1, 0, 0, 0, 0,   0, 0, 0, 0, 1, 5, 6, 6, 0, 7, 7, 1, 0, 0, 0, 0,
	  0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0,   0, 0, 0, 0, 1, 7, 7, 1, 0, 0, 1, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 1, 0, 0, 1, 7, 7, 1, 0, 0, 0, 0,
	  0, 0, 0, 0, 1, 1, 1, 0, 0, 1, 1, 1, 0, 0, 0, 0,   0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0,
	  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0,


	  1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0,   2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	  1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0,   0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	  1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0,   0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	  1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1,   0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	  1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1,   0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	  1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1,   0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	  1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0,   0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	  1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0,   0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	  1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0,   0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	  1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1,   0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	  1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1,   0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	  1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,


	  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0,
	  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 5, 6, 0, 0, 0,
	  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 7, 5, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 5, 7, 5, 4, 0, 0,
	  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 5, 6, 0, 0, 0,
	  0, 0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 4, 0, 0, 0, 0,
	  0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 1, 0, 0, 0, 0, 0,   0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 1, 0, 0, 0, 0, 0,   0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 1, 0, 0, 0, 0, 0,
	  0, 0, 0, 1, 1, 1, 1, 7, 2, 7, 1, 1, 0, 0, 0, 0,   0, 0, 0, 1, 1, 1, 1, 7, 2, 7, 1, 1, 0, 0, 0, 0,   0, 0, 0, 1, 1, 1, 1, 7, 2, 7, 1, 1, 0, 0, 0, 0,
	  0, 0, 3, 1, 1, 1, 1, 1, 7, 1, 1, 1, 1, 0, 0, 0,   0, 0, 3, 1, 1, 1, 1, 1, 7, 1, 1, 1, 1, 0, 0, 0,   0, 0, 3, 1, 1, 1, 1, 1, 7, 1, 1, 1, 1, 0, 0, 0,
	  0, 0, 1, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0,   0, 0, 1, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0,   0, 0, 1, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0,
	  0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0,   0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0,   0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0,
	  0, 0, 1, 1, 1, 3, 1, 3, 1, 1, 1, 1, 1, 0, 0, 0,   0, 0, 1, 1, 1, 3, 1, 3, 1, 1, 1, 1, 1, 0, 0, 0,   0, 0, 1, 1, 1, 3, 1, 3, 1, 1, 1, 1, 1, 0, 0, 0,
	  0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0,   0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0,   0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0,
	  0, 0, 0, 1, 1, 1, 1, 1, 1, 3, 1, 3, 0, 0, 0, 0,   0, 0, 0, 1, 1, 1, 1, 1, 1, 3, 1, 3, 0, 0, 0, 0,   0, 0, 0, 1, 1, 1, 1, 1, 1, 3, 1, 3, 0, 0, 0, 0,
	  0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0,   0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0,   0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0,
	  0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0,
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
	  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
};

/**********************************************************************************/
/* Animation configurations                                                       */
/* beginFrame, frameCount, loop, delay                                            */
/**********************************************************************************/
const AnimationConfig ANIM_PLAYER_UP_IDLE = {
	.beginFrame = 6,
	.frameCount = 1,
	.flags = SF_NONE,
	.delay = 1,
};

const AnimationConfig ANIM_PLAYER_UP_MOVE = {
	.beginFrame = 7,
	.frameCount = 2,
	.flags = SF_NONE,
	.delay = 100,
};

const AnimationConfig ANIM_PLAYER_LEFT_IDLE = {
	.beginFrame = 3,
	.frameCount = 1,
	.flags = SF_FLIP_X,
	.delay = 1,
};

const AnimationConfig ANIM_PLAYER_LEFT_MOVE = {
	.beginFrame = 3,
	.frameCount = 2,
	.flags = SF_FLIP_X,
	.delay = 100,
};

const AnimationConfig ANIM_PLAYER_DOWN_IDLE = {
	.beginFrame = 0,
	.frameCount = 1,
	.flags = SF_NONE,
	.delay = 1,
};

const AnimationConfig ANIM_PLAYER_DOWN_MOVE = {
	.beginFrame = 1,
	.frameCount = 2,
	.flags = SF_NONE,
	.delay = 100,
};

const AnimationConfig ANIM_PLAYER_RIGHT_IDLE = {
	.beginFrame = 3,
	.frameCount = 1,
	.flags = SF_NONE,
	.delay = 1,
};

const AnimationConfig ANIM_PLAYER_RIGHT_MOVE = {
	.beginFrame = 3,
	.frameCount = 2,
	.flags = SF_NONE,
	.delay = 100,
};
/**********************************************************************************/
/* Tileset                                                                        */
/* Collision, sprite, palette, flags, offsetX, offsetY, timeOffsetX, timeOffsetY  */
/**********************************************************************************/
const TileConfig Tiles[] = {
	{CR_NONE,   0,  0, SF_NONE,    0,  0,  0,  0}, //  0, Empty space
	{CR_SOLID, 10,  1, SF_NONE,    0,  0,  0,  0}, //  1, Solid wall
	{CR_SOLID,  9,  1, SF_NONE,    0,  0,  0,  0}, //  2, Brick wall
	{CR_NONE,  11,  2, SF_NONE,    0,  0,  0,  0}, //  4, Grass
	{CR_SOLID, 12,  3, SF_NONE,    0,  0,  0,  0}, //  5, Bomb
};
const unsigned int TileConfigCount = sizeof(Tiles) / sizeof(Tiles[0]);

/*****************************************************************************/
/* Levels                                                                    */
/*****************************************************************************/
GameLevel LEVEL_1_SEWER = {
	.playerStartX = 1,
	.playerStartY = 0,
	.tileCountX = 17, 
	.tileCountY = 15,
	.horizontal = true,
	.targetX = 61,
	.targetY = 13,
	.target = 0,
	.tiles = {
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 3, 3, 3, 3, 3, 3, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1,
		1, 3, 1, 3, 1, 3, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1,
		1, 3, 3, 3, 3, 3, 3, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1,
		1, 3, 1, 3, 1, 3, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1,
		1, 3, 3, 3, 3, 3, 3, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1,
		1, 3, 1, 3, 1, 3, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1,
		1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1,
		1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1,
		1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1,
		1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1,
		1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1,
		1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 3, 1,
		1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 3, 3, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	}
};