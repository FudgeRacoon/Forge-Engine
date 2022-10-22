#ifndef ENDIANNESS_H
#define ENDIANNESS_H

#include "TypeDefinitions.h"
#include "TypeTraits.h"

namespace Forge {
	namespace Common
	{
		namespace Private
		{
			template<typename T,
				Bool IsArithmetic = TIsArithmetic<T>::Value,
				Bool IsFloatingPoint = TIsFloatingPoint<T>::Value,
				Bool IsDoublePrecision = TIsDoublePrecision<T>::Value>
			struct EndiannessImpl {};

			template<typename T>
			struct EndiannessImpl<T, true, false, false>
			{
				using ValueType         = T;
				using ValueTypeRef      = T&;
				using ValueTypePtr      = T*;
				using ConstValueType    = const T;
				using ConstValueTypeRef = const T&;
				using ConstValueTypePtr = const T*;

				static Void SwapEndian(ValueType data, BytePtr buffer, Size size)
				{
					if (size == 1)
					{
						*buffer = (data & (0xFF << (sizeof(data) - 1) * 8)) >> ((sizeof(data) - 1) * 8);
						return;
					}

					EndiannessImpl<ValueType, true, false, false>::SwapEndian(data, buffer + 1, size - 1);

					data = data << 8;
					*buffer = (data & (0xFF << (sizeof(data) - 1) * 8)) >> ((sizeof(data) - 1) * 8);
				}

				static Void RegisterEndian(ValueTypeRef data, BytePtr buffer, Size size)
				{
					if (size == 1)
					{
						data |= (ValueType)(*buffer);
						return;
					}

					data |= (ValueType)(*buffer);
					data = data << 8;

					EndiannessImpl<ValueType, true, false, false>::RegisterEndian(data, buffer + 1, size - 1);
				}
			};

			template<typename T>
			struct EndiannessImpl<T, true, true, false>
			{
				using ValueType = T;
				using ValueTypeRef = T&;
				using ValueTypePtr = T*;
				using ConstValueType = const T;
				using ConstValueTypeRef = const T&;
				using ConstValueTypePtr = const T*;

				union U32F32
				{
					U32 i;
					F32 f;
				} static union_helper;

				static Void SwapEndian(ValueType data, BytePtr buffer, Size size)
				{
					if (size == 1)
					{
						*buffer = (union_helper.i & 0xFF000000) >> 24;
						return;
					}

					EndiannessImpl<ValueType, true, true, false>::SwapEndian(data, buffer + 1, size - 1);

					union_helper.i = union_helper.i << 8;
					*buffer = (union_helper.i & 0xFF000000) >> 24;
				}

				static Void RegisterEndian(ValueTypeRef data, BytePtr buffer, Size size)
				{
					if (size == 1)
					{
						union_helper.i |= (U32)(*buffer);
						data = union_helper.f;
						return;
					}

					union_helper.i |= (U32)(*buffer);
					union_helper.i = union_helper.i << 8;

					EndiannessImpl<ValueType, true, true, false>::RegisterEndian(data, buffer + 1, size - 1);
				}			
			};

			template<typename T>
			struct EndiannessImpl<T, true, true, true>
			{
				using ValueType         = T;
				using ValueTypeRef      = T&;
				using ValueTypePtr      = T*;
				using ConstValueType    = const T;
				using ConstValueTypeRef = const T&;
				using ConstValueTypePtr = const T*;

				union U64F64
				{
					U64 i;
					F64 f;
				} static union_helper;

				static Void SwapEndian(ValueType data, BytePtr buffer, Size size)
				{
					if (size == 1)
					{
						*buffer = (union_helper.i & 0xFF00000000) >> 32;
						return;
					}

					EndiannessImpl<ValueType, true, true, true>::SwapEndian(data, buffer + 1, size - 1);

					union_helper.i = union_helper.i << 8;
					*buffer = (union_helper.i & 0xFF00000000) >> 32;
				}

				static Void RegisterEndian(ValueTypeRef data, BytePtr buffer, Size size)
				{
					if (size == 1)
					{
						union_helper.i |= (U64)(*buffer);
						data = union_helper.f;
						return;
					}

					union_helper.i |= (U64)(*buffer);
					union_helper.i = union_helper.i << 8;

					EndiannessImpl<ValueType, true, true, true>::RegisterEndian(data, buffer + 1, size - 1);
				}
			};
		}

		/**
		 * @brief Checks if the current system is big-endian.
		 * 
		 * @return True if the system is big-endian.
		 */
		Bool IsBigEndian();
		
		/**
		 * @brief Checks if the current system is little-endian.
		 *
		 * @return True if the system is little-endian.
		 */
		Bool IsLittleEndian();
		
		/**
		 * @brief Swaps between little and big endian and stores the conversion 
		 * result in a buffer.
		 * 
		 * @param[in]  data   The data to switch between little and big endian.
		 * @param[out] buffer The buffer which will store the conversion result.
		 * 
		 * @throws InvalidOperationException if the buffer can not fit the data.
		 */
		template<typename T>
		Void SwapEndian(T data, BytePtr buffer)
		{
			if (TIsFloatingPoint<T>::Value)
				Private::EndiannessImpl::union_helper.f = data;

			Private::EndiannessImpl<T>::SwapEndian(data, buffer, sizeof(data));
		}
		
		/**
		 * @brief Registers the endian conversion result to an arithmetic type.
		 * 
		 * @param[out] data   The data which will store the endian conversion result.
		 * @param[in]  buffer The buffer which contains the endian conversion result.
		 * 
		 * @throws InvalidOperationException if the data can not fit the buffer.
		 */
		template<typename T>
		Void RegisterEndian(T& data, BytePtr buffer)
		{
			if (TIsFloatingPoint<T>::Value)
				Private::EndiannessImpl::union_helper.i = 0;

			Private::EndiannessImpl<T>::RegisterEndian(data, buffer, sizeof(data));
		}
	}
}

#endif // ENDIANNESS_H
