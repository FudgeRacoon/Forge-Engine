#include <GL/glew.h>

#include <GraphicsDevice/Public/OpenGL/GLUtilities.h>
#include <GraphicsDevice/Public/OpenGL/GLGraphicsContextState.h>

namespace Forge {
	namespace Graphics
	{
		GLGraphicsContextState::GLGraphicsContextState(GLGraphicsContextPtr graphics_context)
			: AbstractGraphicsContextState(graphics_context)
		{
			glGetIntegerv(GL_MAX_DRAW_BUFFERS, &m_context_limits.max_draw_buffers);
			glGetIntegerv(GL_MAX_RENDERBUFFER_SIZE, &m_context_limits.max_renderbuffer_size);
			glGetIntegerv(GL_MAX_VERTEX_UNIFORM_COMPONENTS, &m_context_limits.max_vertex_uniform_components);
			glGetIntegerv(GL_MAX_FRAGMENT_UNIFORM_COMPONENTS, &m_context_limits.max_fragment_uniform_components);
			glGetIntegerv(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS, &m_context_limits.max_combind_texture_image_units);

			InvalidateCache();
			InitializeCache();
		}

		Void GLGraphicsContextState::EnableDepthTest(Bool enable)
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
		Void GLGraphicsContextState::EnableStencilTest(Bool enable)
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
		Void GLGraphicsContextState::EnableScissorTest(Bool enable)
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
		Void GLGraphicsContextState::EnableFaceCulling(Bool enable)
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
		Void GLGraphicsContextState::EnableColorBlending(Bool enable)
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

		Bool GLGraphicsContextState::SetDepthWriteMask(Bool mask)
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
		Bool GLGraphicsContextState::SetDepthComparisonFunction(ComparisonFuncMask function)
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

		Bool GLGraphicsContextState::SetStencilWriteMask(Byte mask)
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
		Bool GLGraphicsContextState::SetStencilComparisonFunction(ComparisonFuncMask function, I32 ref, U32 mask)
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

		Bool GLGraphicsContextState::SetScissorBoundingRegion(I32 x, I32 y, I32 width, I32 height)
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

		Bool GLGraphicsContextState::SetFaceCullingMode(FaceCullMask mode)
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
		
		Bool GLGraphicsContextState::SetColorBlendingConstant(F32 red, F32 green, F32 blue, F32 alpha)
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
		Bool GLGraphicsContextState::SetColorBlendingFunction(BlendFuncMask src_function, BlendFuncMask dst_function)
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
		
		Void GLGraphicsContextState::SetLineWidth(F32 width)
		{
			if (m_rasterizer_state.line_width != width)
			{
				glLineWidth(width);
				m_rasterizer_state.line_width = width;
			}
		}
		Void GLGraphicsContextState::SetActiveTexture(U32 index)
		{
			FORGE_NOT_IMPLEMENTED()
		}
		Void GLGraphicsContextState::SetFillMode(PolygonFillMask mode)
		{
			if (m_rasterizer_state.polygon_fill_mode != mode)
			{
				glPolygonMode(GL_FRONT_AND_BACK, mode == PolygonFillMask::FORGE_SOLID ? GL_FILL : GL_LINE);
				m_rasterizer_state.polygon_fill_mode = mode;
			}
		}
		Void GLGraphicsContextState::SetFrontFace(FrontFaceMask front_face)
		{
			if (m_rasterizer_state.front_face_mode != front_face)
			{
				glFrontFace(front_face == FrontFaceMask::FORGE_CW ? GL_CW : GL_CCW);
				m_rasterizer_state.front_face_mode = front_face;
			}
		}
		Void GLGraphicsContextState::SetPixelStorage(PixelStorageMask mode, I32 value)
		{
			FORGE_NOT_IMPLEMENTED()
		}
		Void GLGraphicsContextState::SetColorClear(F32 red, F32 green, F32 blue, F32 alpha)
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
		Void GLGraphicsContextState::SetColorWriteMask(F32 red, F32 green, F32 blue, F32 alpha)
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

		Void GLGraphicsContextState::InitializeCache(Void)
		{
			if(m_rasterizer_state.depth_state.is_enabled)
				glEnable(GL_DEPTH_TEST);
			else 
				glDisable(GL_DEPTH_TEST);

			if (m_rasterizer_state.stencil_state.is_enabled)
				glEnable(GL_STENCIL_TEST);
			else
				glDisable(GL_STENCIL_TEST);

			if (m_rasterizer_state.scissor_state.is_enabled)
				glEnable(GL_SCISSOR_TEST);
			else
				glDisable(GL_SCISSOR_TEST);

			if(m_rasterizer_state.face_culling_state.is_enabled)
				glEnable(GL_CULL_FACE);
			else
				glDisable(GL_CULL_FACE);

			if (m_rasterizer_state.color_blending_state.is_enabled)
				glEnable(GL_BLEND);
			else
				glDisable(GL_BLEND);

			glDepthMask(m_rasterizer_state.depth_state.write_mask);
			glDepthFunc(ConvertToGLCompareFunction(m_rasterizer_state.stencil_state.comparison_function));

			glStencilMask(m_rasterizer_state.stencil_state.write_mask);
			glStencilFunc(ConvertToGLCompareFunction(m_rasterizer_state.stencil_state.comparison_function), 0, ~((U32)0));


			glScissor(m_rasterizer_state.scissor_state.bounding_region[0], 
				      m_rasterizer_state.scissor_state.bounding_region[1],
				      m_rasterizer_state.scissor_state.bounding_region[2], 
				      m_rasterizer_state.scissor_state.bounding_region[3]);
			

			glCullFace(m_rasterizer_state.face_culling_state.mode == FaceCullMask::FORGE_BACK  ? GL_BACK  :
				       m_rasterizer_state.face_culling_state.mode == FaceCullMask::FORGE_FRONT ? GL_FRONT : GL_FRONT_AND_BACK);


			glBlendColor(m_rasterizer_state.color_blending_state.constant[0], 
				         m_rasterizer_state.color_blending_state.constant[1], 
				         m_rasterizer_state.color_blending_state.constant[2], 
				         m_rasterizer_state.color_blending_state.constant[3]);
			glBlendFunc(ConvertToGLBlendFunction(m_rasterizer_state.color_blending_state.src_function), 
				        ConvertToGLBlendFunction(m_rasterizer_state.color_blending_state.dst_function));

			glLineWidth(m_rasterizer_state.line_width);

			glPolygonMode(GL_FRONT_AND_BACK, m_rasterizer_state.polygon_fill_mode == PolygonFillMask::FORGE_SOLID ? GL_FILL : GL_LINE);
			
			glFrontFace(m_rasterizer_state.front_face_mode == FrontFaceMask::FORGE_CW ? GL_CW : GL_CCW);
			
			glClearColor(m_rasterizer_state.color_clear[0],
				         m_rasterizer_state.color_clear[1],
				         m_rasterizer_state.color_clear[2],
				         m_rasterizer_state.color_clear[3]);

			glColorMask(m_rasterizer_state.color_write_mask[0],
				        m_rasterizer_state.color_write_mask[1],
				        m_rasterizer_state.color_write_mask[2],
				        m_rasterizer_state.color_write_mask[3]);
		}
		Void GLGraphicsContextState::InvalidateCache(Void)
		{
			glUseProgram(0);

			glBindVertexArray(0);
			glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
			glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);

			m_rasterizer_state.depth_state.is_enabled          = true;
			m_rasterizer_state.stencil_state.is_enabled        = false;
			m_rasterizer_state.scissor_state.is_enabled        = false;
			m_rasterizer_state.face_culling_state.is_enabled   = true;
			m_rasterizer_state.color_blending_state.is_enabled = true;

			m_rasterizer_state.depth_state.write_mask          = 0xFF;
			m_rasterizer_state.depth_state.comparison_function = ComparisonFuncMask::FORGE_LESS;

			m_rasterizer_state.stencil_state.write_mask          = 0xFF;
			m_rasterizer_state.stencil_state.comparison_function = ComparisonFuncMask::FORGE_ALWAYS;

			m_rasterizer_state.scissor_state.bounding_region[0] = 0;
			m_rasterizer_state.scissor_state.bounding_region[1] = 0;
			m_rasterizer_state.scissor_state.bounding_region[2] = m_graphics_context->GetWindow()->GetClientSize().x;
			m_rasterizer_state.scissor_state.bounding_region[3] = m_graphics_context->GetWindow()->GetClientSize().y;

			m_rasterizer_state.face_culling_state.mode = FaceCullMask::FORGE_BACK;

			m_rasterizer_state.color_blending_state.constant[0]  = 0.0f;
			m_rasterizer_state.color_blending_state.constant[1]  = 0.0f;
			m_rasterizer_state.color_blending_state.constant[2]  = 0.0f;
			m_rasterizer_state.color_blending_state.constant[3]  = 0.0f;
			m_rasterizer_state.color_blending_state.src_function = BlendFuncMask::FORGE_SRC_ALPHA;
			m_rasterizer_state.color_blending_state.dst_function = BlendFuncMask::FORGE_ONE_MINUS_SRC_ALPHA;

			m_rasterizer_state.line_width = 1.0f;

			m_rasterizer_state.front_face_mode = FrontFaceMask::FORGE_CW;

			m_rasterizer_state.polygon_fill_mode = PolygonFillMask::FORGE_SOLID;

			m_rasterizer_state.color_clear[0] = 0.0f;
			m_rasterizer_state.color_clear[1] = 0.0f;
			m_rasterizer_state.color_clear[2] = 0.0f;
			m_rasterizer_state.color_clear[3] = 0.0f;

			m_rasterizer_state.color_write_mask[0] = 0xFF;
			m_rasterizer_state.color_write_mask[1] = 0xFF;
			m_rasterizer_state.color_write_mask[2] = 0xFF;
			m_rasterizer_state.color_write_mask[3] = 0xFF;
		}

		Void GLGraphicsContextState::BindHardwareBuffer(AbstractHardwareBufferPtr hardware_buffer)
		{

		}
	}
}
