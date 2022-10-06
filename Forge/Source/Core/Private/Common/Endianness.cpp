#include "Core/Public/Common/Endianness.h"

namespace Forge {
	namespace Common
	{
		Bool IsBigEndian()
		{
			union
			{
				U32 i;
				Byte b[4];
			} int_byte = { 0x01020304 };

			return *(int_byte.b) == 0x01;
		}
		Bool IsLittleEndian()
		{
			union
			{
				U32 i;
				Byte b[4];
			} int_Byte = { 0x01020304 };

			return *(int_Byte.b) == 0x04;
		}
	}
}
