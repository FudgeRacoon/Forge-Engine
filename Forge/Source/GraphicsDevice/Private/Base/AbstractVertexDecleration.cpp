#include <GraphicsDevice/Public/Base/AbstractVertexDecleration.h>

namespace Forge {
	namespace Graphics
	{
		Bool AbstractVertexDecleration::operator ==(const AbstractVertexDecleration& other) const
		{
			if (m_vertex_element_list.GetCount() != other.m_vertex_element_list.GetCount())
				return FORGE_FALSE;

			TDynamicArray<VertexElement>::ConstIterator start, end, other_start, other_end;

			start = m_vertex_element_list.GetStartConstItr();
			end = m_vertex_element_list.GetEndConstItr();

			other_start = other.m_vertex_element_list.GetStartConstItr();
			other_end = other.m_vertex_element_list.GetEndConstItr();

			for (; start != end && other_start != other_end; start++, other_start++)
				if (!MemoryCompare(&(*start), &(*other_start), sizeof(VertexElement)))
					return FORGE_FALSE;

			return FORGE_TRUE;
		}
		Bool AbstractVertexDecleration::operator !=(const AbstractVertexDecleration& other) const
		{
			if (m_vertex_element_list.GetCount() == other.m_vertex_element_list.GetCount())
				return FORGE_FALSE;

			TDynamicArray<VertexElement>::ConstIterator start, end, other_start, other_end;

			start = m_vertex_element_list.GetStartConstItr();
			end = m_vertex_element_list.GetEndConstItr();

			other_start = other.m_vertex_element_list.GetStartConstItr();
			other_end = other.m_vertex_element_list.GetEndConstItr();

			for (; start != end && other_start != other_end; start++, other_start++)
				if (MemoryCompare(&(*start), &(*other_start), sizeof(VertexElement)))
					return FORGE_FALSE;

			return FORGE_TRUE;
		}

		Size AbstractVertexDecleration::GetVertexSize(U16 source) const
		{
			Size result = 0;

			m_vertex_element_list.ForEach([&result, source](ConstVertexElementRef element) -> Void
				{
					if (element.GetSource() == source)
						result += element.GetSize();
				}
			);

			return result;
		}

		Size AbstractVertexDecleration::GetVertexElementCount(Void) const
		{
			return m_vertex_element_list.GetCount();
		}

		ConstTDynamicArrayRef<VertexElement> AbstractVertexDecleration::GetVertexElements(Void) const
		{
			return m_vertex_element_list;
		}
		ConstTDynamicArrayRef<VertexElement> AbstractVertexDecleration::GetVertexElements(U16 source) const
		{
			TDynamicArray<VertexElement> result;

			m_vertex_element_list.ForEach([&result, source](ConstVertexElementRef element) -> Void
				{
					if (element.GetSource() == source)
						result.PushBack(element);
				}
			);

			return result;
		}
		ConstTDynamicArrayRef<VertexElement> AbstractVertexDecleration::GetVertexElements(VertexElementSemanticMask semantic) const
		{
			TDynamicArray<VertexElement> result;

			m_vertex_element_list.ForEach([&result, semantic](ConstVertexElementRef element) -> Void
				{
					if (element.GetSemantic() == semantic)
						result.PushBack(element);
				}
			);

			return result;
		}

		Void AbstractVertexDecleration::AddVertexElement(VertexElement vertex_element)
		{
			m_vertex_element_list.PushBack(vertex_element);
		}
		Void AbstractVertexDecleration::RemoveVertexElement(VertexElementSemanticMask semantic)
		{
			m_vertex_element_list.ForEach([this, semantic](VertexElementRef element) -> Void
				{
					if (element.GetSemantic() == semantic)
						m_vertex_element_list.Remove(element);
				}
			);
		}
		Void AbstractVertexDecleration::ModifyVertexElement(U16 index, VertexElement vertex_element)
		{
			m_vertex_element_list[index] = vertex_element;
		}

		Void AbstractVertexDecleration::Clear(Void)
		{
			m_vertex_element_list.Clear();
		}
	}
}
