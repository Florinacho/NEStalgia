#include "Game.hpp"
#include "Font.hpp"
#include "Timer.h"
#include "Data.hpp"

#include <string.h>

Game* GamePtr = NULL;
unsigned int RandomSeed = Timer::GetMicroSeconds() & 0x7fffffffU;
unsigned int GetRandom() {
	RandomSeed = (RandomSeed * 1103515245U + 12345U) & 0x7fffffffU;
	return RandomSeed;
}

void Game::setType(const int value) {
	if (value > 6) {
		return;
	}
	if (currentPiece == value) {
		return;
	}
	
	memcpy(piece, Pieces[value].data, 16);
	piecePalette = GetRandom() % 3 + 1;
	
	currentPiece = value;
}

bool Game::getCollisionTest(const ivec2& newPosition, const unsigned char* pieceData) {
	if (pieceData == NULL) {
		pieceData = piece;
	}
	
	const int px = newPosition.x / 16;
	const int py = newPosition.y / 16;
	
	for (unsigned int y = 0; y < 4; ++y) {
		if (py + y < 0) {
			return true;
		}
		for (unsigned int x = 0; x < 4; ++x) {
			if (px + x < 0) {
				return true;
			}
			int localIndex = y * 4 + x;
			int globalIndex = (py + y) * currentLevel->tileCountX + px + x;
			if ((pieceData[localIndex] != 0) && (currentLevel->tiles[globalIndex] != 0)) {
				return true;
			}
		}
	}
	
	return false;
}

void Game::moveLeft() {
	const int newPositionX = piecePosition.x - (int)TileRenderer::TileWidth;
	if (getCollisionTest(ivec2(newPositionX, piecePosition.y)) == false) {
		piecePosition.x = newPositionX;
	}
}

void Game::moveRight() {
	const int newPositionX = piecePosition.x + (int)TileRenderer::TileWidth;
	if (getCollisionTest(ivec2(newPositionX, piecePosition.y)) == false) {
		piecePosition.x = newPositionX;
	}
}

void Game::moveDown() {
	const int newPositionY = piecePosition.y + (int)TileRenderer::TileHeight;
	if (getCollisionTest(ivec2(piecePosition.x, newPositionY))) {
		score += Pieces[currentPiece].score;
		snap();
		newPiece();
	} else {
		piecePosition.y = newPositionY;
	}
	lastPieceUpdateTime = Timer::GetMilliSeconds();
}

void Game::rotate() {
	char newData[16] = {0};

	for (unsigned int y = 0; y < Pieces[currentPiece].length; ++y) {
		for (unsigned int x = 0; x < Pieces[currentPiece].length; ++x) {
			const int index0 = y * 4 + x;
			const int index1 = (Pieces[currentPiece].length - 1 - x) * 4 + y;
			newData[index0] = piece[index1];
		}
	}
	
	if (getCollisionTest(piecePosition, (const unsigned char*)newData) == false) {
		memcpy(piece, newData, 16);
	}
}

void Game::snap() {
	if (getCollisionTest(piecePosition, piece)) {
		return;
	}
	
	const int px = piecePosition.x / 16;
	const int py = piecePosition.y / 16;
	
	for (unsigned int y = 0; y < 4; ++y) {
		for (unsigned int x = 0; x < 4; ++x) {
			int localIndex = y * 4 + x;
			int globalIndex = (py + y) * currentLevel->tileCountX + px + x;
			if (piece[localIndex] != 0) {
				currentLevel->tiles[globalIndex] = piecePalette + 1;
			}
		}
	}
	checkLines();
}

void Game::checkLines() {
	int scoreMultiplier = 1;
	
	for (unsigned int y = 13; y > 0; --y) {
		bool complete = true;
		for (unsigned int x = 4; x < 15; ++x) {
			const int index = y * currentLevel->tileCountX + x;
			if (currentLevel->tiles[index] <= 1) {
				complete = false;
			}
		}

		if (complete) {
			score += 100 * scoreMultiplier;
			scoreMultiplier += 1;
			// Move rows down
			for (unsigned int ny = y; ny > 1; --ny) {
				for (unsigned int x = 4; x < 15; ++x) {
					const int index0 = (ny - 1) * currentLevel->tileCountX + x;
					const int index1 = ny * currentLevel->tileCountX + x;
					currentLevel->tiles[index1] = currentLevel->tiles[index0];
				}
			}
			++y;
		}
	}
}

void Game::newPiece() {
	piecePosition.x = currentLevel->startX * TileRenderer::TileWidth;
	piecePosition.y = currentLevel->startY * TileRenderer::TileHeight;

	setType(nextPiece);
	nextPiece = GetRandom() % EPT_COUNT;
	piecePalette = GetRandom() % 3 + 1;
	lastPieceUpdateTime = Timer::GetMilliSeconds();
	
	if (getCollisionTest(piecePosition, piece)) {
		state = EGS_GAMEOVER;
	}
}

Game::Game() {
	GamePtr = this;
	
	state = EGS_PAUSE;

	renderer.setPaletteList(Palettes);
	renderer.setTransparentColor(ubvec4( 0, 0, 0, 0));
	renderer.setSpriteBuffer(SpriteData);
	renderer.setSpriteCount(SpriteCount);
	renderer.setTileset(Tiles);
	
	score = 0;
	
	currentLevel = NULL;
	piecePalette = 0;
	nextPiece = GetRandom() % EPT_COUNT;
}
	
Game::~Game() {
	GamePtr = NULL;
}
	
int Game::loadLevel(GameLevel* level) {
	currentLevel = level;
	
	renderer.setTileBuffer(level->tiles, uvec2(level->tileCountX, level->tileCountY));
	
	renderer.tileOffset.x = 0;
	renderer.tileOffset.y = 0;
	renderer.pixelOffset.x = 0;
	renderer.pixelOffset.x = 0;
	
	topScore = score = 0;
	
	newPiece();
	
	return 0;
}

void Game::resetLevel() {
	for (int y = 0; y < 14; ++y) {
		for (int x = 4; x < 15; ++x) {
			const unsigned int index = y * currentLevel->tileCountX + x;
			currentLevel->tiles[index] = 0;
		}
	}
	score = 0;
	newPiece();
	state = EGS_RUNNING;
}

bool Game::onEvent(Event& event) {
	switch (event.type) {
	case Event::KEYBOARD :
		switch (event.key) {
		case KEY_SPACE :
			if (event.state == 1)
			switch (state) {
			case EGS_RUNNING :
				state = EGS_PAUSE;
				break;
			case EGS_PAUSE :
				state = EGS_RUNNING;
				break;
			case EGS_GAMEOVER :
				resetLevel();
				break;
			}
			return true;
		case KEY_LEFT :
			if ((event.state == 1) && (state != EGS_GAMEOVER)) {
				moveLeft();
			}
			return true;
		case KEY_RIGHT :
			if ((event.state == 1) && (state != EGS_GAMEOVER)) {
				moveRight();
			}
			return true;
		case KEY_UP :
			if ((event.state == 1) && (state != EGS_GAMEOVER)) {
				rotate();
			}
			return true;
		case KEY_DOWN :
			if ((event.state == 1) && (state != EGS_GAMEOVER)) {
				moveDown();
			}
			return true;
		}
		break;
	}
	
	return false;
}

void Game::update(unsigned int deltaTime) {
	switch (state) {
	case EGS_PAUSE :
	case EGS_GAMEOVER :
		return;
	}

	const unsigned long currentTime = Timer::GetMilliSeconds();

	while (currentTime - lastPieceUpdateTime >= 1000) {
		moveDown();
	}
	if (score > topScore) {
		topScore = score;
	}
}

void Game::draw(Image* output, const unsigned long long currentTime) {
	// Draw tiles
	renderer.draw(output, currentTime);
	
	switch (state) {
	case EGS_RUNNING :
		for (unsigned int y = 0; y < 4; ++y) {
			for (unsigned int x = 0; x < 4; ++x) {
				const int index = y * 4 + x;
				if (piece[index]) {
					renderer.drawSprite(output, 1, piecePalette, piecePosition + ivec2(x * TileRenderer::TileWidth, y * TileRenderer::TileHeight), 0);
				}
			}
		}
		break;
	case EGS_PAUSE :
		DrawText(output, 
		         uvec2(8 * TileRenderer::TileWidth, 7 * TileRenderer::TileHeight) * TileRenderer::PixelScale, 
				 Vector4ub(255, 255,  255, 255), 
				 TileRenderer::PixelScale * 2, 
				 "PAUSE");
		break;
	case EGS_GAMEOVER :
		DrawText(output, 
		         uvec2(6 * TileRenderer::TileWidth, 7 * TileRenderer::TileHeight) * TileRenderer::PixelScale, 
				 Vector4ub(255, 255,  255, 255), 
				 TileRenderer::PixelScale * 2, 
				 "GAME OVER");
		break;
	}
	
	DrawText(output, 
	         uvec2(0, 0) * TileRenderer::PixelScale, 
			 Vector4ub(255, 255,  255, 255), TileRenderer::PixelScale, 
			 "SCORE");
	DrawText(output, 
	         uvec2(0, 1) * TileRenderer::PixelScale * 7, 
			 Vector4ub(255, 255,  255, 255), 
			 TileRenderer::PixelScale, 
			 "%.7u", 
			 score);
	DrawText(output, 
	         uvec2(0, 3) * TileRenderer::PixelScale * 7,
			 Vector4ub(255, 255,  255, 255), TileRenderer::PixelScale, 
			 "TOP");
	DrawText(output, 
	         uvec2(0, 4) * TileRenderer::PixelScale * 7, 
			 Vector4ub(255, 255,  255, 255), 
			 TileRenderer::PixelScale, 
			 "%.7u", 
			 topScore);
	DrawText(output, 
	         uvec2(0, 6) * TileRenderer::PixelScale * 7, 
			 Vector4ub(255, 255,  255, 255), TileRenderer::PixelScale, 
			 "NEXT");
	for (int y = 0; y < 4; ++y) {
		for (int x = 0; x < 4; ++x) {
			const unsigned int index = y * 4 + x;
			if (Pieces[nextPiece].data[index] == 1) {
				renderer.drawSprite(output, 1, 4, ivec2(x, 4 + y) * 16, 0);
			}
		}
	}
}