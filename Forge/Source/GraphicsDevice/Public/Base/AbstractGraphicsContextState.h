#ifndef ABSTRACT_GRAPHICS_CONTEXT_STATE_H
#define ABSTRACT_GRAPHICS_CONTEXT_STATE_H

#include <Core/Public/Common/Common.h>

#include <GraphicsDevice/Public/GraphicsTypes.h>
#include <GraphicsDevice/Public/GraphicsContext.h>

namespace Forge {
	namespace Graphics
	{
		/**
		 * @brief Context state class which is responsible for managing the state of
		 * the graphics pipeline. 
		 * 
		 * @author Karim Hisham.
		 */
		class AbstractGraphicsContextState
		{
		protected:
			struct RasterizerState
			{
				/**
				 * @brief The raster line width.
				 */
				F32 line_width;

				/**
				 * @brief The current clear color to use.
				 */
				Byte color_clear[4];

				/**
				 * @brief The current color write mask to use.
				 */
				Byte color_write_mask[4];

				/**
				 * @brief The current front face winding to use.
				 */
				FrontFaceMask front_face_mode;

				/**
				 * @brief The current fill mode of polygons to use.
				 */
				PolygonFillMask polygon_fill_mode;

				struct DepthState
				{
					/**
					 * @brief Is depth testing enabled or not?
					 */
					Bool is_enabled;

					/**
					 * @brief The current depth write mask used.
					 */
					Bool write_mask;

					/**
					 * @brief The current depth comparison function used.
					 */
					ComparisonFuncMask comparison_function;
				} depth_state;

				struct StencilState
				{
					/**
					 * @brief Is stencil testing enabled or not?
					 */
					Bool is_enabled;

					/**
					 * @brief The current stencil write mask used.
					 */
					Byte write_mask;

					/**
					 * @brief The current stencil comparison function used.
					 */
					ComparisonFuncMask comparison_function;
				} stencil_state;

				struct ScissorState
				{
					/**
					 * @brief Is scissor testing enabled or not?
					 */
					Bool is_enabled;

					/**
					 * @brief The current scissor bounding region used.
					 */
					I32 bounding_region[4];
				} scissor_state;

				struct FaceCullingState
				{
					/**
					 * @brief Is face culling enabled or not?
					 */
					Bool is_enabled;

					/**
					 * @brief The current face culling mode to use.
					 */
					FaceCullMask mode;
				} face_culling_state;

				struct ColorBlendingState
				{
					/**
					 * @brief Is color blending enabled or not?
					 */
					Bool is_enabled;

					/**
					 * @brief The current constant blending color to use.
					 */
					F32 constant[4];

					/**
					 * @brief The current blending source function to use.
					 */
					BlendFuncMask src_function;

					/**
					 * @brief The current blending destination function to use.
					 */
					BlendFuncMask dst_function;

				} color_blending_state;
			};

		protected:
			RasterizerState m_rasterizer_state;

		protected:
			GraphicsContextPtr m_graphics_context;

		public:
			/**
			 * @brief Default Constructor.
			 */
			AbstractGraphicsContextState(GraphicsContextPtr graphics_context)
				: m_graphics_context(graphics_context) {}

			/**
			 * @brief Destructor.
			 */
			virtual ~AbstractGraphicsContextState(Void) = default;

		public:
			/**
			 * @brief Enables or disbales depth test.
			 *
			 * @param enable The state of depth testing.
			 */
			virtual Void EnableDepthTest(Bool enable) = 0;

			/**
			 * @brief Enables or disbales stencil test.
			 *
			 * @param enable The state of stencil testing.
			 */
			virtual Void EnableStencilTest(Bool enable) = 0;

			/**
			 * @brief Enables or disbales scissor test.
			 *
			 * @param enable The state of scissor testing.
			 */
			virtual Void EnableScissorTest(Bool enable) = 0;

			/**
			 * @brief Enables or disables polygon culling based on their winding.
			 *
			 * @param enable The state of face culling.
			 */
			virtual Void EnableFaceCulling(Bool enable) = 0;

			/**
			 * @brief Enables or disables blending of the computed fragment color
			 * values with the values in the color buffer.
			 *
			 * @param enable The state of blending.
			 */
			virtual Void EnableColorBlending(Bool enable) = 0;

		public:
			/**
			 * @brief Sets a mask to enable and disable writing in the depth
			 * buffer.
			 *
			 * @param mask The mask to enable and disable writing in the depth
			 * buffer.
			 * 
			 * @returns True if enabled, otherwise false.
			 */
			virtual Bool SetDepthWriteMask(Bool mask) = 0;

			/**
			 * @brief Sets a depth buffer comparison function.
			 *
			 * @param function The comparison function to use for depth testing.
			 * 
			 * @returns True if enabled, otherwise false.
			 */
			virtual Bool SetDepthComparisonFunction(ComparisonFuncMask function) = 0;

		public:
			/**
			 * @brief Sets a bit mask to enable and disable writing of individual
			 * bits in the stencil planes.
			 *
			 * @param mask The bit mask to enable and disable writing of
			 * individual bits.
			 * 
			 * @returns True if enabled, otherwise false.
			 */
			virtual Bool SetStencilWriteMask(Byte mask) = 0;

			/**
			 * @brief Sets a stencil buffer comparison function and reference
			 * value.
			 *
			 * @param function The comparison function to use for depth testing.
			 * @param ref The reference value for the stencil test.
			 * @param mask The mask that is ANDed with both the reference value
			 * and the stored stencil value when the test is done. 
			 * 
			 * @returns True if enabled, otherwise false.
			 */
			virtual Bool SetStencilComparisonFunction(ComparisonFuncMask function, I32 ref, U32 mask) = 0;

		public:
			/**
			 * @brief Sets a scissor bounding region where fragments outside
			 * will be discarded.
			 *
			 * @param x      The left corner of the bounding region.
			 * @param y      The lower corner of the bounding region.
			 * @param width  The width of the bounding region.
			 * @param height The height of the bounding region.
			 * 
			 * @returns True if enabled, otherwise false.
			 */
			virtual Bool SetScissorBoundingRegion(I32 x, I32 y, I32 width, I32 height) = 0;

		public:
			/**
			 * @brief Sets whether front or back facing polygons are candidates
			 * for culling.
			 *
			 * @param FaceCullMask The face culling mode to use.
			 * 
			 * @returns True if enabled, otherwise false.
			 */
			virtual Bool SetFaceCullingMode(FaceCullMask mode) = 0;

		public:
			/**
			 * @brief Sets a constant blend color that is used when blending the
			 * source and destination colors during the blending operation.
			 *
			 * @param red   The blend color red component.
			 * @param green The blend color green component.
			 * @param blue  The blend color blue component.
			 * @param alpha The blend color alpha component.
			 * 
			 * @returns True if enabled, otherwise false.
			 */
			virtual Bool SetColorBlendingConstant(F32 red, F32 green, F32 blue, F32 alpha) = 0;

			/**
			 * @brief Sets a blend function used to calculate blending factor.
			 *
			 * @param src_function The source function to compute the blending factor.
			 * @param dst_function The destination function to compute the blending factor.
			 * 
			 * @returns True if enabled, otherwise false.
			 */
			virtual Bool SetColorBlendingFunction(BlendFuncMask src_function, BlendFuncMask dst_function) = 0;

		public:
			/**
			 * @brief Sets the width of rasterized lines.
			 *
			 * @param width The width of the rasterized line.
			 */
			virtual Void SetLineWidth(F32 width) = 0;

			/**
			 * @brief Sets a texture unit as active.
			 * 
			 * @param index The index of the texture unit to activate.
			 */
			virtual Void SetActiveTexture(U32 index) = 0;

			/**
			 * @brief Sets a fill rasterizaton mode, which specifies how polygons
			 * will be rendered on screen.
			 *
			 * @param mode The fill rasterization mode.
			 */
			virtual Void SetFillMode(PolygonFillMask mode) = 0;

			/**
		     * @brief Sets the orientation of front facing polygons.
		     *
		     * @param front_face The front face orientation to use.
		     */
			virtual Void SetFrontFace(FrontFaceMask front_face) = 0;

			/**
			 * @brief Sets a pixel storage mode.
			 *
			 * @param mode  The pixel storage mode to be set.
			 * @param value The value of the pixel storage mode.
			 */
			virtual Void SetPixelStorage(PixelStorageMask mode, I32 value) = 0;

			/**
			 * @brief Sets a  clear values for the color buffers.
			 * 
			 * @param red   The color buffer red component.
			 * @param green The color buffer green component.
			 * @param blue  The color buffer blue component.
			 * @param alpha The color buffer alpha component.
			 */
			virtual Void SetColorClear(F32 red, F32 green, F32 blue, F32 alpha) = 0;
			
			/**
			 * @brief Sets a mask to enable and disable writing of individual 
			 * components of the color buffer.
			 * 
			 * @param red   The color buffer red component.
			 * @param green The color buffer green component.
			 * @param blue  The color buffer blue component.
			 * @param alpha The color buffer alpha component.
			 */
			virtual Void SetColorWriteMask(F32 red, F32 green, F32 blue, F32 alpha) = 0;

		public:
			/**
			 * @brief Initializes the entire context state with default values and
			 * store the states.
			 */
			virtual Void InitializeCache(Void) = 0;

			/**
			 * @brief Invalidates the entire context state and unbinds all bounded
			 * textures, buffers, shaders, and vertex arrays.
			 */
			virtual Void InvalidateCache(Void) = 0;

		public:
			// virtual Void BindTexture(TexturePtr texture) = 0;
			
			// virtual Void BindGPUProgram(GPUProgramPtr gpu_program) = 0;

			// virtual Void BindFrameBuffer(RenderTargetPtr render_target) = 0;

			// virtual Void BindHardwareBuffer(HardwareBufferPtr hardware_buffer) = 0;

			// virtual Void BindVertexDecleration(VertexDeclerationPtr vertex_decleration) = 0;
		};

		FORGE_TYPEDEF_DECL(AbstractGraphicsContextState, AbstractGraphicsContextState)
	}
}

#endif
