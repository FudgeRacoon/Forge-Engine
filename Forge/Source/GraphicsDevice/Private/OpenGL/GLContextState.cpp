
#if defined(FORGE_RENDER_API_OPENGL)

#include <GL/glew.h>

#include <GraphicsDevice/Public/OpenGL/GLContextState.h>
#include <GraphicsDevice/Public/OpenGL/GLTypeConversion.h>

namespace Forge {
	namespace Graphics
	{
		GLContextState::GLContextState(Void)
		{
			glGetIntegerv(GL_MAX_DRAW_BUFFERS, &m_context_limits.max_draw_buffers);
			glGetIntegerv(GL_MAX_RENDERBUFFER_SIZE, &m_context_limits.max_renderbuffer_size);
			glGetIntegerv(GL_MAX_VERTEX_UNIFORM_COMPONENTS, &m_context_limits.max_vertex_uniform_components);
			glGetIntegerv(GL_MAX_FRAGMENT_UNIFORM_COMPONENTS, &m_context_limits.max_fragment_uniform_components);
			glGetIntegerv(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS, &m_context_limits.max_combind_texture_image_units);

			InvalidateCache();
			InitializeCache();
		}

		Void GLContextState::EnableDepthTest(Bool enable)
		{
			if (m_rasterizer_state.depth_state.is_enabled != enable)
			{
				if (enable)
				{
					glEnable(GL_DEPTH_TEST);
					m_rasterizer_state.depth_state.is_enabled = FORGE_TRUE;
				}
				else
				{
					glDisable(GL_DEPTH_TEST);
					m_rasterizer_state.depth_state.is_enabled = FORGE_FALSE;
				}
			}
		}
		Void GLContextState::EnableStencilTest(Bool enable)
		{
			if (m_rasterizer_state.stencil_state.is_enabled != enable)
			{
				if (enable)
				{
					glEnable(GL_STENCIL_TEST);
					m_rasterizer_state.stencil_state.is_enabled = FORGE_TRUE;
				}
				else
				{
					glDisable(GL_STENCIL_TEST);
					m_rasterizer_state.stencil_state.is_enabled = FORGE_FALSE;
				}
			}
		}
		Void GLContextState::EnableScissorTest(Bool enable)
		{
			if (m_rasterizer_state.scissor_state.is_enabled != enable)
			{
				if (enable)
				{
					glEnable(GL_SCISSOR_TEST);
					m_rasterizer_state.scissor_state.is_enabled = FORGE_TRUE;
				}
				else
				{
					glDisable(GL_SCISSOR_TEST);
					m_rasterizer_state.scissor_state.is_enabled = FORGE_FALSE;
				}
			}
		}
		Void GLContextState::EnableFaceCulling(Bool enable)
		{
			if (m_rasterizer_state.face_culling_state.is_enabled != enable)
			{
				if (enable)
				{
					glEnable(GL_CULL_FACE);
					m_rasterizer_state.face_culling_state.is_enabled = FORGE_TRUE;
				}
				else
				{
					glDisable(GL_CULL_FACE);
					m_rasterizer_state.face_culling_state.is_enabled = FORGE_FALSE;
				}
			}
		}
		Void GLContextState::EnableColorBlending(Bool enable)
		{
			if (m_rasterizer_state.color_blending_state.is_enabled != enable)
			{
				if (enable)
				{
					glEnable(GL_BLEND);
					m_rasterizer_state.color_blending_state.is_enabled = FORGE_TRUE;
				}
				else
				{
					glDisable(GL_BLEND);
					m_rasterizer_state.color_blending_state.is_enabled = FORGE_FALSE;
				}
			}
		}

		Bool GLContextState::SetDepthWriteMask(Bool mask)
		{
			if (m_rasterizer_state.depth_state.is_enabled)
			{
				if (m_rasterizer_state.depth_state.write_mask != mask)
				{
					glDepthMask(mask);
					m_rasterizer_state.depth_state.write_mask = mask;
				}

				return FORGE_TRUE;
			}
			
			return FORGE_FALSE;
		}
		Bool GLContextState::SetDepthComparisonFunction(ComparisonFuncMask function)
		{
			if (m_rasterizer_state.depth_state.is_enabled)
			{
				if (m_rasterizer_state.depth_state.comparison_function != function)
				{
					glDepthFunc(ConvertToGLCompareFunction(function));
					m_rasterizer_state.depth_state.comparison_function = function;
				}

				return FORGE_TRUE;
			}
			
			FORGE_FALSE;
		}

		Bool GLContextState::SetStencilWriteMask(Byte mask)
		{
			if (m_rasterizer_state.stencil_state.is_enabled)
			{
				if (m_rasterizer_state.stencil_state.write_mask != mask)
				{
					glStencilMask(mask);
					m_rasterizer_state.stencil_state.write_mask = mask;
				}

				return FORGE_TRUE;
			}

			return FORGE_FALSE;
			
		}
		Bool GLContextState::SetStencilComparisonFunction(ComparisonFuncMask function, I32 ref, U32 mask)
		{
			if (m_rasterizer_state.stencil_state.is_enabled)
			{
				if (m_rasterizer_state.stencil_state.comparison_function != function)
				{
					glStencilFunc(ConvertToGLCompareFunction(function), ref, mask);
					m_rasterizer_state.stencil_state.comparison_function = function;
				}

				return FORGE_TRUE;
			}
			
			return FORGE_FALSE;
		}

		Bool GLContextState::SetScissorBoundingRegion(I32 x, I32 y, I32 width, I32 height)
		{
			if (m_rasterizer_state.scissor_state.is_enabled)
			{
				if (m_rasterizer_state.scissor_state.bounding_region[0] != x     ||
					m_rasterizer_state.scissor_state.bounding_region[1] != y     ||
					m_rasterizer_state.scissor_state.bounding_region[2] != width ||
					m_rasterizer_state.scissor_state.bounding_region[3] != height)
				{
					glScissor(x, y, width, height);
					m_rasterizer_state.scissor_state.bounding_region[0] = x;
					m_rasterizer_state.scissor_state.bounding_region[1] = y;
					m_rasterizer_state.scissor_state.bounding_region[2] = width;
					m_rasterizer_state.scissor_state.bounding_region[3] = height;
				}

				return FORGE_TRUE;
			}

			return FORGE_FALSE;
		}

		Bool GLContextState::SetFaceCullingMode(FaceCullMask mode)
		{
			if (m_rasterizer_state.face_culling_state.is_enabled)
			{
				if (m_rasterizer_state.face_culling_state.mode != mode)
				{
					glCullFace(mode == FaceCullMask::FORGE_BACK  ? GL_BACK  : 
						       mode == FaceCullMask::FORGE_FRONT ? GL_FRONT : GL_FRONT_AND_BACK);
					m_rasterizer_state.face_culling_state.mode = mode;
				}

				return FORGE_TRUE;
			}

			return FORGE_FALSE;
		}
		
		Bool GLContextState::SetColorBlendingConstant(F32 red, F32 green, F32 blue, F32 alpha)
		{
			if (m_rasterizer_state.color_blending_state.is_enabled)
			{
				if (m_rasterizer_state.color_blending_state.constant[0] != red   ||
					m_rasterizer_state.color_blending_state.constant[1] != green ||
					m_rasterizer_state.color_blending_state.constant[2] != blue  ||
					m_rasterizer_state.color_blending_state.constant[0] != alpha)
				{
					glBlendColor(red, green, blue, alpha);
					m_rasterizer_state.color_blending_state.constant[0] = red;
					m_rasterizer_state.color_blending_state.constant[1] = green;
					m_rasterizer_state.color_blending_state.constant[2] = blue;
					m_rasterizer_state.color_blending_state.constant[3] = alpha;
				}

				return FORGE_TRUE;
			}

			return FORGE_FALSE;
		}
		Bool GLContextState::SetColorBlendingFunction(BlendFuncMask src_function, BlendFuncMask dst_function)
		{
			if (m_rasterizer_state.color_blending_state.is_enabled)
			{
				if (m_rasterizer_state.color_blending_state.src_function != src_function ||
					m_rasterizer_state.color_blending_state.dst_function != dst_function)
				{
					
					glBlendFunc(ConvertToGLBlendFunction(src_function), 
						        ConvertToGLBlendFunction(dst_function));
					m_rasterizer_state.color_blending_state.src_function = src_function;
					m_rasterizer_state.color_blending_state.dst_function = dst_function;
				}

				return FORGE_TRUE;
			}

			return FORGE_FALSE;
		}
		
		Void GLContextState::SetLineWidth(F32 width)
		{
			if (m_rasterizer_state.line_width != width)
			{
				glLineWidth(width);
				m_rasterizer_state.line_width = width;
			}
		}
		Void GLContextState::SetFillMode(PolygonFillMask mode)
		{
			if (m_rasterizer_state.polygon_fill_mode != mode)
			{
				glPolygonMode(GL_FRONT_AND_BACK, mode == PolygonFillMask::FORGE_SOLID ? GL_FILL : GL_LINE);
				m_rasterizer_state.polygon_fill_mode = mode;
			}
		}
		Void GLContextState::SetFrontFace(FrontFaceMask front_face)
		{
			if (m_rasterizer_state.front_face_mode != front_face)
			{
				glFrontFace(front_face == FrontFaceMask::FORGE_CW ? GL_CW : GL_CCW);
				m_rasterizer_state.front_face_mode = front_face;
			}
		}
		Void GLContextState::SetPixelStorage(PixelStorageMask mode, I32 value)
		{

		}
		Void GLContextState::SetColorClear(F32 red, F32 green, F32 blue, F32 alpha)
		{
			if(m_rasterizer_state.color_clear[0] != red   ||
			   m_rasterizer_state.color_clear[1] != green ||
			   m_rasterizer_state.color_clear[2] != blue  ||
			   m_rasterizer_state.color_clear[3] != alpha)
			{
				glClearColor(red, green, blue, alpha);
				m_rasterizer_state.color_clear[0] = red;
				m_rasterizer_state.color_clear[1] = green;
				m_rasterizer_state.color_clear[2] = blue;
				m_rasterizer_state.color_clear[3] = alpha;
			}
		}
		Void GLContextState::SetColorWriteMask(F32 red, F32 green, F32 blue, F32 alpha)
		{
			if (m_rasterizer_state.color_write_mask[0] != red   ||
				m_rasterizer_state.color_write_mask[1] != green ||
				m_rasterizer_state.color_write_mask[2] != blue  ||
				m_rasterizer_state.color_write_mask[3] != alpha)
			{
				glColorMask(red, green, blue, alpha);
				m_rasterizer_state.color_write_mask[0] = red;
				m_rasterizer_state.color_write_mask[1] = green;
				m_rasterizer_state.color_write_mask[2] = blue;
				m_rasterizer_state.color_write_mask[3] = alpha;
			}
		}

		Void GLContextState::InitializeCache(Void)
		{
			glClearColor(m_rasterizer_state.color_clear[0],
				         m_rasterizer_state.color_clear[1],
				         m_rasterizer_state.color_clear[2],
				         m_rasterizer_state.color_clear[3]);

			glColorMask(m_rasterizer_state.color_write_mask[0],
				        m_rasterizer_state.color_write_mask[1],
				        m_rasterizer_state.color_write_mask[2],
				        m_rasterizer_state.color_write_mask[3]);

			glFrontFace(m_rasterizer_state.front_face_mode == FrontFaceMask::FORGE_CW ? GL_CW : GL_CCW);

			glPolygonMode(GL_FRONT_AND_BACK, m_rasterizer_state.polygon_fill_mode == PolygonFillMask::FORGE_SOLID ? GL_FILL : GL_LINE);

			if(m_rasterizer_state.depth_state.is_enabled)
				glEnable(GL_DEPTH_TEST);
			else 
				glDisable(GL_DEPTH_TEST);

			glDepthMask(m_rasterizer_state.depth_state.write_mask);
			glDepthFunc(ConvertToGLCompareFunction(m_rasterizer_state.stencil_state.comparison_function));

			if (m_rasterizer_state.stencil_state.is_enabled)
				glEnable(GL_STENCIL_TEST);
			else
				glDisable(GL_STENCIL_TEST);

			glStencilMask(m_rasterizer_state.stencil_state.write_mask);
			glStencilFunc(ConvertToGLCompareFunction(m_rasterizer_state.stencil_state.comparison_function), 0, ~((U32)0));

			if (m_rasterizer_state.scissor_state.is_enabled)
				glEnable(GL_SCISSOR_TEST);
			else
				glDisable(GL_SCISSOR_TEST);

			glScissor(m_rasterizer_state.scissor_state.bounding_region[0], 
				      m_rasterizer_state.scissor_state.bounding_region[1],
				      m_rasterizer_state.scissor_state.bounding_region[2], 
				      m_rasterizer_state.scissor_state.bounding_region[3]);
			
			if(m_rasterizer_state.face_culling_state.is_enabled)
				glEnable(GL_CULL_FACE);
			else
				glDisable(GL_CULL_FACE);

			glCullFace(m_rasterizer_state.face_culling_state.mode == FaceCullMask::FORGE_BACK  ? GL_BACK  :
				       m_rasterizer_state.face_culling_state.mode == FaceCullMask::FORGE_FRONT ? GL_FRONT : GL_FRONT_AND_BACK);

			if (m_rasterizer_state.color_blending_state.is_enabled)
				glEnable(GL_BLEND);
			else
				glDisable(GL_BLEND);

			glBlendColor(m_rasterizer_state.color_blending_state.constant[0], 
				         m_rasterizer_state.color_blending_state.constant[1], 
				         m_rasterizer_state.color_blending_state.constant[2], 
				         m_rasterizer_state.color_blending_state.constant[3]);
			glBlendFunc(ConvertToGLBlendFunction(m_rasterizer_state.color_blending_state.src_function), 
				        ConvertToGLBlendFunction(m_rasterizer_state.color_blending_state.dst_function));
		}
		Void GLContextState::InvalidateCache(Void)
		{
			glUseProgram(0);

			glBindVertexArray(0);
			glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
			glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);

			m_rasterizer_state.line_width = 1.0f;

			m_rasterizer_state.color_clear[0] = 0.0f;
			m_rasterizer_state.color_clear[1] = 0.0f;
			m_rasterizer_state.color_clear[2] = 0.0f;
			m_rasterizer_state.color_clear[3] = 0.0f;

			m_rasterizer_state.color_write_mask[0] = 0xFF;
			m_rasterizer_state.color_write_mask[1] = 0xFF;
			m_rasterizer_state.color_write_mask[2] = 0xFF;
			m_rasterizer_state.color_write_mask[3] = 0xFF;

			m_rasterizer_state.front_face_mode = FrontFaceMask::FORGE_CW;

			m_rasterizer_state.polygon_fill_mode = PolygonFillMask::FORGE_SOLID;

			m_rasterizer_state.depth_state.is_enabled = true;
			m_rasterizer_state.depth_state.write_mask = 0xFF;
			m_rasterizer_state.depth_state.comparison_function = ComparisonFuncMask::FORGE_LESS;

			m_rasterizer_state.stencil_state.is_enabled = true;
			m_rasterizer_state.stencil_state.write_mask = 0xFF;
			m_rasterizer_state.stencil_state.comparison_function = ComparisonFuncMask::FORGE_ALWAYS;

			m_rasterizer_state.scissor_state.is_enabled = true;
			m_rasterizer_state.scissor_state.bounding_region[0] = 0;
			m_rasterizer_state.scissor_state.bounding_region[1] = 0;
			m_rasterizer_state.scissor_state.bounding_region[2] = 800;
			m_rasterizer_state.scissor_state.bounding_region[3] = 400;

			m_rasterizer_state.face_culling_state.is_enabled = true;
			m_rasterizer_state.face_culling_state.mode = FaceCullMask::FORGE_BACK;

			m_rasterizer_state.color_blending_state.is_enabled = true;
			m_rasterizer_state.color_blending_state.constant[0] = 0.0f;
			m_rasterizer_state.color_blending_state.constant[1] = 0.0f;
			m_rasterizer_state.color_blending_state.constant[2] = 0.0f;
			m_rasterizer_state.color_blending_state.constant[3] = 0.0f;
			m_rasterizer_state.color_blending_state.src_function = BlendFuncMask::FORGE_SRC_ALPHA;
			m_rasterizer_state.color_blending_state.dst_function = BlendFuncMask::FORGE_ONE_MINUS_SRC_ALPHA;
		}
	}
}

#endif
