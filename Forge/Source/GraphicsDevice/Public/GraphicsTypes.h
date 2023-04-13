#ifndef GRAPHICS_TYPES_H
#define GRAPHICS_TYPES_H

#include <Core/Public/Common/Common.h>

namespace Forge {
	namespace Graphics
	{
		/**
		 * @brief Buffer clear flags specifing the buffers to be cleared.
		 * 
		 * [GL]: https://docs.gl/gl3/glClear
		 */
		enum class ClearFlags : Byte
		{
			/**
			 * @brief Indicates to clear the color buffer.
			 */
			FORGE_ENUM_DECL(FORGE_COLOR_BUFFER,   FORGE_BIT(0))

			/**
			 * @brief Indicates to clear the depth buffer.
			 */
			FORGE_ENUM_DECL(FORGE_DEPTH_BUFFER,   FORGE_BIT(1))

			/**
			 * @brief Indicates to clear the stencil buffer.
			 */
			FORGE_ENUM_DECL(FORGE_STENCIL_BUFFER, FORGE_BIT(2))

			MAX
		};

		/**
		 * @brief Face culling masks specifing whether front or back facing faces
		 * are candidates for culling.
		 * 
		 * [GL]: https://docs.gl/gl3/glCullFace
		 */
		enum class FaceCullMask : Byte
		{
			/**
			 * @brief Indicates to cull front face.
			 */
			FORGE_ENUM_DECL(FORGE_FRONT,          0x0)

			/**
			 * @brief Indicates to cull back face.
			 */
			FORGE_ENUM_DECL(FORGE_BACK,           0x1)

			/**
			 * @brief Indicates to cull front and back face.
			 */
			FORGE_ENUM_DECL(FORGE_FRONT_AND_BACK, 0x2)

			MAX
		};

		/**
		 * @brief Front face masks specifing the orientation of front-facing
		 * polygons.
		 * 
		 * [GL]: https://docs.gl/gl3/glFrontFace
		 */
		enum class FrontFaceMask
		{
			/**
			 * @brief Indicates that clockwise winding is front.
			 */
			FORGE_ENUM_DECL(FORGE_CW,  0x0)

			/**
			 * @brief Indicates that anti-clockwise winding is front.
			 */
			FORGE_ENUM_DECL(FORGE_CCW, 0x1)

			MAX
		};

		/**
		 * @brief Polygon fill masks specifing how polygons will be rasterized.
		 * 
		 * [GL]: https://docs.gl/gl3/glPolygonMode
		 */
		enum class PolygonFillMask : Byte
		{
			/**
			 * @brief Indicates that triangles will be rasterized using wireframe
			 * fill.
			 */
			FORGE_ENUM_DECL(FORGE_WIREFRAME, 0x1)

			/**
			 * @brief Indicates that triangles will be rasterized using solid
			 * fill.
			 */
			FORGE_ENUM_DECL(FORGE_SOLID,     0x2)

			MAX
		};

		/**
		 * @brief Blending functions masks specifing how the red, green, blue, and
		 * alpha source blending factors are computed.
		 * 
		 * [GL]: https://docs.gl/gl3/glBlendFunc
		 */
		enum class BlendFuncMask : Byte
		{
			/**
			 * @brief Indicates to set blending factor to zero.
			 */
			FORGE_ENUM_DECL(FORGE_ZERO,                     0x0)

			/**
			 * @brief Indicates to set blending factor to one.
			 */
			FORGE_ENUM_DECL(FORGE_ONE,                      0x1)

			/**
			 * @brief Indicates to set blending factor to source color vector.
			 */
			FORGE_ENUM_DECL(FORGE_SRC_COLOR,                0x2)

			/**
			 * @brief Indicates to set blending factor to one minus source color
			 * vector.
			 */
			FORGE_ENUM_DECL(FORGE_ONE_MINUS_SRC_COLOR,      0x3)

			/**
			 * @brief Indicates to set blending factor to destination color
			 * vector.
			 */
			FORGE_ENUM_DECL(FORGE_DST_COLOR,                0x4)

			/**
			 * @brief Indicates to set blending factor to one minus destination
			 * color vector.
			 */
			FORGE_ENUM_DECL(FORGE_ONE_MINUS_DST_COLOR,      0x5)

			/**
			 * @brief Indicates to set blending factor to alpha component of the
			 * source color vector.
			 */
			FORGE_ENUM_DECL(FORGE_SRC_ALPHA,                0x6)

			/**
			 * @brief Indicates to set blending factor to one minus alpha
			 * component of the source color vector.
			 */
			FORGE_ENUM_DECL(FORGE_ONE_MINUS_SRC_ALPHA,      0x7)

			/**
			 * @brief Indicates to set blending factor to alpha alpha component of
			 * the destination color vector.
			 */
			FORGE_ENUM_DECL(FORGE_DST_ALPHA,                0x8)

			/**
			 * @brief Indicates to set blending factor to one minus alpha alpha
			 * component of the destination color vector.
			 */
			FORGE_ENUM_DECL(FORGE_ONE_MINUS_DST_ALPHA,      0x9)

			/**
			 * @brief Indicates to set blending factor to constant color vector.
			 */
			FORGE_ENUM_DECL(FORGE_CONSTANT_COLOR,           0x10)

			/**
			 * @brief Indicates to set blending factor to one minus constant color
			 * vector.
			 */
			FORGE_ENUM_DECL(FORGE_ONE_MINUS_CONSTANT_COLOR, 0x11)

			/**
			 * @brief Indicates to set blending factor to alpha component of
			 * constant color vector.
			 */
			FORGE_ENUM_DECL(FORGE_CONSTANT_ALPHA,           0x12)

			/**
			 * @brief Indicates to set blending factor to one minus alpha
			 * component of constant color vector.
			 */
			FORGE_ENUM_DECL(FORGE_ONE_MINUS_CONSTANT_ALPHA, 0x13)

			MAX
		};

		/**
		 * @brief Pixel storage masks specifing the packing of pixel data in
		 * memory.
		 * 
		 * [GL]: https://docs.gl/gl3/glPixelStore
		 */
		enum class PixelStorageMask : Byte
		{
			/**
			 * @brief Indicates the alignment requirements for the start of each
			 * pixel row in memory. 
			 * 
			 * The allowable values are 1, 2, 4, and 8.
			 */
			FORGE_ENUM_DECL(FORGE_PACK_ALIGNMENT, 0x0)

			MAX
		};

		/**
		 * @brief Comparison function masks specifing how to perform tests.
		 * 
		 * [GL]: https://docs.gl/gl3/glDepthFunc
		 *       https://docs.gl/gl3/glStencilFunc
		 */
		enum class ComparisonFuncMask : Byte
		{
			/**
			 * @brief Indicates to never pass the test.
			 */
			FORGE_ENUM_DECL(FORGE_NEVER,    0x0)

			/**
			 * @brief Indicates to pass the test if the incoming value
			 * is less than the stored value.
			 */
			FORGE_ENUM_DECL(FORGE_LESS,     0x1)

			/**
			 * @brief Indicates to pass the test if the incoming value
			 * is equal to the stored value.
			 */
			FORGE_ENUM_DECL(FORGE_EQUAL,    0x2)

			/**
			 * @brief Indicates to pass the test if the incoming value
			 * is less than or equal to the stored value.
			 */
			FORGE_ENUM_DECL(FORGE_LEQUAL,   0x3)

			/**
			 * @brief Indicates to pass the test if the incoming value
			 * is greater than the stored value.
			 */
			FORGE_ENUM_DECL(FORGE_GREATER,  0x4)

			/**
			 * @brief Indicates to pass the test if the incoming value
			 * is not equal to the stored value.
			 */
			FORGE_ENUM_DECL(FORGE_NOTEQUAL, 0x5)

			/**
			 * @brief Indicates to pass the test if the incoming value
			 * is greater than or equal to the stored value.
			 */
			FORGE_ENUM_DECL(FORGE_GEQUAL,   0x6)

			/**
			 * @brief Indicates to always pass the test.
			 */
			FORGE_ENUM_DECL(FORGE_ALWAYS,   0x7)

			MAX
		};
		
		/**
		 * @brief Primitive Topology mask specifing what kind of primitives to
		 * render.
		 * 
		 * [GL]: https://www.khronos.org/opengl/wiki/Primitive
		 */
		enum class PrimitiveTopologyMask : Byte
		{
			/**
			 * @brief Indicates to interpret each individual vertex as a point.
			 */
			FORGE_ENUM_DECL(FORGE_POINT,                    0x0)

			/**
			 * @brief Indicates to interpret each consecutive vertex pairs as a line.
			 */
			FORGE_ENUM_DECL(FORGE_LINE,                     0x1)

			/**
			 * @brief Indicates to interpret all adjacent vertices as a line,
			 * except that the first and last vertices are connected.
			 */
			FORGE_ENUM_DECL(FORGE_LINE_LOOP,                0x2)

			/**
			 * @brief Indicates to interpret all adjacent vertices as a line,
			 * except that the first and last vertices are not connected.
			 */
			FORGE_ENUM_DECL(FORGE_LINE_STRIP,               0x3)

			/**
			 * @brief Indicates to interpret each three consecutive vertices as a
			 * triangle.
			 */
			FORGE_ENUM_DECL(FORGE_TRIANGLE,                 0x4)

			/**
			 * @brief Indicates to fix the first vertex and interpret each two
			 * consecutive vertices with the first as a triangle.
			 */
			FORGE_ENUM_DECL(FORGE_TRIANGLE_FAN,             0x5)

			/**
			 * @brief Indicates to interpret each three consecutive vertices as
			 * triangle strips connected together.
			 */
			FORGE_ENUM_DECL(FORGE_TRIANGLE_STRIP,           0x6)
			
			/**
			 * @brief Indicates to interpret each consecutive vertex pairs as a line.
			 */
			FORGE_ENUM_DECL(FORGE_LINE_ADJACENCY,           0x7)
			
			/**
			 * @brief Indicates to interpret all adjacent vertices as a line,
			 * except that the first and last vertices are not connected.
			 */
			FORGE_ENUM_DECL(FORGE_LINE_STRIP_ADJACENCY,     0x8)

			/**
			 * @brief Indicates to interpret each three consecutive vertices as a
			 * triangle.
			 */
			FORGE_ENUM_DECL(FORGE_TRIANGLE_ADJACENCY,       0x9)

			/**
			 * @brief Indicates to interpret each three consecutive vertices as
			 * triangle strips connected together.
			 */
			FORGE_ENUM_DECL(FORGE_TRIANGLE_STRIP_ADJACENCY, 0x10)

			MAX
		};

		FORGE_FLAG_DECL(ClearFlags)
	}
}

#endif
