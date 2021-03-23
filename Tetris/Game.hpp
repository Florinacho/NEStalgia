#ifndef __GAME_HPP__
#define __GAME_HPP__

#include "Event.h"
#include "Data.hpp"
#include "TileRenderer.hpp"

enum GameState {
	EGS_RUNNING,
	EGS_PAUSE,
	EGS_GAMEOVER
};

class Game {
	TileRenderer renderer;
	
	GameLevel *currentLevel;
	GameState state;
	unsigned int score;
	unsigned int topScore;

	ivec2 piecePosition;	
	unsigned char piecePalette;
	unsigned char piece[16];
	unsigned char currentPiece;
	unsigned char nextPiece;
	unsigned long lastPieceUpdateTime;
	
	// Piece controlls
	void setType(const int value);
	bool getCollisionTest(const ivec2& value, const unsigned char* pieceData = 0);
	void moveLeft();
	void moveRight();
	void moveDown();
	void rotate();
	void snap();
	void checkLines();
	void newPiece();
	void resetLevel();
	
public:
	Game();
	
	~Game();
	
	int loadLevel(GameLevel* level);
	
	bool onEvent(Event& event);
	
	void update(unsigned int deltaTime);
	
	void draw(Image* output, const unsigned long long currentTime);
};

extern Game* GamePtr;

#endif // __GAME_HPP__