#include <stdio.h>

#include "Window.h"
#include "Timer.h"
#include "GUI.hpp"



int main(int argc, char* argv[]) {
	const uvec2 ScreenSize(1024, 720);
	Win32Window output;
	if (output.initialize(ScreenSize, Image::EPF_R8G8B8A8, "Immediate GUI") == false) {
		printf("Failed to initialize the win32 window.\n");
		return 1;
	}

	Image colorBuffer;
	colorBuffer.create(output.getSize(), output.getPixelFormat());
	colorBuffer.wrapping = Image::EWT_DISCARD;
	
	Event event;
	bool running = true;
	unsigned long long lastSecondTime = Timer::GetMilliSeconds();
	unsigned int frameCount = 0;
	
	ubvec4 colors[8] = {
		ubvec4(255, 255, 255, 255),
		ubvec4(255,   0,   0, 255),
		ubvec4(255, 255,   0, 255),
		ubvec4(  0, 255,   0, 255),
		ubvec4(  0, 255, 255, 255),
		ubvec4(  0,   0, 255, 255),
		ubvec4(255,   0, 255, 255),
		ubvec4(  0,   0,   0, 255),
	};
	int selectedColorIndex = 0;
	ubvec4 selectedColor;
	ivec4 colorChooserBounds(0, 0, 304, 236);
	unsigned int colorChooserFlags = GWF_DECORATION | GWF_MOVE;
	
	ivec4 confirmBounds(ScreenSize.x / 2 - 110, ScreenSize.y / 2 - 50, ScreenSize.x / 2 + 110, ScreenSize.y / 2 + 50);
	unsigned int confirmFlags = GWF_DECORATION;
	
	bool vertical = true;
	while (running) {
		const unsigned long long currentTime = Timer::GetMilliSeconds();
		if (currentTime - lastSecondTime >= 1000) {
			printf("FPS: %d\n", frameCount);
			frameCount = 0;
			lastSecondTime += 1000;
		}
		
		while (output.getEvent(&event)) {
			GUI::OnEvent(event);
			
			switch (event.type) {
			case Event::WINDOW_CLOSE :
				running = false;
				break;
			case Event::MOUSE_WHEEL :
				selectedColorIndex = ((unsigned int)selectedColorIndex + event.state / 120) % 8;
				break;
			case Event::KEYBOARD :
				switch (event.key) {
				case KEY_1 :
				case KEY_2 :
				case KEY_3 :
				case KEY_4 :
				case KEY_5 :
				case KEY_6 :
				case KEY_7 :
				case KEY_8 :
					if (event.state == 1) {
						selectedColorIndex = event.key - KEY_1;
					}
					break;
				case KEY_ESCAPE :
					if (event.state == 0) {
						if (colorChooserFlags & GWF_VISIBLE) {
							colorChooserFlags ^= GWF_VISIBLE;
						} else if (confirmFlags & GWF_VISIBLE) {
							confirmFlags ^= GWF_VISIBLE;
						} else {
							confirmFlags |= GWF_VISIBLE;
						}
					}
					break;
				}
				break;
			}
		}

		colorBuffer.clear();

		/*** GUI Begin ***/
		static unsigned int MainWindowFlags = GWF_VISIBLE;
		static ivec4 MainWindowBounds(0, 0, ScreenSize.x, ScreenSize.y);
		if (GUI::WindowBegin(&colorBuffer, MainWindowBounds, "", &MainWindowFlags)) {
			static const char* MainTabPanelNames[] = { "Sprite", "Animation", "Level" };
			static int MainTabSelected = 0;
			switch (GUI::TabbedPanel(&colorBuffer, MainTabPanelNames, 3, MainTabSelected)) {
			case 0 :
				static float HorizontalSplitPanelWeight = 0.05f;
				GUI::SplitPanel(&colorBuffer, HorizontalSplitPanelWeight, false);
					GUI::PushLayout();
					GUI::SetGridLayout(1, 12);
					for (unsigned int index = 0; index < 8; ++index) {
						if (GUI::Button(&colorBuffer, "", index)) {
						}
					}
					GUI::PopLayout();

					//GUI::PushLayout();
					static float VerticalSplitPanelWeight = 0.93f;
					GUI::SplitPanel(&colorBuffer, VerticalSplitPanelWeight, true);
						GUI::Label(&colorBuffer, "Canvas", NULL, 0);

						GUI::PushLayout();
						GUI::SetGridLayout(16, 1);
						for (unsigned int index = 0; index < 8; ++index) {
							if (GUI::Button(&colorBuffer, (index == selectedColorIndex) ? "X" : "", colors[index])) {
								selectedColorIndex = index;
								selectedColor = colors[selectedColorIndex];
								colorChooserFlags |= GWF_VISIBLE;
							}
						}
						GUI::PopLayout();
					
				if (GUI::ColorSelector(&colorBuffer, colorChooserBounds, selectedColor, &colorChooserFlags)) {
					colors[selectedColorIndex] = selectedColor;
				}
				break;
			case 1 :
			case 2 :
				break;
			}
			
			if (GUI::WindowBegin(&colorBuffer, confirmBounds, "QUIT", &confirmFlags)) {
				GUI::SetGridLayout(4, 3);
				GUI::SetGridSize(4);
				GUI::Label(&colorBuffer, "REALLY QUIT?");
				GUI::Label(&colorBuffer, ""); // Dummy
				GUI::PushLayout();
				GUI::SetGridLayout(4, 1);
				GUI::SetGridSize(1);
				GUI::Label(&colorBuffer, ""); // Dummy
				GUI::Label(&colorBuffer, ""); // Dummy
				if (GUI::Button(&colorBuffer, "YES")) {
					running = false;
				}
				if (GUI::Button(&colorBuffer, "NO")) {
					confirmFlags ^= GWF_VISIBLE;
				}
				GUI::PopLayout();
			}
		}
		/*** GUI End   ***/
		
		GUI::PostEvent();
		
		output.blit(&colorBuffer);
		++frameCount;
		Sleep(1);
	}
	
	return 0;
}