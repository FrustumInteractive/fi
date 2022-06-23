/*
 * VFR_SBSLenticular.h
 *
 *  Created on: Aug 18, 2015
 *      Author: Roger Dass
 */

#ifndef SRC_VFR_SBSLENTICULAR_H_
#define SRC_VFR_SBSLENTICULAR_H_

#include "videoFrameRenderer.h"

class Lenticular;

class VFR_SBSLenticular: public VideoFrameRenderer
{
public:
	VFR_SBSLenticular();
	virtual ~VFR_SBSLenticular();

	void initUniforms();
	void setUniforms();

	void setHeadPos( float x, float y, float z);

	void activate();
	void deactivate();

	void setData(void *data);

private:
	unsigned int m_imageSizeUniform;

	unsigned int m_pitchUniform;
	unsigned int m_tanUniform;
	unsigned int m_shiftUniform;
	unsigned int m_magUniform;
	unsigned int m_windowUniform;
	unsigned int m_screenUniform;
	unsigned int m_screenCenterUniform;
	unsigned int m_offsetCenterUniform;
	unsigned int m_magCenterUniform;
	unsigned int m_tcStepUniform;
	unsigned int m_tcWindowUniform;

	Lenticular *m_lenticular;
	bool m_bUsingOwnLenticular;

};

#endif /* SRC_VFR_SBSLENTICULAR_H_ */
