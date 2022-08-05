#ifndef COMPILER_H
#define COMPILER_H

/// Detect compilers and CPU architectures
#if defined(__clang__) || defined(__llvm__)
	#define FORGE_COMPILER_CLANG
	#if defined(__i386__)
		#define FORGE_ARCH_X86
	#elif defined(__x86_64__)
		#define FORGE_ARCH_X64
	#endif
#elif defined (__GNUC__)
	#define FORGE_COMPILER_GCC
	#if defined(__i386__)
		#define FORGE_ARCH_X86
	#elif defined(__x86_64__)
		#define FORGE_ARCH_X64
	#endif
#elif defined(_MSC_VER)
	#define FORGE_COMPILER_MSVC
	#if defined(_M_IX86)
		#define FORGE_ARCH_X86
	#elif defined(_M_X64)
		#define FORGE_ARCH_X64
	#endif
#else
	#error "Unable to detect compiler."
#endif

/// Compiler specific modifiers
#if defined(FORGE_COMPILER_CLANG)
	#error "Clang is not currently supported."
#elif defined(FORGE_COMPILER_GCC)
	#error "GCC is not currently supported."
#elif defined(FORGE_COMPILER_MSVC) 
    #define FORGE_STDCALL __stdcall
	#define FORGE_CDECL __cdecl
	#define FORGE_DLL_EXPORT __declspec(dllexport)
	#define FORGE_DLL_IMPORT __declspec(dllimport)
	#define FORGE_INLINE __inline
	#define FORGE_FORCE_INLINE __forceinline
	#define FORGE_NO_INLINE __declspec(noinline)
	#define FORGE_NO_RETURN __declspec(noreturn)
	#define FORGE_DEPRECATED __declspec(deprecated)
	#define FORGE_DEBUG_BREAK __debugbreak()
#endif

/// Utility macros
#define FORGE_SAFE_DELETE(mem) \
	if(mem != nullptr) {delete mem; mem = nullptr;}

#define BIT(x) (1 << x)

#define FORGE_STRINGIZE(s) #s
#define FORGE_CONCATENATE(s1, s2) s1 ## s2

#endif
