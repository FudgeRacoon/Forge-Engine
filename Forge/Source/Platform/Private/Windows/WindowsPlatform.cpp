#include "Platform/Public/Windows/WindowsPlatform.h"

#if defined(FORGE_PLATFORM_WINDOWS)

namespace Forge {
	namespace Platform
	{
		namespace Internal
		{
			DWORD CountSetBits(ULONG_PTR bitMask)
		{
			DWORD LSHIFT = sizeof(ULONG_PTR) * 8 - 1;
			DWORD bitSetCount = 0;
			ULONG_PTR bitTest = (ULONG_PTR)1 << LSHIFT;
			DWORD i;

			for (i = 0; i <= LSHIFT; ++i)
			{
				bitSetCount += ((bitMask & bitTest) ? 1 : 0);
				bitTest /= 2;
			}

			return bitSetCount;
		}
			LRESULT CALLBACK MainWndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)    // second message parameter
			{
				switch (uMsg)
				{
				case WM_CLOSE:
					DestroyWindow(hwnd);
					break;
				case WM_DESTROY:
					PostQuitMessage(0);
					break;
				default:
					return DefWindowProc(hwnd, uMsg, wParam, lParam);
				}
			}
		}

		WindowsPlatform::MemoryStats WindowsPlatform::GetMemoryStats(Void)
		{
			// TODO: Implement WindowsPlatform::GetMemoryStats
			return MemoryStats();
		}
		WindowsPlatform::ProcessMemoryStats WindowsPlatform::GetProcessMemoryStats(Void)
		{
			// TODO: Implement WindowsPlatform::GetProcessMemoryStats
			return ProcessMemoryStats();
		}

		I32 WindowsPlatform::GetPrimaryMonitorDPI(Void)
		{
			// TODO: Implement WindowsPlatform::GetPrimaryMonitorDPI
			return 0;
		}
		F32 WindowsPlatform::GetPrimiaryMonitorDPIScale(Void)
		{
			// TODO: Implement WindowsPlatform::GetPrimiaryMonitorDPIScale
			return 0;
		}
		Vector2 WindowsPlatform::GetPrimaryMonitorSize(Void)
		{
			return Vector2(
				static_cast<float>(GetSystemMetrics(SM_CXSCREEN)),
				static_cast<float>(GetSystemMetrics(SM_CYSCREEN))
			);
		}
		Vector2 WindowsPlatform::GetVirtualMonitorSize(Void)
		{
			// TODO: Implement WindowsPlatform::GetVirtualMonitorSize
			return Math::Vector2();
		}

		U64 WindowsPlatform::GetCurrentThreadID(Void)
		{
			// TODO: Implement WindowsPlatform::GetCurrentThreadID
			return 1;
		}
		U64 WindowsPlatform::GetCurrentProcessID(Void)
		{
			// TODO: Implement WindowsPlatform::GetCurrentProcessID
			return 1;
		}

		U64 WindowsPlatform::GetSystemTimeCycles(Void)
		{
			// TODO: Implement WindowsPlatform::GetSystemTimeCycles
			return 1;
		}
		F64 WindowsPlatform::GetSystemTimeSeconds(Void)
		{
			// TODO: Implement WindowsPlatform::GetSystemTimeSeconds
			return 1;
		}
		Void WindowsPlatform::GetSystemTimeDate(I32& year, I32& month, I32& week,
												I32& day, I32& hour, I32& minute, I32& second, I32& millisecond)
		{
			// TODO: Implement WindowsPlatform::GetSystemTimeDate
		}

		Bool WindowsPlatform::Initialize(VoidPtr handle)
		{
			m_instance_handle = handle;

			{
				HKEY key_handle;

				U64 byte_offset   = 0;
				U64 return_length = 0;

				Bool succesful = false;
				
				U64 processor_core_count      = 0;
				U64 processor_clock_speed     = 0;
				U64 processor_logical_count   = 0;
				U64 processor_package_count   = 0;
				U64 processor_l1_cache_size   = 0;
				U64 processor_l2_cache_size   = 0;
				U64 processor_l3_cache_size   = 0;
				U64 processor_cache_line_size = 0;

				PCACHE_DESCRIPTOR cache_descriptor;

				PSYSTEM_LOGICAL_PROCESSOR_INFORMATION ptr    = nullptr;
				PSYSTEM_LOGICAL_PROCESSOR_INFORMATION buffer = nullptr;

				U64 processor_clock_speed_buffer_size = sizeof(processor_clock_speed);

				RegOpenKeyExA(HKEY_LOCAL_MACHINE, (LPCSTR)"HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0", NULL, KEY_READ, &key_handle);
				RegQueryValueExA(key_handle, "~MHz", NULL, NULL, (LPBYTE)&processor_clock_speed, (LPDWORD)&processor_clock_speed_buffer_size);

				while (!succesful)
				{
					if (!GetLogicalProcessorInformation(buffer, (LPDWORD)&return_length))
					{
						if (GetLastError() == ERROR_INSUFFICIENT_BUFFER)
						{
							if (buffer)
								DeallocateMemory(buffer);
							else
								buffer = static_cast<PSYSTEM_LOGICAL_PROCESSOR_INFORMATION>(AllocateMemory(return_length, 8));
						}
						else
						{
							// TODO: Throw Exception.
						}
					}
					else
						succesful = true;
				}

				ptr = buffer;

				while (byte_offset + sizeof(SYSTEM_LOGICAL_PROCESSOR_INFORMATION) <= return_length)
				{
					switch (ptr->Relationship)
					{
					case RelationProcessorCore:
					{
						processor_core_count++;
						processor_logical_count += Internal::CountSetBits(ptr->ProcessorMask);
						break;
					}
					case RelationCache:
					{
						cache_descriptor = &ptr->Cache;

						if (cache_descriptor->Level == 1)
							processor_l1_cache_size += cache_descriptor->Size;
						else if (cache_descriptor->Level == 2)
							processor_l2_cache_size += cache_descriptor->Size;
						else if (cache_descriptor->Level == 3)
							processor_l3_cache_size += cache_descriptor->Size;

						processor_cache_line_size = cache_descriptor->LineSize;

						break;
					}
					case RelationProcessorPackage:
					{
						processor_package_count++;
						break;
					}
					}

					ptr++;
					byte_offset += sizeof(SYSTEM_LOGICAL_PROCESSOR_INFORMATION);
				}

				m_cpu_info.processor_core_count      = processor_core_count;
				m_cpu_info.processor_clock_speed     = processor_clock_speed / 1000.0f;
				m_cpu_info.processor_logical_count   = processor_logical_count;
				m_cpu_info.processor_package_count   = processor_package_count;
				m_cpu_info.processor_l1_cache_size   = processor_l1_cache_size;
				m_cpu_info.processor_l2_cache_size   = processor_l2_cache_size;
				m_cpu_info.processor_l3_cache_size   = processor_l3_cache_size;
				m_cpu_info.processor_cache_line_size = processor_cache_line_size;
			}
			
			{
				WNDCLASS window_class;

				MemorySet(&window_class, 0, sizeof(WNDCLASS));

				window_class.style         = CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
				window_class.lpfnWndProc   = Internal::MainWndProc;
				window_class.cbClsExtra    = 0;
				window_class.cbWndExtra    = 0;
				window_class.hInstance     = (HINSTANCE)handle;
				window_class.hIcon         = LoadIcon(nullptr, IDI_APPLICATION);
				window_class.hCursor       = LoadCursor(nullptr, IDC_ARROW);
				window_class.hbrBackground = nullptr;
				window_class.lpszMenuName  = nullptr;
				window_class.lpszClassName = m_application_window_class;

				if (!RegisterClass(&window_class));
				{
					// TODO: Throw Exception.
				}
			}

			{
				DWORD return_length;

				m_user_name = (CharPtr)AllocateMemory(256, 8);
				if (!GetUserNameW((LPWSTR)m_user_name, &return_length));
				{
					// TODO: Throw Exception.
				}

				m_locale_name = (CharPtr)AllocateMemory(256, 8);
				if (!GetUserDefaultLocaleName((LPWSTR)m_locale_name, LOCALE_NAME_MAX_LENGTH));
				{
					// TODO: Throw Exception.
				}

				m_machine_name = (CharPtr)AllocateMemory(256, 8);
				if (!GetComputerNameW((LPWSTR)m_machine_name, &return_length));
				{
					// TODO: Throw Exception.
				}
			}
			
			return true;
		}
		Bool WindowsPlatform::Terminate(Void)
		{
			DeallocateMemory(m_user_name);
			DeallocateMemory(m_locale_name);
			DeallocateMemory(m_machine_name);

			if (!UnregisterClassW((LPCWSTR)m_application_window_class, (HINSTANCE)m_instance_handle));
				return false;

			return true;
		}
		Bool WindowsPlatform::PumpMessages(Void)
		{
			MSG msg;

			while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}

			return true;
		}

		Void WindowsPlatform::PrefetchMemory(VoidPtr address)
		{
			// TODO: Implement WindowsPlatform::PrefetchMemory
		}
		VoidPtr WindowsPlatform::AllocateMemory(Size size, Size alignment)
		{
			return malloc(size);
		}
		Void WindowsPlatform::DeallocateMemory(VoidPtr address)
		{
			// TODO: Implement WindowsPlatform::DeallocateMemory
		}
		VoidPtr WindowsPlatform::AllocatePages(Size count, Size size)
		{
			// TODO: Implement WindowsPlatform::AllocatePages
			return nullptr;
		}
		Void WindowsPlatform::DeallocatePages(VoidPtr address)
		{
			// TODO: Implement WindowsPlatform::DeallocatePages
		}

		I32 WindowsPlatform::StartProcess(ConstCharPtr filename, ConstCharPtr args, ConstCharPtr working_directory)
		{
			// TODO: Implement WindowsPlatform::CreateProcess
			return 0;
		}
		I32 WindowsPlatform::ExecuteProcess(ConstCharPtr filename, ConstCharPtr args, ConstCharPtr working_directory)
		{
			// TODO: Implement WindowsPlatform::ExecuteProcess
			return 0;
		}

		WindowPtr WindowsPlatform::ConstructWindow(WindowDesc& description)
		{
			return new WindowsWindow(description);
		}
		WindowPtr WindowsPlatform::ConstructWindow(ConstCharPtr title)
		{
			WindowDesc description;

			description.m_window_title = title;

			return new WindowsWindow(description);
		}
		WindowPtr WindowsPlatform::ConstructWindow(ConstCharPtr title, const Vector2& position)
		{
			WindowDesc description;

			description.m_window_title = title;
			description.m_client_position = position;

			return new WindowsWindow(description);
		}
		WindowPtr WindowsPlatform::ConstructWindow(ConstCharPtr title, const Vector2& position, const Vector2& size)
		{
			WindowDesc description;

			description.m_window_title = title;
			description.m_client_position = position;
			description.m_client_size = size;

			return new WindowsWindow(description);
		}

		VoidPtr WindowsPlatform::LoadExternalLibrary(ConstCharPtr filename)
		{
			// TODO: Implement WindowsPlatform::LoadLibrary
			return nullptr;
		}
		Bool WindowsPlatform::FreeExternalLibrary(VoidPtr handle)
		{
			// TODO: Implement WindowsPlatform::FreeLibrary
			return false;
		}
		VoidPtr WindowsPlatform::GetExternalLibrarySymbol(VoidPtr handle, ConstCharPtr symbol)
		{
			// TODO: Implement WindowsPlatform::GetLibrarySymbol
			return nullptr;
		}

		Void WindowsPlatform::Sleep(I32 milliseconds)
		{
			// TODO: Implement WindowsPlatform::Sleep
		}
	}
}

#endif
