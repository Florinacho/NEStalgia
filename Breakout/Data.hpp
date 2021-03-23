#ifndef __DATA_H__
#define __DATA_H__

#include "Vector.h"
#include "Util.hpp"
#include "Tile.hpp"

/*****************************************************************************/
/* Palettes                                                                  */
/*****************************************************************************/
extern const Palette Palettes[];
extern const unsigned int PaletteCount;

/*****************************************************************************/
/* Sprites                                                                   */
/*****************************************************************************/
extern const uvec2 SpriteCount;
extern const unsigned int MaxSpriteIndex;
extern const unsigned char SpriteData[];

/*****************************************************************************/
/* Tileset                                                                   */
/*****************************************************************************/
extern const TileConfig Tiles[];
extern const unsigned int TileConfigCount;

/*****************************************************************************/
/* Levels                                                                    */
/*****************************************************************************/
extern GameLevel LEVEL_1;
extern GameLevel LEVEL_2;
extern GameLevel LEVEL_3;
extern GameLevel LEVEL_4;
extern GameLevel LEVEL_5;

#endif // __DATA_H__