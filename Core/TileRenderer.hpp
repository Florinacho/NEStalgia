#ifndef __TILE_RENDERER_H__
#define __TILE_RENDERER_H__

#include "Image.h"
#include "Tile.hpp"
//#include "Data.hpp"

class TileRenderer {
public:
	const Palette *paletteList;
	
	const unsigned char *spriteBuffer;
	uvec2 spriteCount;
	
	const TileConfig *tileset;
	
	unsigned char *tileBuffer;
	uvec2 mapTileCount;
	ivec2 tileOffset;
	ivec2 pixelOffset;
	
	ubvec4 transparentColor;

public:
	TileRenderer();
	
	void setPaletteList(const Palette* value);
	
	const Palette* getPaletteList() const;
	
	void setTransparentColor(const ubvec4& value);
	
	const ubvec4& getTransparentColor() const;
	
	void setSpriteBuffer(const unsigned char* value);
	
	const unsigned char* getSpriteBuffer() const;
	
	void setSpriteCount(const uvec2& value);
	
	const uvec2& getSpriteCount() const;
	
	void setTileset(const TileConfig* value);
	
	const TileConfig* getTileset() const;
	
	void setOffset(int offsetX, int offsetY);
	
	void setTileBuffer(unsigned char* tileBuffer, const uvec2& tileCount);
	
	void draw(Image *output, const unsigned long long currentTime);
	
	void drawSprite(Image* output, const unsigned int spriteIndex, const unsigned int paletteIndex, const ivec2& position, unsigned char flags);
	
	static const unsigned int TileCountX;
	static const unsigned int TileCountY;
	static const unsigned int TileCount;
	static const unsigned int TileWidth;
	static const unsigned int TileHeight;
	static const unsigned int OutputWidth;
	static const unsigned int OutputHeight;
	static const unsigned int PixelScale;
};

#endif // __TILE_RENDERER_H__