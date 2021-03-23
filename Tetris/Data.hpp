#ifndef __DATA_H__
#define __DATA_H__

#include "Vector.h"
#include "Tile.hpp"
#include "Util.hpp"

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
/* Pieces                                                                    */
/*****************************************************************************/
extern const Piece Pieces[EPT_COUNT];

/*****************************************************************************/
/* Levels                                                                    */
/*****************************************************************************/
extern GameLevel LEVEL_1;

#endif // __DATA_H__