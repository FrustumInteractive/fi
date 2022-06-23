/*
*	Copyright (c) 2012 Frustum Interactive
*
*	All rights reserved. No warranty, explicit or implicit, provided.
*/

#ifndef _COLLISION_H
#define _COLLISION_H

#include "math/vec3.h"
#include "math/plane.h"

namespace FI {
namespace GFX {

using MATH::vec3;
using MATH::Plane;

class CollisionPacket 
{ 
public:
	CollisionPacket();
	
	vec3 eRadius; // ellipsoid radius
	
	// Information about the move being requested: (in R3) 
	vec3 R3Velocity; 
	vec3 R3Position;
	
	// Information about the move being requested: (in eSpace) 
	vec3 velocity; 
	vec3 normalizedVelocity; 
	vec3 basePoint;
	vec3 gravVelocity;
	
	// Hit information 
	bool foundCollision; 
	float nearestDistance; 
	vec3 intersectionPoint;
	vec3 lastCollisionNormal;

	int collisionType;

	int collisionRecursionDepth;

	bool bInAir;

	vec3 prevVel;

	float m_time, m_timestep;
	vec3 m_frictionalForce;
	float coefFriction;
};


unsigned int checkPointInTriangle(const vec3 &point, const vec3 &pa, const vec3 &pb, const vec3 &pc);

bool getLowestRoot(float a, float b, float c, float maxR, float* root);

// Assumes: p1,p2 and p3 are given in ellisoid space: 
void checkTriangle(CollisionPacket* colPackage, const vec3& p1, const vec3& p2, const vec3& p3);

} //ns GFX
} //ns FI

#endif
