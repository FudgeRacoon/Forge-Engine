#ifndef TYPE_DEFINITIONS_H
#define TYPE_DEFINITIONS_H

#include "Compiler.h"
#include "PreprocessorUtilities.h"

namespace Forge
{
	using VOID = void;

	using CHAR = char;
	using CCHAR = const char;

	using F32  = float;
	using F64  = double;
	using CF32 = const float;
	using CF64 = const double;

#if defined(FORGE_COMPILER_MSVC)
	using SIZE  = unsigned __int64;

	using BYTE  = unsigned __int8;
	using CBYTE = const unsigned __int8;

	using U8   = unsigned __int8;
	using U16  = unsigned __int16;
	using U32  = unsigned __int32;
	using U64  = unsigned __int64;
	using CU8  = const unsigned __int8;
	using CU16 = const unsigned __int16;
	using CU32 = const unsigned __int32;
	using CU64 = const unsigned __int64;

	using I8   = signed __int8;
	using I16  = signed __int16;
	using I32  = signed __int32;
	using I64  = signed __int64;
	using CI8  = signed __int8;
	using CI16 = const signed __int16;
	using CI32 = const signed __int32;
	using CI64 = const signed __int64;
#elif
	#include<stdint>

	using SIZE  = std::uint64_t;

	using BYTE  = std::uint8_t;
	using CBYTE = const std::uint8_t;

	using U8   = std::uint8_t;
	using U16  = std::uint16_t;
	using U32  = std::uint32_t;
	using U64  = std::uint64_t;
	using CU8  = const std::uint8_t;
	using CU16 = const std::uint16_t;
	using CU32 = const std::uint32_t;
	using CU64 = const std::uint64_t;

	using I8   = std::int8_t;
	using I16  = std::int16_t;
	using I32  = std::int32_t;
	using I64  = std::int64_t;
	using CI8  = const std::int8_t;
	using CI16 = const std::int16_t;
	using CI32 = const std::int32_t;
	using CI64 = const std::int64_t;
#endif

	using PVOID  = VOID*;
	using PCVOID = const VOID*;

	using PBYTE  = BYTE*;
	using PCBYTE = CBYTE*;

	using PSTR  = CHAR*;
	using PCSTR = CCHAR*;

	using PU8   = U8*;
	using PU16  = U16*;
	using PU32  = U32*;
	using PU64  = U64*;
	using PCU8  = CU8*;
	using PCU16 = CU16*;
	using PCU32 = CU32*;
	using PCU64 = CU64*;

	using PI8   = I8*;
	using PI16  = I16*;
	using PI32  = I32*;
	using PI64  = I64*;
	using PCI8  = CI8*;
	using PCI16 = CI16*;
	using PCI32 = CI32*;
	using PCI64 = CI64*;
	
	using PF32  = F32*;
	using PF64  = F64*;
	using PCF32 = CF32*;
	using PCF64 = CF64*;

	FORGE_STATIC_ASSERT(sizeof(CHAR) == 1)

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

#endif
