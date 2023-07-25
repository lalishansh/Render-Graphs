#pragma once

// Tip: This file is for compiler identification
//      and should not be used for anything else.

#if defined(__GNUC__)
	#define COMPILER_GCC                  1
	#define PRAGMIFY(x)                   _Pragma (#x)
	#define COMPILER_WARNING_AVAILABLE(x) __has_warning (x)
	#define COMPILER_WARNING_DISABLE(x)   PRAGMIFY (GCC diagnostic ignored x)
#elif defined(__clang__)
	#define COMPILER_CLANG                1
	#define PRAGMIFY(x)                   _Pragma (#x)
	#define COMPILER_WARNING_AVAILABLE(x) __has_warning (x)
	#define COMPILER_WARNING_DISABLE(x)   PRAGMIFY (clang diagnostic ignored x)
#elif defined(_MSC_VER)
	#define COMPILER_MSVC                 1
	#define PRAGMIFY(x)                   __pragma (x)
	#define COMPILER_WARNING_AVAILABLE(x) 1
	#define COMPILER_WARNING_DISABLE(x)   PRAGMIFY (warning (disable : x))
#else
	#error "Unknown compiler"
#endif

#if defined(__cplusplus) || defined(c_plusplus) || defined(__CPLUSPLUS__)
    #define CPP_COMPILER 1
#endif

#if defined(__OBJC__)
    #define OBJC_COMPILER 1
#endif