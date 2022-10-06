#ifndef ABSTRACT_ITERATOR_H
#define ABSTRACT_ITERATOR_H

#include "Core/Public/Common/TypeDefinitions.h"

namespace Forge {
	namespace Containers
	{
		template<typename InElementType>
		class AbstractIterator
		{
		protected:
			using ElementType         = InElementType;
			using ElementTypeRef      = InElementType&;
			using ElementTypePtr      = InElementType*;
			using ConstElementType    = const InElementType;
			using ConstElementTypeRef = const InElementType&;
			using ConstElementTypePtr = const InElementType*;

		protected:
			ElementTypePtr m_raw_ptr;

		public:
			AbstractIterator(ElementTypePtr ptr)
				: m_raw_ptr(ptr) {}

		public:
			AbstractIterator(AbstractIterator<ElementType>&& rhs)
			{
				m_raw_ptr = rhs.m_raw_ptr;
				rhs.m_raw_ptr = nullptr;
			}
			AbstractIterator(const AbstractIterator<ElementType>& rhs)
			{
				m_raw_ptr = rhs.m_raw_ptr;
			}

		public:
			virtual ~AbstractIterator() = default;

		public:
			virtual AbstractIterator<ElementType>& operator ++(void) = 0;
			virtual AbstractIterator<ElementType>& operator ++(I32 junk) = 0;

		public:
			virtual AbstractIterator<ElementType>& operator --(void) = 0;
			virtual AbstractIterator<ElementType>& operator --(I32 junk) = 0;

		public:
			virtual Bool operator ==(const AbstractIterator<ElementType>& itr);
			virtual Bool operator !=(const AbstractIterator<ElementType>& itr);

		public:
			virtual ElementTypeRef operator *(void);
			virtual ElementTypePtr operator ->(void);
		};

		template<typename T>
		FORGE_FORCE_INLINE Bool AbstractIterator<T>::operator ==(const AbstractIterator<ElementType>& itr) { return m_raw_ptr == itr.m_raw_ptr; }
		template<typename T>
		FORGE_FORCE_INLINE Bool AbstractIterator<T>::operator !=(const AbstractIterator<ElementType>& itr) { return m_raw_ptr != itr.m_raw_ptr; }

		template<typename T>
		FORGE_FORCE_INLINE T& AbstractIterator<T>::operator *(void)  { return *m_raw_ptr; }
		template<typename T>
		FORGE_FORCE_INLINE T* AbstractIterator<T>::operator ->(void) { return m_raw_ptr; }
	}
}

#endif // ABSTRACT_ITERATOR_H
