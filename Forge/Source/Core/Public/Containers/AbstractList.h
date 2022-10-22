#ifndef ABSTRACT_LIST_H
#define ABSTRACT_LIST_H

#include "AbstractCollection.h"

#include "Core/Public/Common/TypeDefinitions.h"

namespace Forge {
	namespace Containers
	{
		template<typename InElementType>
		class AbstractList : public AbstractCollection<InElementType>
		{
		private:
			using ElementType         = InElementType;
			using ElementTypeRef      = InElementType&;
			using ElementTypePtr      = InElementType*;
			using ConstElementType    = const InElementType;
			using ConstElementTypeRef = const InElementType&;
			using ConstElementTypePtr = const InElementType*;

		public:
			class Iterator;
			class ConstIterator;

		public:
			AbstractList(Size size, Size capacity)
				: AbstractCollection<ElementType>(size, capacity) {}
			virtual ~AbstractList() = default;

		public:
			/**
			 * @brief Gets the size of the storage space allocated for this
			 * collection.
			 *
			 * The capacity is not necessarily equal to the size. It can be equal
			 * or greater, with the extra space allowing to accommodate for growth
			 * without the need to reallocate on each insertion in the case of 
			 * dynamic containers
			 *
			 * @return Size storing the capacity.
			 *
			 * @throws InvalidOperationException if operation not supported by
			 * collection.
			 */
			virtual Size GetCapacity() const;

			/**
			 * @brief Gets a direct pointer to the memory array managed by this
			 * collection.
			 *
			 * Elements in the memory array are guranteed to stored in contiguous
			 * memory locations. This allows the pointer to be offsetted to access
			 * different elements.
			 * 
			 * @return Const pointer storing address of the memory array.
			 *
			 * @throws InvalidOperationException if operation not supported by
			 * collection.
			 */
			virtual ConstElementTypePtr GetRawData() const = 0;

		public:
			/**
			 * @brief Returns the index of the first occurence of the specified
			 * element in this list, or -1 if it does not contain the element.
			 *
			 * @param[in] value The element to search for the first occurence.
			 *
			 * @return Size storing the index of the first occurrence of the
			 * specified element, or -1 if this list does not contain the element.
			 *
			 * @throws InvalidOperationException if operation not supported by
			 * this collection.
			 */
			virtual I64 FirstIndexOf(ConstElementTypeRef value) const = 0;

			/**
			 * @brief Returns the index of the last occurence of the specified
			 * element in this list, or -1 if it does not contain the element.
			 * 
			 * @param[in] value The element to search for the last occurence.
			 * 
			 * @return Size storing the index of the last occurrence of the 
			 * specified element, or -1 if this list does not contain the element.
			 * 
			 * @throws InvalidOperationException if operation not supported by
			 * this collection.
			 */
			virtual I64 LastIndexOf(ConstElementTypeRef value) const = 0;

		public:
			/**
			 * @brief Inserts the specified element in the specified index.
			 *
			 * This function will increase count size by one and shift all elements
			 * that preceed the newly inserted element. If the number of elements
			 * overflow the capacity of the collection, a reallocation will occur
			 * to accomodate for the increased size if supported.
			 *
			 * @param[in] ui_index The numerical index to insert the element at.
			 * @param[in] element  The element to insert in the list.
			 *
			 * @throw IndexOutOfRangeException if index to insert element is out
			 * of range.
			 *
			 * @throw InvalidOperationException if operation not supported by
			 * this list.
			 */
			virtual Void InsertAt(Size ui_index, ElementType&& element) = 0;

			/**
			 * @brief Inserts the specified element in the specified index.
			 * 
			 * This function will increase count size by one and shift all elements
			 * that preceed the newly inserted element. If the number of elements 
			 * overflow the capacity of the collection, a reallocation will occur
			 * to accomodate for the increased size if supported.
			 * 
			 * @param[in] ui_index The numerical index to insert the element at.
			 * @param[in] element  The element to insert in the list.
			 * 
			 * @throw IndexOutOfRangeException if index to insert element is out
			 * of range.
			 * 
			 * @throw InvalidOperationException if operation not supported by
			 * this list.
			 */
			virtual Void InsertAt(Size ui_index, ConstElementTypeRef element) = 0;

			/**
			 * @brief Inserts the specified element in the specified position.
			 *
			 * This function will increase count size by one and shift all elements
			 * that preceed the newly inserted element. If the number of elements
			 * overflow the capacity of the collection, a reallocation will occur
			 * to accomodate for the increased size if supported.
			 *
			 * @param[in] position The numerical index to insert the element at.
			 * @param[in] element  The element to insert in the list.
			 *
			 * @throw IndexOutOfRangeException if index to insert element is out
			 * of range.
			 *
			 * @throw InvalidOperationException if operation not supported by
			 * this list.
			 */
			virtual Void InsertAt(Iterator& position, ElementType&& element) = 0;

			/**
			 * @brief Inserts the specified element in the specified position.
			 *
			 * This function will increase count size by one and shift all elements
			 * that preceed the newly inserted element. If the number of elements
			 * overflow the capacity of the collection, a reallocation will occur
			 * to accomodate for the increased size if supported.
			 *
			 * @param[in] position The numerical index to insert the element at.
			 * @param[in] element  The element to insert in the list.
			 *
			 * @throw IndexOutOfRangeException if index to insert element is out
			 * of range.
			 *
			 * @throw InvalidOperationException if operation not supported by
			 * this list.
			 */
			virtual Void InsertAt(Iterator& position, ConstElementTypeRef element) = 0;

			/**
			* @brief Removes an element in the specified index.
			*
			* This function will decrease the count size by one and shift all
			* elements that preceed the removed element.
			*
			* @param[in] ui_index The numerical index to remove the element at.
			*
			* @throw IndexOutOfRangeException if index to remove element at is out
			* of range.
			*
			* @throw InvalidOperationException if operation not supported by
			* this list.
			*/
			virtual Void RemoveAt(Size ui_index) = 0;

			/**
			* @brief Removes an element in the specified position.
			*
			* This function will decrease the count size by one and shift all
			* elements that preceed the removed element.
			*
			* @param[in] position The numerical index to remove the element at.
			*
			* @throw IndexOutOfRangeException if index to remove element at is out
			* of range.
			*
			* @throw InvalidOperationException if operation not supported by
			* this list.
			*/
			virtual Void RemoveAt(Iterator& position) = 0;
		};

		template<typename T>
		FORGE_FORCE_INLINE Size AbstractList<T>::GetCapacity() const { return this->m_capacity; }
	}
}

#endif // ABSTRACT_LIST_H
