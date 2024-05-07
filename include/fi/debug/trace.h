// TRACE macro for win32
#ifndef __DEBUG_H__
#define __DEBUG_H__

#include <iostream>
#include <string>
#include <stdexcept>
#include <chrono>
#include <unordered_map>

// --- debug / logging
namespace FI {

class IntentionalExit : public std::exception
{
public:
	IntentionalExit(std::string reason)
		: m_reason(reason)
	{}

	const char* what() const noexcept override
	{
		return m_reason.c_str();
	}
private:
	std::string m_reason;
};

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
	throw IntentionalExit(s);
}

#define THROW(x)    _THROW(__PRETTY_FUNCTION__,x)

// exmple without using macro - but need to get calling fn name somehow...
//template<typename... Args> inline void DEBUG(Args&&... args)	{ _MSG(__PRETTY_FUNCTION__, ": ", std::forward<Args>(args)...); }

#define TRACE(...)   _MSG(__PRETTY_FUNCTION__, ": ", __VA_ARGS__)
#define LOG(...)     _MSG(__FUNCTION__, ": ", __VA_ARGS__)
#define PRINT(...)   _MSG(__VA_ARGS__)


// -- Timer Utils --

class ScopeTimer
{
public:
	inline ScopeTimer(std::string tag = "", bool isCumulative = false, unsigned iterationsBeforeReport = 0, bool shouldExit = false)
		: m_tag(tag)
		, m_isCumulative(isCumulative)
		, m_shouldExit(shouldExit)
		, m_iterationsBeforeReport(iterationsBeforeReport)

	{
		m_start = std::chrono::steady_clock::now();
	}

	virtual inline ~ScopeTimer()
	{
		static std::unordered_map<std::string, std::pair<double, unsigned>> s_times;
		m_stop = std::chrono::steady_clock::now();

		if (!m_isCumulative)
		{
			s_times[m_tag].first = 0;
		}

		s_times[m_tag].first += std::chrono::duration<double, std::milli>(m_stop-m_start).count();

		if (s_times[m_tag].second == m_iterationsBeforeReport)
		{
			FI::PRINT("\n");
			for (auto& t : s_times)
			{
				FI::PRINT(" Stopwatch ETA <", t.first, "> ", t.second.first, " ms.");
			}
			FI::PRINT("\n");

			if (m_shouldExit)
			{
				FI::THROW("scope timer complete.");
			}
		}
		s_times[m_tag].second++;
	}

private:
	std::chrono::time_point<std::chrono::steady_clock> m_start, m_stop;
	std::string m_tag;
	bool m_isCumulative = false;
	bool m_shouldExit = false;
	unsigned m_iterationsBeforeReport = 0;
};

// ---
} /* NS FI */
#endif // __DEBUG_H__
