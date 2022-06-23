
#ifndef _BITMAP_H
#define _BITMAP_H

#include <iostream>
#include <fstream>
#include <string>

#include "debug/trace.h"

#ifndef __LITTLE_ENDIAN__
#ifndef __BIG_ENDIAN__
#define __LITTLE_ENDIAN__
#endif
#endif

#ifdef __LITTLE_ENDIAN__
#define BITMAP_SIGNATURE 0x4d42
#else
#define BITMAP_SIGNATURE 0x424d
#endif

#if defined(_MSC_VER) || defined(__INTEL_COMPILER)
typedef unsigned __int32 uint32_t;
typedef unsigned __int16 uint16_t;
typedef unsigned __int8 uint8_t;
typedef __int32 int32_t;
#elif defined(__GNUC__) || defined(__CYGWIN__) || defined(__MWERKS__) || defined(__WATCOMC__) || defined(__PGI) || defined(__LCC__)
#include <stdint.h>
#else
typedef unsigned int uint32_t;
typedef unsigned short int uint16_t;
typedef unsigned char uint8_t;
typedef int int32_t;
#endif


#pragma pack(push, 1)

namespace FI { namespace GFX { namespace IMAGE {

typedef struct _BITMAP_FILEHEADER 
{
	uint16_t signature;
	uint32_t size;
	uint32_t reserved;
	uint32_t bitsOffset;
} BITMAP_FILEHEADER;

#define BITMAP_FILEHEADER_SIZE 14

typedef struct _BITMAP_HEADER 
{
	uint32_t headerSize;
	int32_t width;
	int32_t height;
	uint16_t planes;
	uint16_t bitCount;
	uint32_t compression;
	uint32_t sizeImage;
	int32_t pelsPerMeterX;
	int32_t pelsPerMeterY;
	uint32_t clrUsed;
	uint32_t clrImportant;
	uint32_t redMask;
	uint32_t greenMask;
	uint32_t blueMask;
	uint32_t alphaMask;
	uint32_t csType;
	uint32_t endpoints[9]; // see http://msdn2.microsoft.com/en-us/library/ms536569.aspx
	uint32_t gammaRed;
	uint32_t gammaGreen;
	uint32_t gammaBlue;
} BITMAP_HEADER;

typedef struct _RGBA 
{
	uint8_t red;
	uint8_t green;
	uint8_t blue;
	uint8_t alpha;
} RGBA;

typedef struct _BGRA {
	uint8_t blue;
	uint8_t green;
	uint8_t red;
	uint8_t alpha;
} BGRA;

#pragma pack(pop)

class Bitmap 
{
private:
	BITMAP_FILEHEADER m_bitmapFileHeader;
	BITMAP_HEADER m_bitmapHeader;
	RGBA *m_bitmapData;
	unsigned int m_bitmapSize;
	
	// Masks and bit counts shouldn't exceed 32 Bits
public:

	class Color 
	{
    public:
		static inline unsigned int bitCountByMask(unsigned int mask) 
		{
			unsigned int bitCount = 0;
			while (mask) 
			{
				mask &= mask - 1;
				bitCount++;
			}
			return bitCount;
		}
        
		static inline unsigned int bitPositionByMask(unsigned int mask) 
		{
			return bitCountByMask((mask & (~mask + 1)) - 1);
		}
        
		static inline unsigned int componentByMask(unsigned int color, unsigned int mask) 
		{
			unsigned int component = color & mask;
			return component >> bitPositionByMask(mask);
		}
        
		static inline unsigned int bitCountToMask(unsigned int bitCount) 
		{
			return (bitCount == 32) ? 0xFFFFFFFF : (1 << bitCount) - 1;
		}
        
		static unsigned int convert(unsigned int color, unsigned int fromBitCount, unsigned int toBitCount) 
		{
			if (toBitCount < fromBitCount) 
			{
				color >>= (fromBitCount - toBitCount);
			} 
			else 
			{
				color <<= (toBitCount - fromBitCount);
				if (color > 0) 
				{
					color |= bitCountToMask(toBitCount - fromBitCount);
				}
			}
			return color;
		}
	};
    
public:
	
	Bitmap();
	Bitmap(const char* filename);
	~Bitmap();
	
	void dispose();
	
	/* Load specified Bitmap and stores it as RGBA in an internal buffer */
	bool load(const char *filename);	
	
	bool save(const char *filename, unsigned int bitCount = 32);
	bool saveRGBA(const char *filename, unsigned int width, unsigned int height, uint8_t* data);
    
	unsigned int getWidth();
	unsigned int getHeight();
	unsigned int getBitCount();
	int getHeaderWidth();
	int getHeaderHeight();

	/* Copies internal RGBA buffer to user specified buffer */
	bool getBits(void* buffer, unsigned int &size);
	
	/* Returns internal RGBA buffer */	
	void* getBits();

	/* Copies internal RGBA buffer to user specified buffer and converts it into destination
	 * bit format specified by component masks.
	 *
	 * Typical Bitmap color formats (BGR/BGRA):
	 *
	 * Masks for 16 bit (5-5-5): ALPHA = 0x00000000, RED = 0x00007C00, GREEN = 0x000003E0, BLUE = 0x0000001F
	 * Masks for 16 bit (5-6-5): ALPHA = 0x00000000, RED = 0x0000F800, GREEN = 0x000007E0, BLUE = 0x0000001F
	 * Masks for 24 bit: ALPHA = 0x00000000, RED = 0x00FF0000, GREEN = 0x0000FF00, BLUE = 0x000000FF
	 * Masks for 32 bit: ALPHA = 0xFF000000, RED = 0x00FF0000, GREEN = 0x0000FF00, BLUE = 0x000000FF
	 *
	 * Other color formats (RGB/RGBA):
	 *
	 * Masks for 32 bit (RGBA): ALPHA = 0xFF000000, RED = 0x000000FF, GREEN = 0x0000FF00, BLUE = 0x00FF0000
	 *
	 * Bit count will be rounded to next 8 bit boundary. If IncludePadding is true, it will be ensured
	 * that line width is a multiple of 4. padding bytes are included if necessary.
	 *
	 * NOTE: systems with big endian byte order may require masks in inversion order.
	 */
	bool getBits(void* buffer, unsigned int &size, unsigned int redMask, unsigned int greenMask, unsigned int blueMask, unsigned int alphaMask, bool includePadding = true);

	/* See GetBits(). 
	 * It creates a corresponding color table (palette) which have to be destroyed by the user after usage.
	 *
	 * Supported Bit depths are: 4, 8
	 *
	 * Todo: Optimize, use optimized palette, do ditehring (see my dithering class), support padding for 4 bit bitmaps
	 */
	bool getBitsWithPalette(void* buffer, unsigned int &size, unsigned int bitCount, BGRA* &palette, unsigned int &paletteSize, bool optimalPalette = false, bool includePadding = true);

	/* Set Bitmap Bits. Will be converted to RGBA internally */
	void setBits(void* buffer, unsigned int width, unsigned int height, unsigned int redMask, unsigned int greenMask, unsigned int blueMask, unsigned int alphaMask = 0);
};

} // ns IMAGE
} // ns GFX
} // ns FI

#endif
