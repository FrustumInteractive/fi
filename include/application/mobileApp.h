/*
* mobileApp.h
*
*  Created on: Aug 10, 2015
*      Author: Roger Dass
*		Copyright Frustum Interactive Inc. - All rights reserved.
*/

#ifndef _MOBILEAPP_H
#define _MOBILEAPP_H

#include "application.h"
//#include "cocoaWrapper.h"

class MobileApp : public Application
{
public:
	MobileApp(const int argc = 0, const char *argv[] = 0);
	virtual ~MobileApp();

	void createWindow(const char *title, int x, int y, int width, int height, bool fullscreen);
	void destroyWindow();

	void mainloop();	

	//void resize(int width, int height){}

protected:
	
	void swapBuffers();

	//GLint		*m_attributes;
};

#endif /*_MOBILEAPP_H*/
