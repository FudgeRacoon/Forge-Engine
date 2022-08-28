#include "Core/Public/Memory/StackAllocator.h"

namespace Forge {
	namespace Memory
	{
		StackAllocator::StackAllocator(SIZE total_size)
			: AbstractAllocator(nullptr, total_size)
		{
			m_is_mem_owned = true;

			m_start_ptr = malloc(total_size);
			m_offset_ptr = m_start_ptr;
		}
		StackAllocator::StackAllocator(PVOID start, SIZE total_size)
			: AbstractAllocator(start, total_size)
		{
			m_is_mem_owned = false;

			m_offset_ptr = m_start_ptr;
		}
		StackAllocator::~StackAllocator()
		{
			if (m_is_mem_owned) { free(m_start_ptr); }
		}

		PVOID StackAllocator::Allocate(SIZE size, BYTE alignment)
		{
			SIZE header_size = sizeof(AllocationHeader);

			BYTE adjustment = AlignAddressUpwardAdjustment(m_offset_ptr, alignment);

			if ((m_stats.m_used_memory + size + adjustment + header_size) > m_stats.m_total_size)
			{
				static Debug::ExceptionFactory e;
				e.ThrowException(
					Debug::Exception::ERR_BAD_ALLOCATION_EXCEPTION,
					FORGE_LINE_LITERAL,
					FORGE_FUNC_LITERAL,
					FORGE_FILE_LITERAL,
					"No sufficent space for required size"
				);
			}

			PVOID aligned_address = AddAddress(m_offset_ptr, adjustment);

			AllocationHeader* header = (AllocationHeader*)aligned_address;
			header->m_padding = adjustment;
			header->m_prev_address = AddAddress(aligned_address, header_size);

			m_offset_ptr = AddAddress(header->m_prev_address, size);

			if (m_stats.m_peak_size < size) { m_stats.m_peak_size = size; }

			m_stats.m_used_memory += size + adjustment + header_size;
			m_stats.m_num_of_allocs++;

			return header->m_prev_address;
		}
		PVOID StackAllocator::Reallocate(PVOID address, SIZE size, BYTE alignment)
		{
			if (!WithinAddressBounds(m_start_ptr, address, m_stats.m_total_size))
			{
				static Debug::ExceptionFactory e;
				e.ThrowException(
					Debug::Exception::ERR_MEMORY_OUT_OF_BOUNDS_EXCEPTION,
					FORGE_LINE_LITERAL,
					FORGE_FUNC_LITERAL,
					FORGE_FILE_LITERAL
				);
			}

			SIZE header_size = sizeof(AllocationHeader);

			AllocationHeader* header = (AllocationHeader*)SubAddress(address, header_size);

			if (header->m_prev_address != address)
			{
				static Debug::ExceptionFactory e;
				e.ThrowException(
					Debug::Exception::ERR_INVALID_OPERATION_EXCEPTION,
					FORGE_LINE_LITERAL,
					FORGE_FUNC_LITERAL,
					FORGE_FILE_LITERAL,
					"Stack allocator only supports reallocation of the most recently allocated memroy"
				);
			}

			SIZE amt_to_shift = size - (INTPTR)SubAddress(m_offset_ptr, address);
			m_offset_ptr = AddAddress(m_offset_ptr, amt_to_shift);

			m_stats.m_used_memory += amt_to_shift;
		}
		VOID  StackAllocator::Deallocate(PVOID address)
		{
			if (!WithinAddressBounds(m_start_ptr, address, m_stats.m_total_size))
			{
				static Debug::ExceptionFactory e;
				e.ThrowException(
					Debug::Exception::ERR_MEMORY_OUT_OF_BOUNDS_EXCEPTION,
					FORGE_LINE_LITERAL,
					FORGE_FUNC_LITERAL,
					FORGE_FILE_LITERAL
				);
			}

			SIZE header_size = sizeof(AllocationHeader);

			AllocationHeader* header = (AllocationHeader*)SubAddress(address, header_size);

			if (header->m_prev_address != address)
			{
				static Debug::ExceptionFactory e;
				e.ThrowException(
					Debug::Exception::ERR_INVALID_OPERATION_EXCEPTION,
					FORGE_LINE_LITERAL,
					FORGE_FUNC_LITERAL,
					FORGE_FILE_LITERAL,
					"Stack allocator only supports deallocation of the most recently allocated memroy"
				);
			}

			m_stats.m_used_memory -= ((INTPTR)SubAddress(m_offset_ptr, address)) + header_size + header->m_padding;
			m_stats.m_num_of_allocs--;

			m_offset_ptr = SubAddress(header, header->m_padding);
		}

		VOID  StackAllocator::Reset()
		{
			m_offset_ptr = m_start_ptr;

			m_stats.m_peak_size = 0;
			m_stats.m_used_memory = 0;
			m_stats.m_num_of_allocs = 0;
		}
	}
}