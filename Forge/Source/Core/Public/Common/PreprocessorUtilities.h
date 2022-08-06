#ifndef PREPROCESSOR_UTILITIES_H
#define PREPROCESSOR_UTILITIES_H

#define FORGE_INVALID_INDEX (-1)

#define FORGE_BIT(x) (1 << x)

#define FORGE_SAFE_DELETE_UNIT(mem) if(mem != nullptr) {delete mem; mem = nullptr;}
#define FORGE_SAFE_DELETE_BLOCK(mem) if(mem != nullptr) {delete[] mem; mem = nullptr;}

#define FORGE_STRINGIZE(s) #s
#define FORGE_CONCATENATE(s1, s2) s1##s2
#define FORGE_CONCATENATE_VARIADIC(s, ...) s##__VA_ARGS__
#define FORGE_CONCATENATE_COMMA_VARIADIC(s, ...) s, ##__VA_ARGS__

#define FORGE_BYTESWAP_16_UNSIGNED(x) ((((x) >> 8) & 0x00ff) + (((x) << 8) & 0xff00))
#define FORGE_BYTESWAP_32_UNSIGNED(x) (((x) >> 24) + (((x) >> 8) & 0x00ff00) + (((x) << 8) & 0xff0000) + ((x) << 24))

#define FORGE_CLASS_NONCOPYABLE(TypeName)                \
	public: TypeName(Typename&& rhs) = delete            \
	public: Typename(const Typename& rhs) = delete       \
	public: Typename& operator=(Typename&& rhs) = delete \
	public: Typename& operator=(const Typename& rhs) = delete

#define FORGE_CLASS_ALLOCATOR(TypeName)         \
	public: void* operator new(size_t size);    \
	public: void* operator new[](size_t size);  \
	public: void  operator delete(void* ptr);   \
	public: void  operator delete[](void* ptr)
	
#define FORGE_FILE_LINE_LITERAL "[" __FILE__ "][" __LINE__ "]:"

#endif