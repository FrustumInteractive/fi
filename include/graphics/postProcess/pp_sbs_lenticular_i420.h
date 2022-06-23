/*
 * pp_sbs_Lenticular_i420.h
 *
 *  Created on: Aug 18, 2015
 *      Author: Roger Dass
 */

#ifndef SRC_PP_SBSLENTICULAR_I420_H_
#define SRC_PP_SBSLENTICULAR_I420_H_

#include "graphics/postProcess/postProcess.h"

namespace FI{ namespace SHADERS {
	const char *pp_sbs_lenticular_i420_vs_gl2();
	const char *pp_sbs_lenticular_i420_fs_gl2();
	const char *pp_sbs_lenticular_i420_vs_gl3();
	const char *pp_sbs_lenticular_i420_fs_gl3();
	const char *pp_sbs_lenticular_i420_vs_ES3();
	const char *pp_sbs_lenticular_i420_fs_ES3();
}
}

namespace FI {
namespace GFX {

class Lenticular;

class PP_SBSLenticular_I420: public PostProcess
{
public:
	PP_SBSLenticular_I420( API *api );
	virtual ~PP_SBSLenticular_I420();

	void initUniforms();
	void setUniforms();

	void setHeadPos( float x, float y, float z);

	void activate();
	void deactivate();

	virtual void parameter(std::string param, void *outData);
	virtual void setParameter(std::string param, const void *data=nullptr);

private:
	UniformBuffer *m_uniforms;

	Lenticular *m_lenticular;
	bool m_bUsingOwnLenticular;

};

} //ns GFX
} //ns FI

#endif /* SRC_GPP_SBSLENTICULAR_I420_H_ */
