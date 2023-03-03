#ifndef WINDOW_DESC_H
#define WINDOW_DESC_H

#include "Core/Public/Types/TPair.h"
#include "Core/Public/Common/Common.h"

typedef const char* String;
typedef Forge::TPair<Forge::F32, Forge::F32> Vector2;

namespace Forge {
	namespace Platform
	{
		class AbstractWindow;
		typedef AbstractWindow		Window, *WindowPtr;

		enum class WindowCursorType
		{
			/**
			 * @brief Standard arrow.
			 */
			FORGE_ENUM_DECL(ARROW, 0x0)

			/**
			 * @brief Crosshair.
			 */
			FORGE_ENUM_DECL(CROSS, 0x1)

			/**
			 * @brief Hand.
			 */
			FORGE_ENUM_DECL(HAND, 0x2)

			/**
			 * @brief Arrow and question mark.
			 */
			FORGE_ENUM_DECL(HELP, 0x3)

			/**
			 * @brief I-beam.
			 */
			FORGE_ENUM_DECL(IBEAM, 0x4)

			/**
			 * @brief Slashed circle.
			 */
			FORGE_ENUM_DECL(NO, 0x5)

			/**
			 * @brief Four-pointed arrow pointing north, south, east, and west.
			 */
			FORGE_ENUM_DECL(SIZE_ALL, 0x6)

			/**
			 * @brief Double-pointed arrow pointing northeast and southwest.
			 */
			FORGE_ENUM_DECL(SIZE_NESW, 0x7)

			/**
			 * @brief Double-pointed arrow pointing north and south.
			 */
			FORGE_ENUM_DECL(SIZE_NS, 0x8)

			/**
			 * @brief Double-pointed arrow pointing northwest and southeast.
			 */
			FORGE_ENUM_DECL(SIZE_NWSE, 0x9)

			/**
			 * @brief Double-pointed arrow pointing west and east.
			 */
			FORGE_ENUM_DECL(SIZE_WE, 0x10)

			/**
			 * @brief Vertical arrow.
			 */
			FORGE_ENUM_DECL(UP_ARROW, 0x11)

			/**
			 * @brief Hourglass.
			 */
			FORGE_ENUM_DECL(WAIT, 0x12)

			MAX
		};

		enum class WindowStartPositionMode
		{
			/**
			 * @brief The position of the window is determined by the position
			 * property.
			 */
			FORGE_ENUM_DECL(MANUAL, 0x0)

			/**
			 * @brief The position of the window is centered on the current
			 * display.
			 */
			FORGE_ENUM_DECL(CENTER_SCREEN, 0x1)

			/**
			 * @brief The position of the window is centered within the bounds of
			 * its parent window.
			 */
			FORGE_ENUM_DECL(CENTER_PARENT, 0x2)

			MAX
		};

		struct WindowDesc
		{
			/**
			 * @brief The window title.
			 */
			String m_window_title;
			
			/**
			 * @brief The window opacity if transaprency is supported.
			 */
			F32 m_window_opacity = 1.0f;

			/**
			 * @brief The parent window pointer to this window.
			 */
			WindowPtr m_window_parent = nullptr;

			/**
			 * @brief The type of cursor used by this window. 
			 */
			WindowCursorType m_window_cursor_type = WindowCursorType::ARROW;

			/**
			 * @brief The starting position mode of this window.
			 */
			WindowStartPositionMode m_window_start_position = WindowStartPositionMode::MANUAL;

			/**
			 * @brief The window size including border.
			 */
			Vector2 m_window_size = { 640, 480 };

			/**
			 * @brief The window minimum size including border.
			 */
			Vector2 m_window_min_size = { 100, 100 };
			
			/**
			 * @brief The window maximum size including border.
			 */
			Vector2 m_window_max_size = { 7680, 4320 };
			
			/**
			 * @brief The window position in screen coordinates.
			 */
			Vector2 m_window_position = { 100, 400 };

			/**
			 * @brief Is the window visible?
			 */
			Bool m_is_visable = true;
			
			/**
			 * @brief Is the window movable?
			 */
			Bool m_is_movable = true;
			
			/**
			 * @brief Is the window resizable?
			 */
			Bool m_is_resizable = true;

			/**
			 * @brief Is the window minimized?
			 */
			Bool m_is_minimized = false;
			
			/**
			 * @brief Is the window maximized?
			 */
			Bool m_is_maximized = false;
			
			/**
			 * @brief Is the window in fullscreen mode?
			 */
			Bool m_is_fullscreen = false;
			
			/**
			 * @brief Is the window borderless?
			 */
			Bool m_is_borderless = false;
			
			/**
			 * @brief Is the window transparent?
			 */
			Bool m_is_transparent = false;
		};
	}
}

#endif
