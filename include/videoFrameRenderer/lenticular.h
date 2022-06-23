/*
 * lenticular.h
 *
 *  Created on: Aug 25, 2015
 *      Author: Roger Dass
 */

#ifndef SRC_LENTICULAR_H_
#define SRC_LENTICULAR_H_

class Lenticular {
public:
	Lenticular();
	virtual ~Lenticular();

	void update();

	void saveCalibrationFile( const char *filename);
	void loadCalibrationFile( const char *filename);

	void initEyetracker();
	void deinitEyetracker();

	void setRotation( float theta ){m_theta = theta;}
	void setRadius( float r){m_radius = r;}
	void setLensWidth(float lw){m_lensWidth=lw;}
	void setIOR(float n){m_ior = n;}
	void setSubstrateThickness(float t){m_substrateThickness = t;}
	void setObjectPlaneDistance(float d){m_objectPlaneDistance = d;}
	void setDotPitch(float dp){m_dotPitch = dp;}
	void setWindow(float x, float y, float w, float h){m_window[0]=x; m_window[1]=y; m_window[2]=w; m_window[3]=h;}
	void setScreenSize(float w, float h){m_screen[0]=w;m_screen[1]=h;}
	void setShift(float shift){m_shift = shift;}
	void setMagnification(float m){m_magnification = m;}

	float getRotation(){ return m_theta;}
	float getRadius(){return m_radius;}
	float getLensWidth(){return m_lensWidth;}
	float getIOR(){return m_ior;}
	float getSubstrateThickness(){return m_substrateThickness;}
	float getObjectPlaneDistance(){return m_objectPlaneDistance;}
	float getDotPitch(){return m_dotPitch;}
	float getScreenWidth(){return m_screen[0];}
	float getScreenHeight(){return m_screen[1];}
	float getShift(){return m_shift;}
	float getMagnification(){return m_magnification;}

	float getPitchUniform(){return m_px;}
	float getTanUniform(){return m_tan;}
	float getShiftUniform(){return m_shift;}
	float *getMagUniform(){return m_mag;}
	float *getWindowUniform(){return m_window;}
	float *getScreenUniform(){return m_screen;}
	float *getScreenCenterUniform(){return m_screenCenter;}
	float *getOffsetCenterUniform(){return m_offsetCenter;}
	float *getMagCenterUniform(){return m_magCenter;}
	float *getTCStepUniform(){return m_tcStep;}
	float *getTCWindowUniform(){return m_tcWindow;}

private:

	float 	m_theta,
			m_tanTheta,
			m_radius,
			m_lensWidth,
			m_ior,
			m_substrateThickness,
			m_objectPlaneDistance,
			m_screen[2],
			m_dotPitch,
			m_minS,
			m_maxS,
			m_minT,
			m_maxT,
			m_magnification,
			m_pupilaryDistance;

	float	m_pitch[2],
			m_px,
			m_tan,
			m_shift,
			m_mag[2],
			m_window[4],
			m_screenCenter[2],
			m_offsetCenter[2],
			m_magCenter[2],
			m_tcStep[2],
			m_tcWindow[2];
};

#endif /* SRC_LENTICULAR_H_ */
