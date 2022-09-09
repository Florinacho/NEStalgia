#include <stdio.h>

#include "Window.h"
#include "Timer.h"
#include "Game.hpp"

int main(int argc, char* argv[]) {
	/*************************************************************************/
	/* Output                                                                */
	/*************************************************************************/
	const uvec2 ScreenSize(TileRenderer::OutputWidth * TileRenderer::PixelScale, TileRenderer::OutputHeight * TileRenderer::PixelScale);
	Win32Window output;
	if (output.initialize(ScreenSize, Image::EPF_R8G8B8A8, "2D Platformer Concept") == false) {
		printf("Failed to initialize the win32 window.\n");
		return 1;
	}

	/*************************************************************************/
	/* Game                                                                  */
	/*************************************************************************/
	Game game;
	if (game.loadLevel(&LEVEL_1_SEWER) != 0) {
		printf("Game::Failed to load level!");
		return 2;
	}

	/*************************************************************************/
	/* Misc.                                                                 */
	/*************************************************************************/
	Event event;
	bool running = true;

	uint64_t lastSecondTime = Timer::GetMilliSeconds();
	uint64_t lastFrameTime = lastSecondTime;
	uint32_t frameCount = 0;

	while (running) {
		const uint64_t currentTime = Timer::GetMilliSeconds();
		const uint64_t frameTimeDiff = currentTime - lastFrameTime;
		lastFrameTime = currentTime;

		if (currentTime - lastSecondTime >= 1000) {
			printf("FPS: %d\n", frameCount);
			frameCount = 0;
			lastSecondTime += 1000;
		}

		/*********************************************************************/
		/* Check keyboard events.                                            */
		/*********************************************************************/
		while (output.getEvent(&event)) {
			if (game.onEvent(event) == false) {
				switch (event.type) {
				case Event::WINDOW_CLOSE :
					running = false;
					break;
				case Event::KEYBOARD :
					switch (event.key) {
					case KEY_ESCAPE :
						if (event.state == 0) {
							running = false;
						}
						break;
					}
					break;
				}
			}
		}

		/*********************************************************************/
		/* GUI                                                               */
		/*********************************************************************/
		output.clear();
		game.update(frameTimeDiff);
		game.draw(&output, currentTime);

		/*********************************************************************/
		/* Send color buffer to the screen.                                  */
		/*********************************************************************/
		output.blit(NULL);
		++frameCount;
	}

	return 0;
}