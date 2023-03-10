#include "Platform/Public/Windows/WindowsWindow.h"
#include "Platform/Public/Windows/WindowsPlatform.h"

#if defined(FORGE_PLATFORM_WINDOWS)

namespace Forge {
	namespace Platform
	{
		WindowsWindow::WindowsWindow(const WindowDesc& description)
			: AbstractWindow(description)
		{
			U32 window_style = 0, ex_window_style = 0;

			if (m_window_description.m_is_visable)
				window_style |= WS_VISIBLE;

			if (m_window_description.m_is_resizable &&
				!m_window_description.m_is_fullscreen)
				window_style |= WS_MAXIMIZEBOX | WS_THICKFRAME;

			if (m_window_description.m_is_decorated &&
				!m_window_description.m_is_fullscreen)
			{
				window_style |= WS_SYSMENU | WS_MINIMIZEBOX | WS_CAPTION | WS_BORDER;

				RECT windows_rect = { 0, 0, 
					m_window_description.m_client_size.x, 
					m_window_description.m_client_size.y 
				};

				AdjustWindowRectEx(&windows_rect, window_style, false, ex_window_style);

				m_window_description.m_client_position.x += windows_rect.left;
				m_window_description.m_client_position.y += windows_rect.top;

				m_window_description.m_client_size.x = windows_rect.right - windows_rect.left;
				m_window_description.m_client_size.y = windows_rect.bottom - windows_rect.top;
			}

			if (m_window_description.m_is_minimized &&
				!m_window_description.m_is_maximized &&
				!m_window_description.m_is_fullscreen)
				window_style |= WS_MINIMIZE;
			
			if (m_window_description.m_is_maximized &&
				!m_window_description.m_is_minimized &&
				!m_window_description.m_is_fullscreen)
				window_style |= WS_MAXIMIZE;

			if (m_window_description.m_is_fullscreen)
			{
				MONITORINFO monitor_info = { sizeof(monitor_info) };
				GetMonitorInfoW(MonitorFromWindow((HWND)m_window_handle, MONITOR_DEFAULTTONEAREST), &monitor_info);

				m_window_description.m_client_position.x = monitor_info.rcMonitor.left;
				m_window_description.m_client_position.y = monitor_info.rcMonitor.top;

				m_window_description.m_client_size.x = monitor_info.rcMonitor.right - monitor_info.rcMonitor.left;
				m_window_description.m_client_size.y = monitor_info.rcMonitor.bottom - monitor_info.rcMonitor.top;
			}

			if (m_window_description.m_is_transparent)
				ex_window_style |= WS_EX_LAYERED;

			if (!m_window_description.m_allow_minimize)
				window_style ^= WS_MINIMIZEBOX;

			if (!m_window_description.m_allow_maximize)
				window_style ^= WS_MAXIMIZEBOX;

			m_window_handle = CreateWindowExA(
				ex_window_style,
				Platform::GetInstance().m_application_window_class,
				m_window_description.m_window_title,
				window_style,
				m_window_description.m_client_position.x, m_window_description.m_client_position.y,
				m_window_description.m_client_size.x, m_window_description.m_client_size.y,
				m_window_description.m_window_parent ? (HWND)(m_window_description.m_window_parent->GetNativeHandle()) : nullptr,
				nullptr,
				(HINSTANCE)Platform::GetInstance().GetPlatformHandle(),
				nullptr
			);

			if (!m_window_description.m_allow_input)
				this->Deactivate();
		}

		Vector2 WindowsWindow::GetWindowSize(Void) const
		{
			// TODO: Impelemt WindowsWindow::GetClientSize
			return Vector2();
		}
		Vector2 WindowsWindow::GetWindowPosition(Void) const
		{
			// TODO: Impelemt WindowsWindow::GetClientPosition
			return Vector2();
		}
		RectangleF32 WindowsWindow::GetClientBounds(Void) const
		{
			// TODO: Impelemt WindowsWindow::GetClientBounds
			return RectangleF32();
		}

		Vector2 WindowsWindow::GetClientToScreen(Vector2 client_position) const
		{
			// TODO: Impelemt WindowsWindow::GetClientToScreen
			return Vector2();
		}
		Vector2 WindowsWindow::GetScreenToClient(Vector2 screen_position) const
		{
			// TODO: Impelemt WindowsWindow::GetScreenToClient
			return Vector2();
		}

		Void WindowsWindow::SetTitle(ConstCharPtr title)																// TODO: Change ConstCharPtr to const StringView&
		{
			// TODO: Impelemt WindowsWindow::SetTitle
		}

		Void WindowsWindow::SetOpacity(F32 opacity)
		{
			// TODO: Impelemt WindowsWindow::SetOpacity
		}

		Void WindowsWindow::SetClientSize(Vector2& size)
		{
			// TODO: Impelemt WindowsWindow::SetClientSize
		}
		Void WindowsWindow::SetWindowSize(Vector2& size)
		{
			// TODO: Impelemt WindowsWindow::SetWindowSize
		}
		Void WindowsWindow::SetClientPosition(Vector2& position)
		{
			// TODO: Impelemt WindowsWindow::SetClientPosition
		}
		Void WindowsWindow::SetWindowPosition(Vector2& position)
		{
			// TODO: Impelemt WindowsWindow::SetWindowPosition
		}
		Void WindowsWindow::SetClientBounds(RectangleF32& bounds)
		{
			// TODO: Impelemt WindowsWindow::SetClientBounds
		}

		Void WindowsWindow::SetCursorType(WindowCursorType cursor_type)
		{
			// TODO: Impelemt WindowsWindow::GetWindowCursorType
		}

		Void WindowsWindow::SetIsMovable(Bool is_movable)
		{
			// TODO: Impelemt WindowsWindow::SetIsMovable
		}
		Void WindowsWindow::SetIsResizable(Bool is_resizable)
		{
			// TODO: Impelemt WindowsWindow::SetIsResizable
		}
		Void WindowsWindow::SetIsFullscreen(Bool is_fullscreen)
		{
			// TODO: Impelemt WindowsWindow::SetIsFullscreen
		}
		Void WindowsWindow::SetIsTransparent(Bool is_transparent)
		{
			// TODO: Impelemt WindowsWindow::SetIsTransparent
		}

		Void WindowsWindow::Show(Void)
		{
			if (!m_cache_is_visible)
			{
				m_cache_is_visible = true;

				ShowWindow((HWND)m_window_handle, SW_SHOW);
			}
		}
		Void WindowsWindow::Hide(Void)
		{
			if (m_cache_is_visible)
			{
				m_cache_is_visible = false;

				ShowWindow((HWND)m_window_handle, SW_HIDE);
			}
		}
		Void WindowsWindow::Focus(Void)
		{
			if (!m_cache_is_focused)
			{
				m_cache_is_focused = true;

				BringWindowToTop((HWND)m_window_handle);
				SetForegroundWindow((HWND)m_window_handle);
				SetFocus((HWND)m_window_handle);
			}
		}
		Void WindowsWindow::Flash(Void)
		{
			if (m_cache_is_focused)
				return;

			FlashWindow((HWND)m_window_handle, true);
		}
		Void WindowsWindow::Minimize(Void)
		{
			if (!m_window_description.m_allow_minimize || 
				!m_cache_is_visible)
				return;

			m_cache_is_minimized = true;
			m_cache_is_maximized = false;

			ShowWindow((HWND)m_window_handle, SW_MINIMIZE);
		}
		Void WindowsWindow::Maximize(Void)
		{
			if (!m_window_description.m_allow_maximize ||
				!m_cache_is_visible)
				return;

			m_cache_is_maximized = true;
			m_cache_is_minimized = false;

			ShowWindow((HWND)m_window_handle, SW_MAXIMIZE);
		}
		Void WindowsWindow::Activate(Void)
		{
			EnableWindow((HWND)m_window_handle, true);
		}
		Void WindowsWindow::Deactivate(Void)
		{
			EnableWindow((HWND)m_window_handle, false);
		}
		Void WindowsWindow::BringToFront(Void)
		{
			// TODO: Impelemt WindowsWindow::BringToFront
		}
		Void WindowsWindow::Close(WindowClosingReason window_closing_reason)
		{
			// TODO: Impelemt WindowsWindow::Close
		}
	}
}

#endif
