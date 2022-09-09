// https://github.com/OneLoneCoder/videos/blob/master/OneLoneCoder_PlatformGame1.cpp

#include "Character.hpp"
#include "TileRenderer.hpp"
#include "Game.hpp"

int lerp(int target, int value, int delta) {
	const int diff = target - value;
	if (diff < 0) {
		return value - std::min(delta, abs(diff));
	} else if (diff > 0) {
		return value + std::min(delta, abs(diff));
	}
	return target;
}

Character::Character() {
	facingRight = true;
	canClimb[0] = false;
	canClimb[1] = false;
	canClimb[2] = false;
	score = 0;
	status = ECS_IDLE;
	spriteIndex = 0;
}

void Character::setPosition(const ivec2& value) {
	position = value * Character::ValueScaling;
}

const ivec2 Character::getPosition() const {
	return position / Character::ValueScaling;
}

bool Character::setState(CharacterState state) {

}

void Character::moveLeft() {
	setState(ECS_RUN);

	switch (status) {
	case ECS_SWIM :
		targetVelocity.x = - 70;
		break;
	default:
		targetVelocity.x = -100;
		break;
	}

	// Jump off ladder
	if ((status == ECS_CLIMB) && (canClimb[2] == false)) {
		status = ECS_IDLE;
	}
}

void Character::moveRight() {
	setState(ECS_RUN);

	switch (status) {
	case ECS_SWIM :
		targetVelocity.x =  70;
		break;
	default:
		targetVelocity.x = 100;
		break;
	}

	// Jump off ladder
	if ((status == ECS_CLIMB) && (canClimb[2] == false)) {
		status = ECS_IDLE;
	}
}

void Character::moveUp() {
	setState(ECS_CLIMB);

	if (canClimb[1] && status != ECS_CLIMB) {
		// Climb the ladder
		status = ECS_CLIMB;
		velocity.y = 0;
	}

	switch (status) {
	case ECS_CLIMB:
		targetVelocity.y = -50;
		break;
	}
}

void Character::moveDown() {
	setState(ECS_CLIMB);

	if (canClimb[2] && status != ECS_CLIMB) {
		// Climb the ladder
		status = ECS_CLIMB;
		velocity.y = 0;
	}
	switch (status) {
	case ECS_CLIMB:
		targetVelocity.y = 50;
		break;
	}
}

void Character::jump() {
	setState(ECS_FALL);

	switch (status) {
	case ECS_SWIM:
		velocity.y = -300;
		break;
	case ECS_IDLE:
		velocity.y = -350;
		break;
	}
}

void Character::updateCollisionResponse(ivec2& newPosition) {
	uint8_t cra = 0;
	uint8_t crb = 0;

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
		if (status == ECS_CLIMB && canClimb[2] == true) {
			return;
		}
		newPosition.y = ((newPosition.y >> 14) + 0) << 14;
		status = ECS_IDLE;
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
		status = ECS_SWIM;
		break;
	case CR_DIE :
		setDead();
		break;
	case CR_CLIMB :
	case CR_TOP :
		if (status == ECS_CLIMB) {
			position.x = (((position.x + 8192) >> 14) + 0) << 14;
		}
		break;
	}
}

void Character::update(int deltaTime) {
	if (GamePtr == NULL) {
		return;
	}

	// Apply gravity
	switch (status) {
	case ECS_DEAD:
	case ECS_IDLE :
	case ECS_FALL :
		targetVelocity.y = 350;
		break;
	case ECS_CLIMB:
		//if ((keys[KEY_MOVE_UP] == false) && (keys[KEY_MOVE_DOWN] == false))
		{
		//	targetVelocity.y = 0;
		}
		break;
	case ECS_SWIM :
		if (velocity.y >= 0)
			velocity.y = 40;
		break;
	}

	velocity.x = lerp(targetVelocity.x, velocity.x, deltaTime);
	velocity.y = lerp(targetVelocity.y, velocity.y, deltaTime);

	ivec2 newPosition = position + velocity * deltaTime;

	// Apply horizontal drag force set by platforms
	if (dragForce[1] != 0) {
		newPosition.x += dragForce[1].x;
	} else 	if (dragForce[0] != 0) {
		newPosition.x += dragForce[0].x;
	} else 	if (dragForce[2] != 0) {
		newPosition.x += dragForce[2].x;
	}

	// Clamp the player horizontal position within the level bounds
	if (newPosition.x < 0) {
		newPosition.x = 0;
	}
	if (newPosition.y >= (int)((GamePtr->currentLevel->tileCountY + 2) * TileRenderer::TileHeight * 1024)) {
		if (status == ECS_DEAD) {
			ivec2 playerStartPosition(TileRenderer::TileWidth * GamePtr->currentLevel->playerStartX, TileRenderer::TileHeight * GamePtr->currentLevel->playerStartY);
			newPosition = playerStartPosition;
			status = ECS_FALL;
		} else {
			setDead();
			newPosition.y = GamePtr->currentLevel->tileCountY * TileRenderer::TileHeight * 1024;
		}
	}

	switch (status) {
	case ECS_DEAD :
		break;
	case ECS_CLIMB:
		if (canClimb[0] == false && canClimb[1] == false && canClimb[2] == false) {
			status = ECS_FALL;
		}
		break;
	default :
		if (velocity.x != 0) {
			facingRight = velocity.x > 0;
		}
		status = ECS_FALL;
		break;
	}
	updateCollisionResponse(newPosition);
	position = newPosition;

	updateStatus();
}

void Character::draw(Image* output, uint64_t currentTime) {
	TileRenderer *renderer = &GamePtr->renderer;

	uint8_t spriteIndex = 0;
	switch (status) {
	case ECS_IDLE :
		spriteIndex = ((currentTime / ANIM_PLAYER_MOVE.delay) % ANIM_PLAYER_MOVE.frameCount + ANIM_PLAYER_MOVE.beginFrame) * !(velocity.x == 0);
		break;
	case ECS_FALL :
		spriteIndex = 1;
		break;
	case ECS_SWIM :
		spriteIndex = (currentTime / ANIM_PLAYER_SWIM.delay) % ANIM_PLAYER_SWIM.frameCount + ANIM_PLAYER_SWIM.beginFrame;
		break;
	case ECS_CLIMB :
		spriteIndex = ((currentTime / ANIM_PLAYER_CLIMB.delay) % ANIM_PLAYER_CLIMB.frameCount + ANIM_PLAYER_CLIMB.beginFrame) * !(velocity.y == 0) + 7 * (velocity.y == 0);
		break;
	case ECS_DEAD :
		spriteIndex = 2;
		break;
	}

	renderer->drawSprite(output, spriteIndex, paletteIndex, getPosition(), !facingRight * SF_FLIP_X);
}

void Character::setDead() {
	if (status == ECS_DEAD) {
		return;
	}
	status = ECS_DEAD;

	// Player death animation
	velocity.x = 0;
	velocity.y = -400;
	targetVelocity = 0;
}