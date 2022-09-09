#ifndef __CHARACTER_H__
#define __CHARACTER_H__

#include <stdint.h>
#include "Image.h"

class TileRenderer;

enum CharacterState {
	ECS_DEAD,
	ECS_IDLE,
	ECS_RUN,
	ECS_FALL,
	ECS_SWIM,
	ECS_CLIMB,
};

class Character {
public:
	static const uint32_t ValueScaling = 1024;

	ivec2 position;
	ivec2 velocity;
	ivec2 targetVelocity;

	ivec2 dragForce[3];

	bool facingRight;
	bool canClimb[3]; // 0 - up, 1 - middle, 2 - bottom
	uint32_t score;
	uint8_t status;

	uint8_t spriteIndex;
	uint8_t paletteIndex;

	void updateCollisionResponse(ivec2& newPosition);
	void updateStatus();

	Character();

	void setPosition(const ivec2& value);

	const ivec2 getPosition() const;

	bool setState(CharacterState state);

	void moveLeft();

	void moveRight();

	void moveUp();

	void moveDown();

	void jump();

	void update(int deltaTime);

	void draw(Image* output, uint64_t currentTime);

	void setDead();
};

#endif // __CHARACTER_H__