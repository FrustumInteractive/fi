#ifndef _FI_UTIL_
#define _FI_UTIL_

#include <string>
#include <sstream>
#include <vector>
#include <functional>
#include <dirent.h>

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

typedef std::unordered_map<std::string, int> CmdLineArgMap; // intVal: <0 -> has following value, 0 -> no opt, >0 opt flag.
typedef std::function<void(int, std::string)> CmdLineArgHandler;
#define FI_CMD_OPT_NONE "FI_CMD_OPT_NONE"

inline void processCmdLineArgs(
	int argc, char *argv[],
	const CmdLineArgMap &argMap,
	const CmdLineArgHandler &argHandler) // provide map of str->int/enum as well as fn() for passed in int
{
	if (argc == 1)
	{
		argHandler(0, FI_CMD_OPT_NONE);
	}
	for (int i=1; i < argc; i++)
	{
		if (auto id = argMap.find(argv[i]); id != argMap.end())
		{
			// argument is in the provided list...
			std::string out;
			if (id->second > 0)
			{
				// argument has a following value
				if (i+1 < argc)
				{
					out = argv[i+1];
					i++; // skip this next iteration
				}
			}
			argHandler(id->second, out);
		}
		else
		{
			// no option in list - just a loose string, pass on to see if fn() has any ideas.
			argHandler(0, argv[i]);
		}
	}
}

inline void listFiles(const std::string &path, std::function<void(const std::string &)> cb) // recursively list all files in path
{
	if (const auto dir = opendir(path.c_str()))
	{
		while (const auto f = readdir(dir))
		{
			if (f->d_name[0] == '.')
			{
				continue;
			}
			if (f->d_type == DT_DIR)
			{
				listFiles(path + "/" + f->d_name, cb);
			}
			else if (f->d_type == DT_REG)
			{
				cb(path + "/" + f->d_name);
			}
		}
		closedir(dir);
	}
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
