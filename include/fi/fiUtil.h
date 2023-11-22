#ifndef _FI_UTIL_
#define _FI_UTIL_

#include <string>
#include <sstream>

#include "debug/trace.h"

namespace FI {
namespace UTIL {

// incrementing filenames
inline std::string incrementName(const std::string& name)
{
	size_t split = name.length();
	while (split > 0)
	{
		if (!isdigit(name[split - 1]))
			break;
		split--;
	}

	if (split < name.length())
	{
		std::string prefix = name.substr(0, split);
		std::string suffix = name.substr(split, name.length());
		return prefix + "_" + std::to_string(std::stoi(suffix) + 1);
	}
	return name + "_2";
}

inline std::string commaSeparatedNumber(int number)
{
	auto s = std::to_string(number);

	int n = (int)s.length() - 3;
	int end = (number >= 0) ? 0 : 1; // Support for negative numbers
	while (n > end)
	{
		s.insert(n, ",");
		n -= 3;
	}
	return s;
}

} /*NS UTIL*/
} /*NS FI*/

#ifdef __ANDROID_API__

#include <jni.h>

template <typename T>
std::string to_string(T value)
{
	std::ostringstream os ;
	os << value ;
	return os.str() ;
}

FILE* android_fopen(const char* fname, const char* mode);
#define fopen(name, mode) android_fopen(name, mode)

extern void android_thread_attach(const char *name = nullptr);

extern void android_thread_detach();

extern bool android_egl_context_exists();


#endif /*__ANDROID_API__*/


#endif /*_FI_UTIL_*/
