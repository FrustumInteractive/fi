/*
 * pp_mv_lenticular.h
 *
 *  Created on: Aug 18, 2015
 *      Author: Roger Dass
 */

#ifndef SRC_PP_MVLENTICULAR_H_
#define SRC_PP_MVLENTICULAR_H_

#include "graphics/postProcess/postProcess.h"

namespace FI {
namespace GFX {

typedef enum ViewLayout
{
	VIEW_LAYOUT_2X1,
	VIEW_LAYOUT_2X2
} ViewLayout;

class Lenticular;

class PP_MVLenticular: public PostProcess
{
public:
	PP_MVLenticular(API *api);
	virtual ~PP_MVLenticular();

	virtual void initUniforms();
	virtual void setUniforms();

	virtual void activate();
	virtual void deactivate();

	virtual void parameter(std::string param, void *outData);
	virtual void setParameter(std::string param, const void *data=nullptr);

	void setHeadPos( float x, float y, float z);
	void setInputViewLayout(ViewLayout vl);

private:
	UniformBuffer *m_uniforms;

	Lenticular *m_lenticular;
	bool m_bUsingOwnLenticular;

};

} //ns GFX
} //ns FI

#endif /* SRC_PP_MVLENTICULAR_H_ */
