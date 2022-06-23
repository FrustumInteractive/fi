/*
*	Copyright (c) 2012 Frustum Interactive
*
*	All rights reserved. No warranty, explicit or implicit, provided.
*/

#ifndef _SHADERPROGRAM_H
#define _SHADERPROGRAM_H

#include <string>

namespace FI { namespace GFX {

typedef enum eSPCBool
{
	SPC_FALSE,
	SPC_TRUE
}eSPCBool;

typedef enum eShaderType
{
	VERTEX_SHADER,
	PIXEL_SHADER,
	GEOMETRY_SHADER,
	HULL_SHADER,
	COMPUTE_SHADER,
	MAX_SHADER_TYPES
}eShaderType;

typedef enum eShaderLanguage
{
	SHADER_LANGUAGE_GLSL,
	SHADER_LANGUAGE_HLSL,
	MAX_SHADER_LANGUAGES
}eShaderLanguage;

class ShaderProgram
{
public:
	ShaderProgram();
	virtual ~ShaderProgram();

	const char		*getShaderSource( eShaderType type, eShaderLanguage language);
	unsigned int 	getShaderSourceSize( eShaderType type, eShaderLanguage language );
	void 			*getShaderBinary( eShaderType type );
	unsigned int 	getShaderBinarySize( eShaderType type );
	void 			*getProgramBinary();

	void 		setShaderSourceFromBuffer( eShaderType type, eShaderLanguage language, const char *buffer );
    eSPCBool 	setShaderSourceFromFile( eShaderType type, eShaderLanguage language, std::string fname );
	void 		setShaderBinary(eShaderType type, unsigned int size, void *pData);

	unsigned int	vertexShaderID,
					pixelShaderID,
					programID;

private:

	char	*m_shaderSourcePtr[MAX_SHADER_LANGUAGES][MAX_SHADER_TYPES];	//array of shader string pointers

	unsigned int m_shaderSourceSize[MAX_SHADER_LANGUAGES][MAX_SHADER_TYPES];	// of shader string sizes

	void	*m_shaderBinaries[MAX_SHADER_TYPES];	// array of shader bin pointers

	unsigned int m_shaderBinarySize[MAX_SHADER_TYPES];

	void	*m_programBinary;
	
};

} //ns GFX
} //ns FI

#endif
