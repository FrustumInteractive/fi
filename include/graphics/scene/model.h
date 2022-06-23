#ifndef _MODEL_H
#define _MODEL_H

#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <algorithm>
#include <memory.h>
#include <stdio.h>

#include "fiTypes.h"
#include "math/vec3.h"
#include "math/vec2.h"
#include "3ds.h"

namespace FI { namespace GFX {

using MATH::vec2;
using MATH::vec3;

// --- DAT file defines
#define DAT_OBJECT		0x4000
#define DAT_OBJECT_PROP	0x4110

// properties
#define OBJPROP_MASS 0x4111
#define OBJPROP_FRIC 0x4112
// ---

// --- name list structs ---
struct namelistentry3ds
{
	char *name;
};

struct namelist
{
	char *name;
};

// --- color data structs ---
struct color3u
{
	unsigned char r, g, b;

	inline bool operator == (const color3u &_c) const
	{
		if (r == _c.r && g == _c.g && b == _c.b)
			return true;
		return false;
	}
};

struct color4u
{
	unsigned char r, g, b, a;
};

struct fcolor3ds
{
	float r;
	float g;
	float b;
};


// --- Light structs ---
struct lightPos4f
{
	float x, y, z, t;
};

struct lightAttenuate3ds	// use far attenuation in max
{
	unsigned char  on;	//saved in file as unsigned char
	float start;
	float end;
};

struct spotlight3ds
{
	vec3 target;
	float hotspot;
	float falloff;
	float roll;
};

struct Light
{
	char name[11];
	vec3 position;
	fcolor3ds color;
	float multiplier;
	float  dloff;			//saved in file as unsigned char
	lightAttenuate3ds attenuation;
	namelist exclude;
	spotlight3ds spot;
};	

// --- Geometry structs ---
struct AABB
{
	float xmax, xmin;
	float ymax, ymin;
	float zmax, zmin;
	
	vec3 center;
	float halfWidth;
	
	float aabbVertexArray[8][3];
	unsigned short aabbLinesArrayIndex[24];
};

struct faceIndex
{
	unsigned short a, b, c;
};

struct Face
{
	unsigned short vertIndex[3];		// indicies for the verts that make up this triangle
};

struct Indices 
{							
	unsigned short a, b, c, bVisible;	// This will hold point1, 2, and 3 index's into the vertex array plus a visible flag
};

struct InterleavedData
{
	vec3 vertex;
	vec3 norm;
	color4u vColor;
	vec2 texCoord;
	vec2 texCoordLight;
};

struct Vertex	//vertex structure for storing vertex info in a sortable manner (to eliminate duplicates and rebuild index array)
{
	vec3 position;
	vec3 normal;
	color3u color;
	vec2 uv1;
	vec2 uv2;
	int sgroup; 

	inline bool operator == (const Vertex &_v) const
	{
		bool pos, norm, col, t1, t2, sg;

		pos	=	position == _v.position;
		norm=	normal == _v.normal;
		col	=	color == _v.color;
		t1	=	uv1 == _v.uv1;
		t2	=	uv2 == _v.uv2;
		sg	=	sgroup == _v.sgroup;
				
		return (pos && norm && col && t1 && t2 && sg);
	}
};

// --- Materials structs ---
struct MaterialInfo
{
	char  strName[17];			// The texture name
	char  strFile[32];			// The texture file name (If this is set it's a texture map)
	
	bool bHasTexture;
	
	float ambient[4];
	float diffuse[4];
	float specular[4];
	float transparency;
	float shininess;
	float specularLevel;
	float selfIllumination;
	unsigned int glTexureId;	// the texture ID
};;


// --- Object/model/world structs ---
struct FI3DObject
{
	// Default CTOR
	FI3DObject() :
		numVerts(0),
		numFaces(0),
		numTVerts(0),
		numTVerts2(0),
		numCPVVerts(0),
		materialID(0),
		lightmapID(0),
		bHasTexture(false),
		bHasLightMap(false),
		bTransparent(false),
		bHasPerVertexColor(false),
		type(0),
		friction(0.3f),
		mass(1.0f),
		pVerts(0),
		pNormals(0),
		pVertColor(0),
		pTVerts(0),
		pTVerts2(0),
		pFaces(0),
		pSmoothingGroups(0),
		pInterleavedData(0)
	{
		memset(strName, 0, 64);
	}

	~FI3DObject()
	{
	}

	unsigned short  numVerts;			// The number of verts in the model
	unsigned short  numFaces;			// The number of faces in the model
	unsigned short  numTVerts;			// The number of texture coordinates
	unsigned short	numTVerts2;			//number of UVs for lightmap
	unsigned short	numCPVVerts;
	char			materialID;			// The texture ID to use, which is the index into our texture array
	unsigned short	lightmapID;		// The texture ID for object's lightmap
	bool bHasTexture;					// This is TRUE if there is a texture map for this object
	char strName[64];					// The name of the object
	bool bHasLightMap;					// This is a flag for wether or not to use opengl lights for this object
	bool bTransparent;					//object transparency flag
	bool bHasPerVertexColor;

	//Misc. object properties
	int type;					//object type to determin wether renderable mesh, or interactive region, etc
	float friction;				//friction of object
	float mass;					//mass
	
	AABB boundingBox;			// The axis aligned boundgin box
	
	// Object's geometry data
	vec3	*pVerts;			// The object's vertices
	vec3	*pNormals;			// The object's normals
	color3u	*pVertColor;
	vec2	*pTVerts;			// The texture's UV coordinates
	vec2	*pTVerts2;			// The texture UV coords for lightmaps
	faceIndex *pFaces;			// The faces information of the object

    std::vector<std::vector<unsigned short>> vSharedVertexList;
    std::vector<vec3> vFaceNormals;
	 
	unsigned int *pSmoothingGroups;

	InterleavedData *pInterleavedData;	//interleaved data for efficient vertex arrays
};

struct FI3DModel
{
	// default CTOR
	FI3DModel() :
		numOfObjects(0),
		numOfMaterials(0),
		numOfLights(0),
		bUseLightmap(false),
		lightmapID(0),
		playerStartPos(0.0f, 0.0f, 0.0f)
	{
	}

	~FI3DModel()
	{
		pMaterials.clear();
		pObject.clear();
		pLight.clear();
	}

	unsigned short numOfObjects;			// The number of objects in the model
	unsigned short numOfMaterials;			// The number of materials for the model
	unsigned short numOfLights;				// The number of lights in the 3ds scene
	
	bool	bUseLightmap;					//does this scene use lightmaps?
	unsigned int lightmapID;				// if so, this is the texture ID for it
	
	std::vector<MaterialInfo> pMaterials;	// The list of material information (Textures and colors)
	std::vector<FI3DObject> pObject;			// The object list for our model	
	std::vector<Light> pLight;				// The light list for the model

	/*game related info*/
	vec3 playerStartPos;			// Can be used as starting position of player
};

enum eObject_type	//enum for keeping track of zones in a model/world file
{
	MESH,
	ZONE_TIGHT,
    ZONE_CAMERA_3RD_PERSON,
    ZONE_CAMERA_1ST_PERSON,
	ZONE_MAP_FINISH,
	ZONE_MAP_CHECKPOINT,
	ZONE_MAP_START,
	ZONE_MAP_RESTART,
	ZONE_WATER,
	ZONE_FIRE,
	ZONE_FOG,
	ZONE_GRAVITY_ZERO,
	ZONE_GRAVITY_LOW
};

// ---



// This class handles all of the loading code
class ModelLoader
{
public:

	ModelLoader();								// This inits the data members
	virtual ~ModelLoader();
		
	// This is the function that you call to load the 3DS
    bool load3DS(FI3DModel *pModel, std::string strFileName);
		
	// function to load DAT file
    bool loadDAT(FI3DModel *pModel, std::string filename, bool bComputeNormals);
    bool loadDAT(FI3DModel *pModel, std::string filename);
		
private:

	int getString(char *);

	void readChunk(tChunk *);

	void processNextChunk(FI3DModel *pModel, tChunk *);

	void processNextObjectChunk(FI3DModel *pModel, FI3DObject *pObject, tChunk *);

	void processNextMaterialChunk(FI3DModel *pModel, tChunk *);

	void readColorChunk(float *pColor, tChunk *pChunk);

	void readPercentChunk(float *pPercent, tChunk *pChunk);

	void readVertices(FI3DObject *pObject, tChunk *);

	void readVertexIndices(FI3DObject *pObject, tChunk *);

	void readSmoothingGroups(FI3DObject *pObject, tChunk *);

	void readUVCoordinates(FI3DObject *pObject, tChunk *);

	void readObjectMaterial(FI3DModel *pModel, FI3DObject *pObject, tChunk *pPreviousChunk);

	void readLight(FI3DModel *pModel, tChunk *pChunk);

	void computeNormals(FI3DModel *pModel);

	void computeAABB(FI3DModel *pModel);

	void cleanUp();	// This frees memory and closes the file

	FILE *m_FilePointer;

	tChunk *m_CurrentChunk;
	tChunk *m_TempChunk;
};


} //NS GFX
} //NS FI

#endif

