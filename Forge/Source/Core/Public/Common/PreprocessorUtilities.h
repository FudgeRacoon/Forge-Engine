#ifndef PREPROCESSOR_UTILITIES_H
#define PREPROCESSOR_UTILITIES_H

#include <cstdio>

#include "Compiler.h"

#define FORGE_BIT(x) (1 << x)

#define FORGE_SAFE_DELETE_UNIT(mem) if( mem != nullptr ) { delete mem; mem = nullptr; }
#define FORGE_SAFE_DELETE_BLOCK(mem) if( mem != nullptr ) { delete[] mem; mem = nullptr; }

#define IMPL_FORGE_STRINGIZE(s) #s
#define FORGE_STRINGIZE(s) IMPL_FORGE_STRINGIZE(s)

#define IMPL_FORGE_CONCATENATE(s1, s2) s1 ## s2
#define FORGE_CONCATENATE(s1, s2) IMPL_FORGE_CONCATENATE(s1, s2)

#define IMPL_FORGE_CONCATENATE_VARIADIC(s, ...) s ## __VA_ARGS__
#define FORGE_CONCATENATE_VARIADIC(s, ...) IMPL_FORGE_CONCATENATE_VARIADIC(s, ...)

#define IMPL_FORGE_CONCATENATE_COMMA_VARIADIC(s, ...) s, ## __VA_ARGS__
#define FORGE_CONCATENATE_COMMA_VARIADIC(s, ...) IMPL_FORGE_CONCATENATE_COMMA_VARIADIC(s, ...)

#define FORGE_FUNC_LITERAL __FUNCTION__
#define FORGE_LINE_LITERAL FORGE_STRINGIZE(__LINE__)
#define FORGE_FILE_LITERAL FORGE_STRINGIZE(__FILE__)

#define FORGE_CLASS_NONCOPYABLE(Typename)                  \
	public:                                                \
		Typename(Typename&& rhs) = delete;                 \
		Typename(const Typename& rhs) = delete;            \
		Typename& operator=(Typename&& rhs) = delete;      \
		Typename& operator=(const Typename& rhs) = delete; \

#if defined(FORGE_DEBUG)
	#define FORGE_ASSERT(__EXPR__, __MSG__)                                                                      \
		if(__EXPR__) {}                                                                                          \
		else                                                                                                     \
		{                                                                                                        \
			fprintf(stderr, "%s:%s: assertion failed: %s\n", FORGE_FILE_LITERAL, FORGE_LINE_LITERAL, #__EXPR__); \
			fprintf(stderr, "assertion message: %s", #__MSG__);                                                  \
		}											                                                             \

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

#endif // PREPROCESSOR_UTILITIES_H