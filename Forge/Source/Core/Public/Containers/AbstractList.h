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
			AbstractList(Size count, Size max_capacity)
				: AbstractCollection<ElementType>(count, max_capacity) {}

		public:
			virtual ~AbstractList() = default;

		public:
			/**
			 * @brief Gets a direct pointer to the memory array managed by this
			 * list.
			 *
			 * Elements in the memory array are guranteed to be stored in contiguous
			 * memory locations. This allows the pointer to be offsetted to access
			 * different elements.
			 * 
			 * @return ConstElementTypePtr storing address of the memory array.
			 *
			 * @throws InvalidOperationException if operation not supported by
			 * list.
			 */
			virtual ConstElementTypePtr GetRawData() const = 0;

		public:
			/**
			 * @brief Returns the index of the first occurence of the specified
			 * element in this list, or -1 if it does not contain the element.
			 *
			 * @param[in] element The element to search for the first occurence.
			 *
			 * @return Size storing the index of the first occurrence of the
			 * specified element, or -1 if this list does not contain the element.
			 *
			 * @throws InvalidOperationException if operation not supported by
			 * this collection.
			 */
			virtual I64 FirstIndexOf(ConstElementTypeRef element) const = 0;

			/**
			 * @brief Returns the index of the last occurence of the specified
			 * element in this list, or -1 if it does not contain the element.
			 *
			 * @param[in] element The element to search for the first occurence.
			 *
			 * @return Size storing the index of the last occurrence of the
			 * specified element, or -1 if this list does not contain the element.
			 *
			 * @throws InvalidOperationException if operation not supported by
			 * this collection.
			 */
			virtual I64 LastIndexOf(ConstElementTypeRef element) const = 0;

		public:
			/**
			 * @brief Retreives the last element in the list
			 * 
			 * @return ConstElementTypeRef storing the last element in the list.
			 */
			virtual ConstElementTypeRef PeekBack() const = 0;

			/**
			 * @brief Retreives the first element in the list
			 *
			 * @return ConstElementTypeRef storing the first element in the list.
			 */
			virtual ConstElementTypeRef PeekFront() const = 0;

		public:
			/**
			 * @brief Inserts a new element at the end of this list, after its
			 * current last element.
			 * 
			 * @param[in] element The element to insert in the list.
			 * 
			 * @throws InvalidOperationException if operation not supported by
			 * list.
			 */
			virtual Void PushBack(ElementType&& element) = 0;

			/**
			 * @brief Inserts a new element at the start of this list, before its
			 * current first element.
			 *
			 * @param[in] element The element to insert in the list.
			 *
			 * @throws InvalidOperationException if operation not supported by
			 * list.
			 */
			virtual Void PushFront(ElementType&& element) = 0;

			/**
			 * @brief Inserts a new element at the end of this list, after its
			 * current last element.
			 *
			 * @param[in] element The element to insert in the list.
			 *
			 * @throws InvalidOperationException if operation not supported by
			 * list.
			 */
			virtual Void PushBack(ConstElementTypeRef element) = 0;

			/**
			 * @brief Inserts a new element at the start of this list, before its
			 * current first element.
			 *
			 * @param[in] element The element to insert in the list.
			 *
			 * @throws InvalidOperationException if operation not supported by
			 * list.
			 */
			virtual Void PushFront(ConstElementTypeRef element) = 0;

			/**
			 * @brief Removes the element at the end of the list, effectivly reducing the
			 * list count by one.
			 * 
			 * @throws InvalidOperationException if operation not supported by
			 * list.
			 */
			virtual Void PopBack(void) = 0;

			/**
			 * @brief Removes the element at the start of the list, effectivly reducing the
			 * list count by one.
			 *
			 * @throws InvalidOperationException if operation not supported by
			 * list.
			 */
			virtual Void PopFront(void) = 0;

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
			virtual Void InsertAt(Size index, ElementType&& element) = 0;

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
			virtual Void InsertAt(Size index, ConstElementTypeRef element) = 0;

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
			virtual Void RemoveAt(Size index) = 0;

		public:
			/**
			 * @brief Removes the specified element from this collection. This
			 * operation has different behaviours depending on the collection type.
			 *
			 * Collections that support this operation may place limitations on how
			 * elements are removed from the collection and in what order they are
			 * removed.
			 *
			 * @param[in] element ElementType to remove from this collection.
			 *
			 * @return True if removal was successful and the element was found.
			 *
			 * @throws InvalidOperationException if operation not supported by
			 * this collection.
			 */
			virtual Bool Remove(ConstElementTypeRef element) = 0;

			/**
			 * @brief Searches this collection for the specified element. This
			 * operation has different behaviours depening on the collection type.
			 *
			 * @param[in] element ElementType to search for in this collection.
			 *
			 * @return True if the specified element was found in this collection.
			 */
			virtual Bool Contains(ConstElementTypeRef element) const = 0;
		};
	}
}

#endif // ABSTRACT_LIST_H
