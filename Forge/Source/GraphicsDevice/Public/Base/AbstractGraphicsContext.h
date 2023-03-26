#ifndef ABSTRACT_GRAPHICS_CONTEXT_H
#define ABSTRACT_GRAPHICS_CONTEXT_H

#include <Core/Public/Common/Common.h>

namespace Forge {
	namespace Graphics
	{
		class AbstractGraphicsContext
		{
		public:
			AbstractGraphicsContext() = default;
			virtual ~AbstractGraphicsContext() = default;

		public:
			/**
			 * @brief Initializes the graphics context with the specified render
			 * API. 
			 */
			virtual Bool Initialize(Void) = 0;
			
			/**
			 * @brief Terminates the graphics context and releases the specified
			 * render API.
			 */
			virtual Void Terminate(Void) = 0;

		public:
			/**
			 * @brief Sets the graphics context as the current context for main
			 * render window.
			 */
			virtual Void SetCurrent(Void) = 0;

			/**
			 * @brief Ends the graphics context for the main render window but
			 * does not release the context.
			 */
			virtual Void EndCurrent(Void) = 0;

		public:
			/**
			 * @brief Swaps the front and back buffers if the current pixel format
			 * for the window referenced by the graphics context includes a back
			 * buffer.
			 * 
			 * @param swap_internval The number of screen updates to wait from the
			 * time SwapBuffers was called before swapping the buffers and
			 * returning. This is known as Vertical Synchronization
			 */
			virtual Bool SwapBuffers(I32 swap_interval = 0) = 0;
		};
	}
}

#endif
