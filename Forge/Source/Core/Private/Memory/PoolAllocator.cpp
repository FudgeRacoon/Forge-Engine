#include "Core/Public/Memory/PoolAllocator.h"

namespace Forge {
	namespace Memory
	{
		PoolAllocator::PoolAllocator(Size object_size, Size total_size)
			: AbstractAllocator(nullptr, total_size)
		{
			if (object_size < sizeof(VoidPtr))
			{
				/*FORGE_EXCEPT(Debug::Exception::ERR_INVALID_OPERATION_EXCEPTION, "Object Size must be larger than or equal to Void*")*/
			}

			m_start_ptr = malloc(total_size);

			m_is_mem_owned = true;
			m_object_size = object_size;

			MemorySet(m_start_ptr, 0, m_stats.m_total_size);

			Byte adjustment = AlignAddressUpwardAdjustment(m_start_ptr, 4);
			m_head = reinterpret_cast<VoidPtr*>(AddAddress(m_start_ptr, adjustment));

			VoidPtr* temp_ptr = m_head;
			Size num_of_chunks = (m_stats.m_total_size - adjustment) / m_object_size;

			for (int i = 0; i < num_of_chunks - 1; i++)
			{
				*temp_ptr = AddAddress(temp_ptr, m_object_size);
				temp_ptr = reinterpret_cast<VoidPtr*>(*temp_ptr);
			}

			*temp_ptr = nullptr;
		}
		PoolAllocator::PoolAllocator(VoidPtr start, Size object_Size, Size total_Size)
			: AbstractAllocator(start, total_Size)
		{
			if (m_object_size < sizeof(VoidPtr))
			{
				/*FORGE_EXCEPT(Debug::Exception::ERR_INVALID_OPERATION_EXCEPTION, "Object Size must be larger than or equal to Void*")*/
			}

			m_is_mem_owned = false;
			m_object_size = object_Size;

			MemorySet(m_start_ptr, 0, m_stats.m_total_size);

			Byte adjustment = AlignAddressUpwardAdjustment(m_start_ptr, 4);
			m_head = reinterpret_cast<VoidPtr*>(AddAddress(m_start_ptr, adjustment));

			VoidPtr* temp_ptr = m_head;
			Size num_of_chunks = (m_stats.m_total_size - adjustment) / m_object_size;

			for (int i = 0; i < num_of_chunks - 1; i++)
			{
				*temp_ptr = AddAddress(temp_ptr, m_object_size);
				temp_ptr = reinterpret_cast<VoidPtr*>(*temp_ptr);
			}

			*temp_ptr = nullptr;
		}
		
		PoolAllocator::~PoolAllocator()
		{
			if (m_is_mem_owned)
				free(m_start_ptr);
			else
				MemorySet(m_start_ptr, 0, m_stats.m_total_size);
		}

		VoidPtr PoolAllocator::Allocate(Size size, Byte alignment)
		{
			if (size != m_object_size)
			{
				/*FORGE_EXCEPT(Debug::Exception::ERR_BAD_ALLOCATION_EXCEPTION, "Requsted size must be equal to allocator's supported object size")*/
			}

			if (m_head == nullptr)
			{
				/*FORGE_EXCEPT(Debug::Exception::ERR_BAD_ALLOCATION_EXCEPTION, "No sufficent space for required size")*/
			}

			VoidPtr address = m_head;
			m_head = reinterpret_cast<VoidPtr*>(*m_head);

			if (m_stats.m_peak_size < size) { m_stats.m_peak_size = size; }

			m_stats.m_used_memory += m_object_size;
			m_stats.m_num_of_allocs++;

			return address;
		}
		VoidPtr PoolAllocator::Reallocate(VoidPtr address, Size size, Byte alignment)
		{
			/*FORGE_EXCEPT(Debug::Exception::ERR_INVALID_OPERATION_EXCEPTION, "Pool allocator does not support reallocation of memory addresses")*/

			return nullptr;
		}
		Void    PoolAllocator::Deallocate(VoidPtr address)
		{
			if (!WithinAddressBounds(m_start_ptr, address, m_stats.m_total_size))
			{
				/*FORGE_EXCEPT(Debug::Exception::ERR_MEMORY_OUT_OF_BOUNDS_EXCEPTION)*/
			}

			*reinterpret_cast<VoidPtr*>(address) = m_head;
			m_head = reinterpret_cast<VoidPtr*>(address);

			m_stats.m_used_memory -= m_object_size;
			m_stats.m_num_of_allocs--;
		}

		Void PoolAllocator::Reset(void)
		{
			Byte adjustment = AlignAddressUpwardAdjustment(m_start_ptr, 4);
			m_head = reinterpret_cast<VoidPtr*>(AddAddress(m_start_ptr, adjustment));

			VoidPtr* temp_ptr = m_head;
			Size num_of_chunks = (m_stats.m_total_size - adjustment) / m_object_size;

			for (int i = 0; i < num_of_chunks - 1; i++)
			{
				*temp_ptr = AddAddress(temp_ptr, m_object_size);
				temp_ptr = reinterpret_cast<VoidPtr*>(*temp_ptr);
			}

			*temp_ptr = nullptr;

			m_stats.m_used_memory = 0;
			m_stats.m_num_of_allocs = 0;
		}
	}
}
