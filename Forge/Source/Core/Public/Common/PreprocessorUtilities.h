#ifndef PREPROCESSOR_UTILITIES_H
#define PREPROCESSOR_UTILITIES_H

#include <cstdio>

#include "Compiler.h"

#define FORGE_INVALID_INDEX (-1)

#define FORGE_BIT(x) (1 << x)

#define FORGE_SAFE_DELETE_UNIT(mem) if(mem != nullptr) {delete mem; mem = nullptr;}
#define FORGE_SAFE_DELETE_BLOCK(mem) if(mem != nullptr) {delete[] mem; mem = nullptr;}

#define IMPL_FORGE_STRINGIZE(s) #s
#define FORGE_STRINGIZE(s) IMPL_FORGE_STRINGIZE(s)

#define IMPL_FORGE_CONCATENATE(s1, s2) s1 ## s2
#define FORGE_CONCATENATE(s1, s2) IMPL_FORGE_CONCATENATE(s1, s2)

#define IMPL_FORGE_CONCATENATE_VARIADIC(s, ...) s ## __VA_ARGS__
#define FORGE_CONCATENATE_VARIADIC(s, ...) IMPL_FORGE_CONCATENATE_VARIADIC(s, ...)

#define IMPL_FORGE_CONCATENATE_COMMA_VARIADIC(s, ...) s, ## __VA_ARGS__
#define FORGE_CONCATENATE_COMMA_VARIADIC(s, ...) IMPL_FORGE_CONCATENATE_COMMA_VARIADIC(s, ...)

#if defined(FORGE_DEBUG)
	#define FORGE_ASSERT(__EXPR__, __MSG__)           \
		if(__EXPR__) {}                               \
		else                                          \
		{                                             \
			fprintf(stderr, "Assertion failed: ");    \
			fprintf(stderr, "File [%s] ", __FILE__);  \
			fprintf(stderr, "Line [%d] ", __LINE__);  \
			fprintf(stderr, "Expr [%s] ", #__EXPR__); \
			fprintf(stderr, "Msg [%s]\n", #__MSG__);  \
			FORGE_DEBUG_BREAK                         \
		}                                             \

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

#define FORGE_CLASS_NONCOPYABLE(Typename)                  \
	public:                                                \
		Typename(Typename&& rhs) = delete;                 \
		Typename(const Typename& rhs) = delete;            \
		Typename& operator=(Typename&& rhs) = delete;      \
		Typename& operator=(const Typename& rhs) = delete; \


#define FORGE_FILE_LINE_LITERAL "[" __FILE__ "][" __LINE__ "]: "

#endif // PREPROCESSOR_UTILITIES_H