#include <stdio.h>
#include <string.h>
#include <algorithm>

#include "Image.h"

namespace tga {

enum ImageType {
	NO_IMAGE_DATA = 0,
	COLOR_MAP = 1,			//UNCOMPRESSED
	TRUE_COLOR = 2,			//UNCOMPRESSED
	GRAYSCALE = 3,			//UNCOMPRESSED
	RLE_COLOR_MAP = 9,		//COMPRESSED
	RLE_TRUE_COLOR = 10,		//COMPRESSED
	RLE_GRAYSCALE = 11		//COMPRESSED
};

#pragma pack(push, 1)
struct Header {
	unsigned char length;
	unsigned char colorMapType;
	unsigned char compression;
	unsigned short colorMapOffset;
	unsigned short colorMapLength;
	unsigned char colorMapDepth;
	unsigned short xOrigin;
	unsigned short yOrigin;
	unsigned short width;
	unsigned short height;
	unsigned char depth;
	unsigned char descriptor;
};

struct Footer {
	unsigned int extensionOffset;
	unsigned int developerAreaOffset;
	char signature[18];
};

#pragma pack(pop)
static const unsigned int HeaderSize = sizeof(Header);
static const unsigned int FooterSize = sizeof(Footer);
static const char* FooterSignature = "TRUEVISION-XFILE.";
static const unsigned int FooterSignatureLength = 18;

} // namespace tga


unsigned int Image::getLineStride() const {
	return size.x * getPixelSize();
}

Image::Image() {
	data = NULL;
	size.x = 0;
	size.y = 0;
	pixelFormat = Image::EPF_L8;
	wrapping = Image::EWT_DISCARD;
}

Image::~Image() {
	clear();
}

void Image::create(const Vector2u& insize, int inpixelFormat) {
	clear();
	
	size = insize;
	pixelFormat = inpixelFormat;
	
	const unsigned int pixelCount = size.x * size.y;
	const unsigned int pixelSize = getPixelSize();
	const unsigned int totalPixelSize = pixelCount * pixelSize;

	data = new unsigned char[totalPixelSize];
	memset(data, 0, totalPixelSize);
}

void Image::setData(unsigned char* newData, const Vector2u& newSize, int newPixelFormat) {
	data = newData;
	size = newSize;
	pixelFormat = newPixelFormat;
}

const unsigned char* Image::getData() const {
	return data;
}

unsigned int Image::getDataLength() const {
	return size.x * size.y * getPixelSize();
}

Vector2u Image::getSize() const {
	return size;
}

Image::PixelFormat Image::getPixelFormat() const {
	return (Image::PixelFormat)pixelFormat;
}

unsigned int Image::getPixelSize() const {
	switch (pixelFormat) {
	case Image::EPF_L8 :
		return 1;
	case Image::EPF_R5G6B5 :
		return 2;
	case Image::EPF_R8G8B8 :
		return 3;
	case Image::EPF_R8G8B8A8 :
		return 4;
	case Image::EPF_DEPTH :
		return sizeof(float);
	}
	return 0;
}

bool Image::hasAlpha() const {
	switch (pixelFormat) {
	case Image::EPF_R8G8B8A8 :
		return true;
	}
	return false;
}

bool Image::load(const char* filename) {
	clear();

	FILE* file = fopen(filename, "rb");
	if (file == NULL) {
		printf("Image::load(%s) error! Cannot open file.\n", filename);
		return false;
	}

	tga::Header header;
	if (fread(&header, tga::HeaderSize, 1, file) != 1) {
		printf("Image::load(%s) error! Cannot read TGA header.\n", filename);
		fclose(file);
		return false;
	}

	const unsigned int pixelCount = header.width * header.height;
	const unsigned int pixelSize = header.depth / 8;
	const unsigned int totalPixelsSize = pixelCount * pixelSize;
	unsigned char* newdata = new unsigned char[totalPixelsSize];

	switch (header.compression) {
	case 0: //no image data is present
		printf("Image::load(%s) warning! No image data is present.\n", filename);
		break;
	case tga::COLOR_MAP : //uncompressed color-mapped image
		printf("Image::load(%s) error! TGA_COLOR_MAP not supported yet.\n", filename);
		break;
	case tga::TRUE_COLOR : //uncompressed true-color image
	case tga::GRAYSCALE : //uncompressed black-and-white (grayscale) image
		if (fread(newdata, sizeof(unsigned char), totalPixelsSize, file) != totalPixelsSize) {
			printf("%s: Error! Unable to read image data.\n", filename);
			fclose(file);
			delete [] newdata;
			return false;
		}
		break;
	case tga::RLE_COLOR_MAP : //run-length encoded color-mapped image
		printf("Image::load(%s) error! TGA_RLE_COLOR_MAP not supported yet.\n", filename);
		break;
	case tga::RLE_TRUE_COLOR : //run-length encoded true-color image
	case tga::RLE_GRAYSCALE : //run-length encoded black-and-white (grayscale) image
		{
		unsigned char* ptr = newdata;
		for (unsigned int y = 0; y < header.height; y++) {
			static int repeat = 0;
			static int direct = 0;
			static unsigned char sample[4];
			int head;

			for (int x = 0; x < header.width; x++) {
				if (repeat == 0 && direct == 0) {
					head = getc(file);
					if (head == EOF) {
						printf("fuck \n");
						fclose(file);
						return false;
					} else if (head >= 128) {
						repeat = head - 127;
						if (fread (sample, pixelSize, 1, file) < 1) {
							printf("Image::load(%s) error! Cannot read pixel data 1\n", filename);
							fclose(file);
							return false;
						}
					} else {
						direct = head + 1;
					}
				}

				if (repeat > 0) {
					for (unsigned int k = 0; k < pixelSize; ++k) {
						ptr[k] = sample[k];
					}
					repeat--;
				} else { /* direct > 0 */
					if (fread(ptr, pixelSize, 1, file) < 1) {
						printf("Image::load(%s) error! Cannot read pixel data 2\n", filename);
						fclose(file);
						return false;
					}
					direct--;
				}
				ptr += pixelSize;
			}
		}
		}
		break;
	default:
		printf("Image::load(%s) error! Unknown compression type %d.\n", filename, header.compression);
		fclose(file);
		return false;
	}

	fclose(file);

	switch (header.depth) {
	case 8 :
		pixelFormat = Image::EPF_L8;
		break;
	case 16 :
		pixelFormat = Image::EPF_R5G6B5;
		break;
	case 24 :
		pixelFormat = Image::EPF_R8G8B8;
		break;
	case 32 :
		pixelFormat = Image::EPF_R8G8B8A8;
		break;
	default :
		printf("Image::load(%s) error! Unsupported pixel depth %d.\n", filename, header.depth);
		return false;
	}

	data = newdata;
	size.x = header.width;
	size.y = header.height;

	if (header.yOrigin == 0) {
	//	flipVertical();
	}

	return true;
}

void Image::flipVertical() {
	const unsigned int pixelSize = getPixelSize();
	unsigned char tmp[8];

	for (unsigned int yIndex = 0; yIndex < size.y / 2; ++yIndex) {
		for (unsigned int xIndex = 0; xIndex < size.x; ++xIndex) {
			const unsigned int index0 = yIndex * size.x + xIndex;
			const unsigned int index1 = (size.y - 1 - yIndex) * size.x + xIndex;

			unsigned char* pointer0 = data + index0 * pixelSize;
			unsigned char* pointer1 = data + index1 * pixelSize;
			
			memcpy(tmp, pointer0, pixelSize);
			memcpy(pointer0, pointer1, pixelSize);
			memcpy(pointer1, tmp, pixelSize);
		}
	}
}

void Image::flipHorizontal() {
	const unsigned int pixelSize = getPixelSize();
	unsigned char tmp[8];

	for (unsigned int yIndex = 0; yIndex < size.y; ++yIndex) {
		for (unsigned int xIndex = 0; xIndex < size.x / 2; ++xIndex) {
			const unsigned int index0 = yIndex * size.x + xIndex;
			const unsigned int index1 = yIndex * size.x + size.x - xIndex;

			unsigned char* pointer0 = data + index0 * pixelSize;
			unsigned char* pointer1 = data + index1 * pixelSize;
			
			memcpy(tmp, pointer0, pixelSize);
			memcpy(pointer0, pointer1, pixelSize);
			memcpy(pointer1, tmp, pixelSize);
		}
	}
}

void Image::clear() {
	memset(data, 0, getDataLength());
}

void Image::destroy() {
	if (data == NULL) {
		return;
	}
	delete [] data;
	data = NULL;
	size.x = 0;
	size.y = 0;
}

void Image::setPixel(int x, int y, const Vector4f& value) {
	union {
		Pixel16 pixel16;
		struct {
			unsigned char ub0;
			unsigned char ub1;
		} raw;
	};

	if (updateCoordinates(x, y)) {
		return;
	}

	const unsigned int pixelIndex = (y * size.x + x) * getPixelSize();

	unsigned char red = (unsigned char)(value.x * 255.0f);
	unsigned char green = (unsigned char)(value.y * 255.0f);
	unsigned char blue = (unsigned char)(value.z * 255.0f);
	unsigned char alpha = (unsigned char)(value.w * 255.0f);
	
	switch (pixelFormat) {
	case Image::EPF_L8 :
		data[pixelIndex + 0] = red;
		break;
	case Image::EPF_R5G6B5 :
		pixel16.red = (unsigned char)(value.z * 31.0f);
		pixel16.green = (unsigned char)(value.y * 63.0f);
		pixel16.blue = (unsigned char)(value.x * 31.0f);

		data[pixelIndex + 0] = raw.ub0;
		data[pixelIndex + 1] = raw.ub1;
		break;
	case Image::EPF_R8G8B8 :
		data[pixelIndex + 0] = blue;
		data[pixelIndex + 1] = green;
		data[pixelIndex + 2] = red;
		break;
	case Image::EPF_R8G8B8A8 :
		data[pixelIndex + 0] = blue;
		data[pixelIndex + 1] = green;
		data[pixelIndex + 2] = red;
		data[pixelIndex + 3] = alpha;
		break;	
	case Image::EPF_DEPTH :
		fdata[y * size.x + x] = value.x;
		break;
	}
}
	
Vector4f Image::getPixel(int x, int y) const {
	union {
		Pixel16 pixel16;
		struct {
			unsigned char ub0;
			unsigned char ub1;
		} raw;
	};
	static const float oneOver255 = 1.0f / 255.0f;	
	Vector4f ans;
		
	if (updateCoordinates(x, y)) {
		return ans;
	}
	
	const unsigned int pixelIndex = (y * size.x + x) * getPixelSize();
	
	switch (pixelFormat) {
	case Image::EPF_L8 :
		ans.x = (float)data[pixelIndex + 0] / 255.0f;
		ans.y = ans.x;
		ans.z = ans.x;
		ans.w = 1.0f;
		break;
	case Image::EPF_R5G6B5 :
		raw.ub0 = data[pixelIndex + 0];
		raw.ub1 = data[pixelIndex + 1];

		ans.x = (float)pixel16.red / 63.0f;
		ans.y = (float)pixel16.green / 127.0f;
		ans.z = (float)pixel16.blue / 63.0f;
		ans.w = 1.0f;
		break;
	case Image::EPF_R8G8B8 :
		ans.x = (float)data[pixelIndex + 2] / 255.0f;
		ans.y = (float)data[pixelIndex + 1] / 255.0f;
		ans.z = (float)data[pixelIndex + 0] / 255.0f;
		ans.w = 1.0f;
		break;
	case Image::EPF_R8G8B8A8 :
		ans.z = (float)data[pixelIndex + 0] * oneOver255;
		ans.y = (float)data[pixelIndex + 1] * oneOver255;
		ans.x = (float)data[pixelIndex + 2] * oneOver255;
		ans.w = (float)data[pixelIndex + 3] * oneOver255;
		break;
	case Image::EPF_DEPTH :
		ans.x = fdata[y * size.x + x];
		ans.y = ans.x;
		ans.z = ans.x;
		ans.w = 1.0f;
		break;
	}
	
	return ans;
}

Vector4f Image::getPixel(const Vector2u& uv) const {
	return getPixel(uv.x, uv.y);
}

Vector4f Image::sample2D(const Vector2f& uv) const {
	return getPixel(uv.x * (float)size.x, uv.y * (float)size.y);
}

	
Vector4ub Image::getRawPixel(int x, int y) const {
	union {
		Pixel16 pixel16;
		struct {
			unsigned char ub0;
			unsigned char ub1;
		} raw;
	};

	Vector4ub ans;
		
	if (updateCoordinates(x, y)) {
		return ans;
	}
	
	const unsigned int pixelIndex = (y * size.x + x) * getPixelSize();
	
	switch (pixelFormat) {
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
	case Image::EPF_R8G8B8A8 :
		ans.z = data[pixelIndex + 0];
		ans.y = data[pixelIndex + 1];
		ans.x = data[pixelIndex + 2];
		ans.w = data[pixelIndex + 3];
		break;
	case Image::EPF_DEPTH :
		break;
	}
	
	return ans;
}
Vector4ub Image::sampleRaw2D(const Vector2f& uv) const {
	return getRawPixel(uv.x * (float)size.x, uv.y * (float)size.y);
}

void Image::drawLine(const ivec2& begin, const ubvec4& beginColor, const ivec2& end, const ubvec4& endColor) {
	const float xdiff = (end.x - begin.x);
	const float ydiff = (end.y - begin.y);
	float slope;

	if(xdiff == 0.0f && ydiff == 0.0f) {
		setRawPixel(begin.x, begin.y, (beginColor + endColor) / 2);
		return;
	}

	const ubvec4 colorDiff = endColor - beginColor;

	if(fabs(xdiff) > fabs(ydiff)) {
		float xmin, xmax;

		if(begin.x < end.x) {
			xmin = begin.x;
			xmax = end.x;
		} else {
			xmin = end.x;
			xmax = begin.x;
		}

		// draw line in terms of y slope
		slope = ydiff / xdiff;
		for(float x = std::max(0.0f, xmin); x <= std::min(xmax, (float)size.x - 1.0f); x += 1.0f) {
			const float y = begin.y + ((x - begin.x) * slope);
			if (y < 0 || y >= size.y) {
				continue;
			}
			const float proc = (x - begin.x) / xdiff;
			setRawPixel(x, y, beginColor + ubvec4((float)colorDiff.x * proc, (float)colorDiff.y * proc, (float)colorDiff.z * proc, (float)colorDiff.w * proc));
		}
	} else {
		float ymin, ymax;

		if(begin.y < end.y) {
			ymin = begin.y;
			ymax = end.y;
		} else {
			ymin = end.y;
			ymax = begin.y;
		}

		slope = xdiff / ydiff;
		for(float y = std::max(0.0f, ymin); y <= std::min(ymax, (float)size.y - 1.0f); y += 1.0f) {
			const float x = begin.x + ((y - begin.y) * slope);
			if (x < 0 || x >= size.x) {
				continue;
			}
			const float proc = (y - begin.y) / ydiff;
			setRawPixel(x, y, beginColor + ubvec4((float)colorDiff.x * proc, (float)colorDiff.y * proc, (float)colorDiff.z * proc, (float)colorDiff.w * proc));
		}
	}
}

void Image::drawLine(const ivec2& begin, const ivec2& end, const ubvec4& color) {
	drawLine(begin, color, end, color);
}

void Image::drawRectangle(const ivec4& rectangle, const ubvec4& color) {
	// Draw horizontal lines
	for (int x = rectangle.x; x < rectangle.z; ++x) {
		setRawPixel(x, rectangle.y, color);
		setRawPixel(x, rectangle.w, color);
	}
	
	// Draw vertical lines
	for (int y = rectangle.y; y < rectangle.w; ++y) {
		setRawPixel(rectangle.x, y, color);
		setRawPixel(rectangle.z, y, color);
	}
}

void Image::drawFilledRectangle(const ivec4& rectangle, const ubvec4& color) {
#if defined (_WIN32)
	// BGRA
	const unsigned int rawPixel = /* (color.w & 0xFF) << 24 | */ (color.x & 0xFF) << 16 | (color.y & 0xFF) << 8 | (color.z & 0xFF);
#else
	// RGBA
	const unsigned int rawPixel = /* (color.w & 0xFF) << 24 | */ (color.z & 0xFF) << 16 | (color.y & 0xFF) << 8 | (color.x & 0xFF);
#endif
	for (int x = std::max(rectangle.x, 0); x < std::min(rectangle.z, (int)size.x - 1); ++x) {
		for (int y = std::max(rectangle.y, 0); y < std::min(rectangle.w, (int)size.y - 1); ++y) {
			//setRawPixel(x, y, color);
			unsigned int offset = (y * size.x + x) * 4;
			*((unsigned int*)&data[offset]) = rawPixel;
		}
	}
}
#if 0
void Image::drawCircle(const Vector2f& center, float radius, const Vector4f& color) {
	// TODO
}

void Image::drawFilledCircle(const Vector2f& center, float radius, const Vector4f& color) {
	// TODO
}
#endif
void Image::blit(const Image* image, const uvec2& position) {
	if ((image == NULL) || (pixelFormat != image->getPixelFormat())){
		return;
	}
	
	const unsigned int dstWidth  = size.x - position.x;
	const unsigned int dstHeight = size.y - position.y;
	const unsigned int srcWidth  = (dstWidth  < image->getSize().x) ? dstWidth  : image->getSize().x;
	const unsigned int srcHeight = (dstHeight < image->getSize().y) ? dstHeight : image->getSize().y;

	for (unsigned int y = 0; y < srcHeight; ++y) {
		memcpy(data + ((position.y + y) * size.x + position.x) * getPixelSize(),
				image->data + (y * image->getSize().x) * getPixelSize(),
				srcWidth * getPixelSize());
	}
}