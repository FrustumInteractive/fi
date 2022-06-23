/*
 * pp_sbs_anaglyph_i420.h
 *
 *  Created on: Aug 18, 2015
 *      Author: Roger Dass
 */

#ifndef SRC_PP_SBSANAGLYPH_I420_H_
#define SRC_PP_SBSANAGLYPH_I420_H_

#include "graphics/postProcess/postProcess.h"

namespace FI{ namespace SHADERS {
	const char *pp_sbs_anaglyph_i420_vs_gl2();
	const char *pp_sbs_anaglyph_i420_fs_gl2();
	const char *pp_sbs_anaglyph_i420_vs_gl3();
	const char *pp_sbs_anaglyph_i420_fs_gl3();
	const char *pp_sbs_anaglyph_i420_vs_ES3();
	const char *pp_sbs_anaglyph_i420_fs_ES3();
}
}

namespace FI {
namespace GFX {

class PP_SBSAnaglyph_I420: public PostProcess
{
public:
	PP_SBSAnaglyph_I420( API *api );
	virtual ~PP_SBSAnaglyph_I420();

	void initUniforms();
	void setUniforms();

private:
	UniformBuffer *m_uniforms;
};

} //NS GFX
} //NS FI

#endif /* SRC_GPP_SBSANAGLYPH_I420_H_ */
