#include "Core/Public/Memory/LinearAllocator.h"

namespace Forge {
	namespace Memory
	{
		LinearAllocator::LinearAllocator(SIZE total_size)
			: AbstractAllocator(nullptr, total_size)
		{
			m_is_mem_owned = true;
			m_start_ptr = malloc(total_size);
			m_offset_ptr = m_start_ptr;
		}
		LinearAllocator::LinearAllocator(PVOID start, SIZE total_size)
			: AbstractAllocator(start, total_size)
		{
			m_is_mem_owned = false;
			m_offset_ptr = m_start_ptr;
		}
		LinearAllocator::~LinearAllocator()
		{
			if (m_is_mem_owned) { free(m_start_ptr); }
		}

		PVOID LinearAllocator::Allocate(SIZE size, BYTE alignment)
		{
			BYTE adjustment = AlignAddressUpwardAdjustment(m_offset_ptr, alignment);

			if ((m_stats.m_used_memory + size + adjustment) > m_stats.m_total_size)
			{
				/// TODO: Instead of returing a nullptr throw an exception
				return nullptr;
			}

			PVOID aligned_address = AddAddress(m_offset_ptr, adjustment);
			m_offset_ptr = AddAddress(aligned_address, size);

			if (m_stats.m_peak_size < size) { m_stats.m_peak_size = size; }

			m_stats.m_used_memory += size + adjustment;
			m_stats.m_num_of_allocs++;

			return aligned_address;
		}
		VOID  LinearAllocator::Deallocate(PVOID address)
		{
			/// Throw an exception if user tried to deallocate
		}
		VOID  LinearAllocator::Clear()
		{
			m_offset_ptr = m_start_ptr;
			m_stats.m_used_memory = 0;
			m_stats.m_num_of_allocs = 0;
		}
	}
}