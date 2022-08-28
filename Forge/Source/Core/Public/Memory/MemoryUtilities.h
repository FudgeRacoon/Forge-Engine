#ifndef MEMORY_UTILITIES_H
#define MEMORY_UTILITIES_H

#include "Core/Public/Common/Compiler.h"
#include "Core/Public/Common/TypeDefinitions.h"

namespace Forge {
	namespace Memory
	{
		/// @brief Aligns address to an alignment boundry and retrieve the first aligned
		/// address after the address passed.
		/// 
		/// @param[in] address The address to align.
		/// @param[in] alignment The Alignment requirment of the memory, must be power of two.
		/// 
		/// @returns The address of the aligned address in integral form.
		FORGE_FORCE_INLINE PVOID AlignAddressUpward(PVOID address, BYTE alignment)
		{
			return (PVOID)((reinterpret_cast<INTPTR>(address) + (alignment - 1)) & ~(alignment - 1));
		}

		/// @brief Aligns address to an alignment boundry and retrieve the first aligned
		/// address before the address passed.
		/// 
		/// @param[in] address The address to align.
		/// @param[in] alignment The Alignment requirment of the memory, must be power of two.
		/// 
		/// @returns The address of the aligned address in integral form.
		FORGE_FORCE_INLINE PVOID AlignAddressBackward(PVOID address, BYTE alignment)
		{
			return (PVOID)((reinterpret_cast<INTPTR>(address) & ~(alignment - 1)));
		}

		/// @brief Calculates how many bytes are need to align the address upwards.
		/// 
		/// @param[in] address The address to align.
		/// @param[in] alignment The Alignment requirment of the memory, must be power of two.
		/// 
		/// @returns The number of bytes to align address.
		FORGE_FORCE_INLINE BYTE AlignAddressUpwardAdjustment(PVOID address, BYTE alignment)
		{
			BYTE adjustment = alignment - (reinterpret_cast<INTPTR>(address) & (alignment - 1));
			return adjustment != alignment ? adjustment : 0;
		}

		/// @brief Calculates how many bytes are need to align the address backwards.
		/// 
		/// @param[in] address The address to align.
		/// @param[in] alignment The Alignment requirment of the memory, must be power of two.
		/// 
		/// @returns The number of bytes to align address.
		FORGE_FORCE_INLINE BYTE AlignAddressBackwardAdjustment(PVOID address, BYTE alignment)
		{
			BYTE adjustment = (reinterpret_cast<INTPTR>(address) & (alignment - 1));
			return adjustment != alignment ? adjustment : 0;
		}

		/// @brief Checks whether address is aligned to a specific alignment boundry.
		/// 
		/// @param[in] address The address to check for alignment.
		/// @param[in] alignment The Alignment requirment of the memory, must be power of two.
		FORGE_FORCE_INLINE BOOL IsAddressAligned(PVOID address, BYTE alignment)
		{ 
			return AlignAddressUpwardAdjustment(address, alignment) == 0;
		}
		
		/// @brief Performs addition on a non constant void pointer.
		/// 
		/// @param[in] address The address to perform addition on.
		/// @param[in] bytes The number of bytes to add to the address.
		FORGE_FORCE_INLINE PVOID AddAddress(PVOID address, SIZE bytes)
		{
			return (PVOID)(reinterpret_cast<INTPTR>(address) + bytes);
		}

		/// @brief Performs addition on a constant void pointer.
		/// 
		/// @param[in] lh_address The left-hand address to perform addition on.
		/// @param[in] rh_address The right-hand address to perform addition on.
		FORGE_FORCE_INLINE PVOID AddAddress(PVOID lh_address, PVOID rh_address)
		{
			return (PVOID)(reinterpret_cast<INTPTR>(lh_address) + reinterpret_cast<INTPTR>(rh_address));
		}

		/// @brief Performs subtraction on a non constant void pointer.
		/// 
		/// @param[in] address The address to perform subtraction on.
		/// @param[in] bytes The number of bytes to subtract to the address.
		FORGE_FORCE_INLINE PVOID SubAddress(PVOID address, SIZE bytes)
		{
			return (PVOID)(reinterpret_cast<INTPTR>(address) - bytes);
		}

		/// @brief Performs subtraction on a constant void pointer.
		/// 
		/// @param[in] lh_address The left-hand address to perform addition on.
		/// @param[in] rh_address The right-hand address to perform addition on.
		FORGE_FORCE_INLINE PVOID SubAddress(PVOID lh_address, PVOID rh_address)
		{
			return (PVOID)(reinterpret_cast<INTPTR>(lh_address) - reinterpret_cast<INTPTR>(rh_address));
		}
		
		/// @brief Checks whether the marker address is within bounds of the allocated memory.
		/// 
		/// @param[in] start_address The starting address of the memory pool.
		/// @param[in] marker_address The address to bound check.
		/// @param[in] total_size The total size of the memory pool.
		FORGE_FORCE_INLINE BOOL WithinAddressBounds(PVOID start_address, PVOID marker_address, SIZE total_size)
		{
			if (reinterpret_cast<INTPTR>(start_address) > reinterpret_cast<INTPTR>(marker_address) ||
				reinterpret_cast<INTPTR>(start_address) + total_size < reinterpret_cast<INTPTR>(marker_address))
				return false;
			else
				return true;
		}
	
		/// @brief Copies a block of data from source address to destination address.
		///
		/// @param[out] dst THe destination address where data will be copied to.
		/// @param[in] src The source address where data is stored.
		/// @param[in] size The number of bytes to copy.
		FORGE_FORCE_INLINE VOID MemoryCopy(PVOID dst, PVOID src, SIZE size)
		{
			PBYTE temp_dst = reinterpret_cast<PBYTE>(dst);
			PBYTE temp_src = reinterpret_cast<PBYTE>(src);

			for (int i = 0; i < size; i++)
				*(temp_dst + i) = *(temp_src + i);
		}
	}
}

#endif // MEMORY_UTILITIES_H
