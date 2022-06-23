/*
*	Copyright (c) 2012 Frustum Interactive
*
*	All rights reserved. No warranty, explicit or implicit, provided.
*/

#ifndef _GEOMETRY_UNIFORM_BUFFER_H
#define _GEOMETRY_UNIFORM_BUFFER_H

#include "graphics/geometry/geometry.h"

namespace FI {
namespace GFX {
namespace Geometry {

struct SimpleObject
{
	// 128 bytes
	MATH::Matrix   matrix;
	Color4f        color;
	TexCoordRect4f tcRect;
	Property4f     properties[2];
};

struct UniformBuffer
{
	const void *data();
	void dump();

	Property4f     counts;  //object, lights, materials, pad
	MATH::Matrix   mvp;
	SimpleObject      objects[MAX_OBJECTS];
};

struct UniformBuffer_Phong : public UniformBuffer
{
	void dump();

	Light      lights[MAX_LIGHTS];
	Material   materials[MAX_MATERIALS];
	Position4f eye;
};

struct UniformBuffer_UI : public UniformBuffer
{
	void dump();
	Position4f	baseTC;
};

} // NS Geometry
} // NS GFX
} // NS FI

#endif // _GEOMETRY_UNIFORM_BUFFER_H