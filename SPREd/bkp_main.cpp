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
	
	// Palette window
	ivec4 colorChooserBounds(0, 0, 304, 236);
	ubvec4 color(0, 0, 0, 255);
	unsigned int colorChooserFlags = GWF_VISIBLE | GWF_DECORATION | GWF_MOVE;
	
	// Tabbed window
	const char* tabNames[] = {"Tab1", "Tab2", "Tab3"};
	const unsigned int tabCount = sizeof(tabNames) / sizeof(tabNames[0]);
	int selectedTab = 0;
	int selectedTab2 = 0;
	ivec4 utilWindowBounds(0, 237, 304, 637);
	int countX = 5;
	int countY = 3;
	
	// Scalable window
	ivec4 resizeWindowBounds(305, 0, 405, 100);
	unsigned int resizeWindowFlags = GWF_VISIBLE | GWF_TITLEBAR | GWF_TITLE | GWF_CLOSE | GWF_MOVE | GWF_SIZE;
	
	// ListBox
	int offset = 0;
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
			case Event::KEYBOARD :
				switch (event.key) {
				case KEY_SPACE :
					if (event.state == 1) {
						colorChooserFlags ^= GWF_VISIBLE;
					}
					break;
				case KEY_ESCAPE :
					if (event.state == 0) {
						running = false;
					}
					break;
				}
				break;
			}
		}

		colorBuffer.clear();

		if (GUI::ColorSelector(&colorBuffer, colorChooserBounds, color, &colorChooserFlags)) {
			printf("ColorSelector: %u, %u, %u, %u\n", color.x, color.y, color.z, color.w);
		}
		
		if (GUI::WindowBegin(&colorBuffer, utilWindowBounds)) {
			switch (GUI::TabbedPanel(&colorBuffer, ivec4(0, 0, 304 - 14, 380 - 14), tabNames, 2, selectedTab)) {
			case 0 :
				if (GUI::Button(&colorBuffer, "Titlebar", ivec4(8, 8, 128, 28))) {
					resizeWindowFlags ^= GWF_TITLEBAR;
					vertical = !vertical;
				}
				if (GUI::Button(&colorBuffer, "Visible", ivec4(8, 36, 128, 56))) {
					resizeWindowFlags ^= GWF_VISIBLE;
				}
				if (GUI::Button(&colorBuffer, "Move", ivec4(8, 64, 128, 84))) {
					resizeWindowFlags ^= GWF_MOVE;
				}
				if (GUI::Button(&colorBuffer, "Size", ivec4(8, 92, 128, 112))) {
					resizeWindowFlags ^= GWF_SIZE;
				}
				if (GUI::Spinner(&colorBuffer, offset, ivec4(8, 120, 128, 140))) {
					if (offset < 0) offset = 0;
				}
				break;
			case 1 :
				if (GUI::Spinner(&colorBuffer, countX, ivec4(8, 8, 128, 28))) {
					printf("Tab2::Sprinner: %d\n", countX);
					if (countX < 1) countX = 1;
				}
				if (GUI::Spinner(&colorBuffer, countY, ivec4(8, 36, 128, 56))) {
					printf("Tab2::Sprinner: %d\n", countY);
					if (countY < 1) countY = 1;
				}
				break;
			}
		} GUI::WindowEnd();
		
		if (GUI::WindowBegin(&colorBuffer, resizeWindowBounds, "Resize window", &resizeWindowFlags)) {
			static float weight = 0.3f;
			GUI::SplitPanel(&colorBuffer, weight, true);//GUI::SetGridLayout(1, 2);
			
			GUI::PushLayout();
			GUI::SetGridLayout(countX, countY);
			for (unsigned int index = 0; index < 3; ++index) {
				GUI::Label(&colorBuffer, "Label", NULL, GLF_CENTERED);
				
				// Split second cell into 2 vertical cells
				GUI::PushLayout();
				GUI::SetGridLayout(2, 2);
				static bool checked[] = {false, true, false};
				GUI::Label(&colorBuffer, "AA", NULL, GLF_CENTERED);
				if (GUI::Checkbox(&colorBuffer, checked[index])) {
					printf("Checkbox: %d\n", checked[index]);
				}
				GUI::Label(&colorBuffer, "BB", NULL, GLF_CENTERED);
				if (GUI::Checkbox(&colorBuffer, checked[index])) {
					printf("Checkbox2: %d\n", checked[index]);
				}
				GUI::PopLayout();
				
				// Split the 3rd cell into 3 vertical cells
				GUI::PushLayout();
				GUI::SetGridLayout(1, 3);
				static int values[] = {0, 0, 0};
				if (GUI::Spinner(&colorBuffer, values[index])) {
					printf("Spinner%d: %d\n", index, values[index]);
				}
				if (GUI::Spinner(&colorBuffer, values[index])) {
					printf("Spinner%d: %d\n", index, values[index]);
				}
				if (GUI::Spinner(&colorBuffer, values[index])) {
					printf("Spinner%d: %d\n", index, values[index]);
				}
				GUI::PopLayout();
				
				// Use 2 cells per element
				GUI::SetGridSize(2);
				if (GUI::Button(&colorBuffer, "Button")) {
					printf("Button %d pressed\n", index);
				}
				GUI::SetGridSize(1);
			}
			GUI::PopLayout();

			const unsigned int LabelFlags =  0;//GLF_BACKGROUND;
			switch (GUI::TabbedPanel(&colorBuffer, tabNames, 3, selectedTab2)) {
			case 0 :
				static int listBoxSelected = 0;
				static const char* ListBoxItems[] = {
					"Currently",
					"not",
					"working",
					"Line 3",
					"Line 4",
					"Line 5",
					"Line 6",
					"Line 7",
					"Line 8",
					"Line 9",
				};
				if (GUI::ListBox(&colorBuffer, listBoxSelected, offset, ListBoxItems, 10)) {
					printf("ListBox: %d\n", listBoxSelected);
				}
				break;
			case 1 :
				static float verticalSplitPanelOffset = 0.5f;
				if (GUI::SplitPanel(&colorBuffer, verticalSplitPanelOffset, true)) {
					verticalSplitPanelOffset = std::max(std::min(verticalSplitPanelOffset, 0.9f), 0.1f);
				}
				GUI::Label(&colorBuffer, "Hello", NULL, LabelFlags);
					static float horizontalSplitPanelOffset = 0.5f;
					if (GUI::SplitPanel(&colorBuffer, horizontalSplitPanelOffset, false)) {
						horizontalSplitPanelOffset = std::max(std::min(horizontalSplitPanelOffset, 0.9f), 0.1f);
					}
					GUI::Label(&colorBuffer, "from the", NULL, LabelFlags);
					GUI::Label(&colorBuffer, "other size.", NULL, LabelFlags);
				break;
			case 2 :
				GUI::Label(&colorBuffer, "other side.", NULL, LabelFlags);
				break;
			}
		} GUI::WindowEnd();
		
		GUI::PostEvent();
		
		output.blit(&colorBuffer);
		++frameCount;
		Sleep(1);
	}
	
	return 0;
}