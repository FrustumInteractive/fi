/*
 * VideoFrameRenderer.h
 *
 *  Created on: Aug 17, 2015
 *      Author: Roger Dass
 */

#ifndef _VIDEOFRAMERENDERER_H
#define _VIDEOFRAMERENDERER_H

#include "videoFrameRenderer/vfrModule.h"

class QGLShaderProgram;
class QMatrix4x4;
class QGLBuffer;

class VideoFrameRenderer
{
public:
	VideoFrameRenderer(VFRModule *vfrm = nullptr, std::string filename = "");
	virtual ~VideoFrameRenderer(){}

	virtual void initUniforms(){}
	virtual void setUniforms(){}

	virtual void activate();
	virtual void deactivate();

	virtual void setData( void *data ){};
	virtual void onResize(unsigned int w, unsigned int h);
	virtual void onVideoResize(unsigned int w, unsigned int h);

	void init();
	void deinit();
	void render();

	void resize(unsigned int width, unsigned int height);

	const char *getName() const;
	std::string getFilename() const;
	float getPixelAspectRatio() const;

	void setVideoSize( unsigned int width, unsigned int height ); // video frame dimensions
	void setDisplayResolution( unsigned int width, unsigned int height ); // native resolution of the display
	void setWindow( unsigned int x, unsigned int y, unsigned int w, unsigned int h );
	void setZoom(float zoom);
	void setPixelAspectRatio(float a);
	void setTint(float r, float g, float b, float a);
	void setParameterMap(const std::unordered_map<std::string, std::string> *pm);

protected:
	unsigned int
		m_windowX,
		m_windowY,
		m_windowWidth,
		m_windowHeight,
		m_videoWidth,
		m_videoHeight,
		m_resWidth,
		m_resHeight;

	float
		m_zoom,
		m_pixelAspectRatio,
		m_tint[4];

	QGLShaderProgram *m_shaderProgram;

	const char 
		*m_vsFilename,
		*m_fsFilename,
		*m_vsCode,
		*m_fsCode,
		*m_name;

	std::string m_filename;

	QMatrix4x4	*m_matrix;

	QGLBuffer	*m_vbo;

	VFRModule *m_vfrModule;

	std::vector<QGLShaderProgram*> m_passShaderPrograms;

	const std::unordered_map<std::string, std::string> *m_parameterMapPtr;
};

#endif /* _VIDEOFRAMERENDERER_H */
