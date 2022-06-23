/*
 * VFR_hydrogenOne_i420.h
 */

#ifndef _VFR_HYDROGEN_ONE_I420_H_
#define _VFR_HYDROGEN_ONE_I420_H_

#include "videoFrameRenderer.h"

class VFR_HydrogenOne_I420: public VideoFrameRenderer
{
public:
	VFR_HydrogenOne_I420();
	virtual ~VFR_HydrogenOne_I420();

	void initUniforms();
	void setUniforms();

private:
	unsigned int m_imageSizeUniform;
};

#endif /* _VFR_HYDROGEN_ONE_I420_H_ */
