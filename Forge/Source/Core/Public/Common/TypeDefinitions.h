#ifndef TYPE_DEFINITIONS_H
#define TYPE_DEFINITIONS_H

#include "Compiler.h"
#include "PreprocessorUtilities.h"

namespace Forge
{
	typedef void		 VOID, *PVOID;
	typedef const void         *PCVOID;

	typedef bool         BOOL,  *PBOOL;
	typedef const bool   CBOOL, *PCBOOL;

	typedef char         CHAR,  *PCHAR;
	typedef const char   CCHAR, *PCCHAR;

	typedef float        F32,  *PF32;
	typedef double       F64,  *PF64;
	typedef const float  CF32, *PCF32;
	typedef const double CF64, *PCF64;

#if defined(FORGE_COMPILER_MSVC)
	typedef unsigned __int64	   SIZE;
	
	typedef signed __int8	       I8,   *PI8;
	typedef signed __int16	       I16,  *PI16;
	typedef signed __int32	       I32,  *PI32;
	typedef signed __int64	       I64,  *PI64;
	typedef const signed __int8	   CI8,  *PCI8;
	typedef const signed __int16   CI16, *PCI16;
	typedef const signed __int32   CI32, *PCI32;
	typedef const signed __int64   CI64, *PCI64;

	typedef unsigned __int8	       U8,   *PU8;
	typedef unsigned __int16       U16,  *PU16;
	typedef unsigned __int32       U32,  *PU32;
	typedef unsigned __int64       U64,  *PU64;
	typedef const unsigned __int8  CU8,  *PCU8;
	typedef const unsigned __int16 CU16, *PCU16;
	typedef const unsigned __int32 CU32, *PCU32;
	typedef const unsigned __int64 CU64, *PCU64;

	typedef unsigned __int8        BYTE,  *PBYTE;
	typedef const unsigned __int8  CBYTE, *PCBYTE;

	typedef unsigned __int64       INTPTR,  *PINTPTR;
	typedef const unsigned __int64 CINTPTR, *PCINTPTR;
#elif
	#include<stdint.h>

	typedef uint64_t SIZE;

	typedef int8_t	       I8,   *PI8;
	typedef int16_t	       I16,  *PI16;
	typedef int32_t	       I32,  *PI32;
	typedef int64_t	       I64,  *PI64;
	typedef const int8_t   CI8,  *PCI8;
	typedef const int16_t  CI16, *PCI16;
	typedef const int32_t  CI32, *PCI32;
	typedef const int64_t  CI64, *PCI64;

	typedef uint8_t	       U8,   *PU8;
	typedef uint16_t       U16,  *PU16;
	typedef uint32_t       U32,  *PU32;
	typedef uint64_t       U64,  *PU64;
	typedef const uint8_t  CU8,  *PCU8;
	typedef const uint16_t CU16, *PCU16;
	typedef const uint32_t CU32, *PCU32;
	typedef const uint64_t CU64, *PCU64;

	typedef uint8_t        BYTE,  *PBYTE;
	typedef const uint8_t  CBYTE, *PCBYTE;

	typedef uint64_t       INTPTR,  *PINTPTR;
	typedef const uint64_t CINTPTR, *PCINTPTR;
#endif

	FORGE_STATIC_ASSERT(sizeof(BOOL) == 1)

	FORGE_STATIC_ASSERT(sizeof(CHAR) == 1)

	FORGE_STATIC_ASSERT(sizeof(INTPTR) == 8)

	FORGE_STATIC_ASSERT(sizeof(U8)  == 1)
	FORGE_STATIC_ASSERT(sizeof(U16) == 2)
	FORGE_STATIC_ASSERT(sizeof(U32) == 4)
	FORGE_STATIC_ASSERT(sizeof(U64) == 8)

	FORGE_STATIC_ASSERT(sizeof(I8)  == 1)
	FORGE_STATIC_ASSERT(sizeof(I16) == 2)
	FORGE_STATIC_ASSERT(sizeof(I32) == 4)
	FORGE_STATIC_ASSERT(sizeof(I64) == 8)

	FORGE_STATIC_ASSERT(sizeof(F32) == 4)
	FORGE_STATIC_ASSERT(sizeof(F64) == 8)
}

#endif // TYPE_DEFINITIONS_H
