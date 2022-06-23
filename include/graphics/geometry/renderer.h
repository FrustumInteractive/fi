/*
*	Copyright (c) 2012 Frustum Interactive
*
*	All rights reserved. No warranty, explicit or implicit, provided.
*/

#ifndef _GEOMETRY_RENDERER_H
#define _GEOMETRY_RENDERER_H


#include "graphics/geometry/geometry.h"
#include "graphics/geometry/object.h"
#include "graphics/geometry/uniformBuffer.h"


namespace FI {
namespace GFX {

// FORWARD DECL.
class ShaderProgram;
class API;
class PostProcess;
struct SamplerState;

namespace Geometry {

constexpr unsigned SHADER_DEFAULT   = 0;
constexpr unsigned SHADER_CIRCLE    = 1;
constexpr unsigned SHADER_ELLIPSE   = 2;
constexpr unsigned SHADER_SQUARE    = 3;
constexpr unsigned SHADER_RECTANGLE = 4;
constexpr unsigned SHADER_TRIANGLE  = 5;
constexpr unsigned SHADER_NGON      = 6;

constexpr unsigned MAX_BUFFERS     = 8;
constexpr unsigned MAX_BUFFER_SIZE = 65000;

typedef enum RenderType
{
	RENDER_SIMPLE,
	RENDER_PHONG
} RenderType;

// ************************************************************************
// * GEOMETRY RENDERER CLASS
// *
// *	- renders GeometryObject instances
// *	- detects duplicate objects for instanced draw
// *	- verts offset,count and face offset,count must be set per object
// *	- OR objects must be a copy of an object that has these members set
// *	- object hierarchy must be established before adding to renderer
// *
// ************************************************************************

class Renderer
{
public:
	Renderer( API *api, RenderType rt = RENDER_SIMPLE );

	virtual ~Renderer();

	// GET
	unsigned int vertexCount(unsigned int index = 0);
	unsigned int faceCount(unsigned int index = 0);
	std::vector<Object> *objects();
	std::vector<Vertex>	*vertices();
	std::vector<Face> *faces();
	std::string path();
	ShaderProgram *shaderProgram( unsigned int index );

	// SET
	void setVertexData(unsigned int vertexCount,
					   const Vertex *vertices,
					   unsigned int faceCount = 0,
					   const Face *faces = 0,
					   unsigned int index = 0);

	void setMatrix(const MATH::Matrix &m);
	void setMatProj(const MATH::Matrix &m);
	void setMatModel(const MATH::Matrix &m);
	void setMatView(const MATH::Matrix &m);
	void setCameraPosition(const MATH::vec3 &pos);
	void setTexture(unsigned int texID);
	void setViewport(unsigned int x, unsigned int y, unsigned int w, unsigned int h);

	// MULTIVIEW
	void setMultiviewMatricies(MATH::Matrix *matrices, size_t rows, size_t cols, int renderWidthPixels, int renderHeightPixels);

	// DRAW
	void draw( unsigned int drawType );
	void drawElements(unsigned int drawType);

	// object references
	void addObject(Object &obj);
	void addObjects(std::vector<Object> &objects);
	void updateObjects();
	void removeObject(unsigned int index);
	void removeObject(std::string name);			
	void removeObject(Object &obj);
	void clearObjects();

	// lights
	void addLight(const Light &light);
	void addLights(std::vector<Light> &lights);
	void updateLights();
	void clearLights();

	// materials
	void addMaterial(const Material &material);
	void addMaterials(std::vector<Material> &materials);
	void updateMaterials();
	void clearMaterials();

protected:

	void update();
	void perInstancedDrawUpdate(size_t drawCallIndex);
	void addObjectRenderInstance(Object *obj);
	void removeObjectRenderInstance(Object *obj);
	void clearObjectRenderInstances();
	unsigned createColorTexture(uint8_t r, uint8_t g, uint8_t b, uint8_t a);

	API *mAPI;

	RenderType mRenderType;

	unsigned int
		mVbos[MAX_BUFFERS],
		mUbo,
		mEbos[MAX_BUFFERS],
		mCurrentBufferIndex,
		mInputLayout;

	size_t
		mVertexCounts[MAX_BUFFERS],	// total pool counts
		mFaceCounts[MAX_BUFFERS];

	unsigned int
		mTexture,
		mDefaultTexture;

	bool
		mLightsChanged,
		mMaterialsChanged,
		mObjectsChanged,
		mObjectTreeChanged;

	size_t
		mMultiviewRows,
		mMultiviewCols,
		mDisplayWidth,
		mDisplayHeight;


	const Vertex *mVertices[MAX_BUFFERS];	// pool of vertices

	const Face *mFaces[MAX_BUFFERS];	// pool of faces

	UniformBuffer *mUniformBufferData;

	SamplerState *mSamplerState;

	MATH::Matrix
		*mMultiviewMatrices,
		mMatrix,  // mvp matrix
		mMatProj,
		mMatView,
		mMatModel;


	MATH::vec3 mCameraPos;

	std::vector<ShaderProgram>    mShaderPrograms;

	std::vector<Object*>          mObjects;
	std::vector<const Material*>  mMaterials;
	std::vector<const Light*>     mLights;

	ObjectInstanceArray mObjectInstanceArray;
};


} // NS Geometry
} // NS GFX
} // NS FI


#endif // _GEOMETRY_RENDERER_H