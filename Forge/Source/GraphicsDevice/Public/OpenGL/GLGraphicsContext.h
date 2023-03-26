#ifndef GL_WINDOWS_GRAPHICS_CONTEXT_H
#define GL_WINDOWS_GRAPHICS_CONTEXT_H

#include <GraphicsDevice/Public/Base/AbstractGraphicsContext.h>

#if defined(FORGE_RENDER_API_OPENGL)

#if defined(FORGE_PLATFORM_WINDOWS)
	#include <Windows.h>
#endif

namespace Forge {
	namespace Platform
	{
		class AbstractWindow;
	}
}

using namespace Forge::Platform;

namespace Forge {
	namespace Graphics
	{

#if defined(FORGE_PLATFORM_WINDOWS)
		using NativeDeviceContext = HDC;
		using NativeRenderContext = HGLRC;
#endif

		enum class GLContextProfile
		{
			/**
			 * @brief The opengl embedded system profile.
			 */
			FORGE_ENUM_DECL(FORGE_ES,     0x0)

			/**
			 * @brief The opengl core profile.
			 */
			FORGE_ENUM_DECL(FORGE_CORE,   0x1)

			/**
			 * @brief The opengl compatibility profile.
			 */
			FORGE_ENUM_DECL(FORGE_COMPAT, 0x2)

			MAX
		};

		enum class GLContextFlags
		{
			FORGE_ENUM_DECL(FORGE_NONE,           FORGE_BIT(1))

			/**
			 * @brief Specifies that the opengl context is in debug mode.
			 */
			FORGE_ENUM_DECL(FORGE_DEBUG,          FORGE_BIT(2))

			/**
			 * @brief Specifies that the opengl context will not generate errors.
			 */
			FORGE_ENUM_DECL(FORGE_NO_ERROR,       FORGE_BIT(3))

			/**
			 * @brief Specifies that the opengl context supports robust buffer
			 * access.
			 */
			FORGE_ENUM_DECL(FORGE_ROBUSTNESS,     FORGE_BIT(4))

			/**
			 * @brief Specifies the opengl context release behaviour.
			 */
			FORGE_ENUM_DECL(FORGE_RELEASE_FLUSH,  FORGE_BIT(5))

			/**
			 * @brief Specifies that the opengl context support forward
			 * compatibility.
			 */
			FORGE_ENUM_DECL(FORGE_FORWARD_COMPAT, FORGE_BIT(6))

			MAX
		};

		FORGE_FLAG_DECL(GLContextFlags)

		class FORGE_API GLGraphicsContext : public AbstractGraphicsContext
		{
		public:
			struct FrameBufferConfig
			{
				U32 red_bits = 8, green_bits = 8, blue_bits = 8, alpha_bits = 8;

				U32 depth_bits = 24, stencil_bits = 8;
				
				U32 multisamples = 0;

				Bool is_stereo = false, is_srgb_capable = false, is_double_buffer = true;
			};

		private:
			I32 m_major_version;
			I32 m_minor_version;

		private:
			CharPtr m_context_vendor;
			CharPtr m_context_renderer;
			CharPtr m_context_shader_version;

		private:
			GLContextFlags   m_context_flags;
			GLContextProfile m_context_profile;

		private:
			FrameBufferConfig m_framebuffer_config;

		private:
			NativeDeviceContext m_context_device_handle;
			NativeRenderContext m_context_render_handle;

		private:
			Bool m_has_arb_pixel_format;
			Bool m_has_arb_create_context;
			Bool m_has_arb_context_flush_control;
			Bool m_has_arb_create_context_profile;
			Bool m_has_arb_create_context_no_error;
			Bool m_has_arb_create_context_robustness;

		private:
			Bool m_has_ext_swap_control;
			Bool m_has_ext_create_context_es2_profile;

		private:
			/**
			 * @brief Initializes the platform - opengl interface extensions.
			 */
			Bool InteranlInitializeInterface(Void);

			/**
			 * @brief Checks wether the specified extension is supported.
			 */
			Bool InternalIsExtenstionSupported(ConstCharPtr extension);

		public:
			/**
			 * @brief Default Constructor.
			 */
			GLGraphicsContext(AbstractWindow* window, I32 major, I32 minor);

			/**
			 * @brief Default Constructor.
			 */
			GLGraphicsContext(AbstractWindow* window, I32 major, I32 minor, GLContextProfile profile, GLContextFlags flags);

			/**
			 * @brief Default Constructor.
			 */
			GLGraphicsContext(AbstractWindow* window, I32 major, I32 minor, GLContextProfile profile, GLContextFlags flags, FrameBufferConfig config);

		public:
			/**
			 * @brief Gets major release number of the renderer API.
			 *
			 * @returns ConstCharPtr storing the release number of the renderer
			 * API.
			 */
			I32 GetMajorVersion(Void);

			/**
			 * @brief Gets minor release number of the renderer API.
			 *
			 * @returns ConstCharPtr storing the release number of the renderer
			 * API.
			 */
			I32 GetMinorVersion(Void);

		public:
			/**
			 * @brief Gets the company responsible for this renderer
			 * implementation.
			 *
			 * @returns ConstCharPtr storing the company responsible for this
			 * renderer implementation.
			 */
			ConstCharPtr GetVendor(Void);

			/**
			 * @brief Gets the name of the hardware renderer.
			 *
			 * @returns ConstCharPtr storing the name of the hardware renderer.
			 */
			ConstCharPtr GetRenderer(Void);

			/**
			 * @brief Gets release number of the shader language.
			 *
			 * @returns ConstCharPtr storing the release number the shader
			 * language.
			 */
			ConstCharPtr GetShaderVersion(Void);

		public:
			/**
			 * @brief Initializes the graphics context with the specified render
			 * API.
			 */
			Bool Initialize(Void) override;

			/**
			 * @brief Terminates the graphics context and releases the specified
			 * render API.
			 */
			Void Terminate(Void) override;

		public:
			/**
			 * @brief Sets the graphics context as the current context for main
			 * render window.
			 */
			Void SetCurrent(Void) override;

			/**
			 * @brief Ends the graphics context for the main render window but
			 * does not release the context.
			 */
			Void EndCurrent(Void) override;

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
			Bool SwapBuffers(I32 swap_interval = 0) override;
		};

		FORGE_FORCE_INLINE I32 GLGraphicsContext::GetMajorVersion(Void) { return m_major_version; }
		FORGE_FORCE_INLINE I32 GLGraphicsContext::GetMinorVersion(Void) { return m_minor_version; }

		FORGE_FORCE_INLINE ConstCharPtr GLGraphicsContext::GetVendor(Void)        { return m_context_vendor; }
		FORGE_FORCE_INLINE ConstCharPtr GLGraphicsContext::GetRenderer(Void)      { return m_context_renderer; }
		FORGE_FORCE_INLINE ConstCharPtr GLGraphicsContext::GetShaderVersion(Void) { return m_context_shader_version; }

		FORGE_TYPEDEF_DECL(GLGraphicsContext, GraphicsContext)
	}
}

#endif

#endif
