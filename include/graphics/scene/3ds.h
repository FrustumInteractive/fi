#ifndef _3DS_H
#define _3DS_H

// This file handles all of the code needed to load a .3DS file.
// Basically, how it works is, you load a chunk, then you check
// the chunk ID.  Depending on the chunk ID, you load the information
// that is stored in that chunk.  If you do not want to read that information,
// you read past it.  You know how many bytes to read past the chunk because
// every chunk stores the length in bytes of that chunk.

//>------ Primary Chunk, at the beginning of each file
#define PRIMARY       0x4D4D

//>------ Main Chunks
#define OBJECTINFO    0x3D3D				// This gives the version of the mesh and is found right before the material and object information
#define VERSION       0x0002				// This gives the version of the .3ds file
#define EDITKEYFRAME  0xB000				// This is the header for all of the key frame info

//>------ sub defines of OBJECTINFO
#define MATERIAL	  0xAFFF				// This stored the texture info
#define OBJECT		  0x4000				// This stores the faces, vertices, etc...

//>------ sub defines of MATERIAL
#define MATNAME			0xA000				// This holds the material name
#define MATAMBIENT		0XA010				// ambient value 	
#define MATDIFFUSE		0xA020				// This holds the color of the object/material
#define MATSPECULAR		0XA030
#define MATSHININESS	0XA040
#define MATSPECLEVEL	0XA041
#define MATTRANSPARENCY 0xA050
#define MATMAP			0xA200				// This is a header for a new material
#define MATMAPFILE		0xA300				// This holds the file name of the texture

#define OBJECT_MESH		0x4100				// This lets us know that we are reading a new object

//>------ sub defines of OBJECT_MESH
#define OBJECT_VERTICES     0x4110			// The objects vertices
#define OBJECT_VERTEX_OPT	0x4111			// Vertex Options
#define OBJECT_FACES		0x4120			// The objects faces
#define OBJECT_MATERIAL		0x4130			// This is found if the object has a material, either texture map or color
#define OBJECT_UV			0x4140			// The UV texture coordinates
#define OBJECT_FACE_SG		0x4150			// Face smoothing group
#define OBJECT_MATRIX		0x4160			// transform matrix for rot and center used by keyframer. 3x4 matrix (float[12])
#define OBJECT_COLOR		0x4165			// The objects mesh color from inside 3ds editor (ubyte). (might be object visibility instead)

//>------- LIGHTS
#define OBJECT_LIGHT		0x4600			// Light object
#define LIGHTOFF			0x4620
#define LIGHTRANGEOUT		0x465A
#define LIGHTRANGEIN		0x4659
#define LIGHTMULTIPLIER		0x465B
#define LIGHTATTENUATE		0x4625

#define MAX_TEXTURES 100								// The maximum amount of textures to load

// This holds the chunk info
struct tChunk
{
	unsigned short int ID;					// The chunk's ID		
	unsigned int length;					// The length of the chunk
	size_t bytesRead;					// The amount of bytes read within that chunk
};



#endif