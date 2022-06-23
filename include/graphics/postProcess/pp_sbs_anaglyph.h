/*
 * pp_sbs_anaglyph.h
 *
 *  Created on: Aug 18, 2015
 *      Author: Roger Dass
 */

#ifndef SRC_PP_SBSANAGLYPH_H_
#define SRC_PP_SBSANAGLYPH_H_

#include "graphics/postProcess/postProcess.h"

namespace FI{ namespace SHADERS {
	const char *pp_sbs_anaglyph_vs_gl2();
	const char *pp_sbs_anaglyph_fs_gl2();
	const char *pp_sbs_anaglyph_vs_gl3();
	const char *pp_sbs_anaglyph_fs_gl3();
	const char *pp_sbs_anaglyph_vs_ES2();
	const char *pp_sbs_anaglyph_fs_ES2();
	const char *pp_sbs_anaglyph_vs_ES3();
	const char *pp_sbs_anaglyph_fs_ES3();
}
}

namespace FI {
namespace GFX {

class PP_SBSAnaglyph: public PostProcess
{
public:
	PP_SBSAnaglyph( API *api );
	virtual ~PP_SBSAnaglyph();

	void initUniforms();
	void setUniforms();

private:
	UniformBuffer *m_uniforms;
};


} //NS GFX
} //NS FI

#endif /* SRC_PP_SBSANAGLYPH_H_ */
