/*
 *	Copyright (c) 2012 Frustum Interactive
 *
 *	All rights reserved. No warranty, explicit or implicit, provided.
 */

#ifndef _OCTREE_H
#define _OCTREE_H
 
#include <vector>
#include "collision.h"
#include "entity.h"
#include "math/frustum.h"

#include "graphics/geometry/geometry.h"
#include "graphics/geometry/renderer.h"
#include "graphics/geometry/object.h"

namespace FI {
namespace GFX {

class API;

const float unitsPerMeter = 100.0f;

// These values (0 - 7) store the index ID's for the octree node array (m_pOctreeNodes)
enum eOctreeNodes
{
	TOP_LEFT_FRONT,			// 0
	TOP_LEFT_BACK,			// 1
	TOP_RIGHT_BACK,			// etc...
	TOP_RIGHT_FRONT,
	BOTTOM_LEFT_FRONT,
	BOTTOM_LEFT_BACK,
	BOTTOM_RIGHT_BACK,
	BOTTOM_RIGHT_FRONT
};

struct tFaceList
{
	std::vector<bool> pFaceList;	// vector of booleans to store if the face index is in the nodes 3D Space
	unsigned int totalFaceCount;	// stores the total faces in the nodes 3D space (how many "true"'s)
};


// Debug lines class to view the octree visually
class DebugDraw 
{
public:
	DebugDraw(API *api);
	virtual ~DebugDraw();

	void setMatrix( const Matrix &mvp );
	void setColor( float r, float g, float b, float a );
	void addDebugLine(vec3 vPoint1, vec3 vPoint2);
	void addDebugRectangle(vec3 vCenter, float width, float height, float depth);
	void draw();
	void clear();

protected:
	std::vector<Geometry::Vertex>	m_vLines;	// This is the vector list of all of our lines

	bool 				m_isFirstDraw;	// flag to init vbo if its first draw call since update

	Geometry::Renderer 	*m_pGeomRenderer;	// used to render our vertices

	Geometry::Object	m_object;		// object which represents the debug wireframe

	API *m_pAPI;
};


class Octree
{
public:

	Octree();
	virtual ~Octree();
	
	// GETTERS
	vec3			center();	// returns center of this current node
	unsigned int	triangleCount();
	float			width();
	void			sceneDimensions( const Geometry::DataPool &scene ); // get width, height and depth for the whole scene
	unsigned int	sceneTriangleCount( const Geometry::DataPool &scene ); // returns number of polys in our entire scene
	vec3			newNodeCenter(const vec3 &vCenter, float width, unsigned int nodeID);
	void			currentIBOList(Octree *pNode, /*Out*/Geometry::DataPool& rootScene);	//accumulate IBO list
	
	// SETTERS
	void setMaxTriangles( unsigned int max );
	void setMaxSubdivisions( unsigned int max );
	void setMVPMatrix( const Matrix &modelViewProj );
	void setAPI(API *api);

	bool isSubDivided();	// is this node subdivided

	void addObjectIndexToList(unsigned int index); // adds the object index to our end node's list of object indices

	void createNode(const Geometry::DataPool& scene, unsigned int numTriangles, const vec3 &vCenter, float width);	// subdivides based on triangle count and node width
	
	void createNewNode(const Geometry::DataPool& scene, tFaceList pList, unsigned int triangleCount, const vec3 &vCenter, float width, unsigned int nodeID);

	void assignTrianglesToNode( const Geometry::DataPool &scene, unsigned int numTriangles);	// Once done subdividing, assign the face indices to the end node

	void drawOctree(Octree *pNode, const Geometry::DataPool &rootScene);	// Starting at Root node, go through the nodes and draw the end node's vertices

	void calculateFrustum(); // calculate view frustum to use with octree

	void drawDebugLines();	// draw debug lines when API was alread specfied

	// recusively check for collisions 
	char collisionTest(Octree *pNode, const Geometry::DataPool& rootScene, CollisionPacket *collisionPackage);
	void collideAndSlide( Octree *pNode, const Geometry::DataPool& rootScene, Entity& e, const float timestep, const vec3& gravity);
	void collideAndSlideCamera( Octree *pNode, const Geometry::DataPool& rootScene, Entity& e, const float timestep );
	vec3 collideWithScene( Octree *pNode, const Geometry::DataPool& rootScene, CollisionPacket *collisionPackage, const vec3& pos, const vec3& vel);

protected:

	unsigned int	m_maxTriangles,
					m_maxSubdivisions,
					m_endNodeCount,	
					m_totalNodesDrawn,
					m_currentSubdivision;

	bool 	m_bSubDivided;	// This tells us if we have divided this node into more sub nodes
	bool	m_bRootNode;	// is this the root node?
	
	float	m_width;			// This is the size of the cube for this current node
	vec3	m_vCenter;			// This is the center (X, Y, Z) point in this node

	unsigned int m_triangleCount;		// Holds the amount of triangles stored in this node
	
	FI::GFX::Geometry::DataPool m_scene;	// This holds all the scene geometry information (verts, normals, texture info, etc..) for this node

	std::vector<unsigned int> m_pObjectList;	// This stores the indices into the original model's object list

	Octree *m_pOctreeNodes[8];	// These are the eight nodes branching down from this current node

	const Matrix		*m_matrix;		// ptr to scene's modelViewProj matrix

	static DebugDraw	*m_pDebugDraw;	// draws bouding boxes for debug purpose
	static Frustum		*m_pFrustum;	// countains current view frustum info
	static API	*m_pAPI;
};


} //NS GFX
} //NS FI

#endif

