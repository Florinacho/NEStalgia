#ifndef __GUI_HPP__
#define __GUI_HPP__

#include "Vector.h"
#include "Event.h"

class Image;

const unsigned int GWF_VISIBLE = 1 << 0;
const unsigned int GWF_TITLEBAR = 1 << 1;
const unsigned int GWF_TITLE = 1 << 2;
const unsigned int GWF_CLOSE = 1 << 3;
const unsigned int GWF_MOVE = 1 << 4;
const unsigned int GWF_SIZE = 1 << 5;

const unsigned int GLF_BACKGROUND = 1 << 0;
const unsigned int GLF_OUTLINE = 1 << 1;
const unsigned int GLF_CENTERED = 1 << 2;

const unsigned int GWF_DECORATION = GWF_TITLEBAR | GWF_TITLE | GWF_CLOSE;
const unsigned int GWF_DEFAULT = GWF_VISIBLE | GWF_DECORATION | GWF_MOVE;

struct GUI {
	static void SetViewport(const ivec4& bounds);
	
	static void PushLayout();
	static void PopLayout();
	static void SetGridSize(int value);
	static void SetGridLayout(int x, int y);
	static void SetSplitLayout(bool vertical, float weight);
	
	static void OnEvent(const Event& event);
	static void PostEvent();

	static bool WindowBegin(Image* output, ivec4& r, const char* title = 0, unsigned int* flags = 0);
	static bool WindowEnd();
	static int  TabbedPanel(Image* output, const char** names, const unsigned int count, int& selected, const ivec4* rect = 0);
	static bool SplitPanel(Image* output, float& weight, bool vertical, const ivec4* rect = 0);
	
	static void Label(Image* output, const char* text, const ivec4* r = 0, const unsigned int flags = 0);
	static bool Button(Image* output, const char* text, const ivec4* r = 0);
	static bool Button(Image* output, const char* text, const ubvec4& color, const ivec4* r = 0);
	static bool Button(Image* output, const char*, const unsigned int spriteIndex, const ivec4* r = 0);
	static bool Spinner(Image* output, int& value, const ivec4* r = 0);
	static bool Checkbox(Image* output, bool &checked, const ivec4* r = 0);
	static bool Palette(Image* output, ubvec4& color, const ivec4* r = 0);
	static bool ColorSelector(Image* output, ivec4& r, ubvec4& color, unsigned int* flags = 0);
	static bool ListBox(Image* output, int& selected, int& offset, const char** items, const unsigned int count, const ivec4* relativeBounds = 0);
	static bool Scrollbar(Image* output, int& offset, const unsigned int max, bool vertical, const ivec4* relativeBounds = 0);

	static inline void Label(Image* output, const char* text, const ivec4& r, const unsigned int flags = 0) {
		Label(output, text, &r, flags);
	}	
	static inline bool Button(Image* output, const char* text, const ivec4& r) {
		return Button(output, text, &r);
	}
	static inline bool Spinner(Image* output, int& value, const ivec4& r) {
		return Spinner(output, value, &r);
	}
	static inline bool Checkbox(Image* output, bool &checked, const ivec4& r) {
		return Checkbox(output, checked, &r);
	}
	static inline int TabbedPanel(Image* output, const ivec4& rect, const char** names, const unsigned int count, int& selected) {
		return TabbedPanel(output, names, count, selected, &rect);
	}
	static inline bool SplitPanel(Image* output, float& weight, bool vertical, const ivec4& rect) {
		return SplitPanel(output, weight, vertical, &rect);
	}
	static inline bool Palette(Image* output, ubvec4& color, const ivec4& r) {
		return Palette(output, color, &r);
	}
	static inline bool ListBox(Image* output, int& selected, int& offset, const char** items, const unsigned int count, const ivec4& relativeBounds) {
		return ListBox(output, selected, offset, items, count, &relativeBounds);
	}
	static inline bool Scrollbar(Image* output, int& offset, const unsigned int max, bool vertical, const ivec4& relativeBounds) {
		return Scrollbar(output, offset, max, vertical, &relativeBounds);
	}
};

#endif // __GUI_HPP__