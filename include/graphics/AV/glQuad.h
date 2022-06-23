#ifndef _GL_QUAD_H
#define _GL_QUAD_H

#include "application/oglApp.h"

namespace FI {

class GLQuad
{
public:
	GLQuad( unsigned int texWidth, unsigned int texHeight, const float* matrix = 0);
	virtual ~GLQuad();
	
	void draw();
	
	void setTexture(GLuint tex);
	void setMatrix(float *m);
	
private:
	GLuint loadShader(GLenum type, const char* shaderSrc);
	
	GLuint	m_width,
	m_height,
	m_tex,
	m_shaderProgram,
	m_matUniformLoc,
	m_vPosAttrib,
	m_vertexBuffer;
	
	const float *m_matrix;
	float m_intMat[16];
};
	

} /* NS FI*/

#endif /*_GL_QUAD_H*/