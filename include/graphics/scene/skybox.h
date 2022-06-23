#ifndef _SKYBOX_H
#define _SKYBOX_H

#include "math/vec3.h"

namespace FI {
namespace GFX {

class Skybox
{
public:
	Skybox();
	~Skybox();

	bool init(const char *fname);
	void cleanup();
	void update();
	void draw();

	void setViewPos(const vec3 &pos);
	void setViewRot(const vec3 &rot);
	void setViewDir(const vec3 &dir);

	const char *m_filePath;

private:

	void m_loadTextures();
	void m_releaseTextures();

	unsigned int m_texID[6];
	vec3 m_viewPos;
	vec3 m_viewRot;
	vec3 m_viewDir;
	//CWorld m_skyboxModel;
};


} //NS GFX
} //NS FI

#endif