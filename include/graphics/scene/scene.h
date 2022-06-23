/*
 *  scene.h
 *  FIEngine
 *
 *  Created by Roger Dass on 12-05-01.
 *  Copyright 2012 Frustum Interactive. All rights reserved.
 *
 */

#ifndef _SCENE_H
#define _SCENE_H

#include <vector>
#include <string>

#include "fiTypes.h"
#include "fiUtil.h"
#include "math/frustum.h"
#include "model.h"
#include "material.h"
#include "entity.h"
#include "math/matrix.h"
#include "state.h"
#include "event.h"

#include "graphics/API/API.h"
#include "graphics/geometry/renderer.h"

namespace FI {
namespace GFX {

using MATH::Matrix;
using MATH::vec2;
using MATH::vec3;

class ModelLoader;
class Octree;

enum eMatrixType
{
	MATRIX_MODEL,
	MATRIX_VIEW,
	MATRIX_PROJECTION
};
	
enum eRenderUse
{
	RENDERUSE_STATIC,
	RENDERUSE_DYNAMIC
};


class Scene 
{

public:

	Scene();
	virtual ~Scene();

	bool init( API *pApi, int width, int height, std::string path );
	void deinit();
	
	int pushEntity( const Entity *e );	// push entity to the scene's entity stack
	void popEntity( int index );		// pop entity from back of entity stack
	void deleteEntity( int index );

	void collideEntityWithGravity(Entity *entity, const float timestep, const vec3& gravity);
	void collideEntity(Entity *entity, const float timestep);

	bool loadModelFile(const std::string& fname,
					   eRenderUse usage = RENDERUSE_STATIC,
					   bool useDefaultMaterials = false,
					   bool useDefaultLights = false);

	void buildOctree();
	
	// Scene dynamic objects
	void addObjectInstance(Geometry::Object &obj);

	// States
	void stateChange( SceneState* state );
	void statePush( SceneState* state );
	void statePop();
	void statePause();
	void stateResume();

	// GETTERS
	unsigned int	numObjects();
	unsigned int	numVertices();
	unsigned int	numFaces();
	unsigned int	numLights();
	unsigned int	numMaterials();
	float			sceneExtent();
	Entity			&observer();
	ShaderProgram*	shaderProgram();
	std::vector<Geometry::Object> *staticObjectList();
	std::vector<Geometry::Object> *objectList();


	//SETTERS
	void setEvent(Event e);
	void setMatrix( eMatrixType type, const Matrix &m );
	void setUBOID( unsigned int id );
	void setUseFrustumCulling( bool b );
	void setMultiviewMatricies( MATH::Matrix *matricies, size_t rows, size_t cols, int renderWidthPixels, int renderHeightPixels);

	void update();
	void draw();

	// default filenames (test purposes)
	const char *m_pDiffuseMapFilename;
	const char *m_pBumpMapFilename;
	const char *m_pSpecularMapFilename;
	const char *m_pOpacityMapFilename;

private:

	API *m_pAPI;	// rendering API

	ModelLoader *m_modelLoader; // model file loader utility (supports .3DS & .DAT)

	float m_sceneExtent;	// how many units the scene extends from the center

	Matrix	
		m_matModel,
		m_matView,
		m_matProj,
		m_matMVP;

	const char *m_workingFilePath;

	bool m_bShowOctreeLines;
	bool m_bShowAABBLines;
	bool m_bUseFrustumCulling;
	bool m_bUseDefaultMaterial;

	Octree		*m_pOctree;
	
	Entity		m_observer;		// this is our 'camera' or viewer
	EntityList	m_entities;		// will store a pointer to where its vertex data lives in pool as well as face list, etc. 
	
	Geometry::Renderer	*m_pStaticGeometryRenderer,
						*m_pGeometryRenderer;

	std::vector<std::vector<Geometry::Vertex>>        m_vertices, m_staticVertices;
	std::vector<std::vector<Geometry::Face>>          m_faces, m_staticFaces;
	std::vector<std::vector<Geometry::FaceProperty>>  m_faceProperties, m_staticFaceProperties;

	Material		*m_pDefaultMaterial;	// default scene material

	Event	m_event;

	Geometry::Object                m_staticSceneObject;	// static scene in a single object
	std::vector<Geometry::Object>   m_staticSceneObjects;	// static object references for scene
	std::vector<Geometry::Object>   m_objects;				// dynamic scene objects
	std::vector<Geometry::Light>    m_lights;				// shader compatible lights
	std::vector<Geometry::Material> m_materials;			// shader-compatible materials

	std::vector<SceneState*> m_states;
};

} //NS GFX
} //NS FI

#endif
