#ifndef ABSTRACT_PLATFORM
#define ABSTRACT_PLATFORM

#include "Core/Public/Common/Common.h"

#include "Core/Public/Types/Singleton.h"

namespace Forge {
	namespace Platform
	{
		enum class PlatformType
		{
			/**
			 * @brief Running on mac platform.
			 */
			PLATFORM_MAC = 1,

			/**
			 * @brief Running on linux platform.
			 */
			PLATFORM_LINUX = 2,

			/**
			 * @brief Running on android platform.
			 */
			PLATFORM_ANDROID = 3,

			/**
			 * @brief Running on windows platform.
			 */
			PLATFORM_WINDOWS = 4,
		};

		enum class ArchitectureType
		{
			/**
			 * @brief Running on x86 32-bit.
			 */
			ARCHITECTURE_X86 = 1,

			/**
			 * @brief Running on x86 64-bit.
			 */
			ARCHITECTURE_X64 = 2,

			/**
			 * @brief Running on ARM 32-bit.
			 */
			ARCHITECTURE_ARM = 3,

			/**
			 * @brief Running on ARM 64-bit.
			 */
			ARCHITECTURE_ARM64 = 4
		};

		class FORGE_API AbstractPlatform : public Forge::TSingleton<AbstractPlatform>
		{
		FORGE_CLASS_SINGLETON(AbstractPlatform)

		public:
			struct CPUInfo
			{
				/**
				 * @brief The CPU clock speed in Hz.
				 */
				U32 processor_clock_speed = 0;

				/**
				 * @brief The number of physical processor cores.
				 */
				U32 processor_core_count = 0;

				/**
				 * @brief The number of logical processor cores.
				 */
				U32 logical_processor_count = 0;
				
				/**
				 * @brief The number of physical processor packages.
				 */
				U32 processor_package_count = 0;

				/**
				 * @brief The size of L1 processor cache in bytes.
				 */
				U32 processor_l1_cache_count = 0;

				/**
				 * @brief The size of L2 processor cache in bytes.
				 */
				U32 processor_l2_cache_count = 0;

				/**
				 * @brief The size of L3 processor cache in bytes.
				 */
				U32 processor_l3_cache_count = 0;

				/**
				 * @brief The processor cache line size in bytes.
				 */
				U32 processor_cache_line_size = 0;
			};

			struct MemoryStats
			{
				/**
				 * @brief The amount of total physical memory in bytes.
				 */
				U32 total_physical_memory = 0;

				/**
				 * @brief The amount of used physical memory in bytes.
				 */
				U32 used_physical_memory = 0;

				/**
				 * @brief The amount of total virtual memory in bytes.
				 */
				U32 total_virtual_memory = 0;

				/**
				 * @brief The amount of used virtual memory in bytes.
				 */
				U32 used_virtual_memory = 0;
			};

			struct ProcessMemoryStats
			{
				/**
				 * @brief The amount of used physical memory in bytes.
				 */
				U32 used_physical_memory = 0;

				/**
				 * @brief The amount of used virtual memory in bytes.
				 */
				U32 used_virtual_memory = 0;
			};

		public:
			/**
			 * @brief Logs the current system information to a log appender.
			 *
			 * This function should be called after the platform service has
			 * been initialized.
			 */
			Void LogSystemInfo(Void);

			/**
			 * @brief Shows an information message to the user.
			 *
			 * This function creates a platform native message box that displays
			 * the message sent as an information.
			 *
			 * @param message The information message to display.
			 */
			Void Info(ConstCharPtr message); // TODO: Change ConstCharPtr to const StringView&

			/**
			 * @brief Shows a warning message to the user.
			 *
			 * This function creates a platform native message box that displays
			 * the message sent as a warning.
			 *
			 * @param message The warning message to display.
			 */
			Void Warn(ConstCharPtr message); // TODO: Change ConstCharPtr to const StringView&

			/**
			 * @brief Shows an error message to the user.
			 *
			 * This function creates a platform native message box that displays
			 * the message sent as an error.
			 *
			 * @param message The error message to display.
			 */
			Void Error(ConstCharPtr message); // TODO: Change ConstCharPtr to const StringView&

			/**
			 * @brief Shows a fatal message to the user.
			 *
			 * This function creates a platform native message box that displays
			 * the message sent as a fatal error, it then creates a stacktrace
			 * and a minidump to be logged to an appender and exits the program.
			 *
			 * @param message The fatal message to display.
			 * @param context The platform dependent context for stacktrace and
			 * minidump collecting.
			 */
			Void Fatal(ConstCharPtr message, VoidPtr context); // TODO: Change ConstCharPtr to const StringView&

		public:
			/**
			 * @brief Gets the current runtime platform type.
			 * 
			 * @returns PlatformType storing the platform type.
			 */
			PlatformType GetPlatformType(Void);

			/**
			 * @brief Gets the current system architecture type.
			 *
			 * @returns ArchitectureType storing the architecture type.
			 */
			ArchitectureType GetArchitectureType(Void);

		public:
			/**
			 * @brief Gets the system CPU information.
			 * 
			 * @returns CPUInfo storing CPU information.
			 */
			virtual CPUInfo GetCPUInfo(Void) = 0;

			/**
			 * @brief Gets the system memory statistics.
			 *
			 * @returns MemoryStats storing memory statistics.
			 */
			virtual MemoryStats GetMemoryStats(Void) = 0;

			/**
			 * @brief Gets the current process memory statistics.
			 *
			 * @returns ProcessMemoryStats storing memory statistics.
			 */
			virtual ProcessMemoryStats GetProcessMemoryStats(Void) = 0;

		public:
			/**
			 * @brief Gets the size of the primary display monitor in pixels.
			 * 
			 * @returns Vector2 storing the size of the primary display monitor.
			 */
			virtual Vector2 GetPrimaryMonitorSize(Void) = 0;

		public:
			/**
			 * @brief Gets the current thread unique identifier.
			 * 
			 * @returns U64 storing the thread unique identifier.
			 */
			virtual U64 GetCurrentThreadID(Void) = 0;

			/**
			 * @brief Gets the current process unique identifier.
			 *
			 * @returns U64 storing the process unique identifier.
			 */
			virtual U64 GetCurrentProcessID(Void) = 0;

		public:
			/**
			 * @brief Gets the current time as CPU cycles counter.
			 * 
			 * @returns U64 storing the CPU cycles counter value. 
			 */
			virtual U64 GetSystemTimeCycles(Void) = 0;

			/**
			 * @brief Gets the current time in seconds.
			 *
			 * @returns U64 storing the time in seconds.
			 */
			virtual F64 GetSystemTimeSeconds(Void) = 0;

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
			virtual Void GetSystemTimeDate(I32& year, I32& month, I32& week, 
				                           I32& day, I32& hour, I32& minute, I32& second, I32& millisecond) = 0;

		public:
			/**
			 * @brief Initializes the runtime platform service.
			 *
			 * This function should be called at the very start of the engine start up.
			 *
			 * @returns True if platform initialization was succesful, otherwise false.
			 */
			virtual Bool Initialize(Void) = 0;

			/**
			 * @brief Terminates the runtime platform service.
			 *
			 * This function should be called at the very end of the engine shut down.
			 *
			 * @returns True if platform termination was succesful, otherwise false.
			 */
			virtual Bool Terminate(Void) = 0;

			/**
			 * @brief Retrieves messages from the platform message queue and
			 * dispatches them to the window associated with the current thread.
			 *
			 * In order to recieve system and input events this function should
			 * be called inside the engine main loop.
			 */
			virtual Void PumpMessages(Void) = 0;

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
			virtual VoidPtr AllocateMemory(Size size, Size alignment) = 0;

			/**
			 * @brief Deallocates a block of allocated memory.
			 *
			 * This function deallocates memory on the heap memory segment using 
			 * the platform dependant deallocation routine.
			 *
			 * @param address The address of the allocated memory block.
			 */
			virtual Void DeallocateMemory(VoidPtr address) = 0;

			/**
			 * @brief Allocates a number of pages with a specified size.
			 *
			 * This function allocates pages on the virtual memory using the
			 * platform dependant allocation routine.
			 *
			 * @param count The number of pages to allocate.
			 * @param size The size of the allocated page in bytes.
			 *
			 * @returns VoidPtr storing the address of the allocated pages.
			 */
			virtual VoidPtr AllocatePages(Size count, Size size) = 0;

			/**
			 * @brief Deallocates a block of allocated pages.
			 *
			 * This function deallocates pages on the virtual memory segment using
			 * the platform dependant deallocation routine.
			 * 
			 * @param address The address of the allocated pages.
			 */
			virtual Void DeallocatePages(VoidPtr address) = 0;
		};
	}
}

#endif
