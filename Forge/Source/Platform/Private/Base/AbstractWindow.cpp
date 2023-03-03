#include "Platform/Public/Platform.h"
#include "Platform/Public/Base/AbstractWindow.h"

namespace Forge {
	namespace Platform
	{
		AbstractWindow::AbstractWindow(const WindowDesc& description)
			: m_window_handle(nullptr), m_window_description(description)
		{

			if (m_window_description.m_window_start_position == WindowStartPositionMode::CENTER_SCREEN ||
				m_window_description.m_window_start_position == WindowStartPositionMode::CENTER_PARENT)
			{
				Math::TRectangle<U32> parent_bounds = Math::TRectangle<U32>({ 0, 0 }, Platform::GetInstance().GetPrimaryMonitorSize());

				if (m_window_description.m_window_parent != nullptr &&
					m_window_description.m_window_start_position == WindowStartPositionMode::CENTER_PARENT)
					parent_bounds = m_window_description.m_window_parent->GetClientBounds();

				m_window_description.m_window_position = parent_bounds.GetTopLeft() + (parent_bounds.GetSize() - m_window_description.m_window_size) * 0.5f;
			}
		}

		ConstVoidPtr AbstractWindow::GetNativeHandle(Void)
		{
			return m_window_handle;
		}
		WindowDesc AbstractWindow::GetWindowDescription(Void)
		{
			return m_window_description;
		}

		String AbstractWindow::GetTitle(Void) const
		{
			return m_window_description.m_window_title;
		}
		F32 AbstractWindow::GetOpacity(Void) const
		{
			return m_window_description.m_window_opacity;
		}
		Vector2 AbstractWindow::GetWindowSize(Void) const
		{
			return m_window_description.m_window_size;
		}
		Vector2 AbstractWindow::GetWindowMinSize(Void) const
		{
			return m_window_description.m_window_min_size;
		}
		Vector2 AbstractWindow::GetWindowMaxSize(Void) const
		{
			return m_window_description.m_window_max_size;
		}
		Vector2 AbstractWindow::GetWindowPosition(Void) const
		{
			return m_window_description.m_window_position;
		}

		Bool AbstractWindow::IsVisable(Void) const
		{
			return m_window_description.m_is_visable;
		}
		Bool AbstractWindow::IsMovable(Void) const
		{
			return m_window_description.m_is_movable;
		}
		Bool AbstractWindow::IsResizable(Void) const
		{
			return m_window_description.m_is_resizable;
		}
		Bool AbstractWindow::IsMinimized(Void) const
		{
			return m_window_description.m_is_minimized;
		}
		Bool AbstractWindow::IsMaximized(Void) const
		{
			return m_window_description.m_is_maximized;
		}
		Bool AbstractWindow::IsFullscreen(Void) const
		{
			return m_window_description.m_is_fullscreen;
		}
		Bool AbstractWindow::IsBorderless(Void) const
		{
			return m_window_description.m_is_borderless;
		}
		Bool AbstractWindow::IsTransparent(Void) const
		{
			return m_window_description.m_is_transparent;
		}
	}
}
