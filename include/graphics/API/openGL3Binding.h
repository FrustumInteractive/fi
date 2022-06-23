/*
* OpenGL3Binding.h
*
*  Created on: Aug 10, 2015
*      Author: Roger Dass
*		Copyright Frustum Interactive Inc. - All rights reserved.
*/

#ifndef _3DAPIOGL_H
#define _3DAPIOGL_H

#include "application/oglApp.h"
#include "graphics/API/API.h"
#include <vector>

// DEFINES
//#define _USE_GL_SAMPLER_OBJECTS

namespace FI { namespace GFX {

struct GLVertexAttribArgs
{
	int index;
	int size;
	unsigned int type;
	unsigned char normalized;
	int stride;
	const void *pointer;
};

struct InputLayout_OpenGL
{
	int numElements;
	int stride;
	GLVertexAttribArgs *pVaArgs;
	unsigned int VAO;
};

class ShaderProgram;

class OGLAPI : public API
{
public:
	OGLAPI() :
#ifdef WIN32
		m_pixelFormat(0)
		m_hDC(0),
		m_hRC(0),
#endif /*WIN32*/
		m_currentInputLayout(-1),
		m_pCurrentBoundShaderProgram(0),
		m_globalUniformsBlockIndex(0),
		m_globalUniformsBindingPoint(0)
	{}
	virtual ~OGLAPI(){}

	bool APIInit( int width, int height, bool vsync, void *hwnd, bool fullscreen, float nearClip, float farClip);
	void APIShutdown();
	void clear( int target );
	void present();

	// Buffers
	void createBuffer( eBufferType type, size_t size, const void *pData, eUsage usage, unsigned int *buffer, const char *IDString = "GlobalUniforms" );
	void deleteBuffer( eBufferType type, unsigned int buffer );
	void bindBuffer( eBufferType buffType, unsigned int buffer, const char *IDString="GlobalUniforms" );
	void bufferSubData( eBufferType buffType, unsigned int offset, int size, const void *pData, unsigned int buffer );
    void bufferSubDataAsync( eBufferType buffType, unsigned int offset, int size, const void *pData, unsigned int buffer );
	void initRenderBuffer( eInternalFormat format, unsigned int width, unsigned int height, unsigned int buffer );
	void attachRenderBuffer( eAttachment attachment, unsigned int buffer );
	void setFrameBufferTexture(eAttachment attachment, unsigned int textureID, unsigned int mipLevel );
	void setDrawBuffers( unsigned int numBufs, eAttachment *atts );
	bool checkFrameBuffer();
    int  setDefaultFramebufferFromCurrent();
	int  getDefaultFramebuffer();
	void readPixels(unsigned int x, unsigned int y, unsigned int width, unsigned int height, eInternalFormat format, eType type, void * data);

	// Texture
	void createTexture2D( const Texture2DDesc *pDesc, const void *pData, unsigned int *textureID );
	void deleteTexture( unsigned int textureID );
	void createSamplerState( SamplerState *pSS);
	void setSamplerState( unsigned int index, SamplerState *pSS );
	void bindTexture( unsigned int location, unsigned int *textureID );

	// Input Data
	void createInputLayout( 
		const InputLayoutDesc *inputLayoutDesc,
		int numElements,
		int stride,
		ShaderProgram *spc, unsigned int *inputLayout );
	void deleteInputLayout(unsigned int inputLayout);
	void setInputLayout( unsigned int inputLayout );

	void clearColor ( float r, float g, float b, float a);

	// Draw
	void drawArrays( eGeomType mode, unsigned int first, unsigned int count );
	void drawArraysInstanced(eGeomType mode, unsigned int first, unsigned int count, unsigned int instanceCount);
	void drawElements( eGeomType mode, unsigned int count, eType type, unsigned int startOffset);
	void drawElementsInstanced(eGeomType mode, unsigned int count, eType type, unsigned int startOffset, unsigned int instanceCount);
	void drawElementsBaseVertex( eGeomType mode, unsigned int count, eType type, unsigned int startOffset, unsigned int baseVertex);

	// Shaders
	void buildShaderProgram( ShaderProgram *spc );
	void deleteShaderProgram(ShaderProgram *sp);
	void useShaderProgram ( const ShaderProgram *spc );
	void setShaderConstantiv( const char *name, const int *data, int intSize, int count);
	void setShaderConstantfv( const char *name, const float *data, int floatSize, int count);
	void setShaderConstantMatrix4fv( const char *name, int count, int transpose, const float *data);
	void setShaderProfileSupport( eShaderProfileSupport sps ){}
	void setViewport( unsigned x, unsigned y, unsigned width, unsigned height );
	
	// States
	void setFaceWinding( eFaceWinding w );
	void setFaceCulling( eFaceCullMode c );
	void setRenderState( eRenderState state, bool enable );
	void setScissor( int x, int y, int width, int height);

	// Sync
	virtual void finish();
	virtual void flush();

private:

#ifdef WIN32
	int	m_pixelFormat;
	
	void	*m_hDC;		// Private GDI Device Context
	void	*m_hRC;		// Permanent Rendering Context
#endif /*WIN32*/

	int m_currentInputLayout; //what is the currently set input layout

	const ShaderProgram *m_pCurrentBoundShaderProgram;

	// constant buffer stuff
	unsigned int	m_globalUniformsBlockIndex,
					m_globalUniformsBindingPoint;

	std::vector<InputLayout_OpenGL*> m_vInputLayoutPtrArray;

	std::vector<std::string> m_glExtensions;

	std::function<void()>	m_renderbufferCallback;
};


} //NS GFX
} //NS FI

#endif
