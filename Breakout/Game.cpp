#include "Game.hpp"

#include "Font.hpp"
#include "Timer.h"

Game* GamePtr = NULL;

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
	
	playerSize = 2;
	currentLevel = NULL;
	
	score = 0;
	scoreMultiplier = 0;
	
	winCondition = 0;
	
	lifeCount = 3;
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
	
	state = EGS_INITIAL;
	
	playerSize = 2;
	
	paddlePosition.x =  6 * TileRenderer::TileWidth + 8;
	paddlePosition.y = 13 * TileRenderer::TileHeight;
	
	ballPosition.x = (paddlePosition.x - 0) * 1024;
	ballPosition.y = (paddlePosition.y + 8) * 1024;
	ballVelocity.x = 0;
	ballVelocity.y = -100;
	
	scoreMultiplier = 1;
	
	winCondition = 0;
	const unsigned int maxTileCount = currentLevel->tileCountY * currentLevel->tileCountX;
	for (unsigned int index = 0; index < maxTileCount; ++index) {
		if (Tiles[currentLevel->tiles[index]].collision == CR_DESTR) {
			++winCondition;
		}
	}
	
	return 0;
}

bool Game::onEvent(Event& event) {
	switch (event.type) {
	case Event::MOUSE_POSITION :
		switch (state) {
		case EGS_INITIAL:
		case EGS_RUNNING :
			paddlePosition.x = (int)event.x / 3;
			return true;
		}
		break;
	case Event::KEYBOARD :
		switch (event.key) {
		case KEY_SPACE :
			if (event.state == 1) {
				switch (state) {
				case EGS_INITIAL :
					state = EGS_RUNNING;
					break;
				case EGS_RUNNING :
					state = EGS_PAUSE;
					break;
				case EGS_PAUSE :
					state = EGS_RUNNING;
					break;
				}
			}
			return true;
		case KEY_1 :
			playerSize = 1;
			return true;
		case KEY_2 :
			playerSize = 2;
			return true;
		case KEY_3 :
			playerSize = 3;
			return true;
		case KEY_LEFT :
			keys[KEY_MOVE_LEFT] = event.state;
			return true;
		case KEY_RIGHT :
			keys[KEY_MOVE_RIGHT] = event.state;
			return true;
		case KEY_UP :
			keys[KEY_MOVE_UP] = event.state;
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
	switch (state) {
	case EGS_INITIAL :
		ballPosition.x = paddlePosition.x * 1024;
		ballPosition.y = paddlePosition.y * 1024;
		break;
	case EGS_PAUSE :
	case EGS_WON :
	case EGS_GAMEOVER :
		return;
	}

	// Ball
	ivec2 newBallPosition = ballPosition + ballVelocity * deltaTime;
	
	{
	// Check vertical collision
	const int ballRadius = ((ballVelocity.y < 0) ? - 3 : 3);
	const int currentX = ballPosition.x / 1024 / TileRenderer::TileWidth;
	const int nextY = (newBallPosition.y / 1024 + ballRadius) / TileRenderer::TileHeight;
	const int verticalIndex = nextY * TileRenderer::TileWidth + currentX;
	const TileConfig config = Tiles[currentLevel->tiles[verticalIndex]];
	
	switch (config.collision) {
	case CR_DESTR :
		currentLevel->tiles[verticalIndex] = 4;
		score += scoreMultiplier;
		scoreMultiplier += 2;
		--winCondition;
	case CR_SOLID :
		newBallPosition.y = ballPosition.y;
		ballVelocity.y = -ballVelocity.y;
		break;
	}	
	}
	{ // Left / Right
	// Check horizontal collision
	const int ballRadius = ((ballVelocity.x < 0) ? - 3 : 3);
	const int currentY = ballPosition.y / 1024 / TileRenderer::TileHeight;
	const int nextX = (newBallPosition.x / 1024 + ballRadius) / TileRenderer::TileWidth;
	const int horizontalIndex = currentY * TileRenderer::TileHeight + nextX;
	const TileConfig config = Tiles[currentLevel->tiles[horizontalIndex]];
	
	switch (config.collision) {
	case CR_DESTR :
		currentLevel->tiles[horizontalIndex] = 4;
		score += scoreMultiplier;
		scoreMultiplier *= 2;
		--winCondition;
	case CR_SOLID :
		newBallPosition.x = ballPosition.x;
		ballVelocity.x = -ballVelocity.x;
		break;
	}
	}
	
	// Paddle 
	const int paddleWidth = playerSize * TileRenderer::TileWidth;
	const int halfPaddleWidth = paddleWidth / 2;
	
	// Constrain paddle
	if (keys[KEY_MOVE_LEFT]) {
		paddlePosition.x -= deltaTime / 3;
	}
	
	if (keys[KEY_MOVE_RIGHT]) {
		paddlePosition.x += deltaTime / 3;
	}
	
	if ((paddlePosition.x - halfPaddleWidth) < (int)( 1 * TileRenderer::TileWidth)) {
		paddlePosition.x = ( 1 * TileRenderer::TileWidth) + halfPaddleWidth;
	}
	if ((paddlePosition.x + halfPaddleWidth) > (12 * TileRenderer::TileWidth)) {
		paddlePosition.x = (12 * TileRenderer::TileWidth) - halfPaddleWidth;
	}
	
	// Ball-paddle collision
	if (((newBallPosition.x / 1024 + 3) >= (paddlePosition.x - halfPaddleWidth)) && ((newBallPosition.x / 1024 - 3) <= (paddlePosition.x + halfPaddleWidth))) {
		if ((newBallPosition.y / 1024 + 3) >= (paddlePosition.y + 11) && (newBallPosition.y / 1024 - 3) <= (paddlePosition.y + 16)) {
			newBallPosition.y = (paddlePosition.y + 11 - 4) * 1024;

			const int ballOffset = newBallPosition.x - (paddlePosition.x * 1024);

			ballVelocity.x = ballOffset / 1024 * 5;
			// TODO: Fix perfect horizontal velocity
			ballVelocity.y = -(100 - abs(ballVelocity.x));

			scoreMultiplier = 1;
		}
	}
	
	ballPosition = newBallPosition;
	
	// Check loose condition
	if (ballPosition.y >= 16 * 15 * 1024) {
		state = EGS_INITIAL;
		
		if (--lifeCount <= 0) {
			state = EGS_GAMEOVER;
			return;
		}
		score = 0;
		scoreMultiplier = 1;
		
		paddlePosition.x =  6 * TileRenderer::TileWidth + 8;
		paddlePosition.y = 13 * TileRenderer::TileHeight;
	
		ballPosition.x = (paddlePosition.x - 0) * 1024;
		ballPosition.y = (paddlePosition.y + 8) * 1024;
	}
	
	// Check win condition
	if (winCondition <= 0) {
		if (currentLevel->target) {
			loadLevel(currentLevel->target);
		} else {
			state = EGS_WON;
		}
	}
}

void Game::draw(Image* output, const unsigned long long currentTime) {
	// Draw tiles
	renderer.draw(output, currentTime);
	
	// Draw player paddle
	switch (playerSize) {
	case 1 :
		renderer.drawSprite(output, 3, 0, ivec2(paddlePosition.x -  8, paddlePosition.y), SF_NONE);
		break;
	case 2 :
		renderer.drawSprite(output, 4, 0, ivec2(paddlePosition.x - TileRenderer::TileWidth, paddlePosition.y), SF_NONE);
		renderer.drawSprite(output, 4, 0, ivec2(paddlePosition.x +  0, paddlePosition.y), SF_FLIP_X);
		break;
	case 3 :
		renderer.drawSprite(output, 4, 0, ivec2(paddlePosition.x - TileRenderer::TileWidth - 8, paddlePosition.y), SF_NONE);
		renderer.drawSprite(output, 5, 0, ivec2(paddlePosition.x - 8, paddlePosition.y), SF_NONE);
		renderer.drawSprite(output, 4, 0, ivec2(paddlePosition.x - 8 + TileRenderer::TileWidth, paddlePosition.y), SF_FLIP_X);
		break;
	}
	
	// Draw ball
	renderer.drawSprite(output, 1, 0, ballPosition / 1024 - 8, SF_NONE);
	
	// Draw game status related messages
	switch (state) {
	case EGS_INITIAL:
		DrawText(output, 
				uvec2(2 * TileRenderer::TileWidth * TileRenderer::PixelScale, 9 * TileRenderer::TileHeight * TileRenderer::PixelScale), 
				Vector4ub(255, 255,  255, 255), TileRenderer::PixelScale + 1, "PRESS A TO BEGIN");
		break;
	case EGS_PAUSE :
		DrawText(output, 
				uvec2(5 * TileRenderer::TileWidth * TileRenderer::PixelScale, 9 * TileRenderer::TileHeight * TileRenderer::PixelScale), 
				Vector4ub(255, 255,  255, 255), TileRenderer::PixelScale + 1, "PAUSE");
		break;
	case EGS_WON :
		DrawText(output, 
				uvec2(2 * TileRenderer::TileWidth * TileRenderer::PixelScale, 9 * TileRenderer::TileHeight * TileRenderer::PixelScale), 
				Vector4ub(255, 255,  255, 255), TileRenderer::PixelScale + 1, "CONGRATULATIONS!");
		break;
	case EGS_GAMEOVER :
		DrawText(output, 
				uvec2(4 * TileRenderer::TileWidth * TileRenderer::PixelScale, 9 * TileRenderer::TileHeight * TileRenderer::PixelScale), 
				Vector4ub(255, 255,  255, 255), TileRenderer::PixelScale + 1, "GAME OVER");
		break;
	}
	
	// Draw score board
	DrawText(output, 
	         uvec2(13 * TileRenderer::TileWidth * TileRenderer::PixelScale, 0), 
			 Vector4ub(255, 255,  255, 255), TileRenderer::PixelScale + 1, 
			 "Score");
	DrawText(output, 
	         uvec2(13 * TileRenderer::TileWidth * 3, 7 * 4), 
			 Vector4ub(255, 255,  255, 255), 
			 TileRenderer::PixelScale + 1, 
			 "%.5u", 
			 score);
	DrawText(output, 
	         uvec2(13 * TileRenderer::TileWidth * TileRenderer::PixelScale, 7 * 12), 
			 Vector4ub(255, 255,  255, 255), TileRenderer::PixelScale + 1, 
			 "LIFES");
	DrawText(output, 
	         uvec2(14 * TileRenderer::TileWidth * 3, 7 * 16), 
			 Vector4ub(255, 255,  255, 255), 
			 TileRenderer::PixelScale + 1, 
			 "%.2u", 
			 lifeCount);
}