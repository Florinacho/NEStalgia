#ifndef __IMAGE_H__
#define __IMAGE_H__

#include "Vector.h"
#include <stdio.h>
#define IMAGE_CHECK_BOUNDRY

struct __attribute__((packed)) Pixel8 {
	unsigned int red : 3;
	unsigned int green : 3;
	unsigned int blue : 2;
};

struct __attribute__((packed)) Pixel16 {
	unsigned int red : 5;
	unsigned int green : 6;
	unsigned int blue : 5;
};
class Image {
public:
	union {
		unsigned char* data;
		unsigned int *udata32;
		float* fdata;
	};
	Vector2u size;
	int pixelFormat;


	// Make the copy operation illegal
	Image(const Image& other){}
	Image& operator = (const Image& other) {return *this;}
	
public:
	/*************************************************************************/
	/* Updates the coordinates based on the wrapping member.                 */
	/* Return true if the coordinates should be discarded(outside bounds).   */
	/*************************************************************************/
	inline bool updateCoordinates(int& x, int& y) const {
		switch (wrapping.x) {
		case Image::EWT_REPEAT :
			if (x <            0) x += size.x;
			if (x >= (int)size.x) x -= size.x;
			break;
		case Image::EWT_MIRROR : return true; // TODO test
			if (x <            0) x = -x;
			if (x >= (int)size.x) x = size.x - 1 - (x - size.x);
			break;
		case Image::EWT_CLAMP :
			if (x <            0) x = 0;
			if (x >= (int)size.x) x = size.x - 1;
			break;
		case Image::EWT_DISCARD :
			if ((x < 0) || (x >= (int)size.x)) {
				return true;
			}
		}
				
		switch (wrapping.y) {
		case Image::EWT_REPEAT :
			if (y <            0) y += size.y;
			if (y >= (int)size.y) y -= size.y;
			break;
		case Image::EWT_MIRROR : return true; // TODO test
			if (y <            0) y = -y;
			if (y >= (int)size.y) y = size.y - 1 - (y - size.y);
			break;
		case Image::EWT_CLAMP :
			if (y <            0) y = 0;
			if (y >= (int)size.y) y = size.y - 1;
			break;
		case Image::EWT_DISCARD :
			if ((y < 0) || (y >= (int)size.y)) {
				return true;
			}
		}
				
		return false;
	}
	
	Vector2ub wrapping;
	
	static inline unsigned int PackPixel32(const unsigned char r, const unsigned char g, const unsigned int b, const unsigned char a) {
		return ((a << 24) | (r << 16) | (g << 8) | b);
	}
	
	enum PixelFormat {
		EPF_L8,		// 8,  Luminance
		EPF_R5G6B5,	// 16, 
		EPF_R8G8B8,	// 24, Red + Green + Blue
		EPF_R8G8B8A8,	// 32, Red + Green + Blue + Alpha

		EPF_DEPTH,
	};
	
	enum WrappingType {
		EWT_REPEAT,	// Default
		EWT_MIRROR,
		EWT_CLAMP,
		EWT_DISCARD
	};

	Image();

	virtual ~Image();
	
	void create(const Vector2u& size, int pixelFormat);
	
	void setData(unsigned char* data, const Vector2u& size, int pixelFormat);
	
	const unsigned char* getData() const;

	virtual unsigned int getDataLength() const;

	Vector2u getSize() const;
	
	virtual unsigned int getLineStride() const;

	Image::PixelFormat getPixelFormat() const;

	unsigned int getPixelSize() const;

	bool hasAlpha() const;

	bool load(const char* filename);

	void flipVertical();

	void flipHorizontal();
	
	void clear();

	void destroy();
	
	virtual void setPixel(const int x, const int y, const Vector4f& value);
	
	virtual Vector4f getPixel(int x, int y) const;
	
	virtual Vector4f getPixel(const Vector2u& uv) const;

	Vector4f sample2D(const Vector2f& uv) const;
	
	inline virtual void setRawPixel(int x, int y, const Vector4ub& value) {
		union {
			Pixel16 pixel16;
			struct {
				unsigned char ub0;
				unsigned char ub1;
			} raw;
		};
#if defined (IMAGE_CHECK_BOUNDRY)
		if (updateCoordinates(x, y)) {
			return;
		}
#endif // IMAGE_CHECK_BOUNDRY
		const unsigned int pixelIndex = y * getLineStride() + x * getPixelSize();
		
		switch (pixelFormat) {
		case Image::EPF_L8 :
			data[pixelIndex + 0] = value.x;
			break;
		case Image::EPF_R5G6B5 :
			pixel16.red = (unsigned char)(value.z);
			pixel16.green = (unsigned char)(value.y);
			pixel16.blue = (unsigned char)(value.x);

			data[pixelIndex + 0] = raw.ub0;
			data[pixelIndex + 1] = raw.ub1;
			break;
		case Image::EPF_R8G8B8 :
			data[pixelIndex + 0] = value.z;
			data[pixelIndex + 1] = value.y;
			data[pixelIndex + 2] = value.x;
			break;
		case Image::EPF_R8G8B8A8 :
			data[pixelIndex + 0] = value.z;
			data[pixelIndex + 1] = value.y;
			data[pixelIndex + 2] = value.x;
			data[pixelIndex + 3] = value.w;
			break;	
		case Image::EPF_DEPTH :
			break;
		}
	}

	inline virtual void setRawPixel(int x, int y, const unsigned int value) {
#if defined (IMAGE_CHECK_BOUNDRY)
		if (updateCoordinates(x, y)) {
			return;
		}
#endif // IMAGE_CHECK_BOUNDRY
		unsigned int pixelIndex = pixelIndex = y * size.x + x;
		switch (pixelFormat) {
		case Image::EPF_L8 :
//			data[pixelIndex + 0] = value.x;
			break;
		case Image::EPF_R5G6B5 :
//			pixel16.red = (unsigned char)(value.z);
//			pixel16.green = (unsigned char)(value.y);
//			pixel16.blue = (unsigned char)(value.x);

//			data[pixelIndex + 0] = raw.ub0;
//			data[pixelIndex + 1] = raw.ub1;
			break;
		case Image::EPF_R8G8B8 :
			pixelIndex *= getPixelSize();
			data[pixelIndex + 0] = (value >>  0) & 0xFF;
			data[pixelIndex + 1] = (value >>  8) & 0xFF;
			data[pixelIndex + 2] = (value >> 16) & 0xFF;
			break;
		case Image::EPF_R8G8B8A8 :
			udata32[pixelIndex] = value;
			break;	
		case Image::EPF_DEPTH :
			break;
		}
	}

	inline unsigned int getRawPixel2(int x, int y) const {
		const unsigned int pixelIndex = (y * size.x + x);// * getPixelSize();
		unsigned int ans = 0;
#if defined (IMAGE_CHECK_BOUNDRY)
		if (updateCoordinates(x, y)) {
			return 0;
		}
#endif // IMAGE_CHECK_BOUNDRY
		switch (pixelFormat) {
/*			
		case Image::EPF_L8 :
			ans.x = data[pixelIndex + 0];
			ans.y = ans.x;
			ans.z = ans.x;
			ans.w = 255;
			break;
		case Image::EPF_R5G6B5 :
			raw.ub0 = data[pixelIndex + 0];
			raw.ub1 = data[pixelIndex + 1];

			ans.x = pixel16.red;
			ans.y = pixel16.green;
			ans.z = pixel16.blue;
			ans.w = 255;
			break;
		case Image::EPF_R8G8B8 :
			ans.x = data[pixelIndex + 2];
			ans.y = data[pixelIndex + 1];
			ans.z = data[pixelIndex + 0];
			ans.w = 255;
			break;
*/
		case Image::EPF_R8G8B8A8 :
//			ans.z = data[pixelIndex + 0];
//			ans.y = data[pixelIndex + 1];
//			ans.x = data[pixelIndex + 2];
//			ans.w = data[pixelIndex + 3];
			ans = udata32[pixelIndex];
			break;
		case Image::EPF_DEPTH :
			break;
		}
		
		return ans;
	}
		
	virtual Vector4ub getRawPixel(int x, int y) const;
	
	Vector4ub sampleRaw2D(const Vector2f& uv) const;
	
	void drawLine(const ivec2& begin, const ubvec4& beginColor, const ivec2& end, const ubvec4& endColor);
	
	void drawLine(const ivec2& begin, const ivec2& end, const ubvec4& color);
	
	void drawRectangle(const ivec4& rectangle, const ubvec4& color);
	
	void drawFilledRectangle(const ivec4& rectangle, const ubvec4& color);
#if 0
	void drawCircle(const Vector2f& center, float radius, const ubvec4& color);
	
	void drawFilledCircle(const Vector2f& center, float radius, const Vector4f& color);
#endif
	void blit(const Image* image, const uvec2& position);
};

#endif // __IMAGE_H__
