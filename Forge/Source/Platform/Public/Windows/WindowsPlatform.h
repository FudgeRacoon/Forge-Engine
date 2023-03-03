#ifndef WINDOWS_PLATFORM_H
#define WINDOWS_PLATFORM_H

#include "Platform/Public/Base/AbstractPlatform.h"

#if defined(FORGE_PLATFORM_WINDOWS)

namespace Forge {
	namespace Platform
	{
		class FORGE_API WindowsPlatform : public AbstractPlatform
		{
		public:
			/**
			* @brief Gets the system CPU information.
			*
			* @returns CPUInfo storing CPU information.
			*/
			CPUInfo GetCPUInfo(Void) override;

			/**
			 * @brief Gets the system memory statistics.
			 *
			 * @returns MemoryStats storing memory statistics.
			 */
			MemoryStats GetMemoryStats(Void) override;

			/**
			 * @brief Gets the current process memory statistics.
			 *
			 * @returns ProcessMemoryStats storing memory statistics.
			 */
			ProcessMemoryStats GetProcessMemoryStats(Void) override;

		public:
			/**
			 * @brief Gets the size of the primary display monitor in pixels.
			 *
			 * @returns Vector2 storing the size of the primary display monitor.
			 */
			Vector2 GetPrimaryMonitorSize(Void) override;

		public:
			/**
			 * @brief Gets the current thread unique identifier.
			 *
			 * @returns U64 storing the thread unique identifier.
			 */
			U64 GetCurrentThreadID(Void) override;

			/**
			 * @brief Gets the current process unique identifier.
			 *
			 * @returns U64 storing the process unique identifier.
			 */
			U64 GetCurrentProcessID(Void) override;

		public:
			/**
			 * @brief Gets the current time as CPU cycles counter.
			 *
			 * @returns U64 storing the CPU cycles counter value.
			 */
			U64 GetSystemTimeCycles(Void) override;

			/**
			 * @brief Gets the current time in seconds.
			 *
			 * @returns U64 storing the time in seconds.
			 */
			F64 GetSystemTimeSeconds(Void) override;

			/**
			 * @brief Gets the current system time based on the computer
			 * settings.
			 *
			 * @param year The result year value.
			 * @param month The result month value.
			 * @param week The result week value.
			 * @param day The result day value.
			 * @param hour The result hour value.
			 * @param minute The result minute value.
			 * @param second The result second value.
			 * @param millisecond The result millisecond value.
			 */
			Void GetSystemTimeDate(I32& year, I32& month, I32& week,
				I32& day, I32& hour, I32& minute, I32& second, I32& millisecond) override;

		public:
			/**
			 * @brief Initializes the runtime platform service.
			 *
			 * This function should be called at the very start of the engine start up.
			 *
			 * @returns True if platform initialization was succesful, otherwise false.
			 */
			Bool Initialize(Void) override;

			/**
			 * @brief Terminates the runtime platform service.
			 *
			 * This function should be called at the very end of the engine shut down.
			 *
			 * @returns True if platform termination was succesful, otherwise false.
			 */
			Bool Terminate(Void) override;

			/**
			 * @brief Retrieves messages from the platform message queue and
			 * dispatches them to the window associated with the current thread.
			 *
			 * In order to recieve system and input events this function should
			 * be called inside the engine main loop.
			 */
			Void PumpMessages(Void) override;

		public:
			/**
			 * @brief Allocates a block of memory with a specified alignment
			 * boundry.
			 *
			 * This function allocates memory on the heap memory segment using the
			 * platform dependant allocation routine.
			 *
			 * @param size The number of bytes to allocate.
			 * @param alignment The alignment boundry of the allocated memory block.
			 *
			 * @returns VoidPtr storing the address of the allocated memory block.
			 */
			VoidPtr AllocateMemory(Size size, Size alignment) override;

			/**
			 * @brief Deallocates a block of allocated memory.
			 *
			 * This function deallocates memory on the heap memory segment using
			 * the platform dependant deallocation routine.
			 *
			 * @param address The address of the allocated memory block.
			 */
			Void DeallocateMemory(VoidPtr address) override;

			/**
			 * @brief Allocates a number of pages with a specified size.
			 *
			 * This function allocates pages on the memory using the
			 * platform dependant allocation routine.
			 *
			 * @param count The number of pages to allocate.
			 * @param size The size of the allocated page in bytes.
			 *
			 * @returns VoidPtr storing the address of the allocated pages.
			 */
			VoidPtr AllocatePages(Size count, Size size) override;

			/**
			 * @brief Deallocates a block of allocated pages.
			 *
			 * This function deallocates pages on the memory segment using
			 * the platform dependant deallocation routine.
			 *
			 * @param address The address of the allocated pages.
			 */
			Void DeallocatePages(VoidPtr address) override;
		};
	}
}

#endif

#endif
