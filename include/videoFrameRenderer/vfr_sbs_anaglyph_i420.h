/*
 * VFR_SBSAnaglyph_I420.h
 *
 *  Created on: Aug 18, 2015
 *      Author: Roger Dass
 */

#ifndef SRC_VFR_SBSANAGLYPH_I420_H_
#define SRC_VFR_SBSANAGLYPH_I420_H_

#include "videoFrameRenderer.h"

class VFR_SBSAnaglyph_I420: public VideoFrameRenderer
{
public:
	VFR_SBSAnaglyph_I420();
	virtual ~VFR_SBSAnaglyph_I420();

	void initUniforms();
	void setUniforms();

private:
	unsigned int m_imageSizeUniform;
};

#endif /* SRC_VFR_SBSANAGLYPH_I420_H_ */
