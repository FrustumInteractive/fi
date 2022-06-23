/*
 * GraphicsPostProcess.h
 *
 *  Created on: Aug 17, 2015
 *      Author: Roger Dass
 */

#ifndef _GFX_POST_PROCESS_H
#define _GFX_POST_PROCESS_H

#include <string>
#include "math/matrix.h"

namespace FI{ namespace SHADERS {
	const char *pp_default_vs_gl2();
	const char *pp_default_fs_gl2();
	const char *pp_default_vs_gl3();
	const char *pp_default_fs_gl3();
	const char *pp_default_vs_ES2();
	const char *pp_default_fs_ES2();
	const char *pp_default_vs_ES3();
	const char *pp_default_fs_ES3();
	const char *pp_sbs_default_vs_gl2();
	const char *pp_sbs_default_fs_gl2();
	const char *pp_sbs_default_vs_gl3();
	const char *pp_sbs_default_fs_gl3();
	const char *pp_sbs_default_vs_ES2();
	const char *pp_sbs_default_fs_ES2();
	const char *pp_sbs_default_vs_ES3();
	const char *pp_sbs_default_fs_ES3();
}
}

namespace FI { namespace GFX {

class ShaderProgram;
class API;
struct SamplerState;
struct UniformBuffer;

struct Vertex2D
{
	float 	x, y, u, v;
};

class PostProcess
{
public:
	PostProcess( FI::GFX::API *api );
	virtual ~PostProcess();

	virtual void initUniforms();// set uniform buffer pointer and size members here.
	virtual void setUniforms();	// set values inside uniform buffer

	virtual void activate(){}
	virtual void deactivate(){}

	virtual void parameter(std::string param, void *outData){}
	virtual void setParameter( std::string param, const void *data=nullptr ){};

    void init(std::string path="");
	void deinit();
	void render();
	void framePixels(int width, int height, int channels, void *data);

	void resize(unsigned int width, unsigned int height);

	std::string getName();

	void setMatrix( const MATH::Matrix &mat ); //model-view-proj matrix for rendering fullscreen quad
	void setVideoSize( unsigned int width, unsigned int height ); // video frame dimensions
	void setDisplayResolution( unsigned int width, unsigned int height ); // native resolution of the display
	void setWindow( unsigned int x, unsigned int y, unsigned int w, unsigned int h );
    
    std::string path(); // get the search path

protected:
	unsigned int  	m_windowX,
					m_windowY,
					m_windowWidth,
					m_windowHeight,
					m_videoWidth,
					m_videoHeight,
					m_resWidth,
					m_resHeight;

	ShaderProgram	*m_shaderProgram;

	FI::GFX::API	*m_gfx;

	SamplerState  	*m_samplerState;

	const void		*m_uniformBufferPtr;
	unsigned int  	m_uniformBufferSize;

	const char   	*m_vsCode,
					*m_fsCode;

	unsigned int  	m_vbo,
					m_ubo,
					m_inputLayout;

	Vertex2D 		*m_vertexData;

	std::string		m_name;
	
	MATH::Matrix	m_matrix;
    
    std::string     m_path; //searchpath for shaders, etc.
};

} //ns GFX
} //NS FI

#endif /* _GFX_POST_PROCESS_H */
