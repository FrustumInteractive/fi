#ifndef _FI_UTIL_
#define _FI_UTIL_

#include <string>
#include <sstream>

#include "debug/trace.h"

#ifdef __ANDROID_API__

namespace std {
	template <typename T>
	std::string to_string(T value)
	{
		std::ostringstream os ;
		os << value ;
		return os.str() ;
	}
}

FILE* android_fopen(const char* fname, const char* mode);
#define fopen(name, mode) android_fopen(name, mode)

#endif /*__ANDROID_API__*/

#endif /*_FI_UTIL_*/
