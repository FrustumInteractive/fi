/*
*	Copyright (c) 2012 Frustum Interactive
*
*	All rights reserved. No warranty, explicit or implicit, provided.
*/

#ifndef _MATERIAL_H
#define _MATERIAL_H

#include "fiTypes.h"
#include "imagefile.h"
#include <vector>

namespace FI { namespace GFX {

class MaterialRenderPass
{
public:
	MaterialRenderPass();
	~MaterialRenderPass();

	void setActive();

	COLOR4F	m_ambient;
	COLOR4F	m_diffuse;
	COLOR4F	m_specular;
	float		m_specularPower;
	float		m_opacity;

	const char	*VSFilename,
				*PSFilename;

	unsigned int m_shaderProgramID;

	ImageFile *m_pDiffuseMap;
	ImageFile *m_pSpecularMap;
	ImageFile *m_pOpacityMap;
	ImageFile *m_pBumpMap;
};


class Material
{
public:
	Material();
	~Material();

	void createRenderPasses( int numberOfPasses );

	// GETTERS
	unsigned int getNumRenderPasses();
	MaterialRenderPass *getRenderPass( unsigned int index );
	unsigned int getNumFaces(); // Get number of faces with this material

	// SETTERS
	void setName(const char *n);
	void setActive();

private:

	char m_name[64];
	std::vector<MaterialRenderPass> m_renderPasses;
};

} //ns GFX
} //ns FI

#endif
