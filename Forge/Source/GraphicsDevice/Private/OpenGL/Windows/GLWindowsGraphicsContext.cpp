#include "GraphicsDevice/Public/OpenGL/Windows/GLWindowsGraphicsContext.h"

#pragma comment (lib, "opengl32.lib")

namespace Forge {
	namespace Graphics
	{
		GLWindowsGraphicsContext::GLWindowsGraphicsContext(HWND native_window_handle)
		{
			PIXELFORMATDESCRIPTOR pfd =
			{
				sizeof(PIXELFORMATDESCRIPTOR),
				1,
				PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,    //Flags
				PFD_TYPE_RGBA,        // The kind of framebuffer. RGBA or palette.
				32,                   // Colordepth of the framebuffer.
				0, 0, 0, 0, 0, 0,
				0,
				0,
				0,
				0, 0, 0, 0,
				24,                   // Number of bits for the depthbuffer
				8,                    // Number of bits for the stencilbuffer
				0,                    // Number of Aux buffers in the framebuffer.
				PFD_MAIN_PLANE,
				0,
				0, 0, 0
			};

			m_device_context_handle = GetDC(native_window_handle);

			int  letWindowsChooseThisPixelFormat;
			letWindowsChooseThisPixelFormat = ChoosePixelFormat(m_device_context_handle, &pfd);
			SetPixelFormat(m_device_context_handle, letWindowsChooseThisPixelFormat, &pfd);

			m_rendering_context_handle = wglCreateContext(m_device_context_handle);
			wglMakeCurrent(m_device_context_handle, m_rendering_context_handle);
		}

		Void GLWindowsGraphicsContext::SetCurrent(Void)
		{

		}

		Void GLWindowsGraphicsContext::EndCurrent(Void)
		{

		}

		Void GLWindowsGraphicsContext::ReleaseContext(Void)
		{

		}
	}
}
