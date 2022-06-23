#ifndef _OSXAPP_H
#define _OSXAPP_H

#include "application/application.h"
#include "cocoaWrapper.h"

class OSXApp : public Application
{
public:
	OSXApp(const int argc = 0, const char *argv[] = 0);
	virtual ~OSXApp();

	void createWindow(const char *title, int x, int y, int width, int height, bool fullscreen) override;
	void destroyWindow() override;

	void mainloop() override;

protected:
	
	void swapBuffers();

	int	*m_attributes;
};

#endif /*_OSXAPP_H*/
