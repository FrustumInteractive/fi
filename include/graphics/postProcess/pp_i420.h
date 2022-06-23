/*
 * pp_i420.h
 *
 *  Created on: Aug 17, 2015
 *      Author: Roger Dass
 */

#ifndef SRC_PP_I420_H_
#define SRC_PP_I420_H_

#include "graphics/postProcess/postProcess.h"

namespace FI{ namespace SHADERS {
	const char *pp_i420_vs_gl2();
	const char *pp_i420_fs_gl2();
	const char *pp_i420_vs_gl3();
	const char *pp_i420_fs_gl3();
	const char *pp_i420_vs_ES3();
	const char *pp_i420_fs_ES3();
}
}

namespace FI {
namespace GFX {

class PP_I420: public PostProcess
{
public:
	PP_I420( API *api );
	virtual ~PP_I420();

	void initUniforms();
	void setUniforms();

private:
	UniformBuffer *m_uniforms;
};

} //ns GFX
} //ns FI

#endif /* SRC_PP_I420_H_ */
