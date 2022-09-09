#ifndef __GRAPHICS_H__
#define __GRAPHICS_H__

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
extern const uint32_t MaxSpriteIndex;
extern const uint8_t SpriteData[];

/*****************************************************************************/
/* Animations                                                                */
/*****************************************************************************/
extern const Animation ANIM_PLAYER_IDLE;
extern const Animation ANIM_PLAYER_MOVE;
extern const Animation ANIM_PLAYER_SWIM;
extern const Animation ANIM_PLAYER_JUMP;
extern const Animation ANIM_PLAYER_CLIMB;
extern const Animation ANIM_PLAYER_DEAD;

extern const Animation ANIM_BLOB_MOVE;

/*****************************************************************************/
/* Tileset                                                                   */
/*****************************************************************************/
extern const TileConfig Tiles[];
extern const unsigned int TileConfigCount;

/*****************************************************************************/
/* Levels                                                                    */
/*****************************************************************************/
extern GameLevel LEVEL_1_SEWER;
extern GameLevel LEVEL_2_SEWER;
extern GameLevel LEVEL_3_STREET;

#endif // __GRAPHICS_H__