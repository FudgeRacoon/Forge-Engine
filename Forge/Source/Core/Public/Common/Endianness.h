#ifndef ENDIANNESS_H
#define ENDIANNESS_H

#include "TypeTraits.h"
#include "TypeDefinitions.h"

namespace Forge {
	namespace Endian
	{
		template<typename ValueType, SIZE Bytes,
			BOOL IsFloatingPoint = TypeTraits::TIsFloatingPoint<ValueType>::Value,
			BOOL IsDoublePrecision = TypeTraits::TIsDoublePrecision<ValueType>::Value>
		struct Impl_Endian;

		/// Integer Specilization
		template<typename ValueType, SIZE Bytes>
		struct Impl_Endian<ValueType, Bytes, false, false>
		{
			static VOID Swap(ValueType& value, PBYTE buffer)
			{
				Impl_Endian<ValueType, Bytes - 1>::Swap(value, buffer + 1);

				value = value << 8;
				*buffer = (value & 0xFF000000) >> 24;
			}

			static VOID Register(ValueType& value, PBYTE buffer)
			{
				value |= (ValueType)(*buffer);
				value = value << 8;

				Impl_Endian<ValueType, Bytes - 1>::Register(value, buffer + 1);
			}
		};

		/// Float Specilization
		template<typename ValueType, SIZE Bytes>
		struct Impl_Endian<ValueType, Bytes, true, false>
		{
			static VOID Swap(ValueType& value, PBYTE buffer)
			{
				union
				{
					U32 i;
					F32 f;
				} &int_float = { value };

				Impl_Endian<ValueType, Bytes - 1>::Swap(value, buffer + 1);

				int_float.i = int_float.i << 8;
				*buffer = (int_float.i & 0xFF000000) >> 24;
			}

			static VOID Register(ValueType& value, PBYTE buffer)
			{
				union
				{
					U32 i;
					F32 f;
				} &int_float = { value };

				int_float.i |= (U32)(*buffer);
				int_float.i = int_float.i << 8;

				Impl_Endian<ValueType, Bytes - 1>::Register(value, buffer + 1);
			}
		};

		/// Double Specilization
		template<typename ValueType, SIZE Bytes>
		struct Impl_Endian<ValueType, Bytes, true, true>
		{
			static VOID Swap(ValueType& value, PBYTE buffer)
			{
				union
				{
					U64 i;
					F64 d;
				} int_double = { value };

				Impl_Endian<ValueType, Bytes - 1>::Swap(value, buffer + 1);

				int_double.i = int_double.i << 8;
				*buffer = (int_double.i & 0xFF000000) >> 24;
			}

			static VOID Register(ValueType& value, PBYTE buffer)
			{
				union
				{
					U64 i;
					F64 f;
				} int_double = { value };

				int_double.i |= (U64)(*buffer);
				int_double.i = int_double.i << 8;

				Impl_Endian<ValueType, Bytes - 1>::Register(value, buffer + 1);
			}
		};

		/// Integer Specilization
		template<typename ValueType>
		struct Impl_Endian<ValueType, 1, false, false>
		{
			static VOID Swap(ValueType& value, PBYTE buffer)
			{
				*buffer = (value & 0xFF000000) >> 24;
			}

			static VOID Register(ValueType& value, PBYTE buffer)
			{
				value |= (ValueType)(*buffer);
			}
		};

		/// Float Specilization
		template<typename ValueType>
		struct Impl_Endian<ValueType, 1, true, false>
		{
			static VOID Swap(ValueType& value, PBYTE buffer)
			{
				union
				{
					U32 i;
					F32 f;
				} int_float = { value };

				*buffer = (int_float.i & 0xFF000000) >> 24;
			}

			static VOID Register(ValueType& value, PBYTE buffer)
			{
				union
				{
					U32 i;
					F32 f;
				} int_float = { value };

				int_float.i |= (U32)(*buffer);
			}
		};

		/// Double Specilization
		template<typename ValueType>
		struct Impl_Endian<ValueType, 1, true, true>
		{
			static VOID Swap(ValueType& value, PBYTE buffer)
			{
				union
				{
					U64 i;
					F64 d;
				} int_double = { value };

				*buffer = (int_double.i & 0xFF000000) >> 24;
			}

			static VOID Register(ValueType& value, PBYTE buffer)
			{
				union
				{
					U64 i;
					F64 d;
				} int_double = { value };

				int_double.i |= (U64)(*buffer);
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

		template<typename ValueType, SIZE Bytes>
		struct Utility
		{
			/// @brief Swaps between little-endian and big-endian and
			/// stores the conversion result in a buffer.
			/// 
			/// @param[in] value The value to convert.
			/// @param[out] buffer The buffer which will store conversion result.
			static VOID Swap(ValueType value, PBYTE buffer)
			{
				Impl_Endian<ValueType, Bytes>::Swap(value, buffer);
			}

			/// @brief Registers the conversion result to an arithmetic type.
			/// 
			/// @param[out] value The value which will store the conversion result.
			/// @param[in] buffer The buffer which already has a conversion result.
			static VOID Register(ValueType& value, PBYTE buffer)
			{
				Impl_Endian<ValueType, Bytes>::Register(value, buffer);
			}
		};
	}
}

#endif // ENDIANNESS_H
