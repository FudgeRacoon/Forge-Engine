#ifndef ABSTRACT_COLLECTION_H
#define ABSTRACT_COLLECTION_H

#include "Core/Public/Common/Compiler.h"
#include "Core/Public/Common/TypeDefinitions.h"

namespace Forge {
	namespace Containers
	{
		template<typename InElementType>
		class AbstractCollection
		{
		private:
			using ElementType         = InElementType;
			using ElementTypeRef      = InElementType&;
			using ElementTypePtr      = InElementType*;
			using ConstElementType    = const InElementType;
			using ConstElementTypeRef = const InElementType&;
			using ConstElementTypePtr = const InElementType*;

		protected:
			Size m_size;
			Size m_capacity;
		
		public:
			class Iterator;
			using ConstIterator = const Iterator;

		public:
			AbstractCollection(Size size, Size capacity)
				: m_size(size), m_capacity(capacity) {}
			virtual ~AbstractCollection() = default;
		
		public:
			/**
			 * @brief Gets the number of elements stored in this collection.
			 * 
			 * @return Size storing the number of elements.
			 */
			virtual Size GetSize(void) const;

		public:
			/**
			 * @brief Returns an iterator pointing to the first element in the
			 * collection.
			 *
			 * @return Iterator pointing to the first element.
			 */
			virtual Iterator GetStartItr(void) = 0;

			/**
			 * @brief Returns an iterator pointing to the past-end element in the
			 * collection.
			 *
			 * @return Iterator pointing to the past-end element element.
			 */
			virtual Iterator GetEndItr(void) = 0;

			/**
			 * @brief Returns a constant iterator pointing to the first element in
			 * the collection.
			 *
			 * @return ConstIterator pointing to the first element.
			 */
			virtual ConstIterator GetStartConstItr(void) = 0;

			/**
			 * @brief Returns a constant iterator pointing to the past-end element
			 * in the collection.
			 *
			 * @return Iterator pointing to the past-end element element.
			 */
			virtual ConstIterator GetEndConstItr(void) = 0;

		public:
			/**
			 * @brief Checks whether this collection is full and is at maximum
			 * size.
			 *
			 * @return True if this collection is full.
			 */
			virtual Bool IsFull(void) const;

			/**
			 * @brief Checks whether this collection is empty and not storing any
			 * elements.
			 * 
			 * @return True if this collection is empty.
			 */
			virtual Bool IsEmpty(void) const;

			/**
			 * @brief Checks whether this collection is equal to the specified
			 * collection.
			 * 
			 * Equality between collections is governed by their size, the order
			 * of the elements in the collection and the eqaulity of the elements
			 * they store.
			 * 
			 * @param[in] collection The collection to be compared with this
			 * collection.
			 * 
			 * @return True if the specified collection is equal to this collection. 
			 */
			virtual Bool IsEqual(const AbstractCollection<ElementType>& collection) const = 0;

		public:
			/**
			 * @brief Returns an array containing all the elements returned by this
			 * collection's forward iterator.
			 * 
			 * The length of the array is equal to the number of elements returned
			 * by the iterator. If this collection makes any guarantees as to what 
			 * order its elements are returned by its iterator, this method must 
			 * return the elements in the same order. The returned array contains 
			 * deep copies of the elements.
			 * 
			 * @return ElementTypePtr storing the address of the array.
			 * 
			 * @throws InvalidOperationException if operation not supported by
			 * this collection.
			 */
			virtual ElementTypePtr ToArray(void) const = 0;

			/**
			 * @brief Returns an array containing all the elements returned by this
			 * collection's forward iterator.
			 *
			 * The length of the array is equal to the number of elements returned
			 * by the iterator. If this collection makes any guarantees as to what
			 * order its elements are returned by its iterator, this method must
			 * return the elements in the same order. The returned array contains
			 * deep copies of the elements.
			 *
			 * @param[out] array The array to store this collection's elements.
			 * 
			 * @return ElementTypePtr storing the address of the array.
			 * 
			 * @throws InvalidOperationException if operation not supported by
			 * this collection.
			 */
			virtual ElementTypePtr ToArray(ElementTypePtr array) const = 0;

		public:
			/**
			 * @brief Inserts the specified element in this collection. This
			 * operation has different behaviours depending on the collection type.
			 * 
			 * Collections that support this operation may place limitations on how
			 * elements are inserted into the collection and in what order they are
			 * placed.
			 * 
			 * @param[in] element ElementType to insert in this collection.
			 * 
			 * @return True if insertion was successful and no duplicates in
			 * this collection if supported.
			 * 
			 * @throws InvalidOperationException if operation not supported by
			 * this collection.
			 */
			virtual Bool Insert(ElementType element) = 0;

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
			virtual Bool Remove(ElementType element) = 0;

			/**
			 * @brief Searches this collection for the specified element. This
			 * operation has different behaviours depening on the collection type.
			 * 
			 * @param[in] element ElementType to search for in this collection.
			 * 
			 * @return True if the specified element was found in this collection.
			 */
			virtual Bool Contains(ElementType element) = 0;

		public:
			/**
			 * @brief Inserts all the elements in the specified collection to this
			 * collection. This operation has different behaviours depending on the
			 * collection type.
			 * 
			 * @param[in] collection The collection containing elements to be added
			 * to this collection.
			 * 
			 * @return True if insertion was successful and no duplicates in
			 * this collection if supported.
			 * 
			 * @throws InvalidOperationException if operation not supported by
			 * this collection.
			 */
			virtual Bool InsertAll(const AbstractCollection<ElementType>& collection) = 0;

			/**
			 * @brief Removes all the elements in the specified collection from this
			 * collection. This operation has different behaviours depending on the
			 * collection type.
			 *
			 * @param[in] collection The collection containing elements to be 
			 * removed from this collection.
			 *
			 * @return True if removal was successful and the elements were found.
			 * 
			 * @throws InvalidOperationException if operation not supported by
			 * this collection.
			 */
			virtual Bool RemoveAll(const AbstractCollection<ElementType>& collection) = 0;

			/**
			 * @brief Searches for all the elements in the specified collection in 
			 * this collection. This operation has different behaviours depending
			 * on the collection type.
			 *
			 * @param[in] collection The collection containing elements to be
			 * search for in this collection.
			 * 
			 * @return True if the specified elements were found in this collection.
			 */
			virtual Bool ContainsAll(const AbstractCollection<ElementType>& collection) = 0;

		public:
			/**
			 * @brief Removes all the elements from this collections.
			 * 
			 * This collection will be empty after this operation.
			 */
			virtual Void Clear(void) = 0;
		};

		template<typename T>
		FORGE_FORCE_INLINE Size AbstractCollection<T>::GetSize() const { return m_size; }
		template<typename T>
		FORGE_FORCE_INLINE Bool AbstractCollection<T>::IsFull() const  { return GetSize() == m_capacity; }
		template<typename T>
		FORGE_FORCE_INLINE Bool AbstractCollection<T>::IsEmpty() const { return GetSize() == 0; }
	}
}

#endif // ABSTRACT_COLLECTION_H
