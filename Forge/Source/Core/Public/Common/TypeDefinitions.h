#ifndef TYPE_DEFINITIONS_H
#define TYPE_DEFINITIONS_H

namespace Forge
{
	/// Byte types
	using BYTE = unsigned __int8;
	using CBYTE = const unsigned __int8;

	/// Char types
	using CHAR = char;
	using CCHAR = const char;

	/// Unsigned integer types
	using U8   = unsigned __int8;
	using U16  = unsigned __int16;
	using U32  = unsigned __int32;
	using U64  = unsigned __int64;
	using CU8  = const unsigned __int8;
	using CU16 = const unsigned __int16;
	using CU32 = const unsigned __int32;
	using CU64 = const unsigned __int64;
	
	/// Signed integer types
	using I8   = signed __int8;
	using I16  = signed __int16;
	using I32  = signed __int32;
	using I64  = signed __int64;
	using CI8  = signed __int8;
	using CI16 = const signed __int16;
	using CI32 = const signed __int32;
	using CI64 = const signed __int64;
	
	/// Floating-point types
	using F32 = float;
	using F64 = double;
	using CF32 = const float;
	using CF64 = const double;

	/// Void pointer types
	using PVOID = void*;
	using PCVOID = const void*;

	/// Byte pointer types
	using PBYTE  = unsigned __int8*;
	using PCBYTE = const unsigned __int8*;

	/// Char pointer types
	using PSTR = char*;
	using PCSTR = const char*;

	/// Unsinged integer pointer types
	using PU8   = unsigned __int8*;
	using PU16  = unsigned __int16*;
	using PU32  = unsigned __int32*;
	using PU64  = unsigned __int64*;
	using PCU8  = const unsigned __int8*;
	using PCU16 = const unsigned __int16*;
	using PCU32 = const unsigned __int32*;
	using PCU64 = const unsigned __int64*;

	/// Singed integer pointer types
	using PI8   = signed __int8*;
	using PI16  = signed __int16*;
	using PI32  = signed __int32*;
	using PI64  = signed __int64*;
	using PCI8  = const signed __int8*;
	using PCI16 = const signed __int16*;
	using PCI32 = const signed __int32*;
	using PCI64 = const signed __int64*;
	
	/// Floating-point pointer types
	using PF32 = float*;
	using PF64 = double*;
	using PCF32 = const float*;
	using PCF64 = const double*;
}

#endif
