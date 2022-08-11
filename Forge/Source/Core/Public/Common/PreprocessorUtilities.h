#ifndef PREPROCESSOR_UTILITIES_H
#define PREPROCESSOR_UTILITIES_H

#include <cstdio>

#include "Compiler.h"

#define FORGE_INVALID_INDEX (-1)

#define FORGE_BIT(x) (1 << x)

#define FORGE_SAFE_DELETE_UNIT(mem) if(mem != nullptr) {delete mem; mem = nullptr;}
#define FORGE_SAFE_DELETE_BLOCK(mem) if(mem != nullptr) {delete[] mem; mem = nullptr;}

#define _FORGE_STRINGIZE(s) #s
#define  FORGE_STRINGIZE(s) _FORGE_STRINGIZE(s)

#define _FORGE_CONCATENATE(s1, s2) s1 ## s2
#define  FORGE_CONCATENATE(s1, s2) _FORGE_CONCATENATE(s1, s2)

#define _FORGE_CONCATENATE_VARIADIC(s, ...) s ## __VA_ARGS__
#define  FORGE_CONCATENATE_VARIADIC(s, ...) _FORGE_CONCATENATE_VARIADIC(s, ...)

#define _FORGE_CONCATENATE_COMMA_VARIADIC(s, ...) s, ## __VA_ARGS__
#define  FORGE_CONCATENATE_COMMA_VARIADIC(s, ...) _FORGE_CONCATENATE_COMMA_VARIADIC(s, ...)

#if defined(FORGE_DEBUG)
	#define FORGE_ASSERT(__EXPR__)                   \
		if(__EXPR__) {}                              \
		else                                         \
		{                                            \
			fprintf(stderr, "File: %s ", __FILE__);  \
			fprintf(stderr, "Line: %d ", __LINE__);  \
			fprintf(stderr, "Expr: %s ", #__EXPR__); \
			FORGE_DEBUG_BREAK                        \
		}                                            \

	#define FORGE_STATIC_ASSERT(__EXPR__)            \
		enum                                         \
		{                                            \
			FORGE_CONCATENATE(assert_fail, __LINE__) \
				= 1 / (int) (!!(__EXPR__))           \
		};
#elif defined(FORGE_NDEBUG)
	#define FORGE_ASSERT(__EXPR__)
	#define FORGE_STATIC_ASSERT(__EXPR__)
#endif

#define FORGE_CLASS_NONCOPYABLE(TypeName)                \
	public: TypeName(Typename&& rhs) = delete            \
	public: Typename(const Typename& rhs) = delete       \
	public: Typename& operator=(Typename&& rhs) = delete \
	public: Typename& operator=(const Typename& rhs) = delete

#define FORGE_CLASS_ALLOCATOR(TypeName)        \
	public: void* operator new(size_t size);   \
	public: void* operator new[](size_t size); \
	public: void  operator delete(void* ptr);  \
	public: void  operator delete[](void* ptr)
	
#define FORGE_FILE_LINE_LITERAL "[" __FILE__ "][" __LINE__ "]: "

#endif // PREPROCESSOR_UTILITIES_H