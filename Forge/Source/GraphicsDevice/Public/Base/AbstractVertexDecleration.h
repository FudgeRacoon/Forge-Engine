#ifndef ABSTRACT_VERTEX_DECLERATION_H
#define ABSTRACT_VERTEX_DECLERATION_H

#include <Core/Public/Common/Common.h>
#include <Core/Public/Memory/MemoryUtilities.h>
#include <Core/Public/Containers/TDynamicArray.h>

#include <GraphicsDevice/Public/VertexElement.h>

using namespace Forge::Memory;
using namespace Forge::Containers;

namespace Forge {
	namespace Graphics
	{
		/**
		 * @brief Abstract class defining the layout of a hardware vertex buffer.
		 * 
		 * @author Karim Hisham.
		 */
		class FORGE_API AbstractVertexDecleration
		{
		private:
			TDynamicArray<VertexElement> m_vertex_element_list;

		public:
			/**
			 * @brief Default constructor.
			 */
			AbstractVertexDecleration(Void) = default;

		public:
			/**
			 * @brief Default destructor.
			 */
			virtual ~AbstractVertexDecleration(Void) = default;
	
		public:
			/**
			 * @brief Equality operator.
			 */
			Bool operator ==(const AbstractVertexDecleration& other) const;
				
			/**
			 * @brief Inequality operator.
			 */
			Bool operator !=(const AbstractVertexDecleration& other) const;

		public:
			/**
			 * @brief Gets the size of the vertex defined by the vertex
			 * decleration in bytes.
			 * 
			 * @param source[in] The source of the vertex element.
			 * 
			 * @returns Size storing the size of the vertex defined by the vertex
			 * decleration in bytes.
			 */
			Size GetVertexSize(U16 source) const;

		public:
			/**
			 * @brief Gets the number of elements in the vertex decleration.
			 * 
			 * @returns Size storing the number of elements in the vertex
			 * decleration.
			 */
			Size GetVertexElementCount(Void) const;

		public:
			/**
			 * @brief Gets the vertex elements in the vertex decleration.
			 * 
			 * This function provides read-only access to the returned elements.
			 * 
			 * @returns VertexElementList storing the vertex elements.
			 */
			ConstTDynamicArrayRef<VertexElement> GetVertexElements(Void) const;

			/**
			 * @brief Gets the vertex elements in the vertex decleration using
			 * the specified source.
			 *
			 * This function provides read-only access to the returned elements.
			 *
			 * @param source[in] The source of the vertex element.
			 * 
			 * @returns VertexElementList storing the vertex elements.
			 */
			ConstTDynamicArrayRef<VertexElement> GetVertexElements(U16 source) const;

			/**
			 * @brief Gets the vertex elements in the vertex decleration using
			 * the specified semantic.
			 *
			 * This function provides read-only access to the returned elements.
			 *
			 * @param semantic[in] The semantic of the vertex element.
			 *
			 * @returns VertexElementList storing the vertex elements.
			 */
			ConstTDynamicArrayRef<VertexElement> GetVertexElements(VertexElementSemanticMask semantic) const;

		public:
			/**
			 * @brief Adds a vertex element to the vertex decleration.
			 * 
			 * @param vertex_element[in] The vertex element to add.
			 */
			Void AddVertexElement(VertexElement vertex_element);

			/**
		     * @brief Removes a vertex element from the vertex decleration using
		     * the specified semantic.
		     *
		     * @param semantic[in] The semantic of the vertex element.
		     */
			Void RemoveVertexElement(VertexElementSemanticMask semantic);

			/**
			 * @brief Modifies a vertex element stored inside the vertex decleration.
			 * 
			 * @param index[in]          The index of the vertex element inside the list.
			 * @param vertex_element[in] The new vertex element data.
			 */
			Void ModifyVertexElement(U16 index, VertexElement vertex_element);

		public:
			/**
			 * @brief Removes all vertex elements from the vertex decleration.
			 */
			Void Clear(Void);
		};


	}
}
#endif // ABSTRACT_VERTEX_DECLERATION_H
