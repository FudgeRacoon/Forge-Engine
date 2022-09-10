#ifndef POOL_ALLOCATOR_H
#define POOL_ALLOCATOR_H

#include <stdlib.h>

#include "MemoryUtilities.h"
#include "AbstractAllocator.h"

#include "Core/Public/Common/Common.h"

namespace Forge {
	namespace Memory
	{
		/// @brief A pool allocator that is used to allocate memory in
		/// fixed Sizes and does not enforce any constrains on deallocation.
		class FORGE_API PoolAllocator : public AbstractAllocator
		{
		private:
			VoidPtr* m_head;

		private:
			Size m_object_size;

		public:
			PoolAllocator(Size object_size, Size total_size);
			PoolAllocator(VoidPtr start, Size object_size, Size total_size);
		   ~PoolAllocator();

		public:
			/// @brief Retrieves properly aligned memory address from pre-allocated memory pool.
			/// 
			/// @param[in] size      The size of memory to allocate in Bytes.
			/// @param[in] alignment The Alignment requirment of the memory, must be power of two.
			/// 
			/// @returns Address to the start of the allocated memory.
			/// 
			/// @throw Will throw a bad allocation error if the Size requested is not
			/// equal to the object Size supported by the allocator.
			VoidPtr Allocate(Size size, Byte alignment = 4) override;

			/// @brief The pool allocator does not allow reallocation to previously
			/// allocated memory blocks, thus this function should not be used at all.
			/// 
			/// @throw Will throw invalid operation error if attempted to reallocate an address.
			VoidPtr Reallocate(VoidPtr address, Size size, Byte alignment = 4) override;

			/// @brief Frees the address present in the pre-allocated memory pool.
			/// 
			/// @param[in] address The address to deallocate.
			/// 
			// @throw Will throw memory out of bounds error if the address is out of bounds, 
			/// bad allocation error if not allocated.
			Void  Deallocate(VoidPtr address) override;

		public:
			/// @brief Completely erases the whole memory pool.
			Void  Reset() override;
		};
	}
}

#endif // POOL_ALLOCATOR_H
