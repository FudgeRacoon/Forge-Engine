#ifndef MEMORY_UTILITIES_H
#define MEMORY_UTILITIES_H

#include "Core/Public/Common/Common.h"

namespace Forge {
	namespace Memory
	{
		/// @brief Aligns address to an alignment boundry and retrieve the first aligned
		/// address after the address passed.
		/// 
		/// @param[in] address   The address to align.
		/// @param[in] alignment The Alignment requirment of the memory, must be power of two.
		/// 
		/// @returns The address of the aligned address in integral form.
		FORGE_FORCE_INLINE VoidPtr AlignAddressUpward(VoidPtr address, Byte alignment)
		{
			return (VoidPtr)((reinterpret_cast<U64>(address) + (alignment - 1)) & ~(alignment - 1));
		}

		/// @brief Aligns address to an alignment boundry and retrieve the first aligned
		/// address before the address passed.
		/// 
		/// @param[in] address   The address to align.
		/// @param[in] alignment The Alignment requirment of the memory, must be power of two.
		/// 
		/// @returns The address of the aligned address in integral form.
		FORGE_FORCE_INLINE VoidPtr AlignAddressBackward(VoidPtr address, Byte alignment)
		{
			return (VoidPtr)((reinterpret_cast<U64>(address) & ~(alignment - 1)));
		}

		/// @brief Calculates how many Bytes are need to align the address upwards.
		/// 
		/// @param[in] address   The address to align.
		/// @param[in] alignment The Alignment requirment of the memory, must be power of two.
		/// 
		/// @returns The number of Bytes to align address.
		FORGE_FORCE_INLINE Byte AlignAddressUpwardAdjustment(VoidPtr address, Byte alignment)
		{
			Byte adjustment = alignment - (reinterpret_cast<U64>(address) & (alignment - 1));
			return adjustment != alignment ? adjustment : 0;
		}

		/// @brief Calculates how many Bytes are need to align the address backwards.
		/// 
		/// @param[in] address   The address to align.
		/// @param[in] alignment The Alignment requirment of the memory, must be power of two.
		/// 
		/// @returns The number of Bytes to align address.
		FORGE_FORCE_INLINE Byte AlignAddressBackwardAdjustment(VoidPtr address, Byte alignment)
		{
			Byte adjustment = (reinterpret_cast<U64>(address) & (alignment - 1));
			return adjustment != alignment ? adjustment : 0;
		}

		/// @brief Checks whether address is aligned to a specific alignment boundry.
		/// 
		/// @param[in] address   The address to check for alignment.
		/// @param[in] alignment The Alignment requirment of the memory, must be power of two.
		FORGE_FORCE_INLINE Bool IsAddressAligned(VoidPtr address, Byte alignment)
		{ 
			return AlignAddressUpwardAdjustment(address, alignment) == 0;
		}
		
		/// @brief Performs addition on a non constant Void pointer.
		/// 
		/// @param[in] address The address to perform addition on.
		/// @param[in] Bytes   The number of Bytes to add to the address.
		FORGE_FORCE_INLINE VoidPtr AddAddress(VoidPtr address, Size bytes)
		{
			return (VoidPtr)(reinterpret_cast<U64>(address) + bytes);
		}

		/// @brief Performs addition on a constant Void pointer.
		/// 
		/// @param[in] lh_address The left-hand address to perform addition on.
		/// @param[in] rh_address The right-hand address to perform addition on.
		FORGE_FORCE_INLINE VoidPtr AddAddress(VoidPtr lh_address, VoidPtr rh_address)
		{
			return (VoidPtr)(reinterpret_cast<U64>(lh_address) + reinterpret_cast<U64>(rh_address));
		}

		/// @brief Performs subtraction on a non constant Void pointer.
		/// 
		/// @param[in] address The address to perform subtraction on.
		/// @param[in] Bytes   The number of Bytes to subtract to the address.
		FORGE_FORCE_INLINE VoidPtr SubAddress(VoidPtr address, Size bytes)
		{
			return (VoidPtr)(reinterpret_cast<U64>(address) - bytes);
		}

		/// @brief Performs subtraction on a constant Void pointer.
		/// 
		/// @param[in] lh_address The left-hand address to perform addition on.
		/// @param[in] rh_address The right-hand address to perform addition on.
		FORGE_FORCE_INLINE VoidPtr SubAddress(VoidPtr lh_address, VoidPtr rh_address)
		{
			return (VoidPtr)(reinterpret_cast<U64>(lh_address) - reinterpret_cast<U64>(rh_address));
		}

		/// @brief Performs subtraction on a constant Void pointer.
		/// 
		/// @param[in] lh_address The left-hand address to perform addition on.
		/// @param[in] rh_address The right-hand address to perform addition on.
		FORGE_FORCE_INLINE ConstVoidPtr SubAddress(ConstVoidPtr lh_address, ConstVoidPtr rh_address)
		{
			return (ConstVoidPtr)(reinterpret_cast<U64>(lh_address) - reinterpret_cast<U64>(rh_address));
		}
		
		/// @brief Checks whether the marker address is within bounds of the allocated memory.
		/// 
		/// @param[in] start_address  The starting address of the memory pool.
		/// @param[in] marker_address The address to bound check.
		/// @param[in] total_Size     The total Size of the memory pool.
		FORGE_FORCE_INLINE Bool WithinAddressBounds(VoidPtr start_address, VoidPtr marker_address, Size total_size)
		{
			if (reinterpret_cast<U64>(start_address) > reinterpret_cast<U64>(marker_address) ||
				reinterpret_cast<U64>(start_address) + total_size < reinterpret_cast<U64>(marker_address))
				return false;
			else
				return true;
		}
	
		/// @brief Copies a block of data from source address to destination address.
		///
		/// @param[out] dst The destination address where data will be copied to.
		/// @param[in]  src  The source address where data is stored.
		/// @param[in]  Size The number of Bytes to copy.
		FORGE_FORCE_INLINE Void MemoryCopy(VoidPtr dst, VoidPtr src, Size size)
		{
			BytePtr temp_dst = reinterpret_cast<BytePtr>(dst);
			BytePtr temp_src = reinterpret_cast<BytePtr>(src);

			for (int i = 0; i < size; i++)
				*(temp_dst + i) = *(temp_src + i);
		}
		
		/// @brief Sets a block of data to the value specified.
		///
		/// @param[out] dst   The destination address where data will be set.
		/// @param[in]  value The value the memory block will be set to.
		/// @param[in]  Size  The number of Bytes to set.
		FORGE_FORCE_INLINE Void MemorySet(VoidPtr dst, int value, Size size)
		{
			BytePtr temp_dst = reinterpret_cast<BytePtr>(dst);

			for (int i = 0; i < size; i++)
				*(temp_dst + i) = value;
		}
	}
}

#endif // MEMORY_UTILITIES_H
