/*
*	Copyright (c) 2012 Frustum Interactive
*
*	All rights reserved. No warranty, explicit or implicit, provided.
*/

#ifndef _GEOMETRY_H
#define _GEOMETRY_H

#include "math/vec2.h"
#include "math/vec3.h"
#include "math/matrix.h"
#include "fiTypes.h"
#include <vector>
#include <string>
#include <utility>
#include <algorithm>

//#define INT_FACE_INDEX

namespace FI { 
namespace GFX {


// ************************************************
// * GEOM STRUCTS
// *
// *  -data types directly compatible with shaders
// *
// ************************************************

namespace Geometry {

constexpr unsigned MAX_LIGHTS    = 4;    // 4   x 64 bytes  = 256 
constexpr unsigned MAX_OBJECTS   = 64;   // 256 x 128 bytes = 16384
constexpr unsigned MAX_MATERIALS = 32;   // 32  x 64 bytes  = 2048 
                                         // total = 64(matrix) + 16(eye) + 18688 (should be less than 32K [32768])

enum Shape
{
	DEFAULT,
	CIRCLE,
	ELLIPSE,
	SQUARE,
	RECTANGLE,
	TRIANGLE,
	NGON,
	NUM_SHAPES
};

typedef struct FaceData
{
#ifndef INT_FACE_INDEX
	unsigned short a, b, c;
#else
	unsigned int a, b , c;
#endif
} Face;

typedef struct FaceProperty
{
	unsigned short materialID;
	unsigned char pad1;
	unsigned char pad2;
} FaceProperty;

struct TexCoordRect4f
{
	TexCoordRect4f() :
		xmin(0.0f),
		ymin(0.0f),
		xmax(1.0f),
		ymax(1.0f)
	{}
	TexCoordRect4f(float _xmin, float _ymin, float _xmax, float _ymax) :
		xmin(_xmin),
		ymin(_ymin),
		xmax(_xmax),
		ymax(_ymax)
	{}

	float xmin, ymin, xmax, ymax;
};

struct Color4f
{
	Color4f() :
		r(1.0f),
		g(1.0f),
		b(1.0f),
		a(1.0f)
	{}
	Color4f(float _r, float _g, float _b, float _a) :
		r(_r),
		g(_g),
		b(_b),
		a(_a)
	{}
	float r, g, b, a;
};

struct Property4u
{
	Property4u() :
		a(0),
		b(0),
		c(0),
		d(0)
	{}
	Property4u(uint32_t _a, uint32_t _b, uint32_t _c, uint32_t _d) :
		a(_a),
		b(_b),
		c(_c),
		d(_d)
	{}
	uint32_t a, b, c, d;
};

struct Property4i
{
	Property4i() :
		a(-1),
		b(-1),
		c(-1),
		d(-1)
	{}
	Property4i(int _a, int _b, int _c, int _d) :
		a(_a),
		b(_b),
		c(_c),
		d(_d)
	{}
	int a, b, c, d;
};
	
struct Property4f
{
	Property4f() :
	a(0.0f),
	b(0.0f),
	c(0.0f),
	d(0.0f)
	{}
	Property4f(float _a, float _b, float _c, float _d) :
	a(_a),
	b(_b),
	c(_c),
	d(_d)
	{}
	float a, b, c, d;
};

struct Position4f
{
	Position4f() :
		x(0),
		y(0),
		z(0),
		w(1.0f)
	{}
	Position4f(float _x, float _y, float _z, float _w) :
		x(_x),
		y(_y),
		z(_z),
		w(_w)
	{}
	float x, y, z, w;
};

struct Material
{
	// 64 bytes
	Color4f		ambient;
	Color4f		diffuse;
	Color4f		specular;
	Property4f	pad;
};

struct Light
{
	// 64 bytes
	Position4f	position;
	Color4f		color;
	Color4f		properties;
	Property4f	pad;
};

struct Vertex
{
	MATH::vec3 position;
	MATH::vec3 normal;
	MATH::vec2 uv1;
	MATH::vec2 uv2;
	unsigned int objectID;
	unsigned int materialID;
};

struct DataPool
{
	DataPool() :
		pVertices(nullptr),
		pFaces(nullptr),
		pFaceProperties(nullptr)
	{}

	DataPool(std::vector<Vertex> *pV, std::vector<FaceData>	*pF, std::vector<FaceProperty> *pFP) :
		pVertices(pV),
		pFaces(pF),
		pFaceProperties(pFP)
	{}

	std::vector<Vertex> *pVertices;
	std::vector<FaceData>	*pFaces;
	std::vector<FaceProperty> *pFaceProperties;
};

} // NS Geometry
} // NS GFX
} // NS FI

#endif /* _GEOMETRY_H */
