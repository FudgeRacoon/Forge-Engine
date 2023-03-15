#ifndef GL_GRAPHICS_CONTEXT_H
#define GL_GRAPHICS_CONTEXT_H

#include <Windows.h>

#include "../../GraphicsContext.h"

namespace Forge {
	namespace Graphics
	{
		class FORGE_API GLWindowsGraphicsContext : public GraphicsContext
		{
		public:
			HDC   m_device_context_handle;
			HGLRC m_rendering_context_handle;

		public:
			GLWindowsGraphicsContext(HWND native_window_handle);

		public:
			Void SetCurrent(Void) override;

			Void EndCurrent(Void) override;

		public:
			Void ReleaseContext(Void) override;
		};
	}
}

#endif
