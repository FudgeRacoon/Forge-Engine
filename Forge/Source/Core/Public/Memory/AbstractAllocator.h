#ifndef ABSTRACT_ALLOCATOR_H
#define ABSTRACT_ALLOCATOR_H

#include "Core/Public/Common/Compiler.h"
#include "Core/Public/Common/TypeDefinitions.h"
#include "Core/Public/Common/PreprocessorUtilities.h"

#include "Core/Public/Debug/Exception/ExceptionFactory.h"

namespace Forge {
	namespace Memory
	{
		/// @brief Base class for all custom allocators.
		class FORGE_API AbstractAllocator
		{
		FORGE_CLASS_NONCOPYABLE(AbstractAllocator)

		protected:
			PVOID m_start_ptr;

		protected:
			struct AllocatorStats
			{
				SIZE m_peak_size;
				SIZE m_total_size;
				SIZE m_used_memory;
				SIZE m_freed_memory;
				SIZE m_num_of_allocs;
			} m_stats = {0, 0, 0, 0, 0};
		
		protected:
			BOOL m_is_mem_owned;

		public:
			AbstractAllocator(PVOID start, SIZE total_size);
			virtual ~AbstractAllocator() = default;
		
		public:
			/// @brief Get the starting address of the memory pool.
			PVOID GetStartAddress();

			/// @brief Get the maximum size allocated during lifetime of the allocator.
			SIZE  GetPeakSize();

			/// @brief Get the total size allocated for the memory pool.
			SIZE  GetTotalSize();

			/// @brief Get the currently occupied memory.
			SIZE  GetUsedMemory();

			/// @brief Get the number of allocations made during lifetime of the allocator.
			SIZE  GetNumOfAllocs();

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
			virtual PVOID Allocate(SIZE size, BYTE alignment = 4) = 0;

			/// @brief Resizes an allocated address to a new size and copies its content
			/// to the new chunk.
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
			virtual PVOID Reallocate(PVOID address, SIZE size, BYTE alignment = 4) = 0;

			/// @brief Frees the address present in the pre-allocated memory pool.
			/// 
			/// @param[in] address The address to deallocate.
			/// 
			// @throw Will throw memory out of bounds error if the address is out of bounds, 
			/// bad allocation error if not allocated or an invalid operation error if 
			/// address is not the most recently allocated.
			virtual VOID  Deallocate(PVOID address) = 0;
			
		public:
			/// @brief Completely erases the whole memory pool.
			virtual VOID  Reset() = 0;
		};

		AbstractAllocator::AbstractAllocator(PVOID start, SIZE total_size)
			: m_start_ptr(start), m_stats({ 0, total_size, 0, 0, 0 }), m_is_mem_owned(false) {}

		FORGE_FORCE_INLINE PVOID AbstractAllocator::GetStartAddress() { return m_start_ptr; }
		FORGE_FORCE_INLINE SIZE  AbstractAllocator::GetPeakSize() { return m_stats.m_peak_size; }
		FORGE_FORCE_INLINE SIZE  AbstractAllocator::GetTotalSize() { return m_stats.m_total_size; }
		FORGE_FORCE_INLINE SIZE  AbstractAllocator::GetUsedMemory() { return m_stats.m_used_memory; }
		FORGE_FORCE_INLINE SIZE  AbstractAllocator::GetNumOfAllocs() { return m_stats.m_num_of_allocs; }
	}
}

#endif // ABSTRACT_ALLOCATOR_H
