#ifndef ENDIANNESS_H
#define ENDIANNESS_H

#include "TypeDefinitions.h"
#include "TypeTraits/TypeTraits.h"

namespace Forge {
	namespace Common
	{
		/// @brief Checks if the current system is big-endian.
		Bool IsBigEndian()
		{
			union
			{
				U32 i;
				Byte b[4];
			} int_byte = { 0x01020304 };

			return *(int_byte.b) == 0x01;
		}
		/// @brief Checks if the current system is little-endian.
		Bool IsLittleEndian()
		{
			union
			{
				U32 i;
				Byte b[4];
			} int_Byte = { 0x01020304 };

			return *(int_Byte.b) == 0x04;
		}

		/// @brief Swaps between little-endian and big-endian and
		/// stores the conversion result in a buffer.
		/// @param[in]  value  The value to convert.
		/// @param[out] buffer The buffer which will store conversion result.
		/// @param[in]  Size   The Size of the the value in Bytes.
		template<typename ValueType,
			Bool IsArithmetic = TIsArithmetic<ValueType>::Value,
			Bool IsFloatingPoint = TIsFloatingPoint<ValueType>::Value,
			Bool IsDoublePrecision = TIsDoublePrecision<ValueType>::Value>
		Void SwapEndian(ValueType value, BytePtr buffer, Size size) {}

		/// @brief Registers the conversion result to an arithmetic type.
		/// @param[out] value  The value which will store the conversion result.
		/// @param[in]  buffer The buffer which already has a conversion result.
		/// @param[in]  Size   The Size of the the buffer in Bytes.
		template<typename ValueType,
			Bool IsArithmetic = TIsArithmetic<ValueType>::Value,
			Bool IsFloatingPoint = TIsFloatingPoint<ValueType>::Value,
			Bool IsDoublePrecision = TIsDoublePrecision<ValueType>::Value>
		Void RegisterEndian(ValueType value, BytePtr buffer, Size size) {}

		template<typename ValueType>
		Void SwapEndian<true, false, false>(ValueType value, BytePtr buffer, Size size)
		{
			if (size == 1)
			{
				*buffer = (value & 0xFF000000) >> 24;
				return;
			}

			SwapEndian(value, buffer + 1, size - 1);

			value = value << 8;
			*buffer = (value & 0xFF000000) >> 24;
		}
		template<typename ValueType>
		Void SwapEndian<true, true, false>(ValueType value, BytePtr buffer, Size size)
		{
			union
			{
				U32 i;
				F32 f;
			} static int_float = { value };

			if (size == 1)
			{
				*buffer = (int_float.i & 0xFF000000) >> 24;
				return;
			}

			SwapEndian(value, buffer + 1, size - 1);

			int_float.i = int_float.i << 8;
			*buffer = (int_float.i & 0xFF000000) >> 24;
		}
		template<typename ValueType>
		Void SwapEndian<true, false, true>(ValueType value, BytePtr buffer, Size size)
		{
			union
			{
				U64 i;
				F64 d;
			} static int_double = { value };

			if (size == 1)
			{
				*buffer = (int_double.i & 0xFF000000) >> 24;
				return;
			}

			SwapEndian(value, buffer + 1, size - 1);

			int_double.i = int_double.i << 8;
			*buffer = (int_double.i & 0xFF000000) >> 24;
		}

		template<typename ValueType>
		Void RegisterEndian<true, false, false>(ValueType value, BytePtr buffer, Size size)
		{
			if (size == 1)
			{
				value |= (ValueType)(*buffer);
				return;
			}

			value |= (ValueType)(*buffer);
			value = value << 8;

			RegisterEndian(value, buffer + 1, size - 1);
		}
		template<typename ValueType>
		Void RegisterEndian<true, true, false>(ValueType value, BytePtr buffer, Size size)
		{
			union
			{
				U32 i;
				F32 f;
			} static& int_float = { value };

			if (size == 1)
			{
				int_float.i |= (U32)(*buffer);
				return;
			}

			int_float.i |= (U32)(*buffer);
			int_float.i = int_float.i << 8;

			RegisterEndian(value, buffer + 1, size - 1);
		}
		template<typename ValueType>
		Void RegisterEndian<true, false, false>(ValueType value, BytePtr buffer, Size size)
		{
			union
			{
				U64 i;
				F64 f;
			} static& int_double = { value };

			if (size == 1)
			{
				int_double.i |= (U32)(*buffer);
				return;
			}

			int_double.i |= (U32)(*buffer);
			int_double.i = int_double.i << 8;

			RegisterEndian(value, buffer + 1, size - 1);
		}
	}
}

#endif // ENDIANNESS_H
