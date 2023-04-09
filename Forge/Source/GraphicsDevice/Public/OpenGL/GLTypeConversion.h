#ifndef GL_TYPE_CONVERSION_H
#define GL_TYPE_CONVERSION_H

#include <GL/glew.h>

#include <Core/Public/Common/Common.h>

#include <GraphicsDevice/Public/GraphicsTypes.h>

namespace Forge {
	namespace Graphics
	{
		/**
		 * @brief Converts Engine API blend function to Opengl blending function.
		 * 
		 * @param function The engine API blend function to convert.
		 *
		 * @returns GLenum storing Opengl blend function.
		 */
		FORGE_FORCE_INLINE GLenum ConvertToGLBlendFunction(BlendFuncMask function)
		{
			GLenum gl_function;

			switch (function)
			{
			case BlendFuncMask::FORGE_ZERO:                     gl_function = GL_ZERO;                     break;
			case BlendFuncMask::FORGE_ONE:                      gl_function = GL_ONE;                      break;
			case BlendFuncMask::FORGE_SRC_COLOR:                gl_function = GL_SRC_COLOR;                break;
			case BlendFuncMask::FORGE_ONE_MINUS_SRC_COLOR:      gl_function = GL_ONE_MINUS_SRC_COLOR;      break;
			case BlendFuncMask::FORGE_DST_COLOR:                gl_function = GL_DST_COLOR;                break;
			case BlendFuncMask::FORGE_ONE_MINUS_DST_COLOR:      gl_function = GL_ONE_MINUS_DST_COLOR;      break;
			case BlendFuncMask::FORGE_SRC_ALPHA:                gl_function = GL_SRC_ALPHA;                break;
			case BlendFuncMask::FORGE_ONE_MINUS_SRC_ALPHA:      gl_function = GL_ONE_MINUS_SRC_ALPHA;      break;
			case BlendFuncMask::FORGE_DST_ALPHA:               	gl_function = GL_DST_ALPHA;                break;
			case BlendFuncMask::FORGE_ONE_MINUS_DST_ALPHA:		gl_function = GL_ONE_MINUS_DST_ALPHA;      break;
			case BlendFuncMask::FORGE_CONSTANT_COLOR:			gl_function = GL_CONSTANT_COLOR;           break;
			case BlendFuncMask::FORGE_ONE_MINUS_CONSTANT_COLOR:	gl_function = GL_ONE_MINUS_CONSTANT_COLOR; break;
			case BlendFuncMask::FORGE_CONSTANT_ALPHA:			gl_function = GL_CONSTANT_ALPHA;           break;
			case BlendFuncMask::FORGE_ONE_MINUS_CONSTANT_ALPHA:	gl_function = GL_ONE_MINUS_CONSTANT_ALPHA; break;
			}

			return gl_function;
		}

		/**
		 * @brief Converts Engine API compare function to Opengl compare function.
		 *
		 * @param function The engine API compare function to convert.
		 *
		 * @returns GLenum storing Opengl compare function.
		 */
		FORGE_FORCE_INLINE GLenum ConvertToGLCompareFunction(ComparisonFuncMask function)
		{
			GLenum gl_function;

			switch (function)
			{
			case ComparisonFuncMask::FORGE_LESS:     gl_function = GL_LESS;     break;
			case ComparisonFuncMask::FORGE_NEVER:    gl_function = GL_NEVER;    break;
			case ComparisonFuncMask::FORGE_EQUAL:    gl_function = GL_EQUAL;    break;
			case ComparisonFuncMask::FORGE_LEQUAL:   gl_function = GL_LEQUAL;   break;
			case ComparisonFuncMask::FORGE_GEQUAL:   gl_function = GL_GEQUAL;   break;
			case ComparisonFuncMask::FORGE_ALWAYS:   gl_function = GL_ALWAYS;   break;
			case ComparisonFuncMask::FORGE_GREATER:  gl_function = GL_GREATER;  break;
			case ComparisonFuncMask::FORGE_NOTEQUAL: gl_function = GL_NOTEQUAL; break;
			}

			return gl_function;
		}
	}
}

#endif
