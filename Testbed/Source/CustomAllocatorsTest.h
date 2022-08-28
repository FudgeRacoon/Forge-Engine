#ifndef CUSTOM_ALLOCATOR_TESTS
#define CUSTOM_ALLOCATOR_TESTS

#include <chrono>

#include "Core/Public/Memory/Memory.h"
#include "Core/Public/Common/Common.h"

using namespace Forge;
using namespace Forge::Memory;

class AllocatorBenchmark
{
private:
	using Milliseconds = std::chrono::nanoseconds;
	using HighResClock = std::chrono::high_resolution_clock;
	using Timepoint    = std::chrono::time_point<HighResClock>;

private:
	AbstractAllocator* m_allocator;

public:
	Timepoint m_start_time;
	Timepoint m_finish_time;

public:
	struct BenchmarkResults
	{
		F64 m_op_per_ms;
		F64 m_memory_used;

		SIZE m_operations;
		SIZE m_memory_size;
		SIZE m_memory_peak;

		INTPTR m_memory_start;

		Milliseconds m_time_elapsed;
	};

public:
	enum ALLOCATOR_TYPE
	{
		C_ALLOCATOR = 0x1,
		LINEAR_ALLOCATOR,
		STACK_ALLOCATOR,
		POOL_ALLOCATOR,
		FREELIST_ALLOCATOR
	};

public:
	AllocatorBenchmark() = default;
   ~AllocatorBenchmark() = default;

public:
	VOID StartRound();
	VOID FinishRound();

public:
	VOID PrintResults(BenchmarkResults results);
	BenchmarkResults BuildResults(Milliseconds elapsed_time);

public:
	VOID InitializeAllocator(ALLOCATOR_TYPE type, SIZE total_size);

public:
	VOID SingleAllocation(SIZE size, BYTE alignment);
	VOID SingleDeallocation(SIZE size, BYTE alignment);
	VOID MultipleAllocation(BYTE* size, BYTE alignment, SIZE size_count);
	VOID MultipleDeallocation(BYTE* size, BYTE alignment, SIZE size_count);
};

	VOID AllocatorBenchmark::StartRound() { m_start_time = HighResClock::now(); }
	VOID AllocatorBenchmark::FinishRound() { m_finish_time = HighResClock::now(); }
	
	VOID AllocatorBenchmark::PrintResults(AllocatorBenchmark::BenchmarkResults results)
	{
		printf("**********RESULTS:           ********\n");
		printf("           Ops/ms: %.3lf             \n", results.m_op_per_ms);
		printf("      Memory Used: %.3lf%%           \n", results.m_memory_used);
		printf("      Memory Size: %llu Bytes        \n", results.m_memory_size);
		printf("      Memory Peak: %llu Bytes        \n", results.m_memory_peak);
		printf("     Memory Start: 0x%llx            \n", results.m_memory_start);
		printf("     Time Elapsed: %llu ms           \n\n", results.m_time_elapsed.count());

	}
	AllocatorBenchmark::BenchmarkResults AllocatorBenchmark::BuildResults(Milliseconds elapsed_time)
	{
		BenchmarkResults results;

		results.m_op_per_ms   = (F64)elapsed_time.count() / (F64)m_allocator->GetNumOfAllocs();
		results.m_memory_used = ((F64)m_allocator->GetUsedMemory() / (F64)m_allocator->GetTotalSize()) * 100.0;

		results.m_operations  = m_allocator->GetNumOfAllocs();
		results.m_memory_size = m_allocator->GetTotalSize();
		results.m_memory_peak = m_allocator->GetPeakSize();

		results.m_memory_start = reinterpret_cast<INTPTR>(m_allocator->GetStartAddress());

		results.m_time_elapsed = elapsed_time;

		return results;
	}
	
	VOID AllocatorBenchmark::InitializeAllocator(ALLOCATOR_TYPE type, SIZE total_size)
	{
		switch (type)
		{
			/// case C_ALLOCATOR:        m_allocator = new LinearAllocator(total_size);
			case LINEAR_ALLOCATOR:   m_allocator = new LinearAllocator(total_size);
			case STACK_ALLOCATOR:    m_allocator = new StackAllocator(total_size);
			/// case POOL_ALLOCATOR:     m_allocator = new LinearAllocator(total_size);
			/// case FREELIST_ALLOCATOR: m_allocator = new LinearAllocator(total_size);
		}
	}
	
	VOID AllocatorBenchmark::SingleAllocation(SIZE size, BYTE alignment)
	{
		StartRound();
		m_allocator->Allocate(size, alignment);
		FinishRound();

		BenchmarkResults results = BuildResults(std::chrono::duration_cast<Milliseconds>(m_finish_time - m_start_time));
		PrintResults(results);
	}
	VOID AllocatorBenchmark::SingleDeallocation(SIZE size, BYTE alignment)
	{

	}
	VOID AllocatorBenchmark::MultipleAllocation(BYTE* size, BYTE alignment, SIZE size_count)
	{
		StartRound();
		for (int i = 0; i < size_count; i++)
			m_allocator->Allocate(size[i], alignment);
		FinishRound();

		BenchmarkResults results = BuildResults(std::chrono::duration_cast<Milliseconds>(m_finish_time - m_start_time));
		PrintResults(results);
			
	}
	VOID AllocatorBenchmark::MultipleDeallocation(BYTE* size, BYTE alignment, SIZE size_count)
	{

	}

#endif
