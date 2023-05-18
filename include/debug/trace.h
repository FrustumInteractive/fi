// TRACE macro for win32
#ifndef __DEBUG_H__
#define __DEBUG_H__

#include <iostream>
#include <string>
#include <stdexcept>
#include <chrono>


// --- debug / logging
namespace FI {

inline void _MSG()
{
	std::cout << std::endl << std::flush;
}

template<typename Head, typename... Args>
inline void _MSG(const Head& head, const Args&... args )
{
	std::cout << head << " ";
	_MSG(args...);
}

inline void _THROW( const std::string fn, const std::string desc )
{
	std::string s = fn + ": " + desc;
	throw std::invalid_argument(s);
}

#define THROW(x)    _THROW(__PRETTY_FUNCTION__,x)

// exmple without using macro - but need to get calling fn name somehow...
//template<typename... Args> inline void DEBUG(Args&&... args)	{ _MSG(__PRETTY_FUNCTION__, ": ", std::forward<Args>(args)...); }

#define TRACE(...)   _MSG(__PRETTY_FUNCTION__, ": ", __VA_ARGS__)
#define LOG(...)     _MSG(__FUNCTION__, ": ", __VA_ARGS__)
#define PRINT(...)   _MSG(__VA_ARGS__)

class ScopeTimer
{
public:
	inline ScopeTimer(std::string tag = "") :
		m_tag(tag)
	{
		m_start = std::chrono::steady_clock::now();
	}
	
	virtual inline ~ScopeTimer()
	{
		m_stop = std::chrono::steady_clock::now();
		FI::PRINT(
			"Stopwatch ETA <", m_tag, "> ",
			std::chrono::duration<double, std::milli>(m_stop-m_start).count(),
			" ms.");
	}
private:
	std::chrono::time_point<std::chrono::steady_clock> m_start, m_stop;
	std::string m_tag;
};

// ---
} /* NS FI */
#endif // __DEBUG_H__
