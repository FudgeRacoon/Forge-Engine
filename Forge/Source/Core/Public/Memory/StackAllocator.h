#ifndef STACK_ALLOCATOR_H
#define STACK_ALLOCATOR_H

#include <stdlib.h>

#include "MemoryUtilities.h"
#include "AbstractAllocator.h"

#include "Core/Public/Common/Common.h"

namespace Forge {
	namespace Memory
	{
		/// @brief A stack allocator that is used to allocate memory in a
		/// LIFO form and constraints deallocation to only the
		/// most recently allocated memory chunk.
		class FORGE_API StackAllocator : public AbstractAllocator
		{
		private:
			VoidPtr m_offset_ptr;
			VoidPtr m_prev_address;

		private:
			struct AllocationHeader
			{
				Byte m_padding;
			};

		public:
			StackAllocator(Size total_size);
			StackAllocator(VoidPtr start, Size total_size);
		   ~StackAllocator();

		public:
			/// @brief Retrieves properly aligned memory address from pre-allocated memory pool.
			/// 
			/// @param[in] size      The size of memory to allocate in Bytes.
			/// @param[in] alignment The Alignment requirment of the memory, must be power of two.
			/// 
			/// @returns Address to the start of the allocated memory.
			/// 
			/// @throw Will throw a bad allocation error if the Size requested is larger
			/// than the memory pool.
			VoidPtr Allocate(Size size, Byte alignment = 4) override;

			/// @brief ReSizes an the most recently allocated address to a 
			/// new Size and copies its content to the new chunk.
			/// 
			/// @param[in] address   The address to reSize.
			/// @param[in] size      The new Size of memory to reallocate in Bytes.
			/// @param[in] alignment The Alignment requirment of the memory, must be power of two.
			/// 
			/// @returns Address to the start of the reallocated memory.
			/// 
			//  @throw Will throw memory out of bounds error if the address is out of bounds,
			/// bad allocation error if not allocated or an invalid operation error if
			/// address is not the most recently allocated.
			VoidPtr Reallocate(VoidPtr address, Size size, Byte alignment = 4) override;

			/// @brief Frees the the most recently allocated address present
			/// in the pre-allocated memory pool.
			/// 
			/// @param[in] address The address to deallocate.
			/// 
			/// @throw Will throw memory out of bounds error if the address is out of bounds,
			/// bad allocation error if not allocated or an invalid operation error if
			/// address is not the most recently allocated.
			Void  Deallocate(VoidPtr address) override;

		public:
			/// @brief Completely erases the whole memory pool.
			Void  Reset() override;
		};
	}
}

#endif // STACK_ALLOCATOR_H
