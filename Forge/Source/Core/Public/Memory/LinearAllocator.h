#ifndef LINEAR_ALLOCATOR_H
#define LINEAR_ALLOCATOR_H

#include <stdlib.h>

#include "MemoryUtilities.h"
#include "AbstractAllocator.h"

namespace Forge {
	namespace Memory
	{
		/// @brief A linear allocator that is used to allocate memory in a 
		/// seqeuntial form and constraints deallocation to only the 
		/// whole memory pool.
		class FORGE_API LinearAllocator : public AbstractAllocator
		{
		private:
			VoidPtr m_offset_ptr;

		public:
			LinearAllocator(Size total_size);
			LinearAllocator(VoidPtr start, Size total_size);
		   ~LinearAllocator();

		public:
			/// @brief Retrieves properly aligned memory address from pre-allocated memory pool.
			/// 
			/// @param[in] Size      The size of memory to allocate in bytes.
			/// @param[in] alignment The alignment requirment of the memory, must be power of two.
			/// 
			/// @returns Address to the start of the allocated memory.
			/// 
			/// @throw Will throw a bad allocation error if the size requested is larger
			/// than the memory pool.
			VoidPtr Allocate(Size size, Byte alignment = 4) override;

			/// @brief The linear allocator does not allow reallocation to previously
			/// allocated memory blocks, thus this function should not be used at all.
			/// 
			/// @throw Will throw invalid operation error if attempted to reallocate an address.
			VoidPtr Reallocate(VoidPtr address, Size Size, Byte alignment = 4) override;

			/// @brief The linear allocator only allows deallocation to the whole memory 
			/// pool, thus this function should not be used at all.
			/// 
			/// @throw Will throw invalid operation error if attempted to deallocate an address.
			Void Deallocate(VoidPtr address) override;

		public:
			/// @brief Completely erases the whole memory pool.
			Void  Reset() override;
		};
	}
}

#endif // LINEAR_ALLOCATOR_H
