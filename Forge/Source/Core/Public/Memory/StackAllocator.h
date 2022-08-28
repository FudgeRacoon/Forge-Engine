#ifndef STACK_ALLOCATOR_H
#define STACK_ALLOCATOR_H

#include <stdlib.h>

#include "MemoryUtilities.h"
#include "AbstractAllocator.h"

#include "Core/Public/Common/Compiler.h"
#include "Core/Public/Common/TypeDefinitions.h"

namespace Forge {
	namespace Memory
	{
		/// @brief A stack allocator that is used to allocate memory in a
		/// LIFO form and constraints deallocation to only the
		/// most recently allocated memory chunk.
		class FORGE_API StackAllocator : public AbstractAllocator
		{
		private:
			PVOID m_offset_ptr;

		private:
			struct AllocationHeader
			{
				BYTE  m_padding;
				PVOID m_prev_address;
			};

		public:
			StackAllocator(SIZE total_size);
			StackAllocator(PVOID start, SIZE total_size);
		   ~StackAllocator();

		public:
			/// @brief Retrieves properly aligned memory address from pre-allocated memory pool.
			/// 
			/// @param[in] size The size of memory to allocate in bytes.
			/// @param[in] alignment The Alignment requirment of the memory, must be power of two.
			/// 
			/// @returns Address to the start of the allocated memory.
			/// 
			/// @throw Will throw a bad allocation error if the size requested is larger
			/// than the memory pool.
			PVOID Allocate(SIZE size, BYTE alignment = 4) override;

			/// @brief Resizes an the most recently allocated address to a 
			/// new size and copies its content to the new chunk.
			/// 
			/// @param[in] address The address to resize.
			/// @param[in] size The new size of memory to reallocate in bytes.
			/// @param[in] alignment The Alignment requirment of the memory, must be power of two.
			/// 
			/// @returns Address to the start of the reallocated memory.
			/// 
			// @throw Will throw memory out of bounds error if the address is out of bounds,
			/// bad allocation error if not allocated or an invalid operation error if
			/// address is not the most recently allocated.
			PVOID Reallocate(PVOID address, SIZE size, BYTE alignment = 4) override;

			/// @brief Frees the the most recently allocated address present
			/// in the pre-allocated memory pool.
			/// 
			/// @param[in] address The address to deallocate.
			/// 
			/// @throw Will throw memory out of bounds error if the address is out of bounds,
			/// bad allocation error if not allocated or an invalid operation error if
			/// address is not the most recently allocated.
			VOID  Deallocate(PVOID address) override;

		public:
			/// @brief Completely erases the whole memory pool.
			VOID  Reset() override;
		};
	}
}

#endif // STACK_ALLOCATOR_H
