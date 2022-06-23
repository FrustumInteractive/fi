/*
 * pp_sbs_lenticular.h
 *
 *  Created on: Aug 18, 2015
 *      Author: Roger Dass
 */

#ifndef SRC_PP_SBSLENTICULAR_H_
#define SRC_PP_SBSLENTICULAR_H_

#include "graphics/postProcess/postProcess.h"

namespace FI{ namespace SHADERS {
	const char *pp_sbs_lenticular_vs_gl2();
	const char *pp_sbs_lenticular_fs_gl2();
	const char *pp_sbs_lenticular_vs_gl3();
	const char *pp_sbs_lenticular_fs_gl3();
	const char *pp_sbs_lenticular_vs_ES2();
	const char *pp_sbs_lenticular_fs_ES2();
	const char *pp_sbs_lenticular_vs_ES3();
	const char *pp_sbs_lenticular_fs_ES3();
}
}

namespace FI {
namespace GFX {

class Lenticular;

class PP_SBSLenticular: public PostProcess
{
public:
	PP_SBSLenticular(API *api);
	virtual ~PP_SBSLenticular();

	virtual void initUniforms();
	virtual void setUniforms();

	virtual void activate();
	virtual void deactivate();

	virtual void parameter(std::string param, void *outData);
	virtual void setParameter(std::string param, const void *data=nullptr);

	void setHeadPos( float x, float y, float z);

private:
	UniformBuffer *m_uniforms;

	Lenticular *m_lenticular;
	bool m_bUsingOwnLenticular;

};

} //ns GFX
} //ns FI

#endif /* SRC_GPP_SBSLENTICULAR_H_ */
