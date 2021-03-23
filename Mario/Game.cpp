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
	keys[KEY_JUMP]       = false;
	
	player.paletteIndex =  0;
	enemy.paletteIndex =  6;
	
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
	renderer.pixelOffset.x = 0;
	renderer.pixelOffset.x = 0;
	
	/*
	keys[KEY_MOVE_LEFT]  = false;
	keys[KEY_MOVE_DOWN]  = false;
	keys[KEY_MOVE_RIGHT] = false;
	keys[KEY_MOVE_UP]    = false;
	keys[KEY_JUMP]       = false;
	player.velocity = ivec2(0, 0);
	player.targetVelocity = ivec2(0, 0);
	player.status = EPS_FALLING;
	*/
	
	if (currentLevel != NULL) {
		player.setPosition(ivec2(TileRenderer::TileWidth * currentLevel->playerStartX, TileRenderer::TileHeight * currentLevel->playerStartY));
		enemy.setPosition(ivec2(TileRenderer::TileWidth * 54, TileRenderer::TileHeight * 13));
		enemy.targetVelocity.x =  50;
		enemy.status = EPS_STATIC;
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
			return true;
		case KEY_RIGHT :
			keys[KEY_MOVE_RIGHT] = event.state;
			return true;
		case KEY_UP :
			keys[KEY_MOVE_UP] = event.state;
			return true;
		case KEY_SPACE :
			keys[KEY_JUMP] = event.state;
			if (event.state == 0)
				jumped = false;
			return true;
		case KEY_DOWN :
			keys[KEY_MOVE_DOWN] = event.state;
			return true;
		}
		break;
	}
	
	return false;
}

void Game::update(unsigned int deltaTime) {
	if (player.status != EPS_DEAD) {
		if (keys[KEY_MOVE_LEFT]) {
			switch (player.status) {
			case EPS_SWIMMING :
				player.targetVelocity.x = - 70;
				break;
			default:
				player.targetVelocity.x = -100;
				break;
			}
			
			// Jump off ladder
			if ((player.status == EPS_CLIMB) && (player.canClimb[2] == false)) {
				player.status = EPS_STATIC;
			}
		} else if (keys[KEY_MOVE_RIGHT]) {
			switch (player.status) {
			case EPS_SWIMMING :
				player.targetVelocity.x =  70;
				break;
			default:
				player.targetVelocity.x = 100;
				break;
			}
			
			// Jump off ladder
			if ((player.status == EPS_CLIMB) && (player.canClimb[2] == false)) {
				player.status = EPS_STATIC;
			}
		} else {
			player.targetVelocity.x = 0;
		}
			
		if (keys[KEY_MOVE_UP] == true) {
			if (player.canClimb[1] && player.status != EPS_CLIMB) {
				// Climb the ladder
				player.status = EPS_CLIMB;
				player.velocity.y = 0;
			}
			
			switch (player.status) {
			case EPS_CLIMB:
				player.targetVelocity.y = -50;
				break;
			}
		} else if (keys[KEY_MOVE_DOWN]) {
			if (player.canClimb[2] && player.status != EPS_CLIMB) {
				// Climb the ladder
				player.status = EPS_CLIMB;
				player.velocity.y = 0;
			}
			switch (player.status) {
			case EPS_CLIMB:
				player.targetVelocity.y = 50;
				break;
			}
		} else {
		}
		
		if (keys[KEY_JUMP] == true) {
			// Hasn't jumped yet
			switch (player.status) {
			case EPS_STATIC:
				if (jumped == false) {
					player.velocity.y = -350;
					jumped = true;
				}
				break;
			case EPS_FALLING :
				break;
			case EPS_SWIMMING :
				if (jumped == false) {
					player.velocity.y = -300;
					jumped = true;
				}
				break;
			}
		}
	}
	
	// Apply gravity
	switch (player.status) {
	case EPS_DEAD:
	case EPS_STATIC :
	case EPS_FALLING :
		player.targetVelocity.y = 350;
		break;
	case EPS_CLIMB:
		if ((keys[KEY_MOVE_UP] == false) && (keys[KEY_MOVE_DOWN] == false)) {
			player.targetVelocity.y = 0;
		}
		break;
	case EPS_SWIMMING :
		if (player.velocity.y >= 0)
			player.velocity.y = 40;
		break;
	}

	player.update(deltaTime);
	
	int playerMidX = player.getPosition().x + 8;
	int playerMidY = player.getPosition().y + 8;
	int playerIndexX = playerMidX / 16;
	int playerIndexY = playerMidY / 16;
	
	if ((currentLevel->target != NULL) && 
		(currentLevel->targetX == playerIndexX) && (currentLevel->targetY == playerIndexY)) {
		loadLevel(currentLevel->target);
	}
	
	// Calculate screen offset based on the player's position
	if (currentLevel->horizontal) {
		const int playerPositionX = player.getPosition().x;
		renderer.tileOffset.x  = playerPositionX / TileRenderer::TileWidth - TileRenderer::TileCountX / 2;
		renderer.pixelOffset.x = playerPositionX % TileRenderer::TileWidth;
		if (renderer.tileOffset.x < 0) {
			renderer.tileOffset.x = 0;
			renderer.pixelOffset.x = 0;
		}
		const unsigned int maxOffset = renderer.mapTileCount.x - TileRenderer::TileCountX;
		if (renderer.tileOffset.x + 1 > maxOffset) {
			renderer.tileOffset.x = maxOffset;
			renderer.pixelOffset.x = 0;
		}
	} else {
		const int playerPositionY = player.getPosition().y;
		renderer.tileOffset.y  = playerPositionY / TileRenderer::TileHeight - TileRenderer::TileCountY / 2;
		renderer.pixelOffset.y = playerPositionY % TileRenderer::TileHeight;
		const unsigned int maxOffset = renderer.mapTileCount.y - TileRenderer::TileCountY;
		if (renderer.tileOffset.y  < 0) {
			renderer.tileOffset.y = 0;
			renderer.pixelOffset.y = 0;
		}
		const unsigned int mo = renderer.mapTileCount.y - TileRenderer::TileCountY;
		if (renderer.tileOffset.y + 1> mo) {
			renderer.tileOffset.y = mo;
			renderer.pixelOffset.y = 0;
		}
	}
	
	{ // Enemy test
	enemy.update(deltaTime);
	ivec2 enemyPos = enemy.getPosition() / 16;
	if (enemy.facingRight) {
		int nextIndex = enemyPos.y * renderer.mapTileCount.x + enemyPos.x + 1;
		if (Tiles[renderer.tileBuffer[nextIndex]].collision != 0) {
			enemy.velocity.x = 0;
			enemy.targetVelocity.x = -50;
		}
	} else {
		int nextIndex = enemyPos.y * renderer.mapTileCount.x + enemyPos.x - 1;
		if (Tiles[renderer.tileBuffer[nextIndex]].collision != 0) {
			enemy.velocity.x = 0;
			enemy.targetVelocity.x = 50;
		}
	}
	
	// Test enemy-player interaction
	if (enemy.status != EPS_DEAD && enemy.getPosition().getDistanceFrom(player.getPosition()) <= 12) {
		if (player.getPosition().y < enemy.getPosition().y - 8) {
			player.velocity.y = -200;
			enemy.setDead();
		} else {
			player.setDead();
		}
	}
	}
}

void Game::draw(Image* output, const unsigned long long currentTime) {
	renderer.draw(output, currentTime);
	
	player.draw(output, currentTime);
	
	if (enemy.status != EPS_DEAD) {
		unsigned char blobSpriteIndex = (currentTime / ANIM_BLOB_MOVE.delay) % ANIM_BLOB_MOVE.frameCount + ANIM_BLOB_MOVE.beginFrame;
		renderer.drawSprite(output, blobSpriteIndex, enemy.paletteIndex, enemy.getPosition(), enemy.facingRight ? 0 : SF_FLIP_X);
	}
	
	DrawText(output, uvec2(0, 0), Vector4ub(255, 255,  255, 255), TileRenderer::PixelScale + 1, "$%.2u", player.score);
}