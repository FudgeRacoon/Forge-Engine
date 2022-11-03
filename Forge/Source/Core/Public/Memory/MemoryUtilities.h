#ifndef MEMORY_UTILITIES_H
#define MEMORY_UTILITIES_H

#include <iostream>

#include "Core/Public/Common/Compiler.h"
#include "Core/Public/Common/TypeTraits.h"
#include "Core/Public/Common/TypeDefinitions.h"

namespace Forge {
	namespace Memory
	{
		/**
		 * @brief Copies data from source memory buffer to destination memory buffer.
		 *
		 * @param[out] dst   The destination memory buffer where data will be copied to.
		 * @param[in]  src   The source memory buffer where data is stored.
		 * @param[in]  bytes The number of bytes to copy to the destination memory buffer.
		 */
		FORGE_FORCE_INLINE Void MemoryCopy(VoidPtr dst, VoidPtr src, Size bytes)
		{
			BytePtr temp_dst = reinterpret_cast<BytePtr>(dst);
			BytePtr temp_src = reinterpret_cast<BytePtr>(src);

			for (int i = 0; i < bytes; i++)
				*(temp_dst + i) = *(temp_src + i);
		}

		/**
		 * @brief Sets the destination memory buffer to the value specified.
		 *
		 * @param[out] dst   The destination memory buffer where data will be set.
		 * @param[in]  value The value the memory buffer will be set to.
		 * @param[in]  bytes The number of bytes to copy to the destination memory buffer.
		 */
		FORGE_FORCE_INLINE Void MemorySet(VoidPtr dst, Byte value, Size bytes)
		{
			BytePtr temp_dst = reinterpret_cast<BytePtr>(dst);

			for (int i = 0; i < bytes; i++)
				*(temp_dst + i) = value;
		}

		/**
		 * @brief Compares the data stored in two memory buffers.
		 *
		 * @param[in] lh_address The left-hand side memory buffer to compare.
		 * @param[in] rh_address The right-hand side memory buffer to comapre.
		 * @param[in] bytes      The number of bytes in the memory buffers.
		 *
		 * @returns True if the data stored in the memory buffers are equal.
		 */
		FORGE_FORCE_INLINE Bool MemoryCompare(VoidPtr lh_address, VoidPtr rh_address, Size bytes)
		{
			if (lh_address == rh_address)
				return true;

			BytePtr temp_lh = reinterpret_cast<BytePtr>(lh_address);
			BytePtr temp_rh = reinterpret_cast<BytePtr>(rh_address);

			for (I32 i = 0; i < bytes; i++)
				if (*(temp_lh + i) != *(temp_rh + i))
					return false;

			return true;
		}

		/**
		 * @brief Compares the data stored in two memory buffers.
		 *
		 * @param[in] lh_address The left-hand side memory buffer to compare.
		 * @param[in] rh_address The right-hand side memory buffer to comapre.
		 * @param[in] bytes      The number of bytes in the memory buffers.
		 *
		 * @returns True if the data stored in the memory buffers are equal.
		 */
		FORGE_FORCE_INLINE Bool MemoryCompare(ConstVoidPtr lh_address, ConstVoidPtr rh_address, Size bytes)
		{
			if (lh_address == rh_address)
				return true;

			ConstBytePtr temp_lh = reinterpret_cast<ConstBytePtr>(lh_address);
			ConstBytePtr temp_rh = reinterpret_cast<ConstBytePtr>(rh_address);

			for (I32 i = 0; i < bytes; i++)
				if (*(temp_lh + i) != *(temp_rh + i))
					return false;

			return true;
		}

		namespace Internal
		{
			template<typename _Type>
			FORGE_FORCE_INLINE Void ConstructImpl(_Type* dst, Size count, Common::TypeIsPod)
			{
				
			}
			template<typename _Type>
			FORGE_FORCE_INLINE Void ConstructImpl(_Type* dst, Size count, Common::TypeIsClass)
			{
				for (I32 i = 0; i < count; i++)
					new (dst + i) _Type();
			}

			template<typename _Type>
			FORGE_FORCE_INLINE Void DestructImpl(_Type* dst, Size count, Common::TypeIsPod)
			{
				
			}
			template<typename _Type>
			FORGE_FORCE_INLINE Void DestructImpl(_Type* dst, Size count, Common::TypeIsClass)
			{
				for (I32 i = 0; i < count; i++)
					(dst + i)->~_Type();
			}

			template<typename _Type>
			FORGE_FORCE_INLINE Void MoveImpl(_Type* dst, _Type&& temp, Size count, Common::TypeIsPod)
			{
				for (I32 i = 0; i < count; i++)
					MemoryCopy(dst + i, &temp, sizeof(_Type));
			}
			template<typename _Type>
			FORGE_FORCE_INLINE Void MoveImpl(_Type* dst, _Type&& temp, Size count, Common::TypeIsClass)
			{
				for (I32 i = 0; i < count; i++)
					*(dst + i) = std::move(temp);
			}

			template<typename _Type>
			FORGE_FORCE_INLINE Void CopyImpl(_Type* dst, const _Type& copy, Size count, Common::TypeIsPod)
			{
				for (I32 i = 0; i < count; i++)
					MemoryCopy(dst + i, const_cast<_Type*>(&copy), sizeof(_Type));
			}
			template<typename _Type>
			FORGE_FORCE_INLINE Void CopyImpl(_Type* dst, const _Type& copy, Size count, Common::TypeIsClass)
			{
				for (I32 i = 0; i < count; i++)
					*(dst + i) = copy;
			}

			template<typename _Type>
			FORGE_FORCE_INLINE Void MoveConstructImpl(_Type* dst, _Type&& temp, Size count, Common::TypeIsPod)
			{
				for (I32 i = 0; i < count; i++)
					MemoryCopy(dst + i, &temp, sizeof(_Type));
			}
			template<typename _Type>
			FORGE_FORCE_INLINE Void MoveConstructImpl(_Type* dst, _Type&& temp, Size count, Common::TypeIsClass)
			{
				for (I32 i = 0; i < count; i++)
					new (dst + i) _Type(std::move(temp));
			}

			template<typename _Type>
			FORGE_FORCE_INLINE Void CopyConstructImpl(_Type* dst, const _Type& copy, Size count, Common::TypeIsPod)
			{
				for (I32 i = 0; i < count; i++)
					MemoryCopy(dst + i, const_cast<_Type*>(&copy), sizeof(_Type));
			}
			template<typename _Type>
			FORGE_FORCE_INLINE Void CopyConstructImpl(_Type* dst, const _Type& copy, Size count, Common::TypeIsClass)
			{
				for (I32 i = 0; i < count; i++)
					new (dst + i) _Type(copy);
			}
			
			template<typename _Type>
			FORGE_FORCE_INLINE Bool CompareArrayImpl(const _Type* lh_array, const _Type* rh_array, Size count, Common::TypeIsPod)
			{
				return MemoryCompare(lh_array, rh_array, count * sizeof(_Type));
			}
			template<typename _Type>
			FORGE_FORCE_INLINE Bool CompareArrayImpl(const _Type* lh_array, const _Type* rh_array, Size count, Common::TypeIsClass)
			{
				for (I32 i = 0; i < count; i++)
					if (*(lh_array + i) != *(rh_array + i))
						return false;

				return true;
			}

			template<typename _Type>
			FORGE_FORCE_INLINE Void CopyArrayImpl(_Type* dst, _Type* src, Size count, Common::TypeIsPod)
			{
				MemoryCopy(dst, src, count * sizeof(_Type));
			}
			template<typename _Type>
			FORGE_FORCE_INLINE Void CopyArrayImpl(_Type* dst, _Type* src, Size count, Common::TypeIsClass)
			{
				for (I32 i = 0; i < count; i++)
					*(dst + i) = *(src + i);
			}

			template<typename _Type>
			FORGE_FORCE_INLINE Void MoveConstructArrayImpl(_Type* dst, _Type* src, Size count, Common::TypeIsPod)
			{
				MemoryCopy(dst, src, count * sizeof(_Type));
			}
			template<typename _Type>
			FORGE_FORCE_INLINE Void MoveConstructArrayImpl(_Type* dst, _Type* src, Size count, Common::TypeIsClass)
			{
				for (I32 i = 0; i < count; i++)
					new (dst + i) _Type(std::move(*(src + i)));
			}

			template<typename _Type>
			FORGE_FORCE_INLINE Void CopyConstructArrayImpl(_Type* dst, _Type* src, Size count, Common::TypeIsPod)
			{
				MemoryCopy(dst, src, count * sizeof(_Type));
			}
			template<typename _Type>
			FORGE_FORCE_INLINE Void CopyConstructArrayImpl(_Type* dst, _Type* src, Size count, Common::TypeIsClass)
			{
				for (I32 i = 0; i < count; i++)
					new (dst + i) _Type(*(src + i));
			}
		}
		
		/**
		 * @brief Constructs object type a number of types in an array
		 * 
		 * The destination array should have enough allocated space to
		 * store the wanted number of copies. If the count is larger than the
		 * allocated space undefined behaviour might occur. 
		 * 
		 * @param[out] dst   The destination array where type will be constructed.
		 * @param[in]  count The number of element to construct in the array. 
		 */
		template<typename _Type>
		FORGE_FORCE_INLINE Void Construct(_Type* dst, Size count)
		{
			Internal::ConstructImpl(dst, count, Common::TTraitInt<Common::TIsPod<_Type>::Value>());
		}

		/**
		 * @brief Destructs object type a number of times in an array
		 *
		 * The destination array should have enough allocated space to
		 * store the wanted number of copies. If the count is larger than the
		 * allocated space undefined behaviour might occur.
		 *
		 * @param[out] dst   The destination array where type will be destructed.
		 * @param[in]  count The number of element to construct in the array.
		 */
		template<typename _Type>
		FORGE_FORCE_INLINE Void Destruct(_Type* dst, Size ui_count)
		{
			Internal::DestructImpl(dst, ui_count, Common::TTraitInt<Common::TIsPod<_Type>::Value>());
		}

		/**
		 * @brief Moves an object a number of times in an array.
		 *
		 * The destination array should have enough allocated space to
		 * store the wanted number of copies. If the count is larger than the
		 * allocated space undefined behaviour might occur.
		 *
		 * @param[out] dst      The destination array where the copies will be stored.
		 * @param[in]  copy     The copy of the object to store in the array.
		 * @param[in]  ui_count The number of element copies to store in the array.
		 */
		template<typename _Type>
		FORGE_FORCE_INLINE Void Move(_Type* dst, _Type&& temp, Size count)
		{
			Internal::MoveImpl(dst, std::move(temp), count, Common::TTraitInt<Common::TIsPod<_Type>::Value>());
		}

		/**
		 * @brief Copies an object a number of times in an array.
		 *
		 * The destination array should have enough allocated space to
		 * store the wanted number of copies. If the count is larger than the
		 * allocated space undefined behaviour might occur.
		 *
		 * @param[out] dst      The destination array where the copies will be stored.
		 * @param[in]  copy     The copy of the object to store in the array.
		 * @param[in]  ui_count The number of element copies to store in the array.
		 */
		template<typename _Type>
		FORGE_FORCE_INLINE Void Copy(_Type* dst, const _Type& copy, Size ui_count)
		{
			Internal::CopyImpl(dst, copy, ui_count, Common::TTraitInt<Common::TIsPod<_Type>::Value>());
		}

		/**
		 * @brief Copy constructs an object a number of times in an array.
		 * 
		 * The destination array should have enough allocated space to
		 * store the wanted number of copies. If the count is larger than the
		 * allocated space undefined behaviour might occur. 
		 * 
		 * @param[out] dst   The destination array where the copies will be stored.
		 * @param[in]  copy  The copy of the object to store in the array.
		 * @param[in]  count The number of element copies to store in the array.
		 */
		template<typename _Type>
		FORGE_FORCE_INLINE Void CopyConstruct(_Type* dst, const _Type& copy, Size ui_count)
		{
			Internal::CopyConstructImpl(dst, copy, ui_count, Common::TTraitInt<Common::TIsPod<_Type>::Value>());
		}

		/**
		 * @brief Move constructs an object a number of times in an array.
		 *
		 * The destination array should have enough allocated space to
		 * store the wanted number of copies. If the count is larger than the
		 * allocated space undefined behaviour might occur.
		 *
		 * @param[out] dst   The destination array where the copies will be stored.
		 * @param[in]  temp  The copy of the object to store in the array.
		 * @param[in]  count The number of element copies to store in the array.
		 */
		template<typename _Type>
		FORGE_FORCE_INLINE Void MoveConstruct(_Type* dst, _Type&& temp, Size count)
		{
			Internal::MoveConstructImpl(dst, std::move(temp), count, Common::TTraitInt<Common::TIsPod<_Type>::Value>());
		}

		/**
		 * @brief Compares the data stored in two arrays.
		 *
		 * @param[in] lh_array The left-hand side array to comapre.
		 * @param[in] rh_array The right-hand side array to compare.
		 * @param[in] count    The number of elements in the arrays.
		 *
		 * @returns True if the data stored in the arrays are equal.
		 */
		template<typename _Type>
		FORGE_FORCE_INLINE Bool CompareArray(const _Type* lh_array, const _Type* rh_array, Size ui_count)
		{
			return Internal::CompareArrayImpl(lh_array, rh_array, ui_count, Common::TTraitInt<Common::TIsPod<_Type>::Value>());
		}

		/**
		 * @brief Copies the elements stored in source array to destination array
		 * 
		 * The number of bytes should be equal to the allocated space of both the
		 * destination and source arrays. If the number of bytes is larger than
		 * the allocated space undefined behaviour might occur.
		 * 
		 * @param[out] dst   The destination array to copy elements to.
		 * @param[in]  src   The source array where elementa will be copied from.
		 * @param[in]  count The number of elements to copy to the destination array.
		 */
		template<typename _Type>
		FORGE_FORCE_INLINE Void CopyArray(_Type* dst, _Type* src, Size ui_count)
		{
			Internal::CopyArrayImpl(dst, src, ui_count, Common::TTraitInt<Common::TIsPod<_Type>::Value>());
		}

		/**
		 * @brief Move constructs the elements stored in source array to
		 * destiniation array.
		 *
		 * The number of bytes should be equal to the allocated space of both the
		 * destination and source arrays. If the number of bytes is larger than
		 * the allocated space undefined behaviour might occur.
		 *
		 * @param[out] dst   The destination array to copy elements to.
		 * @param[in]  src   The source array where elementa will be moved from.
		 * @param[in]  count The number of elements to move to the destination array.
		 */
		template<typename _Type>
		FORGE_FORCE_INLINE Void MoveConstructArray(_Type* dst, _Type* src, Size ui_count)
		{
			Internal::MoveConstructArrayImpl(dst, src, ui_count, Common::TTraitInt<Common::TIsPod<_Type>::Value>());
		}

		/**
		 * @brief Copy constructs the elements stored in source array to
		 * destiniation array.
		 * 
		 * The number of bytes should be equal to the allocated space of both the
		 * destination and source arrays. If the number of bytes is larger than
		 * the allocated space undefined behaviour might occur.
		 * 
		 * @param[out] dst   The destination array to copy elements to.
		 * @param[in]  src   The source array where elementa will be copied from.
		 * @param[in]  count The number of elements to copy to the destination array.
		 */
		template<typename _Type>
		FORGE_FORCE_INLINE Void CopyConstructArray(_Type* dst, _Type* src, Size ui_count)
		{
			Internal::CopyConstructArrayImpl(dst, src, ui_count, Common::TTraitInt<Common::TIsPod<_Type>::Value>());
		}

		/**
		 * @brief Aligns address to an alignment boundry and retrieves the first aligned
		 * address after the address passed.
		 * 
		 * @param[in] address   The address to align.
		 * @param[in] alignment The alignment requirment of the memory, must be power of two.
		 * 
		 * @returns VoidPtr storing the aligned address.
		 */
		FORGE_FORCE_INLINE VoidPtr AlignAddressUpward(VoidPtr address, Byte alignment)
		{
			return reinterpret_cast<VoidPtr>(((reinterpret_cast<U64>(address) + (alignment - 1)) & ~(alignment - 1)));
		}

		/**
		 * @brief Aligns address to an alignment boundry and retrieves the first aligned
		 * address before the address passed.
		 *
		 * @param[in] address   The address to align.
		 * @param[in] alignment The alignment requirment of the memory, must be power of two.
		 *
		 * @returns VoidPtr storing the aligned address.
		 */
		FORGE_FORCE_INLINE VoidPtr AlignAddressBackward(VoidPtr address, Byte alignment)
		{
			return reinterpret_cast<VoidPtr>((reinterpret_cast<U64>(address) & ~(alignment - 1)));
		}

		/**
		 * @brief Calculates how many bytes are need to align the address upwards.
		 * 
		 * @param[in] address   The address to align.
		 * @param[in] alignment The Alignment requirment of the memory, must be power of two.
		 * 
		 * @returns Size storing the number of bytes needed to align the address. 
		 */
		FORGE_FORCE_INLINE Size AlignAddressUpwardAdjustment(VoidPtr address, Byte alignment)
		{
			Size adjustment = alignment - (reinterpret_cast<U64>(address) & (alignment - 1));
			return adjustment != alignment ? adjustment : 0;
		}

		/**
		 * @brief Calculates how many bytes are need to align the address backwards.
		 *
		 * @param[in] address   The address to align.
		 * @param[in] alignment The alignment requirment of the memory, must be power of two.
		 *
		 * @returns Size storing the number of bytes needed to align the address.
		 */
		FORGE_FORCE_INLINE Size AlignAddressBackwardAdjustment(VoidPtr address, Byte alignment)
		{
			Size adjustment = (reinterpret_cast<U64>(address) & (alignment - 1));
			return adjustment != alignment ? adjustment : 0;
		}
		
		/**
		 *@brief Checks whether address is aligned to a specific alignment boundry.
		 * 
		 *@param[in] address   The address to check for alignment.  
		 *@param[in] alignment The alignment requirment of the memory, must be power of two. 
		 *
		 * @returns True if the address is aligned.
		 */
		FORGE_FORCE_INLINE Bool IsAddressAligned(VoidPtr address, Byte alignment)
		{ 
			return AlignAddressUpwardAdjustment(address, alignment) == 0;
		}
		
		/**
		 * @brief Performs addition on a raw memory address.
		 * 
		 * @param[in] address The address to perform addition on.
		 * @param[in] bytes   The number of bytes to add to the address.
		 * 
		 * @returns VoidPtr storing the resultant address.
		 */
		FORGE_FORCE_INLINE VoidPtr AddAddress(VoidPtr address, Size bytes)
		{
			return reinterpret_cast<VoidPtr>((reinterpret_cast<U64>(address) + bytes));
		}

		/**
		 * @brief Performs addition on two raw memory addresses.
		 *
		 * @param[in] lh_address The left-hand side address.
		 * @param[in] rh_address the right-hand side address.
		 *
		 * @returns VoidPtr storing the resultant address.
		 */
		FORGE_FORCE_INLINE VoidPtr AddAddress(VoidPtr lh_address, VoidPtr rh_address)
		{
			return reinterpret_cast<VoidPtr>((reinterpret_cast<U64>(lh_address) + reinterpret_cast<U64>(rh_address)));
		}

		/**
		 * @brief Performs subtraction on a raw memory address.
		 *
		 * @param[in] address The address to perform subtraction on.
		 * @param[in] bytes   The number of bytes to subtract from the address.
		 *
		 * @returns VoidPtr storing the resultant address.
		 */
		FORGE_FORCE_INLINE VoidPtr SubAddress(VoidPtr address, Size bytes)
		{
			return reinterpret_cast<VoidPtr>((reinterpret_cast<U64>(address) - bytes));
		}

		/**
		 * @brief Performs subtraction on two raw memory addresses.
		 *
		 * @param[in] lh_address The left-hand side address.
		 * @param[in] rh_address the right-hand side address.
		 *
		 * @returns VoidPtr storing the resultant address.
		 */
		FORGE_FORCE_INLINE VoidPtr SubAddress(VoidPtr lh_address, VoidPtr rh_address)
		{
			return reinterpret_cast<VoidPtr>((reinterpret_cast<U64>(lh_address) - reinterpret_cast<U64>(rh_address)));
		}

		/**
		 * @brief Performs subtraction on two const raw memory addresses.
		 *
		 * @param[in] lh_address The left-hand side address.
		 * @param[in] rh_address the right-hand side address.
		 *
		 * @returns VoidPtr storing the resultant address.
		 */
		FORGE_FORCE_INLINE ConstVoidPtr SubAddress(ConstVoidPtr lh_address, ConstVoidPtr rh_address)
		{
			return reinterpret_cast<ConstVoidPtr>((reinterpret_cast<U64>(lh_address) - reinterpret_cast<U64>(rh_address)));
		}
		
		/**
		 * @brief Checks whether the address is within bounds of the allocated memory.
		 * 
		 * @param[in] start_address  The starting address of the memory pool.
		 * @param[in] address        The address to bound check.
		 * @param[in] total_Size     The total Size of the memory pool.
		 * 
		 * @return True if the address within the passed bounds.
		 */
		FORGE_FORCE_INLINE Bool WithinAddressBounds(VoidPtr start_address, VoidPtr address, Size total_size)
		{
			if (reinterpret_cast<U64>(start_address) > reinterpret_cast<U64>(address) ||
				reinterpret_cast<U64>(start_address) + total_size < reinterpret_cast<U64>(address))
				return false;
			else
				return true;
		}
	}
}

#endif // MEMORY_UTILITIES_H
