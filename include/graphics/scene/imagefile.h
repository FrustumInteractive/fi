/*
*	Copyright (c) 2012 Frustum Interactive
*
*	All rights reserved. No warranty, explicit or implicit, provided.
*/

#ifndef _IMAGEFILE_H
#define _IMAGEFILE_H

#include "fiTypes.h"

namespace FI { namespace GFX {

// TGA stuff---------------
#define TGA_RGB		2
#define TGA_A		3
#define TGA_RLE		10

struct BMPMAGIC
{
	FI::WORD bfMagic;
};

 struct BMPFILEHEADER 
 { 
	FI::DWORD bfSize; 
	FI::WORD bfReserved1; 
	FI::WORD bfReserved2; 
	FI::DWORD bfOffBits; 
};

struct BMPINFOHEADER 
{ 
	FI::DWORD biSize; 
	FI::LONG biWidth; 
	FI::LONG biHeight; 
	FI::WORD biPlanes; 
	FI::WORD biBitCount; 
	FI::DWORD biCompression; 
	FI::DWORD biSizeImage; 
	FI::LONG biXPelsPerMeter; 
	FI::LONG biYPelsPerMeter; 
	FI::DWORD biClrUsed; 
	FI::DWORD biClrImportant; 
};


struct FIImage
{
	FI::BYTE channels;
    FI::WORD size_x;
    FI::WORD size_y;
	FI::BYTE *imgData;
};
//-------------------------


class ImageFile
{

public:

	//CTOR & DTOR
	ImageFile();
	~ImageFile();

	bool LoadBMP(const char *filename); 
	bool LoadTGA(const char *filename);

	//Getters
	FI::BYTE *GetImageData();
	unsigned int GetWidth();
	unsigned int GetHeight();
	unsigned int GetDepth();

	bool bHasImageData;

	unsigned int m_ID;
	
private:
	FIImage m_image;
};

} //ns GFX
} //NS FI

#endif
