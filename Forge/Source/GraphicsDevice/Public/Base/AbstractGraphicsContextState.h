#ifndef ABSTRACT_GRAPHICS_CONTEXT_STATE_H
#define ABSTRACT_GRAPHICS_CONTEXT_STATE_H

// Placeholder until I implement a Containers::HashTable.

#include <utility>
#include <unordered_map>

#define HashTable(KeyType, ValueType) std::unordered_map<KeyType, ValueType>

#define Insert(Key, Value) insert({Key, Value})


#include <Core/Public/Common/Common.h>
#include <Core/Public/Types/SmartPointer.h>

#include <GraphicsDevice/Public/GraphicsTypes.h>
#include <GraphicsDevice/Public/Base/AbstractHardwareBuffer.h>
#include <GraphicsDevice/Public/Base/AbstractGraphicsContext.h>

using namespace Forge::Common;

namespace Forge {
	namespace Graphics
	{
		/**
		 * @brief Abstract class defining common features of Context state
		 * managers, which is responsible for managing the state of
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
			} m_rasterizer_state;

		protected:
			AbstractGraphicsContextPtr m_graphics_context;

		protected:
			HashTable(U32, TWeakPtr<AbstractHardwareBuffer>) m_bound_buffers;

		public:
			/**
			 * @brief Default Constructor.
			 */
			AbstractGraphicsContextState(AbstractGraphicsContextPtr graphics_context);

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
			 * @param mask[in] The mask to enable and disable writing in the depth
			 * buffer.
			 * 
			 * @returns True if enabled, otherwise false.
			 */
			virtual Bool SetDepthWriteMask(Bool mask) = 0;

			/**
			 * @brief Sets a depth buffer comparison function.
			 *
			 * @param function[in] The comparison function to use for depth testing.
			 * 
			 * @returns True if enabled, otherwise false.
			 */
			virtual Bool SetDepthComparisonFunction(ComparisonFuncMask function) = 0;

		public:
			/**
			 * @brief Sets a bit mask to enable and disable writing of individual
			 * bits in the stencil planes.
			 *
			 * @param mask[in] The bit mask to enable and disable writing of individual bits.
			 * 
			 * @returns True if enabled, otherwise false.
			 */
			virtual Bool SetStencilWriteMask(Byte mask) = 0;

			/**
			 * @brief Sets a stencil buffer comparison function and reference
			 * value.
			 *
			 * @param function[in]  The comparison function to use for stencil testing.
			 * @param reference[in] The reference value for the stencil test.
			 * @param mask[in]      The mask that is ANDed with both the reference value and the stored stencil value. 
			 * 
			 * @returns True if enabled, otherwise false.
			 */
			virtual Bool SetStencilComparisonFunction(ComparisonFuncMask function, I32 reference, U32 mask) = 0;

		public:
			/**
			 * @brief Sets a scissor bounding region where fragments outside
			 * will be discarded.
			 *
			 * @param x[in]      The left corner of the bounding region.
			 * @param y[in]      The lower corner of the bounding region.
			 * @param width[in]  The width of the bounding region.
			 * @param height[in] The height of the bounding region.
			 * 
			 * @returns True if enabled, otherwise false.
			 */
			virtual Bool SetScissorBoundingRegion(I32 x, I32 y, I32 width, I32 height) = 0;

		public:
			/**
			 * @brief Sets whether front or back facing polygons are candidates
			 * for culling.
			 *
			 * @param mode[in] The face culling mode to use.
			 * 
			 * @returns True if enabled, otherwise false.
			 */
			virtual Bool SetFaceCullingMode(FaceCullMask mode) = 0;

		public:
			/**
			 * @brief Sets a constant blend color that is used when blending the
			 * source and destination colors during the blending operation.
			 *
			 * @param red[in]   The blend color red component.
			 * @param green[in] The blend color green component.
			 * @param blue[in]  The blend color blue component.
			 * @param alpha[in] The blend color alpha component.
			 * 
			 * @returns True if enabled, otherwise false.
			 */
			virtual Bool SetColorBlendingConstant(F32 red, F32 green, F32 blue, F32 alpha) = 0;

			/**
			 * @brief Sets a blend function used to calculate blending factor.
			 *
			 * @param src_function[in] The source function to compute the blending factor.
			 * @param dst_function[in] The destination function to compute the blending factor.
			 * 
			 * @returns True if enabled, otherwise false.
			 */
			virtual Bool SetColorBlendingFunction(BlendFuncMask src_function, BlendFuncMask dst_function) = 0;

		public:
			/**
			 * @brief Sets the width of rasterized lines.
			 *
			 * @param width[in] The width of the rasterized line.
			 */
			virtual Void SetLineWidth(F32 width) = 0;

			/**
			 * @brief Sets a texture unit as active.
			 * 
			 * @param index[in] The index of the texture unit to activate.
			 */
			virtual Void SetActiveTexture(U32 index) = 0;

			/**
			 * @brief Sets a fill rasterizaton mode, which specifies how polygons
			 * will be rendered on screen.
			 *
			 * @param mode[in] The fill rasterization mode.
			 */
			virtual Void SetFillMode(PolygonFillMask mode) = 0;

			/**
		     * @brief Sets the orientation of front facing polygons.
		     *
		     * @param front_fac[in]e The front face orientation to use.
		     */
			virtual Void SetFrontFace(FrontFaceMask front_face) = 0;

			/**
			 * @brief Sets a pixel storage mode.
			 *
			 * @param mode[in]  The pixel storage mode to be set.
			 * @param value[in] The value of the pixel storage mode.
			 */
			virtual Void SetPixelStorage(PixelStorageMask mode, I32 value) = 0;

			/**
			 * @brief Sets a  clear values for the color buffers.
			 * 
			 * @param red[in]   The color buffer red component.
			 * @param green[in] The color buffer green component.
			 * @param blue[in]  The color buffer blue component.
			 * @param alpha[in] The color buffer alpha component.
			 */
			virtual Void SetColorClear(F32 red, F32 green, F32 blue, F32 alpha) = 0;
			
			/**
			 * @brief Sets a mask to enable and disable writing of individual 
			 * components of the color buffer.
			 * 
			 * @param red[in]   The color buffer red component.
			 * @param green[in] The color buffer green component.
			 * @param blue[in]  The color buffer blue component.
			 * @param alpha[in] The color buffer alpha component.
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

			virtual Void BindHardwareBuffer(AbstractHardwareBufferPtr hardware_buffer) = 0;

			// virtual Void BindVertexDecleration(VertexDeclerationPtr vertex_decleration) = 0;
		};

		FORGE_TYPEDEF_DECL(AbstractGraphicsContextState)

		FORGE_FORCE_INLINE AbstractGraphicsContextState::AbstractGraphicsContextState(AbstractGraphicsContextPtr graphics_context)
			: m_graphics_context(graphics_context) {}
	}
}

#endif // ABSTRACT_GRAPHICS_CONTEXT_STATE_H
