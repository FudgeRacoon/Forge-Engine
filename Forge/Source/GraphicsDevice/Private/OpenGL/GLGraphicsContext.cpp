#include <string.h>

#include <Core/Public/Memory/MemoryUtilities.h>

#include <Platform/Public/Window.h>
#include <Platform/Public/Platform.h>

#if defined(FORGE_RENDER_API_OPENGL)

#include <GL/glew.h>
#include <GL/wglew.h>

#include <GraphicsDevice/Public/OpenGL/GLGraphicsContext.h>

#pragma comment (lib, "opengl32.lib")

#define SET_ATTRIB(a, v) { attributes[attribute_index++] = a; attributes[attribute_index++] = v; }

namespace Forge {
	namespace Graphics
	{
		Bool GLGraphicsContext::InteranlInitializeInterface(Void)
		{
#if defined (FORGE_PLATFORM_WINDOWS)
			Bool result;

			HMODULE module_handle;

			HDC dummy_device_context;
			HGLRC dummy_render_context;

			HWND dummy_window_handle;
			WNDCLASS dummy_window_class;

			I32 pixel_format_descriptor_index;
			PIXELFORMATDESCRIPTOR pixel_format_descriptor;

			Memory::MemorySet(&dummy_window_class, 0, sizeof(WNDCLASS));

			dummy_window_class.style = CS_OWNDC;
			dummy_window_class.hInstance = (HINSTANCE)Platform::Platform::GetInstance().GetPlatformHandle();
			dummy_window_class.lpfnWndProc = DefWindowProc;
			dummy_window_class.lpszClassName = "dummy_window_class";

			RegisterClass(&dummy_window_class);

			dummy_window_handle = CreateWindow(
				"dummy_window_class",
				"dummy_window_class",
				WS_POPUP | WS_CLIPCHILDREN,
				0, 0, 32, 32,
				nullptr,
				nullptr,
				(HINSTANCE)Platform::Platform::GetInstance().GetPlatformHandle(),
				nullptr
			);

			dummy_device_context = GetDC(dummy_window_handle);

			Memory::MemorySet(&pixel_format_descriptor, 0, sizeof(pixel_format_descriptor));

			pixel_format_descriptor.nSize      = sizeof(pixel_format_descriptor);
			pixel_format_descriptor.nVersion   = 1;
			pixel_format_descriptor.dwFlags    = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
			pixel_format_descriptor.iPixelType = PFD_TYPE_RGBA;
			pixel_format_descriptor.cColorBits = 24;

			pixel_format_descriptor_index = ChoosePixelFormat(dummy_device_context, &pixel_format_descriptor);

			result = SetPixelFormat(dummy_device_context, pixel_format_descriptor_index, &pixel_format_descriptor);
			if (!result)
			{
				Platform::Platform::GetInstance().Error("WGL: Failed to set pixel format for dummy context");
				return FORGE_FALSE;
			}

			dummy_render_context = wglCreateContext(dummy_device_context);
			if (!dummy_render_context)
			{
				Platform::Platform::GetInstance().Error("WGL: Failed to create dummy context");
				return FORGE_FALSE;
			}

			result = wglMakeCurrent(dummy_device_context, dummy_render_context);
			if (!result)
			{
				Platform::Platform::GetInstance().Error("WGL: Failed to make dummy context current");

				wglMakeCurrent(nullptr, nullptr);
				wglDeleteContext(dummy_render_context);

				return FORGE_FALSE;
			}

			if (glewInit() != GLEW_OK)
			{
				Platform::Platform::GetInstance().Error("GLEW: Failed to initialize glew");
				return FORGE_FALSE;
			}

			m_has_arb_pixel_format = InternalIsExtenstionSupported("WGL_ARB_pixel_format");
			m_has_arb_create_context = InternalIsExtenstionSupported("WGL_ARB_create_context");
			m_has_arb_context_flush_control = InternalIsExtenstionSupported("WGL_ARB_context_flush_control");
			m_has_arb_create_context_profile = InternalIsExtenstionSupported("WGL_ARB_create_context_profile");
			m_has_arb_create_context_no_error = InternalIsExtenstionSupported("WGL_ARB_create_context_no_error");
			m_has_arb_create_context_robustness = InternalIsExtenstionSupported("WGL_ARB_create_context_robustness");

			m_has_ext_swap_control = InternalIsExtenstionSupported("WGL_EXT_swap_control");
			m_has_ext_create_context_es2_profile = InternalIsExtenstionSupported("WGL_EXT_create_context_es2_profile");

			wglMakeCurrent(m_context_device_handle, m_context_render_handle);
			wglDeleteContext(dummy_render_context);

			DestroyWindow(dummy_window_handle);
			UnregisterClass("dummy_window_class", (HINSTANCE)Platform::Platform::GetInstance().GetPlatformHandle());
#endif
		}
		Bool GLGraphicsContext::InternalIsExtenstionSupported(ConstCharPtr extension)
		{
			ConstCharPtr extensions = wglGetExtensionsStringARB(m_context_device_handle);
			if (!extensions)
			{
				Platform::Platform::GetInstance().Error("WGL: Failed to describe pixel format");
				return FORGE_FALSE;
			}

			ConstCharPtr start = extensions;

			for (;;)
			{
				const char* where;
				const char* terminator;

				where = strstr(start, extension);

				if (!where)
					return FORGE_FALSE;

				terminator = where + strlen(extension);

				if (where == start || *(where - 1) == ' ')
				{
					if (*terminator == ' ' || *terminator == '\0')
						break;
				}

				start = terminator;
			}

			return FORGE_TRUE;
		}

		GLGraphicsContext::GLGraphicsContext(AbstractWindow* window, I32 major, I32 minor)
			: m_major_version(major),
			  m_minor_version(minor),
			  m_context_flags(GLContextFlags::FORGE_NONE),
			  m_context_profile(GLContextProfileMask::FORGE_CORE),
			  m_context_render_handle(nullptr)
		{
			FORGE_ASSERT(window != nullptr, "Window is null")

#if defined(FORGE_PLATFORM_WINDOWS)
			m_context_device_handle = GetDC((HWND)window->GetNativeHandle());
			if (!m_context_device_handle)
				Platform::Platform::GetInstance().Error("WGL: Failed to retrieve DC for window");
#endif
		}
		GLGraphicsContext::GLGraphicsContext(AbstractWindow* window, I32 major, I32 minor, GLContextProfileMask profile, GLContextFlags flags)
			: m_major_version(major),
			  m_minor_version(minor),
			  m_context_flags(flags),
			  m_context_profile(profile),
			  m_context_render_handle(nullptr)
		{
			FORGE_ASSERT(window != nullptr, "Window is null")

#if defined(FORGE_PLATFORM_WINDOWS)
			m_context_device_handle = GetDC((HWND)window->GetNativeHandle());
			if (!m_context_device_handle)
				Platform::Platform::GetInstance().Error("WGL: Failed to retrieve DC for window");
#endif
		}
		GLGraphicsContext::GLGraphicsContext(AbstractWindow* window, I32 major, I32 minor, GLContextProfileMask profile, GLContextFlags flags, FrameBufferConfig config)
			: m_major_version(major),
			  m_minor_version(minor),
			  m_context_flags(flags),
			  m_context_profile(profile),
			  m_framebuffer_config(config),
			  m_context_render_handle(nullptr)
		{
			FORGE_ASSERT(window != nullptr, "Window is null")

#if defined(FORGE_PLATFORM_WINDOWS)
			m_context_device_handle = GetDC((HWND)window->GetNativeHandle());
			if (!m_context_device_handle)
				Platform::Platform::GetInstance().Error("WGL: Failed to retrieve DC for window");
#endif
		}

		Bool GLGraphicsContext::Initialize(Void)
		{
			InteranlInitializeInterface();

			Bool result;

			I32 pixel_format_descriptor_index;
			U32 pixel_format_descriptors_found;
			PIXELFORMATDESCRIPTOR pixel_format_descriptor;

			I32 attributes[64];
			I32 attribute_mask = 0, attribute_flags = 0, attribute_index = 0;

			if (m_has_arb_pixel_format)
			{
				I32 pixel_attributes[] = {
					WGL_DRAW_TO_WINDOW_ARB, FORGE_TRUE,
					WGL_DRAW_TO_BITMAP_ARB, FORGE_FALSE,

					WGL_SUPPORT_OPENGL_ARB, FORGE_TRUE,

					WGL_PIXEL_TYPE_ARB,		WGL_TYPE_RGBA_ARB,

					WGL_ACCELERATION_ARB,   WGL_FULL_ACCELERATION_ARB,

					WGL_RED_BITS_ARB,       m_framebuffer_config.red_bits,
					WGL_GREEN_BITS_ARB,     m_framebuffer_config.green_bits,
					WGL_BLUE_BITS_ARB,      m_framebuffer_config.blue_bits,

					WGL_DEPTH_BITS_ARB,     m_framebuffer_config.depth_bits,
					WGL_STENCIL_BITS_ARB,   m_framebuffer_config.stencil_bits,

					WGL_DOUBLE_BUFFER_ARB,  m_framebuffer_config.is_double_buffer,
					WGL_STEREO_ARB,         m_framebuffer_config.is_stereo,

					WGL_COLOR_BITS_ARB,     m_framebuffer_config.red_bits +
											m_framebuffer_config.green_bits +
											m_framebuffer_config.blue_bits +
											m_framebuffer_config.alpha_bits,
					0,
				};

				result = wglChoosePixelFormatARB(m_context_device_handle, pixel_attributes, nullptr, 1, &pixel_format_descriptor_index, &pixel_format_descriptors_found);
				if (!result)
				{
					Platform::Platform::GetInstance().Error("WGL: Failed to choose pixel format");
					return FORGE_FALSE;
				}

				result = DescribePixelFormat(m_context_device_handle, pixel_format_descriptor_index, sizeof(pixel_format_descriptor), &pixel_format_descriptor);
				if (!result)
				{
					Platform::Platform::GetInstance().Error("Win32: Failed to describe pixel format");
					return FORGE_FALSE;
				}

				result = SetPixelFormat(m_context_device_handle, pixel_format_descriptor_index, &pixel_format_descriptor);
				if (!result)
				{
					Platform::Platform::GetInstance().Error("Win32: Failed to set pixel format");
					return FORGE_FALSE;
				}
			}
			else
			{
				pixel_format_descriptor.nSize        = sizeof(PIXELFORMATDESCRIPTOR);
				pixel_format_descriptor.nVersion     = 1;
				pixel_format_descriptor.dwFlags      = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
				pixel_format_descriptor.iPixelType   = PFD_TYPE_RGBA;
				pixel_format_descriptor.cColorBits   = 32;
				pixel_format_descriptor.cDepthBits   = 24;
				pixel_format_descriptor.cStencilBits = 8;

				pixel_format_descriptor_index = ChoosePixelFormat(m_context_device_handle, &pixel_format_descriptor);
				if (!pixel_format_descriptor_index)
				{
					Platform::Platform::GetInstance().Error("Win32: Failed to choose pixel format");
					return FORGE_FALSE;
				}

				result = SetPixelFormat(m_context_device_handle, pixel_format_descriptor_index, &pixel_format_descriptor);
				if (!result)
				{
					Platform::Platform::GetInstance().Error("Win32: Failed to set pixel format");
					return FORGE_FALSE;
				}
			}

			if (m_has_arb_create_context)
			{
				if ((m_major_version == 1 && (m_minor_version >= 0 || m_minor_version <= 5)) ||
					(m_major_version == 2 && (m_minor_version >= 0 || m_minor_version <= 1)) ||
					(m_major_version == 3 && (m_minor_version >= 0 || m_minor_version <= 3)) ||
					(m_major_version == 4 && (m_minor_version >= 0 || m_minor_version <= 5)))
				{
					SET_ATTRIB(WGL_CONTEXT_MAJOR_VERSION_ARB, m_major_version)
					SET_ATTRIB(WGL_CONTEXT_MINOR_VERSION_ARB, m_minor_version)
				}
				else
				{
					Platform::Platform::GetInstance().Error("WGL: Invalid opengl version requested");
					return FORGE_FALSE;
				}

				if (m_context_flags & GLContextFlags::FORGE_DEBUG)
					attribute_flags |= WGL_CONTEXT_DEBUG_BIT_ARB;

				if (m_context_flags & GLContextFlags::FORGE_FORWARD_COMPAT)
					attribute_flags |= WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB;

				if (m_has_arb_create_context_profile)
				{
					if (m_context_profile == GLContextProfileMask::FORGE_CORE)
						attribute_mask |= WGL_CONTEXT_CORE_PROFILE_BIT_ARB;
					else if (m_context_profile == GLContextProfileMask::FORGE_COMPAT)
						attribute_mask |= WGL_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB;
					else if (m_has_ext_create_context_es2_profile)
						attribute_mask |= WGL_CONTEXT_ES2_PROFILE_BIT_EXT;
					else
					{
						Platform::Platform::GetInstance().Error("WGL: OpenGL ES2 profile requested but WGL_ARB_create_context_es2_profile is unavailable");
						return FORGE_FALSE;
					}
				}
				else
				{
					Platform::Platform::GetInstance().Error("WGL: OpenGL profile requested but WGL_ARB_create_context_profile is unavailable");
					return FORGE_FALSE;
				}

				if (m_has_arb_create_context_no_error)
				{
					if (m_context_flags & GLContextFlags::FORGE_NO_ERROR)
						SET_ATTRIB(WGL_CONTEXT_OPENGL_NO_ERROR_ARB, FORGE_TRUE)
				}
				else
				{
					Platform::Platform::GetInstance().Error("WGL: OpenGL no error requested but WGL_ARB_create_context_no_error is unavailable");
					return FORGE_FALSE;
				}

				if (m_has_arb_create_context_robustness)
				{
					if (m_context_flags & GLContextFlags::FORGE_ROBUSTNESS)
						attribute_flags |= WGL_CONTEXT_ROBUST_ACCESS_BIT_ARB;
				}
				else
				{
					Platform::Platform::GetInstance().Error("WGL: OpenGL no error requested but WGL_ARB_create_context_robustness is unavailable");
					return FORGE_FALSE;
				}

				if (m_has_arb_context_flush_control)
				{
					if (m_context_flags & GLContextFlags::FORGE_RELEASE_FLUSH)
						SET_ATTRIB(WGL_CONTEXT_RELEASE_BEHAVIOR_ARB, WGL_CONTEXT_RELEASE_BEHAVIOR_FLUSH_ARB)
					else
						SET_ATTRIB(WGL_CONTEXT_RELEASE_BEHAVIOR_ARB, WGL_CONTEXT_RELEASE_BEHAVIOR_NONE_ARB)
				}
				else
				{
					Platform::Platform::GetInstance().Error("WGL: OpenGL no error requested but WGL_ARB_context_flush_control is unavailable");
					return FORGE_FALSE;
				}

				if (attribute_flags)
					SET_ATTRIB(WGL_CONTEXT_FLAGS_ARB, attribute_flags)

				if (attribute_mask)
					SET_ATTRIB(WGL_CONTEXT_PROFILE_MASK_ARB, attribute_mask)

				SET_ATTRIB(0, 0)

				m_context_render_handle = wglCreateContextAttribsARB(m_context_device_handle, nullptr, attributes);
				if (!m_context_render_handle)
				{
					Platform::Platform::GetInstance().Error("WGL: Failed to create context");
					return FORGE_FALSE;
				}
			}
			else
			{
				m_context_render_handle = wglCreateContext(m_context_device_handle);
				if (!m_context_render_handle)
				{
					Platform::Platform::GetInstance().Error("WGL: Failed to create context");
					return FORGE_FALSE;
				}
			}

			result = wglMakeCurrent(m_context_device_handle, m_context_render_handle);
			if (!result)
			{
				Platform::Platform::GetInstance().Error("WGL: Failed to make context current");
				return FORGE_FALSE;
			}

			glGetIntegerv(GL_MAJOR_VERSION, &m_major_version);
			glGetIntegerv(GL_MINOR_VERSION, &m_minor_version);

			m_context_vendor           = (CharPtr)glGetString(GL_VENDOR);
			m_context_renderer         = (CharPtr)glGetString(GL_RENDERER);
			m_context_shader_version   = (CharPtr)glGetString(GL_SHADING_LANGUAGE_VERSION);
		}
		Void GLGraphicsContext::Terminate(Void)
		{
			if (m_context_render_handle != nullptr)
			{
				wglDeleteContext(m_context_render_handle);

				m_context_device_handle = nullptr;
				m_context_render_handle = nullptr;
			}
		}

		Void GLGraphicsContext::SetCurrent(Void)
		{
			FORGE_ASSERT(m_context_device_handle != nullptr, "Device Context is null")
			FORGE_ASSERT(m_context_render_handle != nullptr, "Render Context is null")

			if(!wglMakeCurrent(m_context_device_handle, m_context_render_handle))
				Platform::Platform::GetInstance().Error("WGL: Failed to make context current");
		}
		Void GLGraphicsContext::EndCurrent(Void)
		{
			wglMakeCurrent(nullptr, nullptr);
		}

		Bool GLGraphicsContext::SwapBuffers(I32 swap_interval)
		{
			FORGE_ASSERT(m_context_device_handle != nullptr, "Device Context is null")

			if (m_has_ext_swap_control)
				wglSwapIntervalEXT(swap_interval);
			else
			{
				Platform::Platform::GetInstance().Error("WGL: Swap Interval requested but WGL_EXT_swap_control is unavailable");
				return FORGE_FALSE;
			}
				
			::SwapBuffers(m_context_device_handle);
		}
	}
}

#endif
