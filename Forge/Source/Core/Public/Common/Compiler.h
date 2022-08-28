#ifndef COMPILER_H
#define COMPILER_H

/// Detect plaftorm
#if defined(__ANDROID__)
	#define FORGE_PLATFORM_ANDROID
	#error "Android is not currently supported."
#elif defined(__linux__)
	#define FORGE_PLATFORM_LINUX
	#error "Linux is not currently supported."
#elif defined(__APPLE__)
	#define FORGE_PLATFORM_MACOS
	#error "MacOS is not currently supported."
#elif defined(_WIN32)
	#define FORGE_PLATFORM_WINDOWS
#else
	#error "Unable to detect platform."
#endif

/// Detect compiler
#if defined(__clang__)
	#define FORGE_COMPILER_CLANG
#elif defined(__INTEL_COMPILER)
	#define FORGE_COMPILER_INTEL
#elif defined(__EMSCRIPTEN__)
	#define FORGE_COMPILER_EMSCRIPTEN
#elif defined(__GNUC__)
	#define FORGE_COMPILER_GCC
#elif defined(__MINGW32__)
	#define FORGE_COMPILER_MINGW
#elif defined(_MSC_VER)
	#define FORGE_COMPILER_MSVC
#else
	#error "Unable to detect compiler."
#endif

/// Detect CPU architectures
#if defined(__x86_64__)    \
 || defined(_M_X64)        \
 || defined(__aarch64__)   \
 || defined(__mips64)      \
 || defined(__powerpc64__) \
 || defined(__ppc64__)     \
 || defined(__LP64__)
	#define FORGE_ARCH_64BIT
#else
	#define FORGE_ARCH_32BIT
#endif

/// Platform name
#if defined(FORGE_PLATFORM_ANDROID)
	#define FORGE_PLATFORM_NAME "Android"
#elif defined(FORGE_PLAFTORM_LINUX)
	#define FORGE_PLATFORM_NAME "Linux"
#elif defined(FORGE_PLATFORM_MACOS)
	#define FORGE_PLATFORM_NAME "MacOS"
#elif defined(FORGE_PLATFORM_WINDOWS)
	#define FORGE_PLATFORM_NAME "Windows"
#endif

/// Compiler name
#if defined(FORGE_COMPILER_CLANG)
	#define FORGE_COMPILER_NAME "Clang " \
			#__clang_major__ "."         \
			#__clang_minor__ "."         \
			#__clang_patchlevel__
#elif defined(FORGE_COMPILER_INTEL)
	#define FORGE_COMPILER_NAME "Intel Compiler " \
			#__INTEL_COMPILER
#elif defined(FORGE_COMPILER_EMSCRIPTEN)
	#define FORGE_COMPILER_NAME "Emscripten " \
			#__EMSCRIPTEN_major__ "."         \
			#__EMSCRIPTEN_minor__ "."         \
			#__EMSCRIPTEN_tiny__
#elif defined(FORGE_COMPILER_GCC)
	#define FORGE_COMPILER_NAME "GCC " \
			#__GNUC__ "."              \
			#__GNUC_MINOR__ "."        \
			#__GNUC_PATCHLEVEL__
#elif defined(FORGE_COMPILER_MINGW)
	#define FORGE_COMPILER_NAME "MINGW"  \
			#__MINGW32_MAJOR_VERSION "." \
			#__MINGW32_MINOR_VERSION
#elif defined(FORGE_COMPILER_MSVC)
	#if _MSC_VER >= 1930   /// Visual Studio 2022
		#define FORGE_COMPILER_NAME "MSVC 17.0"
	#elif _MSV_VER >= 1920 /// Visual Studio 2019
		#define FORGE_COMPILER_NAME "MSVC 16.0"
	#elif _MSV_VER >= 1910 /// Visual Studio 2017
		#define FORGE_COMPILER_NAME "MSVC 15.0"
	#elif _MSV_VER >= 1900 /// Visual Studio 2015
		#define FORGE_COMPILER_NAME "MSVC 14.0"
	#elif _MSV_VER >= 1800 /// Visual Studio 2013
		#define FORGE_COMPILER_NAME "MSVC 12.0"
	#elif _MSV_VER >= 1700 /// Visual Studio 2012
		#define FORGE_COMPILER_NAME "MSVC 11.0"
	#elif _MSV_VER >= 1600 /// Visual Studio 2010
		#define FORGE_COMPILER_NAME "MSVC 10.0"
	#elif _MSV_VER >= 1500 /// Visual Studio 2008
		#define FORGE_COMPILER_NAME "MSVC 9.0"
	#else
		#define FORGE_COMPILER_NAME "MSVC"
	#endif
#endif

/// CPU architecture name
#if defined(FORGE_ARCH_32BIT)
	#define FORGE_ARCH_NAME "32-Bit"
#elif defined(FORGE_ARCH_64BIT)
	#define FORGE_ARCH_NAME "64-Bit"
#endif

/// Compiler specific modifiers
#if defined(FORGE_COMPILER_CLANG)
	#define FORGE_CDECL       
	#define FORGE_STDCALL     
	#define FORGE_INLINE      
	#define FORGE_FORCE_INLINE
	#define FORGE_DEBUG_BREAK 
	#define FORGE_DLL_EXPORT  
	#define FORGE_DLL_IMPORT  
	#define FORGE_NO_INLINE   
	#define FORGE_NO_RETURN   
	#define FORGE_DEPRECATED  
	#error "Clang is not currently supported."
#elif defined(FORGE_COMPILER_INTEL)
	#define FORGE_CDECL       
	#define FORGE_STDCALL     
	#define FORGE_INLINE      
	#define FORGE_FORCE_INLINE
	#define FORGE_DEBUG_BREAK 
	#define FORGE_DLL_EXPORT  
	#define FORGE_DLL_IMPORT  
	#define FORGE_NO_INLINE   
	#define FORGE_NO_RETURN   
	#define FORGE_DEPRECATED  
	#error "Intel compiler is not currently supported."
#elif defined(FORGE_COMPILER_EMSCRIPTEN)
	#define FORGE_CDECL       
	#define FORGE_STDCALL     
	#define FORGE_INLINE      
	#define FORGE_FORCE_INLINE
	#define FORGE_DEBUG_BREAK 
	#define FORGE_DLL_EXPORT  
	#define FORGE_DLL_IMPORT  
	#define FORGE_NO_INLINE   
	#define FORGE_NO_RETURN   
	#define FORGE_DEPRECATED  
	#error "Emscripten is not currently supported."
#elif defined(FORGE_COMPILER_GCC)
	#define FORGE_CDECL       
	#define FORGE_STDCALL     
	#define FORGE_INLINE      
	#define FORGE_FORCE_INLINE
	#define FORGE_DEBUG_BREAK 
	#define FORGE_DLL_EXPORT  
	#define FORGE_DLL_IMPORT  
	#define FORGE_NO_INLINE   
	#define FORGE_NO_RETURN   
	#define FORGE_DEPRECATED  
	#error "GCC is not currently supported."
#elif defined(FORGE_COMPILER_MSVC) 
	#define FORGE_CDECL        __cdecl
    #define FORGE_STDCALL      __stdcall
	#define FORGE_INLINE       __inline
	#define FORGE_FORCE_INLINE __forceinline
	#define FORGE_DEBUG_BREAK  __debugbreak();
	#define FORGE_DLL_EXPORT   __declspec(dllexport)
	#define FORGE_DLL_IMPORT   __declspec(dllimport)
	#define FORGE_NO_INLINE    __declspec(noinline)
	#define FORGE_NO_RETURN    __declspec(noreturn)
	#define FORGE_DEPRECATED   __declspec(deprecated)
#endif

#if defined(FORGE_EXPORT)
	#define FORGE_API FORGE_DLL_EXPORT
#else
	#define FORGE_API FORGE_DLL_IMPORT
#endif

#endif // COMPILER_H
