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
	if (output.initialize(ScreenSize, Image::EPF_R8G8B8A8, "Bomberman Concept") == false) {
		printf("Failed to initialize the win32 window.\n");
		return 1;
	}

	Image colorBuffer;
	colorBuffer.create(output.getSize(), output.getPixelFormat());
	colorBuffer.wrapping = Image::EWT_DISCARD;

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
		
	unsigned long long lastSecondTime = Timer::GetMilliSeconds();
	unsigned long long lastFrameTime = lastSecondTime;
	unsigned int frameCount = 0;
	const unsigned int FPSlock = 80;
	const unsigned int frameDelay = 1000 / FPSlock;
		
	while (running) {
		const unsigned long long currentTime = Timer::GetMilliSeconds();
		const unsigned long long frameTimeDiff = currentTime - lastFrameTime;
		lastFrameTime = currentTime;
		
//		while (Timer::GetMilliSeconds() - lastFrameTime <= frameDelay) { __asm__("nop"); }
		
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
		colorBuffer.clear();
		game.update(frameTimeDiff);
		game.draw(&colorBuffer, currentTime);

		/*********************************************************************/
		/* Send color buffer to the screen.                                  */
		/*********************************************************************/
		output.blit(&colorBuffer);
		++frameCount;
	}
	
	return 0;
}