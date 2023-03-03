#ifndef ABSTRACT_WINDOW_H
#define ABSTRACT_WINDOW_H

#include "../WindowDesc.h"

#include "Core/Public/Common/Common.h"
#include "Core/Public/Math/TRectangle.h"
#include "Core/Public/Types/TDelegate.h"

namespace Forge {
	namespace Platform
	{
		enum class WindowClosingReason
		{
			/**
			 * @brief Unknown
			 */
			FORGE_ENUM_DECL(UNKNOWN,     0x0)
			
			/**
			 * @brief Window was closed by user.
			 */
			FORGE_ENUM_DECL(USER,        0x1)

			/**
			 * @brief Window was closed due to engine exit.
			 */
			FORGE_ENUM_DECL(ENGINE_EXIT, 0x2)

			/**
			 * @brief Window was closed due to a close event.
			 */
			FORGE_ENUM_DECL(CLOSE_EVENT, 0x3)

			MAX
		};

		class FORGE_API AbstractWindow
		{
		protected:
			VoidPtr m_window_handle;

		protected:
			WindowDesc m_window_description;

		public:
			/**
			 * @brief Default constructor.
			 * 
			 * Creates a platform dependant window using a description structure.
			 * 
			 * @param description The window description.
			 */
			explicit AbstractWindow(const WindowDesc& description);

			/**
			 * @brief Destructor.
			 */
			virtual ~AbstractWindow(Void) = default;

		public:
			/**
			 * @brief Gets the platform dependant native window handle.
			 * 
			 * @returns ConstVoidPtr storing the address of the window handle.
			 */
			ConstVoidPtr GetNativeHandle(Void);

			/**
			 * @brief Gets the window description associated with this window.
			 * 
			 * @returns WindowDesc storing this window description.
			 */
			WindowDesc GetWindowDescription(Void);

		public:
			/**
			 * @brief Gets the window title.
			 * 
			 * @returns String storing the window title.
			 */
			String GetTitle(Void) const;

			/**
			 * @brief Gets the window opacity.
			 * 
			 * This function is valid only for windows with the is_transparent
			 * flag set to true.
			 * 
			 * @returns F32 storing the opacity value of the window normalized
			 * between 0 and 1.
			 */
			F32 GetOpacity(Void) const;
	
			/**
			 * @brief Gets the window size including border.
			 * 
			 * @returns Vector2 storing the window size including border.
			 */
			Vector2 GetWindowSize(Void) const;

			/**
			 * @brief Gets the window minimum size including border.
			 *
			 * @returns Vector2 storing the window minimum size including border.
			 */
			Vector2 GetWindowMinSize(Void) const;

			/**
			 * @brief Gets the window maximum size including border.
			 *
			 * @returns Vector2 storing the window maximum size including border.
			 */
			Vector2 GetWindowMaxSize(Void) const;

			/**
			 * @brief Gets the window position in screen coordinates.
			 * 
			 * @returns Vector2 storing the window position in screen coordinates. 
			 */
			Vector2 GetWindowPosition(Void) const;

		public:
			/**
		    * @brief Gets the client area size of the window not including border.
		    *
		    * @returns Vector2 storing the client area size of the window not
		    * including border.
		    */
			virtual Vector2 GetClientSize(Void) const = 0;

			/**
			 * @brief Gets the client bounds of the window not including border.
			 *
			 * @returns Rectangle storing the client bounds of the window not
			 * including border.
			 */
			virtual Math::TRectangle<U32> GetClientBounds(Void) const = 0;

		public:
			/**
			 * @brief Checks if the window is visible or hidden.
			 * 
			 * @returns True if the window is visible, otherwise false.
			 */
			Bool IsVisable(Void) const;

			/**
			 * @brief Checks if the window is movable or fixed.
			 *
			 * @returns True if the window is movable, otherwise false.
			 */
			Bool IsMovable(Void) const;

			/**
			 * @brief Checks if the window is resizable or or not.
			 *
			 * @returns True if the window is resizable, otherwise false.
			 */
			Bool IsResizable(Void) const;

			/**
			 * @brief Checks if the window is minimized or maximized.
			 *
			 * @returns True if the window is minimized, otherwise false.
			 */
			Bool IsMinimized(Void) const;

			/**
			 * @brief Checks if the window is maximized or minimized.
			 *
			 * @returns True if the window is maximized, otherwise false.
			 */
			Bool IsMaximized(Void) const;

			/**
			 * @brief Checks if the window is fullscreen or not.
			 *
			 * @returns True if the window is fullscreen, otherwise false.
			 */
			Bool IsFullscreen(Void) const;

			/**
			 * @brief Checks if the window is borderless or not.
			 * 
			 * @returns True if the window is borderless, otherwise false.
			 */
			Bool IsBorderless(Void) const;

			/**
			 * @brief Checks if the window is transparent or opaque.
			 *
			 * @returns True if the window is transparent, otherwise false.
			 */
			Bool IsTransparent(Void) const;

		public:
			/**
			 * @brief Sets the window title.
			 * 
			 * @param title The title of the window.
			 */
			virtual Void SetTitle(ConstCharPtr title) const = 0; // TODO: Change ConstCharPtr to const StringView&

			/**
			 * @brief Sets the window opacity.
			 *
			 * This function is valid only for windows with the is_transparent
			 * flag set to true.
			 * 
			 * @param opacity The opacity value of the window
			 */
			virtual Void SetOpacity(F32 opacity) const = 0;

			/**
			 * @brief Sets the window size including border.
			 * 
			 * @param size The size of the window.
			 */
			virtual Void SetWindowSize(Vector2& size) const = 0;

			/**
			 * @brief Sets the window minimum size including border.
			 * 
			 * @param size The minimum size of the window.
			 */
			virtual Void SetWindowMinSize(Vector2& size) const = 0;

			/**
			 * @brief Sets the window maximum size including border.
			 * 
			 * @param size The minimum size of the window.
			 */
			virtual Void SetWindowMaxSize(Vector2& size) const = 0;

			/**
			 * @brief Sets the window position in screen coordinates.
			 * 
			 * @param position The position of the window.
			 */
			virtual Void SetWindowPosition(Vector2& position) const = 0;

		public:
			/**
			 * @brief Sets the client area size of the window not including border.
			 *
			 * @param size The size of the window client region.
			 */
			virtual Void SetClientSize(Vector2& size) const = 0;

			/**
			 * @brief Sets the client bounds of the window not including border.
			 * 
			 * @param bounds The bounds of the window client region.
			 */
			virtual Void SetClientBounds(Math::TRectangle<U32>& bounds) const = 0;

		public:
			/**
			 * @brief Sets wether the window is visible or hidden.
			 * 
			 * @param is_visible The flag wether the window is visible or not.
			 */
			virtual Void SetIsVisable(Bool is_visible) const = 0;

			/**
			 * @brief Sets wether the window is movable or fixed.
			 *
			 * @param is_movable The flag wether the window is movable or not.
			 */
			virtual Void SetIsMovable(Bool is_movable) const = 0;

			/**
			 * @brief Sets wether the window is resizable or not.
			 *
			 * @param is_resizable The flag wether the window is resizable or not.
			 */
			virtual Void SetIsResizable(Bool is_resizable) const = 0;

			/**
			 * @brief Sets wether the window is minimized or maximized.
			 *
			 * @param is_minimized The flag wether the window is minimized or not.
			 */
			virtual Void SetIsMinimized(Bool is_minimized) const = 0;

			/**
			 * @brief Sets wether the window is maximized or minimized.
			 *
			 * @param is_maximized The flag wether the window is maximized or not.
			 */
			virtual Void SetIsMaximized(Bool is_maximized) const = 0;

			/**
			 * @brief Sets wether the window is fullscreen or not.
			 *
			 * @param is_fullscreen The flag wether the window is fullscreen or
			 * not.
			 */
			virtual Void SetIsFullscreen(Bool is_fullscreen) const = 0;

			/**
			 * @brief Sets wether the window is borderless or not.
			 *
			 * @param is_borderless The flag wether the window is borderless or
			 * not.
			 */
			virtual Void SetIsBorderless(Bool is_borderless) const = 0;

			/**
			 * @brief Sets wether the window is transparent or not.
			 *
			 * @param is_transparent The flag wether the window is transparent or not.
			 */
			virtual Void SetIsTransparent(Bool is_transparent) const = 0;

		public:
			virtual Void OnWindowFocus(Common::TDelegate<Void(Bool)> callback);

			virtual Void OnWindowMinimize(Common::TDelegate<Void(Bool)> callback);
			
			virtual Void OnWindowMaximize(Common::TDelegate<Void(Bool)> callback);
			
			virtual Void OnWindowMove(Common::TDelegate<Void(U32, U32)> callback);

			virtual Void OnWindowResize(Common::TDelegate<Void(U32, U32)> callback);

		public:
			/**
			 * @brief Closes the window.
			 * 
			 * This function destorys the window and frees the nativer handle.
			 * 
			 * @param window_closing_reason The closing reason of the window.
			 */
			virtual Void Close(WindowClosingReason window_closing_reason);
		};
	}
}

#endif
