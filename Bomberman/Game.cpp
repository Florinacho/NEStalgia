#include "Game.hpp"

#include "Font.hpp"
#include "Timer.h"

Game* GamePtr = NULL;

bool Game::isSolid(int x, int y) const{
	return (Tiles[getTile(x, y)].collision == CR_SOLID);
}

Game::Game() {
	GamePtr = this;
	
	renderer.setPaletteList(Palettes);
	renderer.setTransparentColor(ubvec4( 0, 0, 0, 0));
	
	renderer.setSpriteBuffer(SpriteData);
	renderer.setSpriteCount(SpriteCount);
	
	renderer.setTileset(Tiles);
	
	keys[KEY_MOVE_LEFT]  = false;
	keys[KEY_MOVE_DOWN]  = false;
	keys[KEY_MOVE_RIGHT] = false;
	keys[KEY_MOVE_UP]    = false;
	
	player.paletteIndex =  0;
	
	jumped = false;
	
	currentLevel = NULL;
}
	
Game::~Game() {
	GamePtr = NULL;
}
	
int Game::loadLevel(GameLevel* level) {
	currentLevel = level;
	
	renderer.setTileBuffer(level->tiles, uvec2(level->tileCountX, level->tileCountY));
	
	renderer.tileOffset.x = 0;
	renderer.tileOffset.y = 0;
	//renderer.pixelOffset.x = 8;
	renderer.pixelOffset.y = 0;
	
	/*
	keys[KEY_MOVE_LEFT]  = false;
	keys[KEY_MOVE_DOWN]  = false;
	keys[KEY_MOVE_RIGHT] = false;
	keys[KEY_MOVE_UP]    = false;
	player.velocity = ivec2(0, 0);
	player.targetVelocity = ivec2(0, 0);
	player.status = EPS_FALLING;
	*/
	
	if (currentLevel != NULL) {
		player.setPosition(ivec2(TileRenderer::TileWidth * 1, TileRenderer::TileHeight * 1));
	}
	
	return 0;
}

int Game::getTile(const unsigned int x, const unsigned int y) const {
	if (currentLevel == NULL) {
		return 0;
	}
	
	if ((x < 0) || (x >= currentLevel->tileCountX) ||
		(y < 0) || (y >= currentLevel->tileCountY)) {
		return 0;
	}
	
	return currentLevel->tiles[y * currentLevel->tileCountX + x];
}

bool Game::onEvent(Event& event) {
	switch (event.type) {
	case Event::KEYBOARD :
		switch (event.key) {
		case KEY_LEFT :
			keys[KEY_MOVE_LEFT] = event.state;
			if (event.state == 1) {
				player.direction = ECD_LEFT;
			}
			return true;
		case KEY_RIGHT :
			keys[KEY_MOVE_RIGHT] = event.state;
			if (event.state == 1) {
				player.direction = ECD_RIGHT;
			}
			return true;
		case KEY_UP :
			keys[KEY_MOVE_UP] = event.state;
			if (event.state == 1) {
				player.direction = ECD_UP;
			}
			return true;
		case KEY_DOWN :
			keys[KEY_MOVE_DOWN] = event.state;
			if (event.state == 1) {
				player.direction = ECD_DOWN;
			}
			return true;
		case KEY_SPACE :
			if (event.state == 1) {
				const ivec2 playerPosition = player.getPosition() + 8;
				const int px = playerPosition.x / TileRenderer::TileWidth;
				const int py = playerPosition.y / TileRenderer::TileHeight;
				const int index = py * currentLevel->tileCountX + px;
				switch (currentLevel->tiles[index]) {
				case 0 : // Empty
				case 3 : // Grass
					currentLevel->tiles[index] = 4;
					break;
				}
			}
			return true;
		}
		break;
	}
	
	return false;
}

void Game::update(unsigned int deltaTime) {
	if (player.status != EPS_DEAD) {
		if (keys[KEY_MOVE_LEFT]) {
			player.targetVelocity.x = -60;
		} else if (keys[KEY_MOVE_RIGHT]) {
			player.targetVelocity.x = 60;
		} else {
			player.targetVelocity.x = 0;
		}
			
		if (keys[KEY_MOVE_UP] == true) {
			player.targetVelocity.y = -60;
		} else if (keys[KEY_MOVE_DOWN]) {
			player.targetVelocity.y = 60;
		} else {
			player.targetVelocity.y =  0;
		}
	}
	player.update(deltaTime);
}

void Game::draw(Image* output, const unsigned long long currentTime) {
	renderer.draw(output, currentTime);
	
	player.draw(output, currentTime);
}