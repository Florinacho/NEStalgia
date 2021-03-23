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
/* Animations                                                                */
/*****************************************************************************/
extern const AnimationConfig ANIM_PLAYER_UP_IDLE;
extern const AnimationConfig ANIM_PLAYER_UP_MOVE;
extern const AnimationConfig ANIM_PLAYER_LEFT_IDLE;
extern const AnimationConfig ANIM_PLAYER_LEFT_MOVE;
extern const AnimationConfig ANIM_PLAYER_DOWN_IDLE;
extern const AnimationConfig ANIM_PLAYER_DOWN_MOVE;
extern const AnimationConfig ANIM_PLAYER_RIGHT_IDLE;
extern const AnimationConfig ANIM_PLAYER_RIGHT_MOVE;

/*****************************************************************************/
/* Tileset                                                                     */
/*****************************************************************************/
extern const TileConfig Tiles[];
extern const unsigned int TileConfigCount;

/*****************************************************************************/
/* Levels                                                                    */
/*****************************************************************************/
extern GameLevel LEVEL_1_SEWER;

#endif // __DATA_H__