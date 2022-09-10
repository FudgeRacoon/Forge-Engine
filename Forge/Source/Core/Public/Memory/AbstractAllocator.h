#ifndef ABSTRACT_ALLOCATOR_H
#define ABSTRACT_ALLOCATOR_H

#include "Core/Public/Common/Common.h"

#include "Core/Public/Debug/Exception/ExceptionFactory.h"

namespace Forge {
	namespace Memory
	{
		/// @brief Base class for all custom allocators.
		class FORGE_API AbstractAllocator
		{
		FORGE_CLASS_NONCOPYABLE(AbstractAllocator)

		protected:
			VoidPtr m_start_ptr;

		protected:
			struct AllocatorStats
			{
				Size m_peak_size;
				Size m_total_size;
				Size m_used_memory;
				Size m_num_of_allocs;
			} m_stats = {0, 0, 0, 0};
		
		protected:
			Bool m_is_mem_owned;

		public:
			AbstractAllocator(VoidPtr start, Size total_size)
				: m_start_ptr(start), m_stats({ 0, total_size, 0, 0 }), m_is_mem_owned(false) {}
			virtual ~AbstractAllocator() = default;
		
		public:
			/// @brief Get the starting address of the memory pool.
			virtual VoidPtr GetStartAddress(void);

			/// @brief Get the maximum Size allocated during lifetime of the allocator.
			virtual Size GetPeakSize(void);

			/// @brief Get the total Size allocated for the memory pool.
			virtual Size GetTotalSize(void);

			/// @brief Get the currently occupied memory.
			virtual Size GetUsedMemory(void);

			/// @brief Get the number of allocations made during lifetime of the allocator.
			virtual Size GetNumOfAllocs(void);

		public:
			/// @brief Retrieves properly aligned memory address from pre-allocated memory pool.
			/// 
			/// @param[in] size      The size of memory to allocate in nytes.
			/// @param[in] alignment The Alignment requirment of the memory, must be power of two.
			/// 
			/// @returns Address to the start of the allocated memory.
			virtual VoidPtr Allocate(Size size, Byte alignment = 4) = 0;

			/// @brief Resizes an allocated address to a new size and copies its content
			/// to the new chunk.
			/// 
			/// @param[in] address   The address to resize.
			/// @param[in] size      The new size of memory to reallocate in bytes.
			/// @param[in] alignment The Alignment requirment of the memory, must be power of two.
			/// 
			/// @returns Address to the start of the reallocated memory.
			virtual VoidPtr Reallocate(VoidPtr address, Size size, Byte alignment = 4) = 0;

			/// @brief Frees the address present in the pre-allocated memory pool.
			virtual Void Deallocate(VoidPtr address) = 0;
			
		public:
			/// @brief Completely erases the whole memory pool.
			virtual Void Reset(void) = 0;
		};

		FORGE_FORCE_INLINE VoidPtr AbstractAllocator::GetStartAddress(void) { return m_start_ptr;             }
		FORGE_FORCE_INLINE Size    AbstractAllocator::GetPeakSize(void)     { return m_stats.m_peak_size;     }
		FORGE_FORCE_INLINE Size    AbstractAllocator::GetTotalSize(void)    { return m_stats.m_total_size;    }
		FORGE_FORCE_INLINE Size    AbstractAllocator::GetUsedMemory(void)   { return m_stats.m_used_memory;   }
		FORGE_FORCE_INLINE Size    AbstractAllocator::GetNumOfAllocs(void)  { return m_stats.m_num_of_allocs; }
	}
}

#endif // ABSTRACT_ALLOCATOR_H
