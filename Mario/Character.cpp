// https://github.com/OneLoneCoder/videos/blob/master/OneLoneCoder_PlatformGame1.cpp

#include "Character.hpp"
#include "TileRenderer.hpp"
#include "Game.hpp"

int lerp(int target, int value, int delta) {
	int diff = target - value;
	if (diff == 0) {
		return target;
	}
	if (delta > abs(diff)) {
		delta = diff;
	}
	if (diff < 0) {
		return value - delta;
	} else {
		return value + delta;
	}
	return target;
}

Character::Character() {
	facingRight = true;
	canClimb[0] = false;
	canClimb[1] = false;
	canClimb[2] = false;
	score = 0;
	status = EPS_FALLING;
	spriteIndex = 0;
}

void Character::setPosition(const ivec2& value) {
	position = value * Character::ValueScaling;
}

const ivec2 Character::getPosition() const {
	return position / Character::ValueScaling;
}

void Character::updateCollisionResponse(ivec2& newPosition) {
	unsigned char cra = 0;
	unsigned char crb = 0;
	
	// Left
	cra = Tiles[GamePtr->getTile((newPosition.x +     0) >> 14, (position.y +     0) >> 14)].collision;
	crb = Tiles[GamePtr->getTile((newPosition.x +     0) >> 14, (position.y + 15360) >> 14)].collision;
	if ((cra == CR_SOLID) || (crb == CR_SOLID)) {
		newPosition.x = ((newPosition.x >> 14) + 1) << 14;
		targetVelocity.x = 0;
	}
	// Right
	cra = Tiles[GamePtr->getTile((newPosition.x + 16384) >> 14, (position.y +     0) >> 14)].collision;
	crb = Tiles[GamePtr->getTile((newPosition.x + 16384) >> 14, (position.y + 15360) >> 14)].collision;
	if ((cra == CR_SOLID) || (crb == CR_SOLID)) {
		newPosition.x = ((newPosition.x >> 14) + 0) << 14;
		targetVelocity.x = 0;
	}
	// Up
	cra = Tiles[GamePtr->getTile((newPosition.x +     0) >> 14, (newPosition.y +     0) >> 14)].collision;
	crb = Tiles[GamePtr->getTile((newPosition.x + 15360) >> 14, (newPosition.y +     0) >> 14)].collision;
	if ((cra == CR_SOLID) || (crb == CR_SOLID)) {
		newPosition.y = ((newPosition.y >> 14) + 1) << 14;
		velocity.y = 0;
		targetVelocity.y = 0;
	}
	// Down
	cra = Tiles[GamePtr->getTile((newPosition.x +     0) >> 14, (newPosition.y + 16384) >> 14)].collision;
	crb = Tiles[GamePtr->getTile((newPosition.x + 15360) >> 14, (newPosition.y + 16384) >> 14)].collision;
	if ((cra == CR_SOLID) || (crb == CR_SOLID) || (cra == CR_TOP) || (crb == CR_TOP)) {
		if (status == EPS_CLIMB && canClimb[2] == true) {
			return;
		}
		newPosition.y = ((newPosition.y >> 14) + 0) << 14;
		status = EPS_STATIC;
	}
}

void Character::updateStatus() {
	const int px = (position.x + 8192) >> 14;
	
	const int py0 = (position.y + 0) >> 14;
	const int py1= (position.y + 8192) >> 14;
	const int py2 = (position.y + 16384) >> 14;
	
	canClimb[0] = (Tiles[GamePtr->getTile(px, py0)].collision == CR_CLIMB) || (Tiles[GamePtr->getTile(px, py0)].collision == CR_TOP);
	canClimb[1] = (Tiles[GamePtr->getTile(px, py1)].collision == CR_CLIMB) || (Tiles[GamePtr->getTile(px, py1)].collision == CR_TOP);
	canClimb[2] = (Tiles[GamePtr->getTile(px, py2)].collision == CR_CLIMB) || (Tiles[GamePtr->getTile(px, py2)].collision == CR_TOP);
	
	switch (Tiles[GamePtr->getTile(px, py1)].collision){
	case CR_SCORE:
		GamePtr->currentLevel->tiles[py1 * GamePtr->currentLevel->tileCountX + px] = ETT_BACKGROUND_BRICK;
		++score;
		break;
	case CR_SWIM :
		status = EPS_SWIMMING;
		break;
	case CR_DIE :
		setDead();
		break;
	case CR_CLIMB :
	case CR_TOP :
		if (status == EPS_CLIMB) {
			position.x = (((position.x + 8192) >> 14) + 0) << 14;
		}
		break;
	}
}

void Character::update(int deltaTime) {
	if (GamePtr == NULL) {
		return;
	}

	velocity.x = lerp(targetVelocity.x, velocity.x, deltaTime);
	velocity.y = lerp(targetVelocity.y, velocity.y, deltaTime);
	
	ivec2 newPosition = position + velocity * deltaTime;
	
	if (newPosition.x < 0) {
		newPosition.x = 0;
	}
	if (newPosition.y >= (int)((GamePtr->currentLevel->tileCountY + 2) * TileRenderer::TileHeight * 1024)) {
		if (status == EPS_DEAD) {
			ivec2 playerStartPosition(TileRenderer::TileWidth * GamePtr->currentLevel->playerStartX, TileRenderer::TileHeight * GamePtr->currentLevel->playerStartY);
			newPosition = playerStartPosition;
			status = EPS_FALLING;
		} else {
			setDead();
			newPosition.y = GamePtr->currentLevel->tileCountY * TileRenderer::TileHeight * 1024;
		}
	}

	switch (status) {
	case EPS_DEAD :
		break;
	case EPS_CLIMB:
		if (canClimb[0] == false && canClimb[1] == false && canClimb[2] == false) {
			status = EPS_FALLING;
		}
		break;
	default :
		if (velocity.x != 0) {
			facingRight = velocity.x > 0;
		}
		status = EPS_FALLING;
		break;
	}
	updateCollisionResponse(newPosition);
	position = newPosition;
	
	updateStatus();
}

void Character::draw(Image* output, const unsigned long long currentTime) {
	TileRenderer *renderer = &GamePtr->renderer;
	
	unsigned char spriteIndex = 0;
	switch (status) {
	case EPS_STATIC :
		spriteIndex = ((currentTime / ANIM_PLAYER_MOVE.delay) % ANIM_PLAYER_MOVE.frameCount + ANIM_PLAYER_MOVE.beginFrame) * !(velocity.x == 0);
		break;
	case EPS_FALLING :
		spriteIndex = 1;
		break;
	case EPS_SWIMMING :
		spriteIndex = (currentTime / ANIM_PLAYER_SWIM.delay) % ANIM_PLAYER_SWIM.frameCount + ANIM_PLAYER_SWIM.beginFrame;
		break;
	case EPS_CLIMB :
		spriteIndex = ((currentTime / ANIM_PLAYER_CLIMB.delay) % ANIM_PLAYER_CLIMB.frameCount + ANIM_PLAYER_CLIMB.beginFrame) * !(velocity.y == 0) + 7 * (velocity.y == 0);
		break;
	case EPS_DEAD :
		spriteIndex = 2;
		break;
	}
	
	renderer->drawSprite(output, spriteIndex, paletteIndex, getPosition(), !facingRight * SF_FLIP_X);
}

void Character::setDead() {
	if (status == EPS_DEAD) {
		return;
	}
	status = EPS_DEAD;
	
	// Player death animation
	velocity.x = 0;
	velocity.y = -400;
	targetVelocity = 0;
}