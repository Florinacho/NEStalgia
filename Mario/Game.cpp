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

	if (currentLevel != NULL) {
		player.setPosition(ivec2(TileRenderer::TileWidth * currentLevel->playerStartX, TileRenderer::TileHeight * currentLevel->playerStartY));
		enemy.setPosition(ivec2(TileRenderer::TileWidth * 54, TileRenderer::TileHeight * 13));
		enemy.targetVelocity.x =  50;
		enemy.status = ECS_IDLE;
	}

	return 0;
}

int Game::getTile(int32_t x, int32_t y) const {
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

struct Platform {
	ivec2 position;
	ivec2 begin;
	ivec2 end;
	ivec2 speed;
	bool forward;
};

Platform platforms[] = {
	{
		{4 * 16 * 1024, (int)(TileRenderer::TileCountY - 4) * 1024 * 16},
		{4 * 16 * 1024, (int)(TileRenderer::TileCountY - 4) * 1024 * 16},
		{7 * 16 * 1024, (int)(TileRenderer::TileCountY - 4) * 1024 * 16},
		{20, 0},
		true,
	},
	{
		{7 * 16 * 1024, (int)(TileRenderer::TileCountY - 5) * 1024 * 16},
		{4 * 16 * 1024, (int)(TileRenderer::TileCountY - 5) * 1024 * 16},
		{7 * 16 * 1024, (int)(TileRenderer::TileCountY - 5) * 1024 * 16},
		{20, 0},
		false,
	},
	{
		{7 * 16 * 1024, (int)(TileRenderer::TileCountY - 2) * 1024 * 16},
		{4 * 16 * 1024, (int)(TileRenderer::TileCountY - 2) * 1024 * 16},
		{7 * 16 * 1024, (int)(TileRenderer::TileCountY - 2) * 1024 * 16},
		{10, 0},
		false,
	},
	{
		{8 * 16 * 1024, (int)(TileRenderer::TileCountY - 2) * 1024 * 16},
		{5 * 16 * 1024, (int)(TileRenderer::TileCountY - 2) * 1024 * 16},
		{8 * 16 * 1024, (int)(TileRenderer::TileCountY - 2) * 1024 * 16},
		{10, 0},
		false,
	},
	{
		{9 * 16 * 1024, (int)(TileRenderer::TileCountY - 6) * 1024 * 16},
		{9 * 16 * 1024, (int)(TileRenderer::TileCountY - 2) * 1024 * 16},
		{9 * 16 * 1024, (int)(TileRenderer::TileCountY - 6) * 1024 * 16},
		{0, 10},
		false,
	},
};
const uint32_t PLATFORM_COUNT = sizeof(platforms) / sizeof(platforms[0]);

bool Contains(const ivec4& box, const ivec2& point) {
	return ((box.x < point.x) && (point.x < box.z) && (box.y <= point.y) && (point.y < box.w));
}

void PlatformCollide(Platform* platform, Character* player, const ivec2& delta) {
	ivec2 pos2 = platform->position;
	ivec2 newPosition = player->position;

	// Left
	if (Contains(ivec4(pos2.x +    0, pos2.y +    0, pos2.x + 16384, pos2.y + 16384), ivec2(newPosition.x +     0, player->position.y +  6 * 1024)) ||
		Contains(ivec4(pos2.x +    0, pos2.y +    0, pos2.x + 16384, pos2.y + 16384), ivec2(newPosition.x +     0, player->position.y + 10 * 1024))) {
		newPosition.x = pos2.x + 16384;
		player->velocity.x = player->targetVelocity.x = 0;
	}
	// Right
	if (Contains(ivec4(pos2.x +    0, pos2.y +    0, pos2.x + 16384, pos2.y + 16384), ivec2(newPosition.x + 16384, player->position.y +  6 * 1024)) ||
		Contains(ivec4(pos2.x +    0, pos2.y +    0, pos2.x + 16384, pos2.y + 16384), ivec2(newPosition.x + 16384, player->position.y + 10 * 1024))) {
		newPosition.x = pos2.x - 16384;
		player->velocity.x = player->targetVelocity.x = 0;
	}
	// Up
	if (Contains(ivec4(pos2.x +    0, pos2.y +    0, pos2.x + 16384, pos2.y + 16384), ivec2(newPosition.x +     0, newPosition.y +     0)) ||
		Contains(ivec4(pos2.x +    0, pos2.y +    0, pos2.x + 16384, pos2.y + 16384), ivec2(newPosition.x + 15360, newPosition.y +     0))) {
		newPosition.y = pos2.y + 16384;
		player->velocity.y = player->targetVelocity.y = 0;
	}
	// Down
	const bool botCollision[] = {
		Contains(ivec4(pos2.x +    0, pos2.y +    0, pos2.x + 16384, pos2.y + 16384), ivec2(newPosition.x +     0, newPosition.y + 16384)),
		Contains(ivec4(pos2.x +    0, pos2.y +    0, pos2.x + 16384, pos2.y + 16384), ivec2(newPosition.x +  8192, newPosition.y + 16384)),
		Contains(ivec4(pos2.x +    0, pos2.y +    0, pos2.x + 16384, pos2.y + 16384), ivec2(newPosition.x + 16384, newPosition.y + 16384)),
	};
	// Horizontal drag force
	for (uint32_t index = 0; index < 3; ++index) {
		if (botCollision[index]) {
			player->dragForce[index] = delta;
		}
	}

	if (botCollision[0] || botCollision[1] || botCollision[2]) {
		newPosition.y = pos2.y - 16384;
		player->status = ECS_IDLE;
	}

	player->position = newPosition;
}

void PlatformUpdate(Platform* platform, Character* player, uint32_t deltaTime) {
	const int32_t platformDelta = (platform->forward ? deltaTime : -deltaTime);

	platform->position += platform->speed * platformDelta;
	if (platform->speed.x != 0) {
	if (platform->position.x >= platform->end.x) {
		platform->position.x = platform->end.x;
		platform->forward = !platform->forward;
	} else if (platform->position.x <= platform->begin.x) {
		platform->position.x = platform->begin.x;
		platform->forward = !platform->forward;
	}
	}
	if (platform->speed.y != 0) {
	if (platform->position.y <= platform->end.y) {
		platform->position.y = platform->end.y;
		platform->forward = !platform->forward;
	} else if (platform->position.y >= platform->begin.y) {
		platform->position.y = platform->begin.y;
		platform->forward = !platform->forward;
	}
	}

	PlatformCollide(platform, player, platform->speed * platformDelta);
}

void Game::update(uint32_t deltaTime) {
	if (player.status != ECS_DEAD) {
		if (keys[KEY_MOVE_LEFT]) {
			player.moveLeft();
		} else if (keys[KEY_MOVE_RIGHT]) {
			player.moveRight();
		} else {
			player.targetVelocity.x = 0;
		}

		if (keys[KEY_MOVE_UP]) {
			player.moveUp();
		} else if (keys[KEY_MOVE_DOWN]) {
			player.moveDown();
		} else {
			player.targetVelocity.y = 0;
		}

		if (keys[KEY_JUMP] && !jumped) {
			player.jump();
			jumped = true;
		}
	}

	player.update(deltaTime);


	player.dragForce[0] = 0;
	player.dragForce[1] = 0;
	player.dragForce[2] = 0;

	for (uint32_t index = 0; index < PLATFORM_COUNT; ++index) {
		PlatformUpdate(&platforms[index], &player, deltaTime);
	}

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
		const uint32_t maxOffset = renderer.mapTileCount.x - TileRenderer::TileCountX;
		if (renderer.tileOffset.x + 1 > maxOffset) {
			renderer.tileOffset.x = maxOffset;
			renderer.pixelOffset.x = 0;
		}
	} else {
		const int playerPositionY = player.getPosition().y;
		renderer.tileOffset.y  = playerPositionY / TileRenderer::TileHeight - TileRenderer::TileCountY / 2;
		renderer.pixelOffset.y = playerPositionY % TileRenderer::TileHeight;
		const uint32_t maxOffset = renderer.mapTileCount.y - TileRenderer::TileCountY;
		if (renderer.tileOffset.y  < 0) {
			renderer.tileOffset.y = 0;
			renderer.pixelOffset.y = 0;
		}
		const uint32_t mo = renderer.mapTileCount.y - TileRenderer::TileCountY;
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
	if (enemy.status != ECS_DEAD && enemy.getPosition().getDistanceFrom(player.getPosition()) <= 12) {
		if (player.getPosition().y < enemy.getPosition().y - 8) {
			player.velocity.y = -200;
			enemy.setDead();
		} else {
			player.setDead();
		}
	}
	}
}

void Game::draw(Image* output, const uint64_t currentTime) {
	renderer.draw(output, currentTime);

	player.draw(output, currentTime);

	if (enemy.status != ECS_DEAD) {
		uint8_t blobSpriteIndex = (currentTime / ANIM_BLOB_MOVE.delay) % ANIM_BLOB_MOVE.frameCount + ANIM_BLOB_MOVE.beginFrame;
		renderer.drawSprite(output, blobSpriteIndex, enemy.paletteIndex, enemy.getPosition(), enemy.facingRight ? 0 : SF_FLIP_X);
	}

	for (uint32_t index = 0; index < PLATFORM_COUNT; ++index) {
		renderer.drawSprite(output, 15, 1, platforms[index].position / 1024, SF_NONE);
	}

	DrawText(output, uvec2(0, 0), Vector4ub(255, 255,  255, 255), TileRenderer::PixelScale + 1, "$%.2u", player.score);
}