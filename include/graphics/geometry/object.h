/*
*	Copyright (c) 2012 Frustum Interactive
*
*	All rights reserved. No warranty, explicit or implicit, provided.
*/

#ifndef _GEOMETRY_OBJECT_H
#define _GEOMETRY_OBJECT_H

#include "graphics/geometry/geometry.h"

namespace FI {
namespace GFX {
namespace Geometry {

// **********************************
// * GEOMETRY OBJECT CLASS
// *
// *	- outward facing object class
// **********************************

class Object
{
	friend class Renderer;
public:
	Object();
	Object(std::string name,
				   unsigned int vertexOffset,
				   unsigned int vertexCount,
				   unsigned int faceOffset,
				   unsigned int faceCount,
				   unsigned int bufferIndex=0);

	~Object();

	// Factory
	static Object MakePrimitive(Shape, float stroke = 0.0);

	// Getters
	unsigned int vertexOffset() const;
	unsigned int vertexCount() const;
	unsigned int faceOffset() const;
	unsigned int faceCount() const;
	unsigned int bufferIndex() const;
	size_t numChildren() const;
	std::string  name() const;
	bool isVisible() const;
	unsigned int shaderProgramIndex();
	unsigned int bufferIndex();
	MATH::vec3 position();
	MATH::vec3 rotationAxis();
	MATH::vec3 scale();
	float rotationAngle();
	
	// Setters
	void setVertexOffset(unsigned int offset);
	void setFaceOffset(unsigned int offset);
	void setName(std::string name);
	void setVisible(bool b);
	void setShaderProgramIndex(unsigned int index);
	void setBufferIndex(unsigned int index);
	void scale(const MATH::vec3 &scale);
	void rotate(float angle, const MATH::vec3 &axis);
	void position(const MATH::vec3 &pos);
	void translate(const MATH::vec3 &translation);
	
	// debug
	void printTree();
	
	// heirarchy
	void addChild(Object *child);	// must be a a child with it's own geometry data
	void removeChild(std::string name);
	void removeChild(size_t index);
	void removeChildren();

	MATH::Matrix matrix;

	Color4f color;

	TexCoordRect4f texCoordRect;
	
	Property4f properties[2];

private:

	MATH::vec3
		mPosition,
		mRotationAxis,
		mScale;

	std::string mName;

	unsigned int
		mVertexOffset, // start & numVerts in vertex buffer
		mVertexCount,
		mFaceOffset,
		mFaceCount,
		mBufferIndex,
		mShaderProgramIndex;

	bool mVisible;

	int mDrawInstanceID;
	int mDrawInstancePos;

	float mRotationAngle;

	static size_t sShapeCounts[NUM_SHAPES];

public:
	Object *mParent;
	std::vector<Object*> mChildren;
};

typedef std::pair<const Object*, std::vector<const Object*>> ObjectInstance;
typedef std::vector<ObjectInstance> ObjectInstanceArray;


} // NS Geometry
} // NS GFX
} // NS FI

#endif // _GEOMETRY_OBJECT_H