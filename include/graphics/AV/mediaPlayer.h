/* interface to native media player */

#ifndef _MEDIAPLAYER_H
#define _MEDIAPLAYER_H

#include <string>
#include <chrono>
#include <mutex>

namespace FI {

class MediaPlayer
{
public:
	MediaPlayer() :
		m_glTextureName(0),
		m_glTextureTarget(0),
		m_isStarted(false),
		m_isPaused(false),
		m_isRateLimited(true),
		m_hasEnded(true),
		m_filename(""),
		m_frameRate(0)
	{}

	virtual ~MediaPlayer(){}
	
	virtual void load(const std::string &filename){}

	virtual void play(){}
	virtual void pause(){}
	virtual void stop(){}
	virtual void seek(float time){}

	void updateMediaFrame() { updateTexture(); }

	unsigned int textureName()
	{
		std::lock_guard<std::mutex> lock(m_mutex);
		return m_glTextureName;
	}

	unsigned int textureTarget()
	{
		std::lock_guard<std::mutex> lock(m_mutex);
		return m_glTextureTarget;
	}

	unsigned int width(){return m_width;}
	unsigned int height(){return m_height;}
	unsigned int fps(){return m_fps;}
	
	void limitToFrameRate(bool b){m_isRateLimited = b;}
	
	bool hasEnded(){return m_hasEnded;}

    static MediaPlayer* create();
    static void destroy( MediaPlayer* &mp );

protected:
	virtual void initReader(){}
	virtual void cleanupFrame(){}
	virtual void updateTexture(){}

	unsigned int m_glTextureName;
	unsigned int m_glTextureTarget;

	unsigned int m_width, m_height, m_fps;

	bool m_isStarted;
	bool m_isPaused;
	bool m_isRateLimited;
	bool m_hasEnded;
	
	std::string m_filename;
	
	float	m_frameRate;
	std::chrono::time_point<std::chrono::steady_clock> m_updateTime;
	std::mutex m_mutex;
};
} /* NS FI*/


#endif /* _MEDIAPLAYER_H */
