#ifndef __GRAPHICS_H__
#define __GRAPHICS_H__

#include "Vector.h"
#include "Tile.hpp"
#include "Util.hpp"

/*****************************************************************************/
/* MISC.                                                                     */
/*****************************************************************************/
unsigned int GetGraphicMemorySize();

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
/* Animations                                                                */
/*****************************************************************************/
extern const AnimationConfig ANIM_PLAYER_IDLE;
extern const AnimationConfig ANIM_PLAYER_MOVE;
extern const AnimationConfig ANIM_PLAYER_SWIM;
extern const AnimationConfig ANIM_PLAYER_JUMP;
extern const AnimationConfig ANIM_PLAYER_CLIMB;
extern const AnimationConfig ANIM_PLAYER_DEAD;

extern const AnimationConfig ANIM_BLOB_MOVE;

/*****************************************************************************/
/* Character configurations                                                  */
/*****************************************************************************/
extern const CharacterConfig CHR_PLAYER_CONFIG;
extern const CharacterConfig CHR_BLOOOB_CONFIG;

/*****************************************************************************/
/* Tileset                                                                     */
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