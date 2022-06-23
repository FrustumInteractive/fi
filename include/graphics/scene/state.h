/*
*  state.h
*
*  Created by Roger Dass on 12-05-01.
*  Copyright 2012 Frustum Interactive. All rights reserved.
*  No warranty, explicit or implicit, provided.
*
*/

#ifndef _SCENESTATE_H
#define _SCENESTATE_H

namespace FI {
namespace GFX {

class Scene;

class SceneState
{
public:

	virtual void init(Scene *scene) = 0;
	virtual void cleanup() = 0;

	virtual void pause() = 0;
	virtual void resume() = 0;

	virtual void handleEvents() = 0;
	virtual void update() = 0;
	virtual void draw() = 0;

	void changeState(SceneState* state);

protected:
	SceneState(){}
};

} //NS GFX
} //NS FI

#endif