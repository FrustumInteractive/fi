/*
*	Copyright (c) 2012 Frustum Interactive
*
*	All rights reserved. No warranty, explicit or implicit, provided.
*/

#ifndef __ENTITY_H
#define __ENTITY_H

#include <vector>
#include "math/vec2.h"
#include "math/vec3.h"
#include "math/matrix.h"

namespace FI {
namespace GFX {

using MATH::vec2;
using MATH::vec3;
using MATH::Matrix;

struct GeomVertex;
struct FaceData;

enum eEntityType
{
	TRIMESH,
	LIGHT,
	TRIGGER,
	ZONE
};

struct BoundingBox
{
	vec3 lowerFront;
	vec3 upperBack;
};

class Entity
{
public:
	Entity();
	~Entity();

	char name[64];
	
	eEntityType type;

	vec3 position;
	vec3 velocity;
	vec3 acceleration;
	vec3 force;

	float friction;
	float jumpForce;
	float mass;

	unsigned int materialID;

	Matrix transform;	// Entity's transformation matrix

	BoundingBox boundingBox;

	int numFaces;		// number of face indices
	int numVertices;	// Size in bytes of the vertex data block
	int firstVertexIndex;	// First vertex of vertex data memory pool
	int firstFaceIndex;		// First face in face data pool

	GeomVertex *pVertexData; 
	FaceData *pFaceData;
};

typedef std::vector<Entity> EntityList;

} //ns GFX
} //ns FI

#endif
