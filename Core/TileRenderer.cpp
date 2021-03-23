#include <stdlib.h>

#include "TileRenderer.hpp"
#include "Timer.h"

template <typename T>
T min(T a, T b) {
	return (a < b) ? a : b;
}

template <typename T>
T max(T a, T b) {
	return (a > b) ? a : b;
}

void DrawPixel(Image* output, int x, int y, const ubvec4& color, int size = 1) {
	for (int yIndex = 0; yIndex < size; ++yIndex) {
		for (int xIndex = 0; xIndex < size; ++xIndex) {
			output->setRawPixel(x + xIndex, y + yIndex, color);
		}
	}
}

inline void DrawPixel2(Image* output, int x, int y, const ubvec4& color, int k = 1) {
	unsigned int* pixelBuffer = (unsigned int*)output->getData();
	uvec2 size = output->getSize();
	const unsigned int data = color.w << 24 | color.x << 16 | color.y << 8 | color.z;
	unsigned int index = y * size.x + x;
	pixelBuffer[index + 0] = data;
	pixelBuffer[index + 1] = data;
	pixelBuffer[index + 2] = data;
	pixelBuffer[index + size.x + 0] = data;
	pixelBuffer[index + size.x + 1] = data;
	pixelBuffer[index + size.x + 2] = data;
	pixelBuffer[index + 2*size.x + 0] = data;
	pixelBuffer[index + 2*size.x + 1] = data;
	pixelBuffer[index + 2*size.x + 2] = data;
}

const unsigned int TileRenderer::TileCountX = 16;
const unsigned int TileRenderer::TileCountY = 15;
const unsigned int TileRenderer::TileCount = TileCountY * TileCountX;
const unsigned int TileRenderer::TileWidth = 16;
const unsigned int TileRenderer::TileHeight = 16;
const unsigned int TileRenderer::OutputWidth = TileCountX * TileWidth;
const unsigned int TileRenderer::OutputHeight = TileCountY * TileHeight;
const unsigned int TileRenderer::PixelScale = 3;

TileRenderer::TileRenderer() {
	transparentColor = ubvec4(0, 0, 0, 0);

	paletteList = NULL;
	
	spriteBuffer = NULL;
	spriteCount = uvec2(1, 1);
	tileset = NULL;
	
	tileBuffer = NULL;
}

void TileRenderer::setPaletteList(const Palette* value) {
	paletteList = value;
}

const Palette* TileRenderer::getPaletteList() const {
	return paletteList;
}

void TileRenderer::setTransparentColor(const ubvec4& value) {
	transparentColor = value;
}

const ubvec4& TileRenderer::getTransparentColor() const {
	return transparentColor;
}

void TileRenderer::setSpriteBuffer(const unsigned char* value) {
	spriteBuffer = value;
}

const unsigned char* TileRenderer::getSpriteBuffer() const {
	return spriteBuffer;
}

void TileRenderer::setSpriteCount(const uvec2& value) {
	spriteCount = value;
}

const uvec2& TileRenderer::getSpriteCount() const {
	return spriteCount;
}

void TileRenderer::setTileset(const TileConfig* value) {
	tileset = value;
}

const TileConfig* TileRenderer::getTileset() const {
	return tileset;
}
	
void TileRenderer::setOffset(int offsetX, int offsetY) {
	tileOffset.x = offsetX / TileWidth;
	tileOffset.y = offsetY / TileHeight;
	pixelOffset.x = offsetX % TileWidth;
	pixelOffset.y = offsetY % TileHeight;
}

void TileRenderer::setTileBuffer(unsigned char* ntileBuffer, const uvec2& tileCount) {
	tileBuffer = ntileBuffer;
	mapTileCount.x = tileCount.x;
	mapTileCount.y = tileCount.y;
}

void TileRenderer::draw(Image *output, const unsigned long long currentTime) {
	if ((spriteBuffer == NULL) || (paletteList == NULL) || (tileset == NULL) || (tileBuffer == NULL)) {
		return;
	}
	
	for (int tileY = max<int>(tileOffset.y, 0); tileY < min<int>(mapTileCount.y, TileRenderer::TileCountY + tileOffset.y + 1); ++tileY) {
		for (int tileX = max<int>(tileOffset.x, 0); tileX < min<int>(mapTileCount.x, TileRenderer::TileCountX + tileOffset.x+1); ++tileX) {
			const unsigned int tileIndex = tileY * mapTileCount.x + tileX;
			const unsigned char tileValue = tileBuffer[tileIndex];
			if (tileValue == 0) {
				continue;
			}
			const TileConfig tileConfig = tileset[tileValue];
			ivec2 tileSpriteOffset;
			tileSpriteOffset.x = tileConfig.offsetX;
			tileSpriteOffset.y = tileConfig.offsetY;

			if (tileConfig.offsetXDelay != 0) {
				tileSpriteOffset.x += currentTime / tileConfig.offsetXDelay;
			}
			if (tileConfig.offsetYDelay != 0) {
				tileSpriteOffset.y += currentTime / tileConfig.offsetYDelay;
			}
		
			// Offset to the begining of the sprite index
			unsigned int spriteX = tileConfig.spriteIndex % spriteCount.x;
			unsigned int spriteY = tileConfig.spriteIndex / spriteCount.x;
			const unsigned int spriteOffset = spriteY * TileWidth * TileHeight * spriteCount.x + spriteX * TileWidth;

			for (int pixelY = max<int>(-pixelOffset.y, 0); pixelY < TileHeight; ++pixelY) {
				const int destPixelY = ((tileY - tileOffset.y) * TileHeight + pixelY - pixelOffset.y);
				if ((destPixelY < 0) || (destPixelY >= OutputHeight)) {
					continue;
				}
				for (int pixelX = max<int>(0, 0); pixelX < TileWidth; ++pixelX) {
					unsigned int sPixelX = pixelX;
					unsigned int sPixelY = pixelY;
					unsigned int tmp;
					
					switch (tileConfig.flags) {
					case SF_FLIP_X :
						sPixelX = TileWidth  - 1 - sPixelX;
						break;
					case SF_FLIP_Y :
						sPixelY = TileHeight - 1 - sPixelY;
						break;
					case SF_SWAP :
						tmp = sPixelX;
						sPixelX = sPixelY;
						sPixelY = tmp;
						break;
					case SF_FLIP_X | SF_SWAP : // SF_ROT_270
						tmp = TileWidth - 1 - sPixelX;
						sPixelX = sPixelY;
						sPixelY = tmp;
						break;
					case SF_FLIP_Y | SF_SWAP : // SF_ROT_90
						tmp = TileHeight - 1 - sPixelY;
						sPixelY = sPixelX;
						sPixelX = tmp;
						break;						
					case SF_FLIP_X | SF_FLIP_Y : // SF_ROT_180
						sPixelX = TileWidth  - 1 - sPixelX;
						sPixelY = TileHeight - 1 - sPixelY;
						break;
					case SF_FLIP_X | SF_FLIP_Y | SF_SWAP:
						tmp = TileWidth  - 1 - sPixelX;
						sPixelX = TileHeight - 1 - sPixelY;
						sPixelY = tmp;
						break;
					}
					
					const unsigned int sourcePixelIndex = spriteOffset +
						((sPixelY - tileSpriteOffset.y) % TileHeight) * TileWidth * spriteCount.x +
						 (sPixelX - tileSpriteOffset.x) % TileWidth;
						 
					const unsigned char sourcePixel = spriteBuffer[sourcePixelIndex];
					const ubvec4 destPixel = paletteList[tileConfig.paletteIndex][sourcePixel];
					if (destPixel == transparentColor) {
						continue;
					}
					const int destPixelX = ((tileX - tileOffset.x) * TileWidth  + pixelX - pixelOffset.x);
					if ((destPixelX < 0) || (destPixelX >= OutputWidth)) {
						continue;
					}
					DrawPixel2(output, destPixelX * PixelScale, destPixelY * PixelScale, destPixel, PixelScale);
				}
			}
		}
	}
}

void TileRenderer::drawSprite(Image* output, const unsigned int spriteIndex, const unsigned int paletteIndex, const ivec2& position, unsigned char flags) {
	if ((spriteBuffer == NULL) || (paletteList == NULL) || (tileset == NULL) || (tileBuffer == NULL)) {
		return;
	}
	
	const unsigned int spriteOffset = spriteIndex * TileWidth * TileHeight;
	const unsigned int spriteX = spriteIndex % spriteCount.x;
	const unsigned int spriteY = spriteIndex / spriteCount.x;
	
	for (int pixelY = 0; pixelY < TileHeight; ++pixelY) {
		int destPixelY = pixelY + position.y - tileOffset.y * TileHeight - pixelOffset.y;
		if (destPixelY < 0 || destPixelY >= OutputHeight) {
			continue;
		}
		for (int pixelX = 0; pixelX < TileWidth; ++pixelX) {
			int destPixelX = pixelX + position.x - tileOffset.x * TileWidth - pixelOffset.x;
			if (destPixelX < 0 || destPixelX >= OutputWidth) {
				continue;
			}
			unsigned int sPixelX = pixelX;
			unsigned int sPixelY = pixelY;
			unsigned int tmp;
			
			switch (flags) {
			case SF_FLIP_X :
				sPixelX = TileWidth  - 1 - sPixelX;
				break;
			case SF_FLIP_Y :
				sPixelY = TileHeight - 1 - sPixelY;
				break;
			case SF_SWAP :
				tmp = sPixelX;
				sPixelX = sPixelY;
				sPixelY = tmp;
				break;
			case SF_FLIP_X | SF_SWAP :
				tmp = TileWidth - 1 - sPixelX;
				sPixelX = sPixelY;
				sPixelY = tmp;
				break;
			case SF_FLIP_X | SF_FLIP_Y :
				sPixelX = TileWidth  - 1 - sPixelX;
				sPixelY = TileHeight - 1 - sPixelY;
				break;
			case SF_FLIP_X | SF_FLIP_Y | SF_SWAP:
				tmp = TileWidth  - 1 - sPixelX;
				sPixelX = TileHeight - 1 - sPixelY;
				sPixelY = tmp;
				break;
			}
			unsigned int sourceIndex = spriteY * TileHeight * TileWidth * spriteCount.x +
										spriteX * TileWidth +
										sPixelY * TileWidth * spriteCount.x + 
										sPixelX;
			const ubvec4 destPixel = paletteList[paletteIndex][spriteBuffer[sourceIndex]];
			if (destPixel == transparentColor) {
				continue;
			}
			DrawPixel2(output, destPixelX * PixelScale, destPixelY * PixelScale, destPixel, PixelScale);
		}
	}
}