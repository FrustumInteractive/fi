/*
 *  Types.h
 *  
 *
 *  Created by Roger on 27/01/10.
 *  Copyright 2010 __Roger Dass__. All rights reserved.
 *
 */

#ifndef _TYPES_H
#define _TYPES_H

// Generic
namespace FI {
typedef unsigned int    DWORD;  // previously was long, but for 64b long is 8bytes instead of 4bytes. int stays as 4bytes.
typedef unsigned short  WORD;   // short is 2 bytes for 32b and 64b
typedef int             LONG;   // use int instead of long because in 64b long jumps to 8bytes
typedef unsigned char   BYTE;

// Dimensions
struct BYTE_RGB
{
	unsigned char r, g, b;

	inline bool operator == (const BYTE_RGB &_c) const
	{
		return (r == _c.r && g == _c.g && b == _c.b);
	}

};

struct BYTE_RGBA
{
	unsigned char r, g, b, a;

	inline bool operator == (const BYTE_RGBA &_c) const
	{
		return (r==_c.r && g==_c.g && b==_c.b && a==_c.a);
	}
};

struct float3
{
	float x, y, z;
};

struct COLOR3F
{
	COLOR3F(){}
	COLOR3F(float _r, float _g, float _b)
	{
		r = _r;
		g = _g;
		b = _b;
	}
	float r, g, b;
};

struct float4
{
	float x, y, z, w;
};

struct COLOR4F
{
	COLOR4F(){}
	COLOR4F(float _r, float _g, float _b, float _a)
	{
		r = _r;
		g = _g;
		b = _b;
		a = _a;
	}
	float r, g, b, a;
};

struct int4
{
	int4(){};
	int4(int _x, int _y, int _z, int _w)
	{
		x = _x;
		y = _y;
		z = _z;
		w = _w;
	}
	int x, y, z, w;
};

} /* ns FI */

#endif


