#ifndef ENDIANNESS_H
#define ENDIANNESS_H

#include "TypeTraits.h"
#include "TypeDefinitions.h"

namespace Forge {
	namespace Endianness
	{
		/// TODO: Fix float and double swap
		/// TODO: Check whether value type is arithmatic

		template<typename ValueType,
			BOOL IsFloatingPoint = TypeTraits::TIsFloatingPoint<ValueType>::Value,
			BOOL IsDoublePrecision = TypeTraits::TIsDoublePrecision<ValueType>::Value>
		struct Impl_Endian;

		/// Integer Specilization
		template<typename ValueType>
		struct Impl_Endian<ValueType, false, false>
		{
			static VOID Swap(ValueType& value, PBYTE buffer, SIZE bytes)
			{
				if (bytes == 1)
				{
					*buffer = (value & 0xFF000000) >> 24;
					return;
				}

				Impl_Endian<ValueType>::Swap(value, buffer + 1, bytes - 1);

				value = value << 8;
				*buffer = (value & 0xFF000000) >> 24;
			}

			static VOID Register(ValueType& value, PBYTE buffer, SIZE bytes)
			{
				if (bytes == 1)
				{
					value |= (ValueType)(*buffer);
					return;
				}

				value |= (ValueType)(*buffer);
				value = value << 8;

				Impl_Endian<ValueType>::Register(value, buffer + 1, bytes - 1);
			}
		};

		/// Float Specilization
		template<typename ValueType>
		struct Impl_Endian<ValueType, true, false>
		{
			static VOID Swap(ValueType& value, PBYTE buffer, SIZE bytes)
			{
				union
				{
					U32 i;
					F32 f;
				} int_float = { value };

				if (bytes == 1)
				{
					*buffer = (int_float.i & 0xFF000000) >> 24;
					return;
				}

				Impl_Endian<ValueType>::Swap(value, buffer + 1, bytes - 1);

				int_float.i = int_float.i << 8;
				*buffer = (int_float.i & 0xFF000000) >> 24;
			}

			static VOID Register(ValueType& value, PBYTE buffer, SIZE bytes)
			{
				union
				{
					U32 i;
					F32 f;
				} int_float = { value };

				if (bytes == 1)
				{
					int_float.i |= (U32)(*buffer);
					return;
				}

				int_float.i |= (U32)(*buffer);
				int_float.i = int_float.i << 8;

				Impl_Endian<ValueType>::Register(value, buffer + 1, bytes - 1);
			}
		};

		/// Double Specilization
		template<typename ValueType>
		struct Impl_Endian<ValueType, true, true>
		{
			static VOID Swap(ValueType& value, PBYTE buffer, SIZE bytes)
			{
				union
				{
					U64 i;
					F64 d;
				} int_double = { value };

				if (bytes == 1)
				{
					*buffer = (int_double.i & 0xFF000000) >> 24;
					return;
				}

				Impl_Endian<ValueType>::Swap(value, buffer + 1, bytes - 1);

				int_double.i = int_double.i << 8;
				*buffer = (int_double.i & 0xFF000000) >> 24;
			}

			static VOID Register(ValueType& value, PBYTE buffer, SIZE bytes)
			{
				union
				{
					U64 i;
					F64 d;
				} int_double = { value };

				if (bytes == 1)
				{
					int_double.i |= (U32)(*buffer);
					return;
				}

				int_double.i |= (U32)(*buffer);
				int_double.i = int_double.i << 8;

				Impl_Endian<ValueType>::Register(value, buffer + 1, bytes - 1);
			}
		};

		/// @brief Checks if the current system is big-endian.
		BOOL IsBigEndian()
		{
			union
			{
				U32 i;
				BYTE b[4];
			} int_byte = { 0x01020304 };

			return *(int_byte.b) == 0x01;
		}
		/// @brief Checks if the current system is little-endian.
		BOOL IsLittleEndian()
		{
			union
			{
				U32 i;
				BYTE b[4];
			} int_byte = { 0x01020304 };

			return *(int_byte.b) == 0x04;
		}

		/// @brief Swaps between little-endian and big-endian and
		/// stores the conversion result in a buffer.
		/// 
		/// @param[in] value The value to convert.
		/// @param[out] buffer The buffer which will store conversion result.
		template<typename ValueType>
		VOID SwapEndian(ValueType value, PBYTE buffer, SIZE bytes)
			{
				Impl_Endian<ValueType>::Swap(value, buffer, bytes);
			}

		/// @brief Registers the conversion result to an arithmetic type.
		/// 
		/// @param[out] value The value which will store the conversion result.
		/// @param[in] buffer The buffer which already has a conversion result.
		template<typename ValueType>
		VOID RegisterEndian(ValueType& value, PBYTE buffer, SIZE bytes)
			{
				Impl_Endian<ValueType>::Register(value, buffer, bytes);
			}
	}
}

#endif // ENDIANNESS_H
