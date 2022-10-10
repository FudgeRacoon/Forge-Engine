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

		protected:
			Size m_index_ptr;

		public:
			class Iterator;
			using ConstIterator = const Iterator;

		public:
			AbstractList(Size size, Size max_size)
				: m_index_ptr(0), AbstractCollection<ElementType>(size, max_size) {}
			virtual ~AbstractList() = default;

		public:
			virtual ElementTypeRef operator [](Size index) = 0;

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
			virtual I64 FirstIndexOf(ElementType value) const = 0;

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
			virtual I64 LastIndexOf(ElementType value) const = 0;

		public:
			/**
			 * @brief Inserts the specified element after the element in the
			 * specified position in the list.
			 * 
			 * This effectively increases the list size by one, and causes a new
			 * reallocation if the size of the list surpasses the current capacity.
			 * Inserting elements at a position past the capacity bounds, will
			 * reposition all element after the specified position to their new
			 * positions after reallocation.
			 * 
			 * @param[in] index   The numerical index to insert the element at.
			 * @param[in] element The element to insert in the list.
			 * 
			 * @throw InvalidOperationException if operation not supported by
			 * this collection.
			 */
			virtual Void InsertAt(Size index, ElementType element) = 0;

			/**
			 * @brief Inserts the specified element after the element in the
			 * specified position in the list.
			 *
			 * This effectively increases the list size by one, and causes a new
			 * reallocation if the size of the list surpasses the current capacity.
			 * Inserting elements at a position past the capacity bounds, will
			 * reposition all element after the specified position to their new
			 * positions after reallocation.
			 *
			 * @param[in] index   The iterator position to insert the element at.
			 * @param[in] element The element to insert in the list.
			 *
			 * @throw InvalidOperationException if operation not supported by
			 * this collection.
			 */
			virtual Void InsertAt(Iterator& index, ElementType element) = 0;

			/**
			 * @brief Removes the specified element after the element in the
			 * specified position in the list.
			 *
			 * This effectively decreases the list size by one, and destroys the
			 * element but does not deallocate the memory the element was stored
			 * at.
			 *
			 * @param[in] index The numerical index to remove the element at.
			 *
			 * @throw InvalidOperationException if operation not supported by
			 * this collection.
			 */
			virtual Void RemoveAt(Size index) = 0;

			/**
			 * @brief Removes the specified element after the element in the
			 * specified position in the list.
			 *
			 * This effectively decreases the list size by one, and destroys the
			 * element but does not deallocate the memory the element was stored
			 * at.
			 *
			 * @param[in] index The iterator position to remove the element at.
			 *
			 * @throw InvalidOperationException if operation not supported by
			 * this collection.
			 */
			virtual Void RemoveAt(Iterator& index) = 0;
		};

		template<typename T>
		FORGE_FORCE_INLINE Size AbstractList<T>::GetCapacity() const { return this->m_capacity; }
	}
}

#endif // ABSTRACT_LIST_H
