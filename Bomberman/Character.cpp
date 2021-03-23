// https://github.com/OneLoneCoder/videos/blob/master/OneLoneCoder_PlatformGame1.cpp

#include "Character.hpp"
#include "TileRenderer.hpp"
#include "Game.hpp"

#include <stdlib.h>
#include <algorithm>

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
	direction = ECD_DOWN;
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

template<typename T>
Vector2<T> min2(const Vector2<T>& a, const Vector2<T>& b) {
	return Vector2<T>(std::min<T>(a.x, b.x), std::min<T>(a.y, b.y));
}
template<typename T>
Vector2<T> max2(const Vector2<T>& a, const Vector2<T>& b) {
	return Vector2<T>(std::max<T>(a.x, b.x), std::max<T>(a.y, b.y));
}

ivec2 Character::getCollisionResponse(const ivec2& currentPosition, const ivec2& newPosition) {
	const ivec2 currentCell = currentPosition / 1024 / 16;
	const ivec2 targetCell = newPosition / 1024 / 16;
	const ivec2 tileCount = ivec2(GamePtr->currentLevel->tileCountX, GamePtr->currentLevel->tileCountY);
	const ivec2 tileSize = ivec2(16, 16) * 1024;
	const ivec2 areaTL = max2<int>((min2<int>(currentCell, targetCell) - ivec2(1, 1)), ivec2(0, 0));
	const ivec2 areaBR = min2<int>((max2<int>(currentCell, targetCell) + ivec2(2, 2)), tileCount);
	int circleRadius = 8 * 1024;

	const ivec2 ignoreIndices[] = {
		{1, 2},
		{2, 1},
		{0, 1},
		{1, 0},
	};

	ivec2 cell;
	ivec2 ans = newPosition;
	
	for (cell.y = areaTL.y; cell.y < areaBR.y; ++cell.y) {
		for (cell.x = areaTL.x; cell.x < areaBR.x; ++cell.x) {
			const unsigned int index = cell.y * tileCount.x + cell.x;
			if (cell == ivec2(1, 1)) {
				continue;
			}
			const TileConfig tileConfig = Tiles[GamePtr->currentLevel->tiles[index]];
			if (tileConfig.collision != 0) {
				ivec2 nearestPoint;
				nearestPoint.x = std::max<int>(cell.x * tileSize.x, std::min<int>(ans.x, (cell.x + 1) * tileSize.x));
				nearestPoint.y = std::max<int>(cell.y * tileSize.y, std::min<int>(ans.y, (cell.y + 1) * tileSize.y));
				ivec2 rayToNearest = nearestPoint - ans;
				int overlap = circleRadius - (int)(abs(rayToNearest.x) + abs(rayToNearest.y));
				//if (std::isnan(overlap)) overlap = 0;

				if (overlap > 0) {
					vec2 r2n(rayToNearest.x, rayToNearest.y);
					r2n.normalize();
					vec2 r2o = r2n * (float)overlap;
					ivec2 res((int)r2o.x, (int)r2o.y);
					ans = ans - res;
				}
			}
		}
	}
	
	return ans;
}

void Character::updateStatus() {
	// TODO
}

void Character::update(int deltaTime) {
	velocity.x = lerp(targetVelocity.x, velocity.x, deltaTime);
	velocity.y = lerp(targetVelocity.y, velocity.y, deltaTime);
	
	ivec2 newPosition = position + velocity * deltaTime;
	
	position = getCollisionResponse(position + 8 * 1024, newPosition + 8 * 1024) - 8 * 1024;
	//position = newPosition;
}

void Character::draw(Image* output, const unsigned long long currentTime) {
	outputPtr = output;
	
	TileRenderer *renderer = &GamePtr->renderer;
	unsigned char flags = SF_NONE;
	switch (direction) {
	case ECD_UP :
		spriteIndex = ((currentTime / ANIM_PLAYER_UP_MOVE.delay) % ANIM_PLAYER_UP_MOVE.frameCount + ANIM_PLAYER_UP_MOVE.beginFrame) * (velocity.y != 0) + 6 * (velocity.y == 0);
		flags =  ANIM_PLAYER_UP_MOVE.flags;
		break;
	case ECD_LEFT :
		spriteIndex = ((currentTime / ANIM_PLAYER_LEFT_MOVE.delay) % ANIM_PLAYER_LEFT_MOVE.frameCount + ANIM_PLAYER_LEFT_MOVE.beginFrame) * (velocity.x != 0) + 3  * (velocity.x == 0);
		flags =  ANIM_PLAYER_LEFT_MOVE.flags;
		break;
	case ECD_DOWN :
		spriteIndex = ((currentTime / ANIM_PLAYER_DOWN_MOVE.delay) % ANIM_PLAYER_DOWN_MOVE.frameCount + ANIM_PLAYER_DOWN_MOVE.beginFrame) * (velocity.y != 0) + 0 * (velocity.y == 0);
		flags =  ANIM_PLAYER_DOWN_MOVE.flags;
		break;
	case ECD_RIGHT :
		spriteIndex = ((currentTime / ANIM_PLAYER_RIGHT_MOVE.delay) % ANIM_PLAYER_RIGHT_MOVE.frameCount + ANIM_PLAYER_RIGHT_MOVE.beginFrame) * (velocity.x != 0) + 3 * (velocity.x == 0);
		flags =  ANIM_PLAYER_RIGHT_MOVE.flags;
		break;
	}
	// spriteIndex = ((currentTime / ANIM_PLAYER_MOVE.delay) % ANIM_PLAYER_MOVE.frameCount + ANIM_PLAYER_MOVE.beginFrame) * !(velocity.x == 0);
	
	renderer->drawSprite(output, spriteIndex, paletteIndex, getPosition(), flags);
	
	const ivec2 pp = getPosition();
	output->drawRectangle(ivec4(pp.x - 1, pp.y - 1, pp.x + 1, pp.y + 1) * 3, ubvec4(  0, 255,   0, 255));
}

void Character::setDead() {
	// TODO
}