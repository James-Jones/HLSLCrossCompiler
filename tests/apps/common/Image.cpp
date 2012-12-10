
/* * * * * * * * * * * * * Author's note * * * * * * * * * * * *\
*   _       _   _       _   _       _   _       _     _ _ _ _   *
*  |_|     |_| |_|     |_| |_|_   _|_| |_|     |_|  _|_|_|_|_|  *
*  |_|_ _ _|_| |_|     |_| |_|_|_|_|_| |_|     |_| |_|_ _ _     *
*  |_|_|_|_|_| |_|     |_| |_| |_| |_| |_|     |_|   |_|_|_|_   *
*  |_|     |_| |_|_ _ _|_| |_|     |_| |_|_ _ _|_|  _ _ _ _|_|  *
*  |_|     |_|   |_|_|_|   |_|     |_|   |_|_|_|   |_|_|_|_|    *
*                                                               *
*                     http://www.humus.name                     *
*                                                                *
* This file is a part of the work done by Humus. You are free to   *
* use the code in any way you like, modified, unmodified or copied   *
* into your own work. However, I expect you to respect these points:  *
*  - If you use this file and its contents unmodified, or use a major *
*    part of this file, please credit the author and leave this note. *
*  - For use in anything commercial, please request my approval.     *
*  - Share your work and ideas too as much as you can.             *
*                                                                *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "Image.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <vectormath_aos.h>

#pragma pack (push, 1)

// Define some useful macros
#define MCHAR2(a, b) (a | (b << 8))
#define MCHAR4(a, b, c, d) (a | (b << 8) | (c << 16) | (d << 24))

template <typename T, size_t N> char (&ArraySizeHelper(T (&arr)[N]))[N];
#define elementsOf(arr) (sizeof(ArraySizeHelper(arr)))

// Note: returns true for 0
inline bool isPowerOf2(const int x){
	return (x & (x - 1)) == 0;
}

#define min(x, y) (x < y ? x : y)
#define max(x, y) (x > y ? x : y)

Vectormath::Aos::Vector3 saturate(Vectormath::Aos::Vector3& v)
{
   return Vectormath::Aos::Vector3(min(max(v.getX(), 0), 1), min(max(v.getY(), 0), 1), min(max(v.getZ(), 0), 1));
}

float saturate(float f)
{
   return min(max(f, 0), 1);
}

Vectormath::Aos::Vector3 rgbeToRGB(unsigned char *rgbe){
	if (rgbe[3]){
		return Vectormath::Aos::Vector3(rgbe[0], rgbe[1], rgbe[2]) * ldexpf(1.0f, rgbe[3] - (int) (128 + 8));
	} else return Vectormath::Aos::Vector3(0, 0, 0);
}

unsigned int rgbToRGBE8(const Vectormath::Aos::Vector3 &rgb){
	float v = Vectormath::Aos::maxElem(rgb);

	if (v < 1e-32f){
		return 0;
	} else {
		int ex;
		float m = frexpf(v, &ex) * 256.0f / v;

		unsigned int r = (unsigned int) (m * rgb.getX());
		unsigned int g = (unsigned int) (m * rgb.getY());
		unsigned int b = (unsigned int) (m * rgb.getZ());
		unsigned int e = (unsigned int) (ex + 128);

		return r | (g << 8) | (b << 16) | (e << 24);
	}
}

unsigned int rgbToRGB9E5(const Vectormath::Aos::Vector3 &rgb){
   float v = Vectormath::Aos::maxElem(rgb);

	if (v < 1.52587890625e-5f){
		return 0;
	} else if (v < 65536){
		int ex;
		float m = frexpf(v, &ex) * 512.0f / v;

		unsigned int r = (unsigned int) (m * rgb.getX());
		unsigned int g = (unsigned int) (m * rgb.getY());
		unsigned int b = (unsigned int) (m * rgb.getZ());
		unsigned int e = (unsigned int) (ex + 15);

		return r | (g << 9) | (b << 18) | (e << 27);
	} else {
		unsigned int r = (rgb.getX() < 65536)? (unsigned int) (rgb.getX() * (1.0f / 128.0f)) : 0x1FF;
		unsigned int g = (rgb.getY() < 65536)? (unsigned int) (rgb.getY() * (1.0f / 128.0f)) : 0x1FF;
		unsigned int b = (rgb.getZ() < 65536)? (unsigned int) (rgb.getZ() * (1.0f / 128.0f)) : 0x1FF;
		unsigned int e = 31;

		return r | (g << 9) | (b << 18) | (e << 27);
	}
}

struct HTexHeader {
	uint32_t identifier;
	uint32_t version;
	uint64_t format;
	uint32_t width;
	uint32_t height;
	uint32_t depth;
	uint32_t nMipMaps;
};

struct HTexHeader2 {
	uint32_t flags;
	uint32_t nExtraData;
};

#define DDPF_ALPHAPIXELS 0x00000001 
#define DDPF_FOURCC      0x00000004 
#define DDPF_RGB         0x00000040

#define DDSD_CAPS        0x00000001
#define DDSD_HEIGHT      0x00000002
#define DDSD_WIDTH       0x00000004
#define DDSD_PITCH       0x00000008
#define DDSD_PIXELFORMAT 0x00001000
#define DDSD_MIPMAPCOUNT 0x00020000
#define DDSD_LINEARSIZE  0x00080000
#define DDSD_DEPTH       0x00800000

#define DDSCAPS_COMPLEX  0x00000008 
#define DDSCAPS_TEXTURE  0x00001000 
#define DDSCAPS_MIPMAP   0x00400000 

#define DDSCAPS2_CUBEMAP 0x00000200 
#define DDSCAPS2_VOLUME  0x00200000 

#define DDSCAPS2_CUBEMAP_POSITIVEX 0x00000400
#define DDSCAPS2_CUBEMAP_NEGATIVEX 0x00000800
#define DDSCAPS2_CUBEMAP_POSITIVEY 0x00001000
#define DDSCAPS2_CUBEMAP_NEGATIVEY 0x00002000
#define DDSCAPS2_CUBEMAP_POSITIVEZ 0x00004000
#define DDSCAPS2_CUBEMAP_NEGATIVEZ 0x00008000
#define DDSCAPS2_CUBEMAP_ALL_FACES (DDSCAPS2_CUBEMAP_POSITIVEX | DDSCAPS2_CUBEMAP_NEGATIVEX | DDSCAPS2_CUBEMAP_POSITIVEY | DDSCAPS2_CUBEMAP_NEGATIVEY | DDSCAPS2_CUBEMAP_POSITIVEZ | DDSCAPS2_CUBEMAP_NEGATIVEZ)

#define D3D10_RESOURCE_MISC_TEXTURECUBE 0x4
#define D3D10_RESOURCE_DIMENSION_BUFFER    1
#define D3D10_RESOURCE_DIMENSION_TEXTURE1D 2
#define D3D10_RESOURCE_DIMENSION_TEXTURE2D 3
#define D3D10_RESOURCE_DIMENSION_TEXTURE3D 4

struct DDSHeader {
	uint32_t dwMagic;
	uint32_t dwSize;
	uint32_t dwFlags;
	uint32_t dwHeight;
	uint32_t dwWidth;
	uint32_t dwPitchOrLinearSize;
	uint32_t dwDepth; 
	uint32_t dwMipMapCount;
	uint32_t dwReserved[11];

	struct {
        uint32_t dwSize;
		uint32_t dwFlags;
		uint32_t dwFourCC;
		uint32_t dwRGBBitCount;
		uint32_t dwRBitMask;
		uint32_t dwGBitMask;
		uint32_t dwBBitMask;
		uint32_t dwRGBAlphaBitMask; 
	} ddpfPixelFormat;

	struct {
		uint32_t dwCaps1;
		uint32_t dwCaps2;
		uint32_t Reserved[2];
	} ddsCaps;

	uint32_t dwReserved2;
};

struct DDSHeaderDX10 {
    uint32_t dxgiFormat;
    uint32_t resourceDimension;
    uint32_t miscFlag;
    uint32_t arraySize;
    uint32_t reserved;
};

struct TGAHeader {
	uint8_t  descriptionlen;
	uint8_t  cmaptype;
	uint8_t  imagetype;
	uint16_t cmapstart;
	uint16_t cmapentries;
	uint8_t  cmapbits;
	uint16_t xoffset;
	uint16_t yoffset;
	uint16_t width;
	uint16_t height;
	uint8_t  bpp;
	uint8_t  attrib;
};

struct BMPHeader {
	uint16_t bmpIdentifier;
	uint8_t  junk[16];
	uint32_t width;
	uint32_t height;
	uint16_t junk2;
	uint16_t bpp;
	uint16_t compression;
	uint8_t  junk3[22];
};

struct PCXHeader {
	uint8_t  junk[3];
	uint8_t  bitsPerChannel;
	uint8_t  junk2[4];
	uint16_t width;
	uint16_t height;
	uint8_t  junk3[53];
	uint8_t  nChannels;
	uint16_t scanlineLen;
	uint8_t  junk4[60];
};

#pragma pack (pop)


/* ---------------------------------------------- */

struct FormatString {
	FORMAT format;
	const char *string;
};

static const FormatString formatStrings[] = {
	{ FORMAT_NONE,   "NONE"  },

	{ FORMAT_R8,     "R8"    },
	{ FORMAT_RG8,    "RG8"   },
	{ FORMAT_RGB8,   "RGB8"  },
	{ FORMAT_RGBA8,  "RGBA8" },
	
	{ FORMAT_R16,    "R16"   },
	{ FORMAT_RG16,   "RG16"  },
	{ FORMAT_RGB16,  "RGB16" },
	{ FORMAT_RGBA16, "RGBA16"},

	{ FORMAT_R16F,   "R16F"    },
	{ FORMAT_RG16F,  "RG16F"   },
	{ FORMAT_RGB16F, "RGB16F"  },
	{ FORMAT_RGBA16F,"RGBA16F" },

	{ FORMAT_R32F,   "R32F"    },
	{ FORMAT_RG32F,  "RG32F"   },
	{ FORMAT_RGB32F, "RGB32F"  },
	{ FORMAT_RGBA32F,"RGBA32F" },

	{ FORMAT_RGBE8,  "RGBE8"   },
	{ FORMAT_RGB565, "RGB565"  },
	{ FORMAT_RGBA4,  "RGBA4"   },
	{ FORMAT_RGB10A2,"RGB10A2" },

	{ FORMAT_DXT1,   "DXT1"  },
	{ FORMAT_DXT3,   "DXT3"  },
	{ FORMAT_DXT5,   "DXT5"  },
	{ FORMAT_ATI1N,  "ATI1N" },
	{ FORMAT_ATI2N,  "ATI2N" },
};

const char *getFormatString(const FORMAT format){
	for (unsigned int i = 0; i < elementsOf(formatStrings); i++){
		if (format == formatStrings[i].format) return formatStrings[i].string;
	}
	return NULL;
}

FORMAT getFormatFromString(char *string){
	for (unsigned int i = 0; i < elementsOf(formatStrings); i++){
		if (stricmp(string, formatStrings[i].string) == 0) return formatStrings[i].format;
	}
	return FORMAT_NONE;
}


template <typename DATA_TYPE>
inline void swapChannels(DATA_TYPE *pixels, int nPixels, const int channels, const int ch0, const int ch1){
	do {
		DATA_TYPE tmp = pixels[ch1];
		pixels[ch1] = pixels[ch0];
		pixels[ch0] = tmp;
		pixels += channels;
	} while (--nPixels);
}


/* ---------------------------------------------- */

Image::Image(){
	pixels = NULL;
	width  = 0;
	height = 0;
	depth  = 0;
	nMipMaps = 0;
	arraySize = 0;
	format = FORMAT_NONE;

	nExtraData = 0;
	extraData = NULL;
}

Image::Image(const Image &img){
	width  = img.width;
	height = img.height;
	depth  = img.depth;
	nMipMaps = img.nMipMaps;
	arraySize = img.arraySize;
	format = img.format;

	int size = getMipMappedSize(0, nMipMaps) * arraySize;
	pixels = new unsigned char[size];
	memcpy(pixels, img.pixels, size);

	nExtraData = img.nExtraData;
	extraData = new unsigned char[nExtraData];
	memcpy(extraData, img.extraData, nExtraData);
}

Image::~Image(){
	delete [] pixels;
	delete [] extraData;
}

unsigned char *Image::create(const FORMAT fmt, const int w, const int h, const int d, const int mipMapCount, const int arraysize){
    format = fmt;
    width  = w;
	height = h;
	depth  = d;
	nMipMaps = mipMapCount;
	arraySize = arraysize;

	return (pixels = new unsigned char[getMipMappedSize(0, nMipMaps) * arraySize]);
}

void Image::free(){
	delete [] pixels;
	pixels = NULL;

	delete [] extraData;
	extraData = NULL;
}

void Image::clear(){
	free();

	width  = 0;
	height = 0;
	depth  = 0;
	nMipMaps = 0;
	arraySize = 0;
	format = FORMAT_NONE;

	nExtraData = 0;
}

unsigned char *Image::getPixels(const int mipMapLevel) const {
	return (mipMapLevel < nMipMaps)? pixels + getMipMappedSize(0, mipMapLevel) : NULL;
}

unsigned char *Image::getPixels(const int mipMapLevel, const int arraySlice) const {
	if (mipMapLevel >= nMipMaps || arraySlice >= arraySize) return NULL;

	return pixels + getMipMappedSize(0, nMipMaps) * arraySlice + getMipMappedSize(0, mipMapLevel);
}


int Image::getMipMapCountFromDimesions() const {
	int m = max(width, height);
	m = max(m, depth);

	int i = 0;
	while (m > 0){
		m >>= 1;
		i++;
	}

	return i;
}

int Image::getMipMappedSize(const int firstMipMapLevel, int nMipMapLevels, FORMAT srcFormat) const {
	int w = getWidth (firstMipMapLevel);
	int h = getHeight(firstMipMapLevel);
	int d = getDepth (firstMipMapLevel);

	if (srcFormat == FORMAT_NONE) srcFormat = format;
	
	int size = 0;
	while (nMipMapLevels){
		if (isCompressedFormat(srcFormat)){
			size += ((w + 3) >> 2) * ((h + 3) >> 2) * d;
		} else {
			size += w * h * d;
		}
		w >>= 1;
		h >>= 1;
		d >>= 1;
		if (w + h + d == 0) break;
		if (w == 0) w = 1;
		if (h == 0) h = 1;
		if (d == 0) d = 1;

		nMipMapLevels--;
	}

	if (isCompressedFormat(srcFormat)){
		size *= getBytesPerBlock(srcFormat);
	} else {
		size *= getBytesPerPixel(srcFormat);
	}

	return (depth == 0)? 6 * size : size;
}

int Image::getSliceSize(const int mipMapLevel, FORMAT srcFormat) const {
	int w = getWidth (mipMapLevel);
	int h = getHeight(mipMapLevel);

	if (srcFormat == FORMAT_NONE) srcFormat = format;
	
	int size;
	if (isCompressedFormat(srcFormat)){
		size = ((w + 3) >> 2) * ((h + 3) >> 2) * getBytesPerBlock(srcFormat);
	} else {
		size = w * h * getBytesPerPixel(srcFormat);
	}

	return size;
}

int Image::getPixelCount(const int firstMipMapLevel, int nMipMapLevels) const {
	int w = getWidth (firstMipMapLevel);
	int h = getHeight(firstMipMapLevel);
	int d = getDepth (firstMipMapLevel);
	int size = 0;
	while (nMipMapLevels){
		size += w * h * d;
		w >>= 1;
		h >>= 1;
		d >>= 1;
		if (w + h + d == 0) break;
		if (w == 0) w = 1;
		if (h == 0) h = 1;
		if (d == 0) d = 1;

		nMipMapLevels--;
	}

	return (depth == 0)? 6 * size : size;
}

int Image::getWidth(const int mipMapLevel) const {
	int a = width >> mipMapLevel;
	return (a == 0)? 1 : a;
}

int Image::getHeight(const int mipMapLevel) const {
	int a = height >> mipMapLevel;
	return (a == 0)? 1 : a;
}

int Image::getDepth(const int mipMapLevel) const {
	int a = depth >> mipMapLevel;
	return (a == 0)? 1 : a;
}

bool Image::loadHTEX(const char *fileName){
	FILE *file = fopen(fileName, "rb");
	if (file == NULL) return false;

	HTexHeader header;
	fread(&header, sizeof(header), 1, file);

	if (header.identifier != MCHAR4('H','T','E','X') || header.version > 2){
		fclose(file);
		return false;
	}

	HTexHeader2 header2;
	if (header.version >= 2){
		fread(&header2, sizeof(header2), 1, file);
	} else {
		memset(&header2, 0, sizeof(header2));
	}

	format = getFormatFromString((char *) &header.format);
	width  = header.width;
	height = header.height;
	depth  = header.depth;
	nMipMaps = header.nMipMaps;
	arraySize = 1;

	nExtraData = header2.nExtraData;
	
	pixels = new unsigned char[getMipMappedSize(0, nMipMaps)];

	if (isPlainFormat(format)){
		/*int nChannels = getChannelCount(format);
		int bpc = getBytesPerChannel(format);

		for (int ch = 0; ch < nChannels; ch++){
			for (int level = 0; level < nMipMaps; level++){
				int nPixels = getPixelCount(level, 1);

				uint8_t *dest = getPixels(level) + ch * bpc;
				for (int i = 0; i < nPixels; i++){
					fread(dest + i * nChannels * bpc, bpc, 1, file);
				}
			}
		}*/
		fread(pixels, getMipMappedSize(0, nMipMaps), 1, file);

	} else if (isCompressedFormat(format)){
		if (format == FORMAT_DXT1 || format == FORMAT_DXT5){
			char shift = (format == FORMAT_DXT1)? 3 : 4;

			for (int level = 0; level < nMipMaps; level++){
				uint8_t *dest = getPixels(level);
				if (format != FORMAT_DXT1) dest += 8;
				int w = getWidth(level);
				int h = getHeight(level);
				int d = getDepth(level);

				int nBlocks = d * ((w + 3) >> 2) * ((h + 3) >> 2);

				for (int n = 0; n < nBlocks; n++){
					fread(dest + (n << shift), 1, 2, file);
				}

				for (int n = 0; n < nBlocks; n++){
					fread(dest + (n << shift) + 2, 1, 2, file);
				}

				for (int n = 0; n < nBlocks; n++){
					fread(dest + (n << shift) + 4, 1, 4, file);
				}
			}
		}
		if (format == FORMAT_DXT5 || format == FORMAT_ATI1N || format == FORMAT_ATI2N){
			char shift = (format != FORMAT_DXT5)? 3 : 4;

			for (int level = 0; level < nMipMaps; level++){
				uint8_t *src = getPixels(level);
				int w = getWidth(level);
				int h = getHeight(level);
				int d = getDepth(level);

				int nBlocks = d * ((w + 3) >> 2) * ((h + 3) >> 2);

				for (int n = 0; n < nBlocks; n++){
					fread(src + (n << shift), 1, 1, file);
				}
				if (format == FORMAT_ATI2N){
					for (int n = 0; n < nBlocks; n++){
						fread(src + 8 * (nBlocks + n), 1, 1, file);
					}
				}

				for (int n = 0; n < nBlocks; n++){
					fread(src + (n << shift) + 1, 1, 1, file);
				}
				if (format == FORMAT_ATI2N){
					for (int n = 0; n < nBlocks; n++){
						fread(src + 8 * (nBlocks + n) + 1, 1, 1, file);
					}
				}

				for (int n = 0; n < nBlocks; n++){
					fread(src + (n << shift) + 2, 1, 6, file);
				}
				if (format == FORMAT_ATI2N){
					for (int n = 0; n < nBlocks; n++){
						fread(src + 8 * (nBlocks + n) + 2, 1, 6, file);
					}
				}
			}
		}
	}

	if (nExtraData){
		extraData = new unsigned char[nExtraData];
		fread(extraData, 1, nExtraData, file);
	}

	fclose(file);

	return true;
}

bool Image::loadDDS(const char *fileName, uint32_t flags){
	DDSHeader header;

	FILE *file;
	if ((file = fopen(fileName, "rb")) == NULL) return false;

	fread(&header, sizeof(header), 1, file);
	if (header.dwMagic != MCHAR4('D','D','S',' ')){
		fclose(file);
		return false;
	}

	width  = header.dwWidth;
	height = header.dwHeight;
	depth  = (header.ddsCaps.dwCaps2 & DDSCAPS2_CUBEMAP)? 0 : (header.dwDepth == 0)? 1 : header.dwDepth;
	nMipMaps = ((flags & DONT_LOAD_MIPMAPS) || (header.dwMipMapCount == 0))? 1 : header.dwMipMapCount;
	arraySize = 1;

	if (header.ddpfPixelFormat.dwFourCC == MCHAR4('D','X','1','0')){
		DDSHeaderDX10 dx10Header;
		fread(&dx10Header, sizeof(dx10Header), 1, file);

		switch (dx10Header.dxgiFormat){
			case 61: format = FORMAT_R8; break;
			case 49: format = FORMAT_RG8; break;
			case 28: format = FORMAT_RGBA8; break;

			case 56: format = FORMAT_R16; break;
			case 35: format = FORMAT_RG16; break;
			case 11: format = FORMAT_RGBA16; break;

			case 54: format = FORMAT_R16F; break;
			case 34: format = FORMAT_RG16F; break;
			case 10: format = FORMAT_RGBA16F; break;

			case 41: format = FORMAT_R32F; break;
			case 16: format = FORMAT_RG32F; break;
			case 6:  format = FORMAT_RGB32F; break;
			case 2:  format = FORMAT_RGBA32F; break;

			case 67: format = FORMAT_RGB9E5; break;
			case 26: format = FORMAT_RG11B10F; break;
			case 24: format = FORMAT_RGB10A2; break;

			case 71: format = FORMAT_DXT1; break;
			case 74: format = FORMAT_DXT3; break;
			case 77: format = FORMAT_DXT5; break;
			case 80: format = FORMAT_ATI1N; break;
			case 83: format = FORMAT_ATI2N; break;
			default:
				fclose(file);
				return false;
		}

	} else {

		switch (header.ddpfPixelFormat.dwFourCC){
			case 34:  format = FORMAT_RG16; break;
			case 36:  format = FORMAT_RGBA16; break;
			case 111: format = FORMAT_R16F; break;
			case 112: format = FORMAT_RG16F; break;
			case 113: format = FORMAT_RGBA16F; break;
			case 114: format = FORMAT_R32F; break;
			case 115: format = FORMAT_RG32F; break;
			case 116: format = FORMAT_RGBA32F; break;
			case MCHAR4('D','X','T','1'): format = FORMAT_DXT1; break;
			case MCHAR4('D','X','T','3'): format = FORMAT_DXT3; break;
			case MCHAR4('D','X','T','5'): format = FORMAT_DXT5; break;
			case MCHAR4('A','T','I','1'): format = FORMAT_ATI1N; break;
			case MCHAR4('A','T','I','2'): format = FORMAT_ATI2N; break;
			default:
				switch (header.ddpfPixelFormat.dwRGBBitCount){
					case 8: format = FORMAT_I8; break;
					case 16:
						format = (header.ddpfPixelFormat.dwRGBAlphaBitMask == 0xF000)? FORMAT_RGBA4 : 
								 (header.ddpfPixelFormat.dwRGBAlphaBitMask == 0xFF00)? FORMAT_IA8 : 
								 (header.ddpfPixelFormat.dwBBitMask == 0x1F)? FORMAT_RGB565 : FORMAT_I16;
						break;
					case 24: format = FORMAT_RGB8; break;
					case 32:
						format = (header.ddpfPixelFormat.dwRBitMask == 0x3FF00000)? FORMAT_RGB10A2 : FORMAT_RGBA8;
						break;
					default:
						fclose(file);
						return false;
				}
		}
	}

	int size = getMipMappedSize(0, nMipMaps);
	pixels = new unsigned char[size];
	if (isCube()){
		for (int face = 0; face < 6; face++){
			for (int mipMapLevel = 0; mipMapLevel < nMipMaps; mipMapLevel++){
				int faceSize = getMipMappedSize(mipMapLevel, 1) / 6;
                unsigned char *src = getPixels(mipMapLevel) + face * faceSize;

				fread(src, 1, faceSize, file);
			}
			if ((flags & DONT_LOAD_MIPMAPS) && header.dwMipMapCount > 1){
				fseek(file, getMipMappedSize(1, header.dwMipMapCount - 1) / 6, SEEK_CUR);
			}
		}
	} else {
		fread(pixels, 1, size, file);
	}

	if ((format == FORMAT_RGB8 || format == FORMAT_RGBA8) && header.ddpfPixelFormat.dwBBitMask == 0xFF){
		int nChannels = getChannelCount(format);
		swapChannels(pixels, size / nChannels, nChannels, 0, 2);
	}

	fclose(file);
	return true;
}

bool Image::loadImage(const char *fileName, uint32_t flags){
	const char *extension = strrchr(fileName, '.');

	clear();

	if (extension == NULL) return false;

	if (stricmp(extension, ".htex") == 0){
		if (!loadHTEX(fileName)) return false;
	} else if (stricmp(extension, ".dds") == 0){
		if (!loadDDS(fileName, flags)) return false;
   }
	else {
		return false;
	}
	return true;
}

bool Image::loadSlicedImage(const char **fileNames, const int nImages, const int nArraySlices, uint32_t flags){
	int maxImage = nImages? nImages : 6;

	Image *images = new Image[maxImage * nArraySlices];

	for (int i = 0; i < maxImage * nArraySlices; i++){
		if (!images[i].loadImage(fileNames[i], flags)){
			delete [] images;
			return false;
		}
	}

	uint32_t nMipMaps = images[0].nMipMaps;
	uint8_t *dest = create(images[0].format, images[0].width, images[0].height, nImages, nMipMaps, nArraySlices);

	for (int arraySlice = 0; arraySlice < nArraySlices; arraySlice++){
		int base = arraySlice * maxImage;

		for (uint32_t level = 0; level < nMipMaps; level++){
			int size = images[0].getMipMappedSize(level, 1);
			for (int i = 0; i < maxImage; i++){
				memcpy(dest, images[base + i].getPixels(level), size);
				dest += size;
			}
		}
	}

	delete [] images;

	return true;
}

bool Image::saveHTEX(const char *fileName){
	if (!(isPlainFormat(format) || format == FORMAT_DXT1 || format == FORMAT_DXT5 || format == FORMAT_ATI1N || format == FORMAT_ATI2N)) return false;

	FILE *file = fopen(fileName, "wb");
	if (file == NULL) return false;


	HTexHeader header;
	header.identifier = MCHAR4('H','T','E','X');
	header.version = 2;

	header.format = 0;
	strcpy((char *) &header.format, getFormatString(format));

	header.width  = width;
	header.height = height;
	header.depth  = depth;
	header.nMipMaps = nMipMaps;

	HTexHeader2 header2;
	header2.flags = 0;
	header2.nExtraData = nExtraData;

	fwrite(&header,  sizeof(header),  1, file);
	fwrite(&header2, sizeof(header2), 1, file);


	if (isPlainFormat(format)){
		/*int nChannels = getChannelCount(format);
		int bpc = getBytesPerChannel(format);

		for (int ch = 0; ch < nChannels; ch++){
			for (int level = 0; level < nMipMaps; level++){
				int nPixels = getPixelCount(level, 1);

				uint8_t *src = getPixels(level) + ch * bpc;
				for (int i = 0; i < nPixels; i++){
					fwrite(src + i * nChannels * bpc, bpc, 1, file);
				}
			}
		}*/
		fwrite(pixels, getMipMappedSize(0, nMipMaps), 1, file);

	} else if (isCompressedFormat(format)){
		if (format == FORMAT_DXT1 || format == FORMAT_DXT5){
			char shift = (format == FORMAT_DXT1)? 3 : 4;

			for (int level = 0; level < nMipMaps; level++){
				uint8_t *src = getPixels(level);
				if (format != FORMAT_DXT1) src += 8;
				int w = getWidth(level);
				int h = getHeight(level);
				int d = getDepth(level);

				int nBlocks = d * ((w + 3) >> 2) * ((h + 3) >> 2);

				for (int n = 0; n < nBlocks; n++){
					fwrite(src + (n << shift), 1, 2, file);
				}

				for (int n = 0; n < nBlocks; n++){
					fwrite(src + (n << shift) + 2, 1, 2, file);
				}

				for (int n = 0; n < nBlocks; n++){
					fwrite(src + (n << shift) + 4, 1, 4, file);
				}
			}
		}

		if (format == FORMAT_DXT5 || format == FORMAT_ATI1N || format == FORMAT_ATI2N){
			char shift = (format != FORMAT_DXT5)? 3 : 4;

			for (int level = 0; level < nMipMaps; level++){
				uint8_t *src = getPixels(level);
				int w = getWidth(level);
				int h = getHeight(level);
				int d = getDepth(level);

				int nBlocks = d * ((w + 3) >> 2) * ((h + 3) >> 2);

				for (int n = 0; n < nBlocks; n++){
					fwrite(src + (n << shift), 1, 1, file);
				}
				if (format == FORMAT_ATI2N){
					for (int n = 0; n < nBlocks; n++){
						fwrite(src + 8 * (nBlocks + n), 1, 1, file);
					}
				}

				for (int n = 0; n < nBlocks; n++){
					fwrite(src + (n << shift) + 1, 1, 1, file);
				}
				if (format == FORMAT_ATI2N){
					for (int n = 0; n < nBlocks; n++){
						fwrite(src + 8 * (nBlocks + n) + 1, 1, 1, file);
					}
				}

				for (int n = 0; n < nBlocks; n++){
					fwrite(src + (n << shift) + 2, 1, 6, file);
				}
				if (format == FORMAT_ATI2N){
					for (int n = 0; n < nBlocks; n++){
						fwrite(src + 8 * (nBlocks + n) + 2, 1, 6, file);
					}
				}
			}
		}
	}

	if (nExtraData > 0){
		fwrite(extraData, 1, nExtraData, file);
	}

	fclose(file);

	return true;
}

bool Image::saveDDS(const char *fileName){
	// Set up the header
	DDSHeader header;
	memset(&header, 0, sizeof(header));
	DDSHeaderDX10 headerDX10;
	memset(&headerDX10, 0, sizeof(headerDX10));

	header.dwMagic = MCHAR4('D', 'D', 'S', ' ');
	header.dwSize = 124;
	header.dwFlags = DDSD_CAPS | DDSD_PIXELFORMAT | DDSD_WIDTH | DDSD_HEIGHT | (nMipMaps > 1? DDSD_MIPMAPCOUNT : 0) | (depth > 1? DDSD_DEPTH : 0);
	header.dwHeight = height;
	header.dwWidth  = width;
	header.dwPitchOrLinearSize = 0;
	header.dwDepth = (depth > 1)? depth : 0;
	header.dwMipMapCount = (nMipMaps > 1)? nMipMaps : 0;

	int nChannels = getChannelCount(format);

	header.ddpfPixelFormat.dwSize = 32;
	if (format <= FORMAT_I16 || format == FORMAT_RGB10A2){
		header.ddpfPixelFormat.dwFlags = ((nChannels < 3)? 0x00020000 : DDPF_RGB) | ((nChannels & 1)? 0 : DDPF_ALPHAPIXELS);
		if (format <= FORMAT_RGBA8){
			header.ddpfPixelFormat.dwRGBBitCount = 8 * nChannels;
			header.ddpfPixelFormat.dwRBitMask = (nChannels > 2)? 0x00FF0000 : 0xFF;
			header.ddpfPixelFormat.dwGBitMask = (nChannels > 1)? 0x0000FF00 : 0;
			header.ddpfPixelFormat.dwBBitMask = (nChannels > 1)? 0x000000FF : 0;
			header.ddpfPixelFormat.dwRGBAlphaBitMask = (nChannels == 4)? 0xFF000000 : (nChannels == 2)? 0xFF00 : 0;
		} else if (format == FORMAT_I16){
			header.ddpfPixelFormat.dwRGBBitCount = 16;
			header.ddpfPixelFormat.dwRBitMask = 0xFFFF;
		} else {
			header.ddpfPixelFormat.dwRGBBitCount = 32;
			header.ddpfPixelFormat.dwRBitMask = 0x3FF00000;
			header.ddpfPixelFormat.dwGBitMask = 0x000FFC00;
			header.ddpfPixelFormat.dwBBitMask = 0x000003FF;
			header.ddpfPixelFormat.dwRGBAlphaBitMask = 0xC0000000;
		}
	} else {
		header.ddpfPixelFormat.dwFlags = DDPF_FOURCC;

		switch (format){
			case FORMAT_RG16:    header.ddpfPixelFormat.dwFourCC = 34; break;
			case FORMAT_RGBA16:  header.ddpfPixelFormat.dwFourCC = 36; break;
			case FORMAT_R16F:    header.ddpfPixelFormat.dwFourCC = 111; break;
			case FORMAT_RG16F:   header.ddpfPixelFormat.dwFourCC = 112; break;
			case FORMAT_RGBA16F: header.ddpfPixelFormat.dwFourCC = 113; break;
			case FORMAT_R32F:    header.ddpfPixelFormat.dwFourCC = 114; break;
			case FORMAT_RG32F:   header.ddpfPixelFormat.dwFourCC = 115; break;
			case FORMAT_RGBA32F: header.ddpfPixelFormat.dwFourCC = 116; break;
			case FORMAT_DXT1:    header.ddpfPixelFormat.dwFourCC = MCHAR4('D','X','T','1'); break;
			case FORMAT_DXT3:    header.ddpfPixelFormat.dwFourCC = MCHAR4('D','X','T','3'); break;
			case FORMAT_DXT5:    header.ddpfPixelFormat.dwFourCC = MCHAR4('D','X','T','5'); break;
			case FORMAT_ATI1N:   header.ddpfPixelFormat.dwFourCC = MCHAR4('A','T','I','1'); break;
			case FORMAT_ATI2N:   header.ddpfPixelFormat.dwFourCC = MCHAR4('A','T','I','2'); break;
			default:
				header.ddpfPixelFormat.dwFourCC = MCHAR4('D','X','1','0');
				headerDX10.arraySize = 1;
				headerDX10.miscFlag = (depth == 0)? D3D10_RESOURCE_MISC_TEXTURECUBE : 0;
				headerDX10.resourceDimension = is1D()? D3D10_RESOURCE_DIMENSION_TEXTURE1D : is3D()? D3D10_RESOURCE_DIMENSION_TEXTURE3D : D3D10_RESOURCE_DIMENSION_TEXTURE2D;
				switch (format){
					//case FORMAT_RGBA8:    headerDX10.dxgiFormat = 28; break;
					case FORMAT_RGB32F:   headerDX10.dxgiFormat = 6; break;
					case FORMAT_RGB9E5:   headerDX10.dxgiFormat = 67; break;
					case FORMAT_RG11B10F: headerDX10.dxgiFormat = 26; break;
					default:
						return false;
				}
		}
	}

	header.ddsCaps.dwCaps1 = DDSCAPS_TEXTURE | (nMipMaps > 1? DDSCAPS_MIPMAP | DDSCAPS_COMPLEX : 0) | (depth != 1? DDSCAPS_COMPLEX : 0);
	header.ddsCaps.dwCaps2 = (depth > 1)? DDSCAPS2_VOLUME : (depth == 0)? DDSCAPS2_CUBEMAP | DDSCAPS2_CUBEMAP_ALL_FACES : 0;
	header.ddsCaps.Reserved[0] = 0;
	header.ddsCaps.Reserved[1] = 0;
	header.dwReserved2 = 0;

	FILE *file;
	if ((file = fopen(fileName, "wb")) == NULL) return false;

	fwrite(&header, sizeof(header), 1, file);
	if (headerDX10.dxgiFormat) fwrite(&headerDX10, sizeof(headerDX10), 1, file);


	int size = getMipMappedSize(0, nMipMaps);

	// RGB to BGR
	if (format == FORMAT_RGB8 || format == FORMAT_RGBA8) swapChannels(pixels, size / nChannels, nChannels, 0, 2);

	if (isCube()){
		for (int face = 0; face < 6; face++){
			for (int mipMapLevel = 0; mipMapLevel < nMipMaps; mipMapLevel++){
				int faceSize = getMipMappedSize(mipMapLevel, 1) / 6;
                uint8_t *src = getPixels(mipMapLevel) + face * faceSize;
				fwrite(src, 1, faceSize, file);
			}
		}
	} else {
		fwrite(pixels, size, 1, file);
	}
	fclose(file);

	// Restore to RGB
	if (format == FORMAT_RGB8 || format == FORMAT_RGBA8) swapChannels(pixels, size / nChannels, nChannels, 0, 2);

	return true;
}

bool Image::saveImage(const char *fileName){
	const char *extension = strrchr(fileName, '.');

	if (extension != NULL){
		if (stricmp(extension, ".htex") == 0){
			return saveHTEX(fileName);
		} else if (stricmp(extension, ".dds") == 0){
			return saveDDS(fileName);
		}
	}
	return false;
}

void Image::loadFromMemory(void *mem, const FORMAT frmt, const int w, const int h, const int d, const int mipMapCount, bool ownsMemory){
	free();

	width  = w;
	height = h;
	depth  = d;
    format = frmt;
	nMipMaps = mipMapCount;
	arraySize = 1;

	if (ownsMemory){
		pixels = (unsigned char *) mem;
	} else {
		int size = getMipMappedSize(0, nMipMaps);
		pixels = new unsigned char[size];
		memcpy(pixels, mem, size);
	}
}


template <typename DATA_TYPE>
void buildMipMap(DATA_TYPE *dst, const DATA_TYPE *src, const uint32_t w, const uint32_t h, const uint32_t d, const uint32_t c){
	uint32_t xOff = (w < 2)? 0 : c;
	uint32_t yOff = (h < 2)? 0 : c * w;
	uint32_t zOff = (d < 2)? 0 : c * w * h;

	for (uint32_t z = 0; z < d; z += 2){
		for (uint32_t y = 0; y < h; y += 2){
			for (uint32_t x = 0; x < w; x += 2){
				for (uint32_t i = 0; i < c; i++){
					*dst++ = (src[0] + src[xOff] + src[yOff] + src[yOff + xOff] + src[zOff] + src[zOff + xOff] + src[zOff + yOff] + src[zOff + yOff + xOff]) / 8;
					src++;
				}
				src += xOff;
			}
			src += yOff;
		}
		src += zOff;
	}
}

bool Image::createMipMaps(const int mipMaps){
	if (isCompressedFormat(format)) return false;
	if (!isPowerOf2(width) || !isPowerOf2(height) || !isPowerOf2(depth)) return false;

	int actualMipMaps = min(mipMaps, getMipMapCountFromDimesions());

	if (nMipMaps != actualMipMaps){
		int size = getMipMappedSize(0, actualMipMaps);
		if (arraySize > 1){
			uint8_t *newPixels = new uint8_t[size * arraySize];

			// Copy top mipmap of all array slices to new location
			int firstMipSize = getMipMappedSize(0, 1);
			int oldSize = getMipMappedSize(0, nMipMaps);

			for (int i = 0; i < arraySize; i++){
				memcpy(newPixels + i * size, pixels + i * oldSize, firstMipSize);
			}

			delete [] pixels;
			pixels = newPixels;
		} else {
			pixels = (uint8_t *) realloc(pixels, size);
		}
		nMipMaps = actualMipMaps;
	}

	int nChannels = getChannelCount(format);


	int n = isCube()? 6 : 1;

	for (int arraySlice = 0; arraySlice < arraySize; arraySlice++){
		uint8_t *src = getPixels(0, arraySlice);
		uint8_t *dst = getPixels(1, arraySlice);

		for (int level = 1; level < nMipMaps; level++){
			int w = getWidth (level - 1);
			int h = getHeight(level - 1);
			int d = getDepth (level - 1);

			int srcSize = getMipMappedSize(level - 1, 1) / n;
			int dstSize = getMipMappedSize(level,     1) / n;

			for (int i = 0; i < n; i++){
				if (isPlainFormat(format)){
					if (isFloatFormat(format)){
						buildMipMap((float *) dst, (float *) src, w, h, d, nChannels);
					} else if (format >= FORMAT_I16){
						buildMipMap((uint16_t *) dst, (uint16_t *) src, w, h, d, nChannels);
					} else {
						buildMipMap(dst, src, w, h, d, nChannels);
					}
				}
				src += srcSize;
				dst += dstSize;
			}
		}
	}

	return true;
}

bool Image::removeMipMaps(const int firstMipMap, int mipMapsToSave){
	if (arraySize > 1) return false; // TODO: Implement ...
	if (firstMipMap > nMipMaps) return false;

	int mipMapCount = min(firstMipMap + mipMapsToSave, nMipMaps) - firstMipMap;

	int size = getMipMappedSize(firstMipMap, mipMapCount);
	unsigned char *newPixels = new unsigned char[size];

	memcpy(newPixels, getPixels(firstMipMap), size);

	delete [] pixels;
	pixels = newPixels;
	width = getWidth(firstMipMap);
	height = getHeight(firstMipMap);
	depth = depth? getDepth(firstMipMap) : 0;
	nMipMaps = mipMapCount;

	return true;
}

void decodeColorBlock(unsigned char *dest, int w, int h, int xOff, int yOff, FORMAT format, int red, int blue, unsigned char *src){
	unsigned char colors[4][3];

	uint16_t c0 = *(uint16_t *) src;
	uint16_t c1 = *(uint16_t *) (src + 2);
	
	colors[0][0] = ((c0 >> 11) & 0x1F) << 3;
	colors[0][1] = ((c0 >>  5) & 0x3F) << 2;
	colors[0][2] =  (c0        & 0x1F) << 3;
	
	colors[1][0] = ((c1 >> 11) & 0x1F) << 3;
	colors[1][1] = ((c1 >>  5) & 0x3F) << 2;
	colors[1][2] =  (c1        & 0x1F) << 3;

	if (c0 > c1 || format == FORMAT_DXT5){
		for (int i = 0; i < 3; i++){
			colors[2][i] = (2 * colors[0][i] +     colors[1][i] + 1) / 3;
			colors[3][i] = (    colors[0][i] + 2 * colors[1][i] + 1) / 3;
		}
	} else {
		for (int i = 0; i < 3; i++){
			colors[2][i] = (colors[0][i] + colors[1][i] + 1) >> 1;
			colors[3][i] = 0;
		}
	}

	src += 4;
	for (int y = 0; y < h; y++){
		unsigned char *dst = dest + yOff * y;
		unsigned int indexes = src[y];
		for (int x = 0; x < w; x++){
			unsigned int index = indexes & 0x3;
			dst[red]  = colors[index][0];
			dst[1]    = colors[index][1];
			dst[blue] = colors[index][2];
			indexes >>= 2;

			dst += xOff;
		}
	}
}

void decodeDXT3AlphaBlock(unsigned char *dest, int w, int h, int xOff, int yOff, unsigned char *src){
	for (int y = 0; y < h; y++){
		unsigned char *dst = dest + yOff * y;
		unsigned int alpha = ((unsigned short *) src)[y];
		for (int x = 0; x < w; x++){
			*dst = (alpha & 0xF) * 17;
			alpha >>= 4;
			dst += xOff;
		}
	}
}

void decodeDXT5AlphaBlock(unsigned char *dest, int w, int h, int xOff, int yOff, unsigned char *src){
	unsigned char a0 = src[0];
	unsigned char a1 = src[1];
	uint64_t alpha = (*(uint64_t *) src) >> 16;

	for (int y = 0; y < h; y++){
		unsigned char *dst = dest + yOff * y;
		for (int x = 0; x < w; x++){
			int k = ((unsigned int) alpha) & 0x7;
			if (k == 0){
				*dst = a0;
			} else if (k == 1){
				*dst = a1;
			} else if (a0 > a1){
				*dst = ((8 - k) * a0 + (k - 1) * a1) / 7;
			} else if (k >= 6){
				*dst = (k == 6)? 0 : 255;
			} else {
				*dst = ((6 - k) * a0 + (k - 1) * a1) / 5;
			}
			alpha >>= 3;

			dst += xOff;
		}
		if (w < 4) alpha >>= (3 * (4 - w));
	}
}

void decodeCompressedImage(unsigned char *dest, unsigned char *src, const int width, const int height, const FORMAT format){
	int sx = (width  < 4)? width  : 4;
	int sy = (height < 4)? height : 4;

	int nChannels = getChannelCount(format);

	for (int y = 0; y < height; y += 4){
		for (int x = 0; x < width; x += 4){
			unsigned char *dst = dest + (y * width + x) * nChannels;
			if (format == FORMAT_DXT3){
				decodeDXT3AlphaBlock(dst + 3, sx, sy, nChannels, width * nChannels, src);
				src += 8;
			} else if (format == FORMAT_DXT5){
				decodeDXT5AlphaBlock(dst + 3, sx, sy, nChannels, width * nChannels, src);
				src += 8;
			}
			if (format <= FORMAT_DXT5){
				decodeColorBlock(dst, sx, sy, nChannels, width * nChannels, format, 0, 2, src);
				src += 8;
			} else {
				if (format == FORMAT_ATI1N){
					decodeDXT5AlphaBlock(dst, sx, sy, 1, width, src);
					src += 8;
				} else {
					decodeDXT5AlphaBlock(dst,     sx, sy, 2, width * 2, src + 8);
					decodeDXT5AlphaBlock(dst + 1, sx, sy, 2, width * 2, src);
					src += 16;
				}
			}
		}
	}
}

bool Image::uncompressImage(){
	if (isCompressedFormat(format)){
		FORMAT destFormat;
		if (format >= FORMAT_ATI1N){
			destFormat = (format == FORMAT_ATI1N)? FORMAT_I8 : FORMAT_IA8;
		} else {
			destFormat = (format == FORMAT_DXT1)? FORMAT_RGB8 : FORMAT_RGBA8;
		}

		uint8_t *newPixels = new uint8_t[getMipMappedSize(0, nMipMaps, destFormat)];

		int level = 0;
		uint8_t *src, *dst = newPixels;
		while ((src = getPixels(level)) != NULL){
			int w = getWidth(level);
			int h = getHeight(level);
			int d = (depth == 0)? 6 : getDepth(level);

			int dstSliceSize = getSliceSize(level, destFormat);
			int srcSliceSize = getSliceSize(level, format);

			for (int slice = 0; slice < d; slice++){
				decodeCompressedImage(dst, src, w, h, format);

				dst += dstSliceSize;
				src += srcSliceSize;
			}
			level++;
		}

		format = destFormat;
		
		free();
		pixels = newPixels;
	}

	return true;
}

bool Image::unpackImage(){
	int pixelCount = getPixelCount(0, nMipMaps);

	uint8_t *newPixels;
	if (format == FORMAT_RGBE8){
		format = FORMAT_RGB32F;
		newPixels = new unsigned char[getMipMappedSize(0, nMipMaps)];

		for (int i = 0; i < pixelCount; i++){
			((Vectormath::Aos::Vector3 *) newPixels)[i] = rgbeToRGB(pixels + 4 * i);
		}

	} else if (format == FORMAT_RGB565){
		format = FORMAT_RGB8;
		newPixels = new unsigned char[getMipMappedSize(0, nMipMaps)];

		for (int i = 0; i < pixelCount; i++){
			unsigned int rgb565 = ((unsigned short *) pixels)[i];
			newPixels[3 * i    ] = ((rgb565 >> 11) * 2106) >> 8;
			newPixels[3 * i + 1] = ((rgb565 >> 5) & 0x3F) * 1037 >> 8;
			newPixels[3 * i + 2] = ((rgb565 & 0x1F) * 2106) >> 8;
		}
	} else if (format == FORMAT_RGBA4){
		format = FORMAT_RGBA8;
		newPixels = new unsigned char[getMipMappedSize(0, nMipMaps)];

		for (int i = 0; i < pixelCount; i++){
			newPixels[4 * i    ] = (pixels[2 * i + 1] & 0xF) * 17;
			newPixels[4 * i + 1] = (pixels[2 * i]     >>  4) * 17;
			newPixels[4 * i + 2] = (pixels[2 * i]     & 0xF) * 17;
			newPixels[4 * i + 3] = (pixels[2 * i + 1] >>  4) * 17;
		}
	} else if (format == FORMAT_RGB10A2){
		format = FORMAT_RGBA16;
		newPixels = new unsigned char[getMipMappedSize(0, nMipMaps)];

		for (int i = 0; i < pixelCount; i++){
			uint32_t src = ((uint32_t *) pixels)[i];
			((uint16_t *) newPixels)[4 * i    ] = (((src      ) & 0x3FF) * 4198340) >> 16;
			((uint16_t *) newPixels)[4 * i + 1] = (((src >> 10) & 0x3FF) * 4198340) >> 16;
			((uint16_t *) newPixels)[4 * i + 2] = (((src >> 20) & 0x3FF) * 4198340) >> 16;
			((uint16_t *) newPixels)[4 * i + 3] = (((src >> 30) & 0x003) * 21845);
		}
	} else {
		return false;
	}

	delete [] pixels;
	pixels = newPixels;

	return true;
}

bool Image::convert(const FORMAT newFormat){
	uint8_t *newPixels;
	uint32_t nPixels = getPixelCount(0, nMipMaps) * arraySize;

	if (format == FORMAT_RGBE8 && (newFormat == FORMAT_RGB32F || newFormat == FORMAT_RGBA32F)){
		newPixels = new uint8_t[getMipMappedSize(0, nMipMaps, newFormat) * arraySize];
		float *dest = (float *) newPixels;

		bool writeAlpha = (newFormat == FORMAT_RGBA32F);
		uint8_t *src = pixels;
		do {
			*((Vectormath::Aos::Vector3 *) dest) = rgbeToRGB(src);
			if (writeAlpha){
				dest[3] = 1.0f;
				dest += 4;
			} else {
				dest += 3;
			}
			src += 4;
		} while (--nPixels);

	} else {
		if (!isPlainFormat(format) || !(isPlainFormat(newFormat) || newFormat == FORMAT_RGB10A2 || newFormat == FORMAT_RGBE8 || newFormat == FORMAT_RGB9E5)) return false;
		if (format == newFormat) return true;

		uint8_t *src = pixels;
		uint8_t *dest = newPixels = new uint8_t[getMipMappedSize(0, nMipMaps, newFormat) * arraySize];

		if (format == FORMAT_RGB8 && newFormat == FORMAT_RGBA8){
			// Fast path for RGB->RGBA8
			do {
				dest[0] = src[0];
				dest[1] = src[1];
				dest[2] = src[2];
				dest[3] = 255;
				dest += 4;
				src += 3;
			} while (--nPixels);

		} else {
			int srcSize = getBytesPerPixel(format);
			int nSrcChannels = getChannelCount(format);

			int destSize = getBytesPerPixel(newFormat);
			int nDestChannels = getChannelCount(newFormat);

			do {
				float rgba[4];

				if (isFloatFormat(format)){
					if (format <= FORMAT_RGBA16F){
						for (int i = 0; i < nSrcChannels; i++) rgba[i] = ((uint16_t *) src)[i];
					} else {
						for (int i = 0; i < nSrcChannels; i++) rgba[i] = ((float *) src)[i];
					}
				} else if (format >= FORMAT_I16 && format <= FORMAT_RGBA16){
					for (int i = 0; i < nSrcChannels; i++) rgba[i] = ((uint16_t *) src)[i] * (1.0f / 65535.0f);
				} else {
					for (int i = 0; i < nSrcChannels; i++) rgba[i] = src[i] * (1.0f / 255.0f);
				}
				if (nSrcChannels  < 4) rgba[3] = 1.0f;
				if (nSrcChannels == 1) rgba[2] = rgba[1] = rgba[0];
				
				if (nDestChannels == 1)	rgba[0] = 0.30f * rgba[0] + 0.59f * rgba[1] + 0.11f * rgba[2];

				if (isFloatFormat(newFormat)){
					if (newFormat <= FORMAT_RGBA32F){
						if (newFormat <= FORMAT_RGBA16F){
							for (int i = 0; i < nDestChannels; i++)	((uint16_t *) dest)[i] = rgba[i];
						} else {
							for (int i = 0; i < nDestChannels; i++)	((float *) dest)[i] = rgba[i];
						}
					} else {
						if (newFormat == FORMAT_RGBE8){
							*(uint32_t *) dest = rgbToRGBE8(Vectormath::Aos::Vector3(rgba[0], rgba[1], rgba[2]));
						} else {
							*(uint32_t *) dest = rgbToRGB9E5(Vectormath::Aos::Vector3(rgba[0], rgba[1], rgba[2]));
						}
					}
				} else if (newFormat >= FORMAT_I16 && newFormat <= FORMAT_RGBA16){
					for (int i = 0; i < nDestChannels; i++)	((uint16_t *) dest)[i] = (uint16_t) (65535 * saturate(rgba[i]) + 0.5f);
				} else if (/*isPackedFormat(newFormat)*/newFormat == FORMAT_RGB10A2){
					*(uint32_t *) dest =
						(uint32_t(1023.0f * saturate(rgba[0]) + 0.5f) << 22) |
						(uint32_t(1023.0f * saturate(rgba[1]) + 0.5f) << 12) |
						(uint32_t(1023.0f * saturate(rgba[2]) + 0.5f) <<  2) |
						(uint32_t(   3.0f * saturate(rgba[3]) + 0.5f));
				} else {
					for (int i = 0; i < nDestChannels; i++)	dest[i] = (unsigned char) (255 * saturate(rgba[i]) + 0.5f);
				}

				src  += srcSize;
				dest += destSize;
			} while (--nPixels);
		}
	}
	delete [] pixels;
	pixels = newPixels;
	format = newFormat;

	return true;
}

bool Image::swap(const int ch0, const int ch1){
	if (!isPlainFormat(format)) return false;

	unsigned int nPixels = getPixelCount(0, nMipMaps) * arraySize;
	unsigned int nChannels = getChannelCount(format);

	if (format <= FORMAT_RGBA8){
		swapChannels((unsigned char *) pixels, nPixels, nChannels, ch0, ch1);
	} else if (format <= FORMAT_RGBA16F){
		swapChannels((unsigned short *) pixels, nPixels, nChannels, ch0, ch1);
	} else {
		swapChannels((float *) pixels, nPixels, nChannels, ch0, ch1);
	}

	return true;
}

bool Image::flipX(){
	// TODO: Implement ...
	return false;
}

bool Image::flipY(){
	if (arraySize > 1) return false; // TODO: Implement ...
	if (isCompressedFormat(format)) return false;

	uint8_t *newPixels = new uint8_t[getMipMappedSize(0, nMipMaps)];
	uint8_t *dst = newPixels;

	int bytes = getBytesPerPixel(format);

	for (int i = 0; i < nMipMaps; i++){
		int w = getWidth(i);
		int h = getHeight(i);

		int lineWidth = w * bytes;

		uint8_t *src = getPixels(i) + (h - 1) * lineWidth;

		for (int y = 0; y < h; y++){
			memcpy(dst, src, lineWidth);

			dst += lineWidth;
			src -= lineWidth;
		}
	}


	delete [] pixels;
	pixels = newPixels;

	return true;
}

bool Image::dilate(){
	if (format != FORMAT_R8)
		return false;

	uint8_t *newPixels = new uint8_t[getMipMappedSize(0, nMipMaps)];
	uint8_t *dst = newPixels;

	//int ch = getChannelCount(format);

	for (int i = 0; i < nMipMaps; i++){
		int w = getWidth(i);
		int h = getHeight(i);

		uint8_t *src = getPixels(i);

		for (int y = 0; y < h; y++){
			for (int x = 0; x < w; x++){
				int startX = max(x - 1, 0);
				int endX = min(x + 2, w);
				int startY = max(y - 1, 0);
				int endY = min(y + 2, h);

				uint8_t max = 0;
				for (int iy = startY; iy < endY; iy++)
				{
					for (int ix = startX; ix < endX; ix++)
					{
						uint8_t c = src[iy * w + ix];
						if (c > max)
							max = c;
					}
				}

				*dst++ = max;
			}
		}
	}


	delete [] pixels;
	pixels = newPixels;

	return true;
}

bool Image::erode(){
	if (format != FORMAT_R8)
		return false;

	uint8_t *newPixels = new uint8_t[getMipMappedSize(0, nMipMaps)];
	uint8_t *dst = newPixels;

	//int ch = getChannelCount(format);

	for (int i = 0; i < nMipMaps; i++){
		int w = getWidth(i);
		int h = getHeight(i);

		uint8_t *src = getPixels(i);

		for (int y = 0; y < h; y++){
			for (int x = 0; x < w; x++){
				int startX = max(x - 1, 0);
				int endX = min(x + 2, w);
				int startY = max(y - 1, 0);
				int endY = min(y + 2, h);

				uint8_t min = 0xFF;
				for (int iy = startY; iy < endY; iy++)
				{
					for (int ix = startX; ix < endX; ix++)
					{
						uint8_t c = src[iy * w + ix];
						if (c < min)
							min = c;
					}
				}

				*dst++ = min;
			}
		}
	}


	delete [] pixels;
	pixels = newPixels;

	return true;
}

bool Image::toRGBD16(){
	if (arraySize > 1) return false; // TODO: Implement ...
	if (format != FORMAT_RGB32F) return false;

	uint32_t nPixels = getPixelCount(0, nMipMaps);
	float *src = (float *) pixels;

	uint16_t *newPixels = new uint16_t[nPixels * 4];
	for (uint32_t i = 0; i < nPixels; i++){
		float maxChannel = max(max(max(src[3 * i], src[3 * i + 1]), src[3 * i + 2]), 1.0f);

		newPixels[4 * i + 0] = (uint16_t) (65535 * (src[3 * i + 0] / maxChannel));
		newPixels[4 * i + 1] = (uint16_t) (65535 * (src[3 * i + 1] / maxChannel));
		newPixels[4 * i + 2] = (uint16_t) (65535 * (src[3 * i + 2] / maxChannel));
		newPixels[4 * i + 3] = (uint16_t) (65535 * (1.0f / maxChannel));
	}

	delete [] pixels;
	pixels = (uint8_t *) newPixels;
	format = FORMAT_RGBA16;

	return true;
}


// TODO: Take care of black pixels ...
//       Best would be to set RGB to zero and use an exponent that's the average of the surrounding pixels
bool Image::toRGBE16(float &scale, float &bias){
	if (arraySize > 1) return false; // TODO: Implement ...
	if (format != FORMAT_RGB32F) return false;

	uint32_t nPixels = getPixelCount(0, nMipMaps);

	float maxExp = -1e10f;
	float minExp =  1e10f;

	float *src = (float *) pixels;
	for (uint32_t i = 0; i < nPixels; i++){
        float maxChannel = max(max(src[3 * i], src[3 * i + 1]), src[3 * i + 2]);

		if (maxChannel > maxExp) maxExp = maxChannel;
		if (maxChannel < minExp) minExp = maxChannel;
	}

	const float invLog2 = 1.0f / logf(2.0f);

	maxExp = logf(maxExp) * invLog2;
	minExp = logf(minExp) * invLog2;

	scale = maxExp - minExp;
	bias  = minExp;

	uint16_t *newPixels = new uint16_t[nPixels * 4];
	for (uint32_t i = 0; i < nPixels; i++){
		float maxChannel = max(max(src[3 * i], src[3 * i + 1]), src[3 * i + 2]);
		float chExp = logf(maxChannel) * invLog2;

		newPixels[4 * i + 0] = (uint16_t) (65535 * src[3 * i + 0] / maxChannel);
		newPixels[4 * i + 1] = (uint16_t) (65535 * src[3 * i + 1] / maxChannel);
		newPixels[4 * i + 2] = (uint16_t) (65535 * src[3 * i + 2] / maxChannel);
		newPixels[4 * i + 3] = (uint16_t) (65535 * saturate((chExp - bias) / scale));
	}


	delete [] pixels;
	pixels = (uint8_t *) newPixels;
	format = FORMAT_RGBA16;

	return true;
}

bool Image::toE16(float *scale, float *bias, const bool useAllSameRange, const float minValue, const float maxValue){
	if (arraySize > 1) return false; // TODO: Implement ...
	if (format < FORMAT_I32F || format > FORMAT_RGBA32F) return false;

	uint32_t nPixels = getPixelCount(0, nMipMaps);
	uint32_t nChannels = getChannelCount(format);
	uint32_t nElements = nPixels * nChannels;

	uint32_t nRanges = useAllSameRange? 1 : nChannels;


	float maxExp[4] = { minValue, minValue, minValue, minValue };
	float minExp[4] = { maxValue, maxValue, maxValue, maxValue };

	float *src = (float *) pixels;
	for (uint32_t i = 0; i < nElements; i += nRanges){
		for (uint32_t k = 0; k < nRanges; k++){
			float val = min(max(src[i + k], minValue), maxValue);
			if (val > maxExp[k]) maxExp[k] = val;
			if (val < minExp[k]) minExp[k] = val;
		}
	}

	const float invLog2 = 1.0f / logf(2.0f);

	for (uint32_t k = 0; k < nRanges; k++){
		maxExp[k] = logf(maxExp[k]) * invLog2;
		minExp[k] = logf(minExp[k]) * invLog2;

		scale[k] = maxExp[k] - minExp[k];
		bias[k]  = minExp[k];
	}

	uint16_t *newPixels = new uint16_t[nElements];
	for (uint32_t i = 0; i < nElements; i += nRanges){
		for (uint32_t k = 0; k < nRanges; k++){
			if (src[i + k] > minValue){
				if (src[i + k] < maxValue){
					float chExp = logf(src[i + k]) * invLog2;
					newPixels[i + k] = (uint16_t) (65535 * (chExp - bias[k]) / scale[k]);
				} else {
					newPixels[i + k] = 65535;
				}
			} else {
				newPixels[i + k] = 0;
			}
		}
	}

	delete [] pixels;
	pixels = (uint8_t *) newPixels;
	format = (FORMAT) ((FORMAT_I16 - 1) + nChannels);

	return true;
}


bool Image::toFixedPointHDR(float *maxValue, const int finalRgbBits, const int finalRangeBits){
	if (arraySize > 1) return false; // TODO: Implement ...
	if (format != FORMAT_RGB32F) return false;

	float rgbScale = float(1 << finalRgbBits);
	float rangeScale = float(1 << finalRangeBits);

	float clampVal = *maxValue;

	float *src = (float *) pixels;
	uint32_t nPixels = getPixelCount(0, nMipMaps);

	float maxVal = 0;
	for (uint32_t i = 0; i < 3 * nPixels; i++){
        if (src[i] > maxVal) maxVal = src[i];
	}
	if (maxVal > clampVal) maxVal = clampVal;

	uint16_t *newPixels = new uint16_t[4 * nPixels];
	for (uint32_t i = 0; i < nPixels; i++){
		float r = min(src[3 * i + 0], clampVal);
		float g = min(src[3 * i + 1], clampVal);
		float b = min(src[3 * i + 2], clampVal);

		float maxChannel = max(max(r, g), b);
		//float minChannel = min(min(r, g), b);

		r /= maxChannel;
		g /= maxChannel;
		b /= maxChannel;
		float range = maxChannel / maxVal;

/*
		r = sqrtf(r);
		g = sqrtf(g);
		b = sqrtf(b);
		range = sqrtf(range);
*/

		/*
			If range gets too small, scale it up and scale down rgb so that the lowest
			channel's value is equal to range. This gives us a much better distribution
			of bits for low values.
		*/
		//float rgbMin = minChannel / maxChannel;
		//if (range * rangeScale < rgbMin * rgbScale){
			//float f = sqrtf((rgbMin * rgbScale) / (range * rangeScale));
			float f = sqrtf(range * rangeScale / rgbScale);

			//float f = powf(range * rangeScale / rgbScale, 1.0f / 3.0f);

//			f = 1.0f;

			range /= f;
//			f *= f;
			r *= f;
			g *= f;
			b *= f;
		//}

		newPixels[4 * i + 0] = (uint16_t) (65535 * r);
		newPixels[4 * i + 1] = (uint16_t) (65535 * g);
		newPixels[4 * i + 2] = (uint16_t) (65535 * b);
		newPixels[4 * i + 3] = (uint16_t) (65535 * range);
	}


	format = FORMAT_RGBA16;

	delete [] pixels;
	pixels = (uint8_t *) newPixels;

	*maxValue = maxVal;
	return true;
}

bool Image::toNormalMap(FORMAT destFormat, float sZ, float mipMapScaleZ){
	if (arraySize > 1) return false; // TODO: Implement ...
	if (format == FORMAT_RGB8 || format == FORMAT_RGBA8) toGrayScale();
	if (format != FORMAT_I8) return false;
	
	uint32_t xMask = 0, yMask = 0, zMask = 0, hMask = 0;
	uint32_t xShift = 0, yShift = 0, zShift = 0, hShift = 0, hFactor = 1;

	switch (destFormat){
		case FORMAT_RG8:
		case FORMAT_RG8S:
			xMask = yMask = 0xFF;
			xShift = 8;
			break;
		case FORMAT_RGB565:
			xMask = zMask = 0x1F;
			yMask = 0x3F;
			xShift = 11;
			yShift = 5;
			break;
		case FORMAT_RGBA4:
			xMask = yMask = zMask = hMask = 0xF;
			yShift = 4;
			zShift = 8;
			hShift = 12;
			break;
		case FORMAT_RGBA8:
		case FORMAT_RGBA8S:
			xMask = yMask = zMask = hMask = 0xFF;
			yShift = 8;
			zShift = 16;
			hShift = 24;
			break;
		case FORMAT_RGB10A2:
			xMask = yMask = zMask = 0x3FF;
			hMask = 0x03;
			yShift = 10;
			zShift = 20;
			hShift = 30;
			break;
		case FORMAT_RGBA16:
		case FORMAT_RGBA16S:
			xMask = yMask = zMask = hMask = 0xFFFF;
			yShift = 16;
			zShift = 32;
			hShift = 48;
			hFactor = 257;
			break;
		default:
			return false;
	}

	const float sobelX[5][5] = {
		{ 1,  2,  0,  -2, -1 },
		{ 4,  8,  0,  -8, -4 },
		{ 6, 12,  0, -12, -6 },
		{ 4,  8,  0,  -8, -4 },
		{ 1,  2,  0,  -2, -1 },
	};
	const float sobelY[5][5] = {
		{  1,  4,   6,  4,  1 },
		{  2,  8,  12,  8,  2 },
		{  0,  0,   0,  0,  0 },
		{ -2, -8, -12, -8, -2 },
		{ -1, -4,  -6, -4, -1 },
	};

	int bpp = getBytesPerPixel(destFormat);
	bool use16 = (bpp == 2);
	bool use32 = (bpp == 4);

	float xFactor = 0.5f * xMask;
	float yFactor = 0.5f * yMask;
	float zFactor = 0.5f * zMask;
	float bias = isSignedFormat(destFormat)? 0.0f : 1.0f;


	// Size of the z component
	sZ *= 128.0f / max(width, height);

	uint8_t *newPixels = new uint8_t[getMipMappedSize(0, nMipMaps, destFormat)];

	union {
		uint16_t *dest16;
		uint32_t *dest32;
		uint64_t *dest64;
	};
	dest32 = (uint32_t *) newPixels;

	for (int mipMap = 0; mipMap < nMipMaps; mipMap++){
		uint8_t *src = getPixels(mipMap);

		int w = getWidth(mipMap);
		int h = getHeight(mipMap);

		for (int y = 0; y < h; y++){
			for (int x = 0; x < w; x++){
				// Apply a 5x5 Sobel filter
				float sX = 0;
				float sY = 0;
				for (int dy = 0; dy < 5; dy++){
					int fy = (y + dy - 2 + h) % h;
					for (int dx = 0; dx < 5; dx++){
						int fx = (x + dx - 2 + w) % w;
						sX += sobelX[dy][dx] * src[fy * w + fx];
						sY += sobelY[dy][dx] * src[fy * w + fx];
					}
				}
				// Construct the components
				sX *= 1.0f / (48 * 255);
				sY *= 1.0f / (48 * 255);

				// Normalize and store
				float invLen = 1.0f / sqrtf(sX * sX + sY * sY + sZ * sZ);
				float rX = xFactor * (sX * invLen + bias);
				float rY = yFactor * (sY * invLen + bias);
				float rZ = zFactor * (sZ * invLen + bias);

				uint64_t result = 0;
				result |= uint64_t(int(rX) & xMask) << xShift;
				result |= uint64_t(int(rY) & yMask) << yShift;
				result |= uint64_t(int(rZ) & zMask) << zShift;
				result |= uint64_t((src[y * w + x] * hFactor) & hMask) << hShift;

				if (use32){
                    *dest32++ = (uint32_t) result;
				} else if (use16){
                    *dest16++ = (uint16_t) result;
				} else {
					*dest64++ = result;
				}
			}
		}
		sZ *= mipMapScaleZ;
	}

	format = destFormat;
	delete [] pixels;
	pixels = newPixels;

	return true;
}

bool Image::toGrayScale(){
	int nChannels = getChannelCount(format);

	if (!isPlainFormat(format) || isFloatFormat(format) || nChannels < 3) return false;

	uint32_t len = getPixelCount(0, nMipMaps) * arraySize;
	uint32_t size = len;

	if (format <= FORMAT_RGBA8){
		uint8_t *src = pixels, *dest = pixels;
		do {
			*dest++ = (77 * src[0] + 151 * src[1] + 28 * src[2] + 128) >> 8;
			src += nChannels;
		} while (--len);

		format = FORMAT_I8;
	} else {
		uint16_t *src = (uint16_t *) pixels, *dest = (uint16_t *) pixels;
		do {
			*dest++ = (77 * src[0] + 151 * src[1] + 28 * src[2] + 128) >> 8;
			src += nChannels;
		} while (--len);

		format = FORMAT_I16;
		size *= 2;
	}

	pixels = (uint8_t *) realloc(pixels, size);

	return true;
}

bool Image::getRange(float &min, float &max){
	// Only float supported at this point
	if (format < FORMAT_R32F || format > FORMAT_RGBA32F) return false;

	int nElements = getPixelCount(0, nMipMaps) * getChannelCount(format) * arraySize;
	if (nElements <= 0) return false;

	float minVal =  FLT_MAX;
	float maxVal = -FLT_MAX;
	for (int i = 0; i < nElements; i++){
		float d = ((float *) pixels)[i];
		if (d < minVal) minVal = d;
		if (d > maxVal) maxVal = d;
	}
	min = minVal;
	max = maxVal;

	return true;
}

bool Image::scaleBias(const float scale, const float bias){
	// Only float supported at this point
	if (format < FORMAT_R32F || format > FORMAT_RGBA32F) return false;

	int nElements = getPixelCount(0, nMipMaps) * getChannelCount(format) * arraySize;

	for (int i = 0; i < nElements; i++){
		float d = ((float *) pixels)[i];
		((float *) pixels)[i] = d * scale + bias;
	}

	return true;
}

bool Image::normalize(){
	// Only float supported at this point
	if (format < FORMAT_R32F || format > FORMAT_RGBA32F) return false;

	float min, max;
	getRange(min, max);

	int nElements = getPixelCount(0, nMipMaps) * getChannelCount(format) * arraySize;

	float s = 1.0f / (max - min);
	float b = -min * s;
	for (int i = 0; i < nElements; i++){
		float d = ((float *) pixels)[i];
		((float *) pixels)[i] = d * s + b;
	}

	return true;
}

bool Image::removeChannels(bool keepCh0, bool keepCh1, bool keepCh2, bool keepCh3){
	if (!isPlainFormat(format)) return false;

	uint32_t srcChannels = getChannelCount(format);
	if (srcChannels < 4) keepCh3 = false;
	if (srcChannels < 3) keepCh2 = false;
	if (srcChannels < 2) keepCh1 = false;

	if (!(keepCh0 || keepCh1 || keepCh2 || keepCh3)) return false;
	uint32_t destChannels = int(keepCh0) + int(keepCh1) + int(keepCh2) + int(keepCh3);
	if (srcChannels == destChannels) return true;


	uint32_t nPixels = getPixelCount(0, nMipMaps) * arraySize;
	uint32_t bpc = getBytesPerChannel(format);

	format = (FORMAT) (format + (destChannels - srcChannels));
	uint8_t *newPixels = new uint8_t[getMipMappedSize(0, nMipMaps) * arraySize];

	if (bpc == 1){
		uint8_t *src = pixels;
		uint8_t *dst = newPixels;
		do {
			if (keepCh0) *dst++ = src[0];
			if (keepCh1) *dst++ = src[1];
			if (keepCh2) *dst++ = src[2];
			if (keepCh3) *dst++ = src[3];
			src += srcChannels;
		} while (--nPixels);
	} else if (bpc == 2){
		uint16_t *src = (uint16_t *) pixels;
		uint16_t *dst = (uint16_t *) newPixels;
		do {
			if (keepCh0) *dst++ = src[0];
			if (keepCh1) *dst++ = src[1];
			if (keepCh2) *dst++ = src[2];
			if (keepCh3) *dst++ = src[3];
			src += srcChannels;
		} while (--nPixels);
	} else {
		uint32_t *src = (uint32_t *) pixels;
		uint32_t *dst = (uint32_t *) newPixels;
		do {
			if (keepCh0) *dst++ = src[0];
			if (keepCh1) *dst++ = src[1];
			if (keepCh2) *dst++ = src[2];
			if (keepCh3) *dst++ = src[3];
			src += srcChannels;
		} while (--nPixels);
	}

	delete [] pixels;
	pixels = newPixels;

	return true;
}
