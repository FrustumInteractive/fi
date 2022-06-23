/*
 * VFRI420.h
 *
 *  Created on: Aug 17, 2015
 *      Author: Roger Dass
 */

#ifndef SRC_VFR_I420_H_
#define SRC_VFR_I420_H_

#include "videoFrameRenderer.h"

class VFR_I420: public VideoFrameRenderer
{
public:
	VFR_I420();
	virtual ~VFR_I420();

	void initUniforms();
	void setUniforms();

private:
};

#endif /* SRC_VFR_I420_H_ */
