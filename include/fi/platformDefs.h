#ifndef _PLATFORMDEFS_H
#define _PLATFORMDEFS_H

#ifdef __APPLE__
	#include "TargetConditionals.h"
	#if TARGET_IPHONE_SIMULATOR
		// iOS Simulator
		#define IOS
		#define SIMULATOR
		#define _IOS
		#define _SIMULATOR
	#elif TARGET_OS_IPHONE
		// iOS device
		#define _IOS
		#define IOS
	#elif TARGET_OS_MAC
		// Other kinds of Mac OS
		#if __has_feature(objc_arc)
			#define ARC
		#endif
	#else
		#error "Unknown Apple platform"
	#endif
#else
	#if LINUX
	#elif __ANDROID__
		#define _ANDROID
	#else
	#endif /* LINUX */
#endif /* __APPLE__ */

#endif /* _PLATFORMDEFS_H*/