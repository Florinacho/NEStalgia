#include "GUI.hpp"
#include "Font.hpp"

#include <stdio.h>
#include <vector>

static const ubvec4 RawDefaultColor  (128, 128, 128, 255);
static const ubvec4 RawDefaultColor2 (165, 165, 165, 255);
static const ubvec4 RawLightColor    (191, 191, 191, 255);
static const ubvec4 RawDarkColor     ( 76,  76,  76, 255);
static const ubvec4 TextColor        (  0,   0,   0, 255);
static const int Separator = 8;
static const int TextSize = 2;
static const int WindowTitlebarHeight = TextSize * 10;

struct Layout {
	enum Type {
		ABSOLUTE,
		FLOW,
		GRID,
		SPLIT
	};
	Type type;
	ivec4 parent;
	int elementIndex;
	
	union {
		struct {
			ivec2 count;
			ivec2 cellSize;
			int elementSize;
		} grid;
		struct {
			float weight;
			bool vertical;
		} split;
	};
	
	Layout() {
		type = Layout::GRID;
		parent = ivec4();
		elementIndex = 0;
		grid.count = ivec2(1, 1);
		grid.cellSize = ivec2(1, 1);
		grid.elementSize = 1;
	}
	
	Layout(const Layout& other) {
		*this = other;
	}
	
	Layout& operator = (const Layout& other) {
		type = other.type;
		parent = other.parent;
		elementIndex = other.elementIndex;
		
		switch (type) {
		case Layout::GRID :
			grid.count = other.grid.count;
			grid.cellSize = other.grid.cellSize;
			grid.elementSize = other.grid.elementSize;
			break;
		case Layout::SPLIT :
			split.vertical = other.split.vertical;
			split.weight = other.split.weight;
			break;
		}
		return *this;
	}
};

ivec2 MousePosition, LastMousePosition;
bool MouseButtons[3], LastMouseButtons[3];
ivec4 ParentWindowRectangle;
int draggedID = 0;
int windowID = 1;
Layout currentLayout;
std::vector<Layout> layoutStack;

inline bool IsInside(const ivec4& rect, const ivec2& point) {
	return ((point.x >= rect.x) && (point.x <= rect.z) && (point.y >= rect.y) && (point.y <= rect.w));
}

inline ivec4 GUILayoutGetBounds(const ivec4* bounds) {
	ivec4 ans;
	if (bounds) {
		ans = *bounds;
		currentLayout.elementIndex += 1;
	} else {
		switch (currentLayout.type) {
		case Layout::SPLIT :
			{
			const unsigned int width2 = ParentWindowRectangle.z - ParentWindowRectangle.x;
			const unsigned int height2 = ParentWindowRectangle.w - ParentWindowRectangle.y;
			const unsigned int topCellHeight = (height2 - Separator) * currentLayout.split.weight;
			const unsigned int botCellHeight = height2 - Separator - topCellHeight;
			const unsigned int topCellWidth = (width2 - Separator) * currentLayout.split.weight;
			const unsigned int botCellWidth = width2 - Separator - topCellWidth;
			int cellIndex = currentLayout.elementIndex % 2;
			if (currentLayout.split.vertical) {
				ans = ivec4(0, (topCellHeight + Separator) * cellIndex, width2, topCellHeight + (Separator + botCellHeight) * cellIndex);
			} else {
				ans = ivec4((topCellWidth + Separator) * cellIndex, 0, topCellWidth + (Separator + botCellWidth) * cellIndex, height2);
			}
			currentLayout.elementIndex += 1;
			}
			break;
		case Layout::GRID:
			{
			const int indexX = (currentLayout.elementIndex % currentLayout.grid.count.x) % currentLayout.grid.count.x;
			const int indexY = (currentLayout.elementIndex / currentLayout.grid.count.x) % currentLayout.grid.count.y;
			const unsigned int width = currentLayout.parent.z - currentLayout.parent.x;
			const unsigned int height = currentLayout.parent.w - currentLayout.parent.y;
			const int gridCount = std::min(currentLayout.grid.elementSize, currentLayout.grid.count.x - indexX);
			ans = ivec4( indexX              * currentLayout.grid.cellSize.x +  indexX                  * Separator,
						 indexY              * currentLayout.grid.cellSize.y +  indexY                  * Separator,
						(indexX + gridCount) * currentLayout.grid.cellSize.x + (indexX + gridCount - 1) * Separator, 
						(indexY + 1)         * currentLayout.grid.cellSize.y +  indexY                  * Separator);
			currentLayout.elementIndex += gridCount;
			}
			break;
		default :
			ans = ParentWindowRectangle;
			currentLayout.elementIndex += 1;
			break;
		}
	}
	return ans;
}

inline void GUIDrawOutline(Image* output, const ivec4& rectangle, bool invert = false) {
	output->drawLine(ivec2(rectangle.x, rectangle.y), ivec2(rectangle.x, rectangle.w), invert ? RawLightColor : RawDarkColor);
	output->drawLine(ivec2(rectangle.x, rectangle.w), ivec2(rectangle.z, rectangle.w), invert ? RawLightColor : RawDarkColor);
	output->drawLine(ivec2(rectangle.z, rectangle.w), ivec2(rectangle.z, rectangle.y), invert ? RawDarkColor : RawLightColor);
	output->drawLine(ivec2(rectangle.x, rectangle.y), ivec2(rectangle.z, rectangle.y), invert ? RawDarkColor : RawLightColor);
}
inline void GUIDrawQuad(Image* output, const ivec4& bounds, const ubvec4& color) {
	output->drawFilledRectangle(bounds, color);
}

void GUI::SetViewport(const ivec4& bounds) {
	ParentWindowRectangle = bounds;
}

void GUI::PushLayout() {
	currentLayout.parent = ParentWindowRectangle;
	layoutStack.push_back(currentLayout);
	ParentWindowRectangle = GUILayoutGetBounds(NULL) + ivec4(ParentWindowRectangle.x, ParentWindowRectangle.y, ParentWindowRectangle.x, ParentWindowRectangle.y);
}
void GUI::PopLayout() {
	if (layoutStack.size() <= 0) {
		printf("%s::%d::GUI Error: Layout stack is empty\n", __FILE__, __LINE__);
		return;
	}
	currentLayout = layoutStack.back();
	currentLayout.elementIndex += 1;
	ParentWindowRectangle = currentLayout.parent;
	layoutStack.pop_back();
}

void GUI::SetGridSize(int value) {
	currentLayout.grid.elementSize = value;
}

void GUI::SetGridLayout(int x, int y) {
	currentLayout.type = Layout::GRID;
	currentLayout.elementIndex = 0;
	currentLayout.grid.count.x = x;
	currentLayout.grid.count.y = y;
	currentLayout.grid.cellSize.x = (ParentWindowRectangle.z - ParentWindowRectangle.x - Separator * (currentLayout.grid.count.x - 1)) / currentLayout.grid.count.x;
	currentLayout.grid.cellSize.y = (ParentWindowRectangle.w - ParentWindowRectangle.y - Separator * (currentLayout.grid.count.y - 1)) / currentLayout.grid.count.y;
	currentLayout.grid.elementSize = 1;
}

void GUI::SetSplitLayout(bool vertical, float weight) {
	currentLayout.type = Layout::SPLIT;
	currentLayout.elementIndex = 0;
	currentLayout.split.vertical = vertical;
	currentLayout.split.weight = weight;
}

void GUI::OnEvent(const Event& event) {
	switch (event.type) {
	case Event::MOUSE_POSITION :
		MousePosition.x = event.x;
		MousePosition.y = event.y;
		break;
	case Event::MOUSE_BUTTON :
		MouseButtons[event.button] = event.state;
		break;
	}
	windowID = 1;
}

void GUI::PostEvent() {
	for (unsigned int index = 0; index < 3; ++index) {
		LastMouseButtons[index] = MouseButtons[index];
	}
	LastMousePosition = MousePosition;
	if (MouseButtons[0] == false) {
		draggedID = 0;
	}
}

bool GUI::WindowBegin(Image* output, ivec4& r, const char* text, unsigned int* flags) {
	unsigned int defaultFlags = GWF_DEFAULT & ~GWF_CLOSE;
	if (flags == NULL) {
		flags = & defaultFlags;
	}
	
	if ((*flags & GWF_VISIBLE) == 0) {
		++windowID;
		return false;
	}

	if (r.z < r.x + Separator * 2) {
		r.z = r.x + Separator * 2;
	}
	if (r.w < r.y + Separator * 2 + WindowTitlebarHeight) {
		r.w = r.y + Separator * 2 + WindowTitlebarHeight;
	}

	const ivec4 titlebarRectangle(r.x, r.y, r.z, r.y + WindowTitlebarHeight);
	if ((*flags & GWF_TITLEBAR) && (*flags & GWF_MOVE)) {
		if (MouseButtons[0] && LastMouseButtons[0] == false && IsInside(titlebarRectangle,     MousePosition)) {
			draggedID = windowID;
		}
		if (
			(
				(    MouseButtons[0] == true && IsInside(titlebarRectangle,     MousePosition)) ||
				(LastMouseButtons[0] == true && IsInside(titlebarRectangle, LastMousePosition))
			)&&
//			(LastMouseButtons[0] == true && IsInside(titlebarRectangle, LastMousePosition))
			(draggedID == windowID)
			) {
			ivec2 offset = MousePosition - LastMousePosition;
			r += ivec4(offset.x, offset.y, offset.x, offset.y);
		}
	}
	
	// Draw titlebar
	ParentWindowRectangle = r;
	int offsetY = 0;
	if (*flags & GWF_TITLEBAR) {
		GUIDrawQuad(output, ivec4(r.x, r.y, r.z, r.y + WindowTitlebarHeight), RawDarkColor);
		if (*flags & GWF_TITLE && text) {
			DrawText(output, uvec2(r.x, r.y) + 2, text, TextColor, TextSize);
		}
		const int width = r.z - r.x;
		if ((*flags & GWF_CLOSE) && Button(output, "X", ivec4(width - WindowTitlebarHeight + 1, 1, width - 1, WindowTitlebarHeight - 1))) {
			*flags &= ~GWF_VISIBLE;
		}
		offsetY += WindowTitlebarHeight;
	}

	ParentWindowRectangle = r + ivec4(Separator, Separator + offsetY, -Separator, -Separator);
	SetGridLayout(1, 1);
	// Draw window body
	GUIDrawQuad(output, r + ivec4(0, offsetY, 0, 0), RawDefaultColor);
	GUIDrawOutline(output, r);
	
	if (*flags & GWF_SIZE) {
		for (unsigned int index = 1; index < 4; ++index) {
			output->drawLine(ivec2(r.z - index * 5 + 0, r.w - 1), ivec2(r.z + 0, r.w - index * 5 + 0), RawLightColor);
			output->drawLine(ivec2(r.z - index * 5 + 1, r.w + 0), ivec2(r.z + 0, r.w - index * 5 + 1), RawDarkColor);
		}
		const bool isInside = ((draggedID == 0) && (MousePosition.x >= r.z - 15) && (MousePosition.x <= r.z) && (MousePosition.y >= r.w - 15) && (MousePosition.y <= r.w));
		const bool wasInside = ((draggedID == 0) && (LastMousePosition.x >= r.z - 15) && (LastMousePosition.x <= r.z) && (LastMousePosition.y >= r.w - 15) && (LastMousePosition.y <= r.w));
		if ((isInside || wasInside)&& MouseButtons[0]) {
			if (LastMouseButtons[0]) {
				ivec2 offset = MousePosition - LastMousePosition;
				r.z += offset.x;
				r.w += offset.y;
			}
		}
	}
	++windowID;
	return (*flags & GWF_VISIBLE);
}

bool GUI::WindowEnd() {
	ParentWindowRectangle = 0;
	currentLayout.type = Layout::GRID;
	currentLayout.split.vertical = true;
	currentLayout.split.weight = 0.5f;
}

void GUI::Label(Image* output, const char* text, const ivec4* nbounds, const unsigned int flags) {
	const ivec4 absoluteBounds = GUILayoutGetBounds(nbounds) + ivec4(ParentWindowRectangle.x, ParentWindowRectangle.y, ParentWindowRectangle.x, ParentWindowRectangle.y);
	if (flags & GLF_BACKGROUND) {
		GUIDrawQuad(output, absoluteBounds, RawDefaultColor2);
	}
	DrawCenteredText(output, absoluteBounds, text, TextColor, TextSize);
	if (flags & GLF_OUTLINE) {
		GUIDrawOutline(output, absoluteBounds, true);
	}
}

const unsigned char Icons[] = {
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 0, 0, 1, 0,
	0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 0, 0,
	0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0,
	0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0,
	0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0,
	0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0,
	0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0,
	0, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 1, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0,
	0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0,
	0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0,
	0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0,
	0, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 0,
	0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0,
	0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
	0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
	0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
	0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0,
	0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0,
	0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0,
	0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0,
	0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0,
	0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0,
	0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0,
	0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0,
	0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0,
	0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0,
	0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0,
	0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0,
	0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0,
	0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0,
	0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0,
	0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0,
	0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0,
	0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0,
	0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0,
	0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0,
	0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0,
	0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0,
	0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0,
	0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0,
	0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0,
	0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0,
	0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0,
	0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0,
	0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 1, 0, 1, 1, 0, 1, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 1, 0, 1, 1, 0, 1, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0,
	0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0,
	0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
	0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0,
	0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0,
	0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
	0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0,
	0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
};

bool GUI::Button(Image* output, const char* text, const ubvec4& color, const ivec4* nbounds) {
	const ivec4 TextPressedOffset(-2, 2, -2, 2);
	const ivec4 absoluteBounds = GUILayoutGetBounds(nbounds) + ivec4(ParentWindowRectangle.x, ParentWindowRectangle.y, ParentWindowRectangle.x, ParentWindowRectangle.y);
	const bool isInside = ((draggedID == 0) && IsInside(absoluteBounds, MousePosition));
	const bool pressed = isInside && MouseButtons[0];
	GUIDrawQuad(output, absoluteBounds, isInside ? RawDefaultColor2 : color);
	DrawCenteredText(output, absoluteBounds + TextPressedOffset * pressed, text, ubvec4(255, 255, 255, 255) - color, TextSize * 3);
	GUIDrawOutline(output, absoluteBounds, pressed);
	return (isInside && !MouseButtons[0] && LastMouseButtons[0]);
}

bool GUI::Button(Image* output, const char*, const unsigned int spriteIndex, const ivec4* nbounds) {
	const ivec4 TextPressedOffset(-2, 2, -2, 2);
	const ivec4 absoluteBounds = GUILayoutGetBounds(nbounds) + ivec4(ParentWindowRectangle.x, ParentWindowRectangle.y, ParentWindowRectangle.x, ParentWindowRectangle.y);
	const bool isInside = ((draggedID == 0) && IsInside(absoluteBounds, MousePosition));
	const bool pressed = isInside && MouseButtons[0];
	GUIDrawQuad(output, absoluteBounds, isInside ? RawDefaultColor2 : RawDefaultColor);
	
	const unsigned int spriteOffset = spriteIndex * 16 * 16;
	int minSize = std::min(absoluteBounds.z - absoluteBounds.x, absoluteBounds.w - absoluteBounds.y);
	const int pixelSize = minSize / 16;
	for (unsigned int y = 0; y < 16; ++ y) {
		for (unsigned int x = 0; x < 16; ++x) {
			unsigned char sourcePixel = Icons[spriteOffset + y * 16 + x];
			if (sourcePixel == 1) {
				DrawPoint(output, uvec2(absoluteBounds.x + 1 + x * pixelSize - 2 * pressed, absoluteBounds.y + 1 + y * pixelSize + 2 * pressed), ubvec4(0, 0, 0, 255), pixelSize);
			}
		}
	}
	GUIDrawOutline(output, absoluteBounds, pressed);
	return (isInside && !MouseButtons[0] && LastMouseButtons[0]);
}

bool GUI::Button(Image* output, const char* text, const ivec4* nbounds) {
	const ivec4 TextPressedOffset(-2, 2, -2, 2);
	const ivec4 absoluteBounds = GUILayoutGetBounds(nbounds) + ivec4(ParentWindowRectangle.x, ParentWindowRectangle.y, ParentWindowRectangle.x, ParentWindowRectangle.y);
	const bool isInside = ((draggedID == 0) && IsInside(absoluteBounds, MousePosition));
	const bool pressed = isInside && MouseButtons[0];
	GUIDrawQuad(output, absoluteBounds, isInside ? RawDefaultColor2 : RawDefaultColor);
	DrawCenteredText(output, absoluteBounds + TextPressedOffset * pressed, text, TextColor, TextSize);
	GUIDrawOutline(output, absoluteBounds, pressed);
	return (isInside && !MouseButtons[0] && LastMouseButtons[0]);
}

bool GUI::Spinner(Image* output, int& value, const ivec4* nbounds) {
	bool ans = false;
	int BKPGUILayoutElementIndex = currentLayout.elementIndex + 1;
	ivec4 bounds = GUILayoutGetBounds(nbounds);
	const ivec4 rect = bounds + ivec4(ParentWindowRectangle.x, ParentWindowRectangle.y, ParentWindowRectangle.x, ParentWindowRectangle.y);

	const unsigned int buttonWidth = std::min(bounds.z - bounds.x, WindowTitlebarHeight);
	const int centerX = (bounds.z - bounds.x) / 2;
	char tmp[16];
	snprintf(tmp, sizeof(tmp), "%d", value);
	GUIDrawQuad(output, ivec4(rect.x, rect.y, rect.z, rect.w), RawDefaultColor2);
	DrawCenteredText(output, rect, tmp, TextColor, TextSize);
	if (Button(output, "-", ivec4(bounds.x, bounds.y, bounds.x + buttonWidth, bounds.w))) {
		value--;
		ans = true;
	}
	if (Button(output, "+", ivec4(bounds.z - buttonWidth, bounds.y, bounds.z, bounds.w))) {
		value++;
		ans = true;
	}
	currentLayout.elementIndex = BKPGUILayoutElementIndex;
	return ans;
}

bool GUI::Checkbox(Image* output, bool &checked, const ivec4* nbounds) {
	ivec4 rect = GUILayoutGetBounds(nbounds) + ivec4(ParentWindowRectangle.x, ParentWindowRectangle.y, ParentWindowRectangle.x, ParentWindowRectangle.y);
	int centerX = (rect.z - rect.x) / 2 - 7;
	int centerY = (rect.w - rect.y) / 2 - 7;
	// Keep square shape
	const int width  = rect.z - rect.x;
	const int height = rect.w - rect.y;
	int min = width < height ? width : height;
	min = min > 14 ? 14 : min;
	rect.z = rect.x + min;
	rect.w = rect.y + min;
	
	rect.x += centerX;
	rect.z += centerX;
	rect.y += centerY;
	rect.w += centerY;

	GUIDrawQuad(output, rect, RawDefaultColor2);
	if (checked) {
		GUIDrawQuad(output, rect + ivec4(3.0f, 3.0f,-3.0f,-3.0f), RawDarkColor);
	}
	GUIDrawOutline(output, rect, true);
	if ((draggedID == 0) && IsInside(rect, MousePosition) && !MouseButtons[0] && LastMouseButtons[0]) {
		checked = !checked;
		return true;
	}
	return false;
}

bool GUI::Palette(Image* output, ubvec4& color, const ivec4* nbounds) {
	static const unsigned int ColorCountX = 8;
	static const unsigned int ColorCountY = 8;
	static const vec4 primeColors[] = {
		vec4(1.0f, 0.0f, 0.0f, 1.0f), // RED
		vec4(1.0f, 1.0f, 0.0f, 1.0f), // YELLOW
		vec4(0.0f, 1.0f, 0.0f, 1.0f), // GREEN
		vec4(0.0f, 1.0f, 1.0f, 1.0f), // CYAN
		vec4(0.0f, 0.0f, 1.0f, 1.0f), // BLUE
		vec4(1.0f, 0.0f, 1.0f, 1.0f), // VIOLETE
		vec4(1.0f, 0.0f, 0.0f, 1.0f), // RED
	};
	
	const ivec4 rect = GUILayoutGetBounds(nbounds) + ivec4(ParentWindowRectangle.x, ParentWindowRectangle.y, ParentWindowRectangle.x, ParentWindowRectangle.y);
	const unsigned int width = rect.z - rect.x;
	const unsigned int height = rect.w - rect.y; //width;
	const unsigned int primeColorCount = (sizeof(primeColors) / sizeof(primeColors[0])) - 1;
	const unsigned int colorTileSizeX = (width  / ColorCountX / primeColorCount) * 1;
	const unsigned int colorTileSizeY = (height / ColorCountY / primeColorCount) * 3;
	const unsigned int offsetX = (width  - colorTileSizeX * ColorCountX * primeColorCount) / 2;
	const unsigned int offsetY = (height - colorTileSizeY * ColorCountY * 2) / 2;
	
	const int colorValues[4] = { color.x, color.y, color.z, color.w };

	for (unsigned int y = 0; y < ColorCountY * 2; ++y) {
		const int colorIndexY = y / ColorCountY;
		const float procY = (float)(y %ColorCountY) / (float)(ColorCountY);
		const float iprocY = 1.0f - procY;
		for (unsigned int x = 0; x < ColorCountX * primeColorCount; ++x) {
			const int colorIndexX = x / ColorCountX;
			float procX = (float)(x % ColorCountX)/ (float)(ColorCountX);
			const float iprocX = 1.0f - procX;
			const vec4 tmpca[] = {
				vec4(1.0f, 1.0f, 1.0f, 1.0f),
				primeColors[colorIndexX] * iprocX + primeColors[colorIndexX + 1] * procX,
				vec4(0.0f, 0.0f, 0.0f, 1.0f)
			};
			vec4 k = tmpca[colorIndexY] * iprocY + tmpca[colorIndexY + 1] * procY;
			GUIDrawQuad(output,
				ivec4(rect.x + offsetX + x * colorTileSizeX, 
					  rect.y + offsetY + y * colorTileSizeY, 
					  rect.x + offsetX + (x + 1) * colorTileSizeX, 
					  rect.y + offsetY + (y + 1) * colorTileSizeY),
				ubvec4(k.x * 255.0f, k.y * 255.0f, k.z * 255.0f, k.w * 255.0f));
		}
	}
	
	const ivec4 paletteRect(rect.x + offsetX, rect.y + offsetY, rect.x + offsetX + ColorCountX * primeColorCount * colorTileSizeX, rect.y + offsetY + ColorCountY * 2 * colorTileSizeY);
	const bool isInside = ((draggedID == 0) && IsInside(paletteRect, MousePosition));
	const bool clicked = isInside && MouseButtons[0];
	const ivec2 relativeMousePosition = MousePosition - ivec2(paletteRect.x, paletteRect.y);

	if (isInside && MouseButtons[0] == false && LastMouseButtons[0] == true) {
		const int colorIndexX = relativeMousePosition.x / (ColorCountX * colorTileSizeX);
		const int colorIndexY = relativeMousePosition.y / (ColorCountY * colorTileSizeY);
		const int x = (relativeMousePosition.x / colorTileSizeX) % ColorCountX;
		const int y = (relativeMousePosition.y / colorTileSizeY) % ColorCountY;
		const float procX = (float)(x) / (float)(ColorCountX - 1);
		const float procY = (float)(y) / (float)(ColorCountY - 1);
		const vec4 tmpca[] = {
			vec4(1.0f, 1.0f, 1.0f, 1.0f),
			primeColors[colorIndexX] * (1.0f - procX) + primeColors[colorIndexX + 1] * procX,
			vec4(0.0f, 0.0f, 0.0f, 1.0f)
		};
		const vec4 outputColor = tmpca[colorIndexY] * (1.0f - procY) + tmpca[colorIndexY + 1] * procY;
		color = ubvec4(outputColor.x * 255, outputColor.y * 255, outputColor.z * 255, outputColor.w * 255);
		return true;
	}
	return false;
}

bool GUI::ColorSelector(Image* output, ivec4& r, ubvec4& color, unsigned int* flags) {
	if (WindowBegin(output, r, "Palette", flags)) {
		PushLayout();
		SetGridLayout(1, 2);
		
		// Top half
		if (Palette(output, color)) {
			// return true;
		}
		
		// Bottom Half
		PushLayout();
		SetGridLayout(4, 4);
		int colorValues[4] = { color.x, color.y, color.z, color.w };
		const char* text[] = {"R", "G", "B"};
		for (unsigned int index = 0; index < 3; ++index) {
			currentLayout.elementIndex = index * currentLayout.grid.count.x;
			SetGridSize(1);
			Label(output, text[index]);
			SetGridSize(3);
			if (Spinner(output, colorValues[index])) {
				color.x = colorValues[0];
				color.y = colorValues[1];
				color.z = colorValues[2];
				color.w = colorValues[3];
			}
		}
		SetGridSize(4);
		currentLayout.elementIndex = 3 * currentLayout.grid.count.x;
		
		PushLayout();
		SetGridLayout(3, 1);
		SetGridSize(1);
		currentLayout.elementIndex += 1;
		if (Button(output, "OK")) {
			if (flags) {
				*flags = *flags ^ GWF_VISIBLE;
			}
			return true;
		}
		if (Button(output, "CANCEL")) {
			if (flags) {
				*flags = *flags ^ GWF_VISIBLE;
			}
		}
		PopLayout();
		
		PopLayout();
		
		PopLayout();
	} 
	WindowEnd();
	return false;
}

bool GUI::ListBox(Image* output, int& selected, int& offset, const char** items, const unsigned int count, const ivec4* relativeBounds) {
	const ivec4 absoluteBounds = GUILayoutGetBounds(relativeBounds) + ivec4(ParentWindowRectangle.x, ParentWindowRectangle.y, ParentWindowRectangle.x, ParentWindowRectangle.y);
	const unsigned int width = absoluteBounds.z - absoluteBounds.x;
	const unsigned int height = absoluteBounds.w - absoluteBounds.y;
	const unsigned int itemHeight = 7 * TextSize;
	const unsigned int visibleItemCount = height / itemHeight;
	const unsigned int minCount = std::min(visibleItemCount, count);
	bool ans = false;
	int i = offset / itemHeight;
	GUIDrawQuad(output, absoluteBounds, RawDefaultColor2);
	GUIDrawOutline(output, absoluteBounds, true);	
	if (IsInside(absoluteBounds, MousePosition) && MouseButtons[0] == false && LastMouseButtons[0] == true) {
		int k = i + (MousePosition.y - absoluteBounds.y) / visibleItemCount;
		if (k >= 0 && k <= minCount) {
			selected = k;
			ans = true;
		}
	}

	for (unsigned int index = i; index < i + minCount; ++index) {
		int vOffset = index * itemHeight - offset;
		if (vOffset < 0) continue;
		const ivec4 itemBounds(absoluteBounds.x, absoluteBounds.y + vOffset, absoluteBounds.z, absoluteBounds.y + vOffset  +itemHeight);
		if (selected == index && selected >= 0 && selected < visibleItemCount) {
			GUIDrawQuad(output, itemBounds, ubvec4(  0,  0, 255, 255));
		}
		DrawCenteredText(output, itemBounds, items[index], TextColor, TextSize);
	}
	
	float proc = (float)visibleItemCount / (float)count;
	int max = (float)(height - 2 * WindowTitlebarHeight - 1) * (1.0f - proc);
	if (max > 0) {
		if (Scrollbar(output, offset, max, true, ivec4(width - WindowTitlebarHeight - 1, 0, width - 1, height))) {
		}
	}
	
	return ans;
}

bool GUI::Scrollbar(Image* output, int& offset, const unsigned int max, bool vertical, const ivec4* relativeBounds) {
	bool ans = false;
	int BKPGUILayoutElementIndex = currentLayout.elementIndex + 1;
	ivec4 bounds = GUILayoutGetBounds(relativeBounds);
	const ivec4 absoluteBounds = bounds + ivec4(ParentWindowRectangle.x, ParentWindowRectangle.y, ParentWindowRectangle.x, ParentWindowRectangle.y);

	GUIDrawQuad(output, absoluteBounds, RawDefaultColor2);

	const unsigned int buttonWidth  = std::min(bounds.z - bounds.x, WindowTitlebarHeight);
	const unsigned int buttonHeight = std::min(bounds.w - bounds.y, WindowTitlebarHeight);
	
	const unsigned int barWidth  = bounds.z - bounds.x - buttonWidth  * 2 - 1 - max;
	const unsigned int totalHeight = bounds.w - bounds.y - buttonHeight * 2 - 1;
	const unsigned int barHeight = bounds.w - bounds.y - buttonHeight * 2 - 1 - max;
	ivec4 barBounds;
	if (vertical) {
		barBounds = ivec4(absoluteBounds.x, absoluteBounds.y + buttonHeight + offset + 1, absoluteBounds.z, absoluteBounds.y + buttonHeight + offset + barHeight);
	} else {
		barBounds = ivec4(offset + absoluteBounds.x + buttonWidth  + 1, absoluteBounds.y, offset + absoluteBounds.x + buttonWidth  + barWidth , absoluteBounds.w);
	}
	const bool isInside = IsInside(barBounds, MousePosition);
	GUIDrawQuad(output, barBounds, isInside ? RawDefaultColor2 : RawDefaultColor);
	GUIDrawOutline(output, barBounds, false);

	if (vertical) {
		if (Button(output, "-", ivec4(bounds.x, bounds.y, bounds.z, bounds.y + buttonHeight))) {
			printf("totalHeight / max = %f\n", (float)totalHeight / (float)max);
			offset -= ((float)totalHeight / (float)max + 0.5f);
			if (offset < 0) offset = 0;
			ans = true;
		}
		if (Button(output, "+", ivec4(bounds.x, bounds.w - buttonHeight, bounds.z, bounds.w - 1))) {
			//offset++;
			offset += totalHeight / max;
			if (offset > max) offset = max;
			ans = true;
		}
	} else {
		if (Button(output, "-", ivec4(bounds.x, bounds.y, bounds.x + buttonWidth, bounds.w))) {
			offset--;
			if (offset < 0) offset = 0;
			ans = true;
		}
		if (Button(output, "+", ivec4(bounds.z - buttonWidth, bounds.y, bounds.z, bounds.w))) {
			offset++;
			if (offset > max) offset = max;
			ans = true;
		}
	}
	currentLayout.elementIndex = BKPGUILayoutElementIndex;
	return ans;
}

int GUI::TabbedPanel(Image* output, const char** names, const unsigned int count, int& selected, const ivec4* relativeRect) {
	const ivec4 absoluteRectangle = GUILayoutGetBounds(relativeRect) + ivec4(ParentWindowRectangle.x, ParentWindowRectangle.y, ParentWindowRectangle.x, ParentWindowRectangle.y);
	const unsigned int tabWidth = (absoluteRectangle.z - absoluteRectangle.x) / count;
	const unsigned int tabHeight = std::min(absoluteRectangle.w - absoluteRectangle.y, WindowTitlebarHeight);
	for (unsigned int index = 0; index < count; ++index) {
		const ivec4 rect(absoluteRectangle.x + index * tabWidth, absoluteRectangle.y, absoluteRectangle.x + (index + 1) * tabWidth, absoluteRectangle.y + tabHeight);
		const bool isInside = ((draggedID == 0) && IsInside(rect, MousePosition));
		const bool pressed = (isInside && MouseButtons[0]) || (index == selected);
		GUIDrawQuad(output, rect, isInside ? RawDefaultColor2 : RawDefaultColor);
		DrawCenteredText(output, rect + (pressed ? 2 : 1), names[index], TextColor, TextSize);
		GUIDrawOutline(output, rect, pressed);
		if (isInside && !MouseButtons[0] && LastMouseButtons[0]) {
			selected = index;
		}
	}
	ParentWindowRectangle = absoluteRectangle + ivec4(0, tabHeight + 1, 0, 0);
	SetGridLayout(1, 1);
	// GUIDrawQuad(output, ParentWindowRectangle,  RawDefaultColor);
	GUIDrawOutline(output, ParentWindowRectangle);
	return selected;
}

bool GUI::SplitPanel(Image* output, float& weight, bool vertical, const ivec4* relativeRect) {
	const ivec4 absoluteRectangle = GUILayoutGetBounds(relativeRect) + ivec4(ParentWindowRectangle.x, ParentWindowRectangle.y, ParentWindowRectangle.x, ParentWindowRectangle.y);
	const unsigned int width  = absoluteRectangle.z - absoluteRectangle.x;
	const unsigned int height = absoluteRectangle.w - absoluteRectangle.y;
	ivec4 separatorBounds;

	ParentWindowRectangle = absoluteRectangle;
	SetSplitLayout(vertical, weight);

	if (vertical) {
		const unsigned int k = (float)height * weight;
		separatorBounds = ivec4(absoluteRectangle.x, absoluteRectangle.y + k, absoluteRectangle.z, absoluteRectangle.y + k + Separator);
		for (unsigned int index = 0; index < 3; ++index) {
			output->drawLine(ivec2(separatorBounds.x, separatorBounds.y + index * 3 + 0), ivec2(separatorBounds.z, separatorBounds.y + index * 3 + 0), RawDarkColor);
			output->drawLine(ivec2(separatorBounds.x, separatorBounds.y + index * 3 + 1), ivec2(separatorBounds.z, separatorBounds.y + index * 3 + 1), RawLightColor);
		}
	} else {
		const unsigned int k = (float)width * weight;
		separatorBounds = ivec4(absoluteRectangle.x + k, absoluteRectangle.y, absoluteRectangle.x + k + Separator, absoluteRectangle.w);
		for (unsigned int index = 0; index < 3; ++index) {
			output->drawLine(ivec2(separatorBounds.x + index * 3 + 0, separatorBounds.y), ivec2(separatorBounds.x + index * 3 + 0, separatorBounds.w), RawLightColor);
			output->drawLine(ivec2(separatorBounds.x + index * 3 + 1, separatorBounds.y), ivec2(separatorBounds.x + index * 3 + 1, separatorBounds.w), RawDarkColor);
		}
	}
	if ((((draggedID == 0) && IsInside(separatorBounds, MousePosition)) || ((draggedID == 0) && IsInside(separatorBounds, LastMousePosition))) && MouseButtons[0]) {
		if (LastMouseButtons[0]) {
			if (vertical) {
				weight = (float)(MousePosition.y - 4 - absoluteRectangle.y) / (float)height;
			} else {
				weight = (float)(MousePosition.x + 0 - absoluteRectangle.x) / (float)width;
			}
			weight = std::min(std::max(weight, 0.0f), 1.0f);
			return true;
		}
	}
	return false;
}