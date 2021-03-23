#ifndef __CHARACTER_H__
#define __CHARACTER_H__

#include "Image.h"

class TileRenderer;

enum PlayerStatus {
	EPS_DEAD,
	EPS_STATIC,
	EPS_FALLING,
	EPS_SWIMMING,
	EPS_CLIMB,
};

class Character {
public:
	static const unsigned int ValueScaling = 1024;
	
	ivec2 position;
	ivec2 velocity;
	ivec2 targetVelocity;
	bool facingRight;
	bool canClimb[3]; // 0 - up, 1 - middle, 2 - bottom
	unsigned int score;
	unsigned char status;
	
	unsigned char spriteIndex;
	unsigned char paletteIndex;
	
	void updateCollisionResponse(ivec2& newPosition);
	void updateStatus();
	
	Character();
	
	void setPosition(const ivec2& value);
	
	const ivec2 getPosition() const;
	
	void update(int deltaTime);
	
	void draw(Image* output, const unsigned long long currentTime);
	
	void setDead();
};

#endif // __CHARACTER_H__