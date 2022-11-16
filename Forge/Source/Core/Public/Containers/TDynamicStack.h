#ifndef T_DYNAMIC_STACK_H
#define T_DYNAMIC_STACK_H

#include <utility>
#include <stdlib.h>
#include <initializer_list>

#include "AbstractList.h"
#include "TLinkedList.h"

#include "Core/Public/Common/TypeDefinitions.h"
#include "Core/Public/Common/PreprocessorUtilities.h"

#include "Core/Public/Memory/PoolAllocator.h"
#include "Core/Public/Memory/MemoryUtilities.h"

namespace Forge {
	namespace Containers
	{
		template<typename InElementType>
		class TDynamicStack : public AbstractList<InElementType>
		{
		private:
			using ElementType         = InElementType;
			using ElementTypeRef      = InElementType&;
			using ElementTypePtr      = InElementType*;
			using ConstElementType    = const InElementType;
			using ConstElementTypeRef = const InElementType&;
			using ConstElementTypePtr = const InElementType*;

		private:
			using SelfType         = TDynamicStack<ElementType>;
			using SelfTypeRef      = TDynamicStack<ElementType>&;
			using SelfTypePtr      = TDynamicStack<ElementType>*;
			using ConstSelfType    = const TDynamicStack<ElementType>;
			using ConstSelfTypeRef = const TDynamicStack<ElementType>&;
			using ConstSelfTypePtr = const TDynamicStack<ElementType>*;

		private:
			TLinkedList<ElementType>* m_container;

		public:
			/**
			 * @brief Default constructor.
			 *
			 * Constructs an empty dynamic stack.
			 */
			TDynamicStack(void)
				: AbstractList<ElementType>(0, ~((Size)0))
			{
				m_container = new TLinkedList<ElementType>();
			}

			/**
			 * @brief Move element constructor.
			 *
			 * Constructs a dynamic stack with a copy of an element.
			 */
			TDynamicStack(ElementType&& element, Size count)
				: AbstractList<ElementType>(0, ~((Size)0))
			{
				m_container = new TLinkedList<ElementType>(std::move(element), count);

				this->m_count = m_container->GetCount();
			}

			/**
			 * @brief Copy element constructor.
			 *
			 * Constructs a dynamic stack with a copy of an element.
			 */
			TDynamicStack(ConstElementTypeRef element, Size count)
				: AbstractList<ElementType>(0, ~((Size)0))
			{
				m_container = new TLinkedList<ElementType>(element, count);

				this->m_count = m_container->GetCount();
			}

			/**
			 * @brief Initializer list constructor.
			 *
			 * Constructs a dynamic stack with an initializer list.
			 */
			TDynamicStack(std::initializer_list<ElementType> init_list)
				: AbstractList<ElementType>(0, ~((Size)0))
			{
				m_container = new TLinkedList<ElementType>(init_list);

				this->m_count = m_container->GetCount();
			}

		public:
			/**
			 * @brief Move constructor.
			 */
			TDynamicStack(SelfType&& other)
				: AbstractList<ElementType>(other)
			{
				*this = std::move(other);
			}

			/**
			 * @brief Copy constructor.
			 */
			TDynamicStack(ConstSelfTypeRef other)
				: AbstractList<ElementType>(other)
			{
				*this = other;
			}

		public:
			~TDynamicStack()
			{
				this->Clear();
			}

		public:
			/**
			 * @brief Move constructor.
			 */
			SelfTypeRef operator =(SelfType&& other)
			{
				Memory::Move(this->m_container, other.m_container, 1);

				this->m_count = this->m_container->GetCount();

				other.m_container = nullptr;
				other.m_count = 0;

				return *this;
			}

			/**
			 * @brief Copy constructor.
			 */
			SelfTypeRef operator =(ConstSelfTypeRef other)
			{
				Memory::Copy(this->m_container, other.m_container, 1);

				this->m_count = this->m_container->GetCount();

				return *this;
			}

		public:
			/**
			 * @brief Returns an iterator pointing to the first element in this
			 * collection.
			 *
			 * @return Iterator pointing to the first element.
			 */
			auto GetStartItr(void)
			{
				return this->m_container->GetStartItr();
			}

			/**
			 * @brief Returns an iterator pointing to the past-end element in this
			 * collection.
			 *
			 * @return Iterator pointing to the past-end element element.
			 */
			auto GetEndItr(void)
			{
				return this->m_container->GetEndItr();
			}

			/**
			 * @brief Returns a const iterator pointing to the first element in this
			 * collection.
			 *
			 * @return ConstIterator pointing to the first element.
			 */
			auto GetStartConstItr(void) const
			{
				return this->m_container->GetStartConstItr();
			}

			/**
			 * @brief Returns a const iterator pointing to the past-end element in
			 * this collection.
			 *
			 * @return ConstIterator pointing to the past-end element element.
			 */
			auto GetEndConstItr(void) const
			{
				return this->m_container->GetEndConstItr();
			}

		public:
			/**
			 * @brief This function is not supported by this collection.
			 *
			 * @throws InvalidOperationException if attempted to retrieve
			 * this collection's raw pointer.
			 */
			ConstElementTypePtr GetRawData() const override
			{
				return this->m_container->GetRawData();
			}

		public:
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
			Bool IsEqual(AbstractCollection<ElementType>& collection) const override
			{
				return this->m_container->IsEqual(collection);
			}

		public:
			/**
			 * @brief Returns an array containing all the elements returned by this
			 * collection's iterator.
			 *
			 * The length of the array is equal to the number of elements returned
			 * by the iterator. If this collection makes any guarantees as to what
			 * order its elements are returned by its iterator, this method must
			 * return the elements in the same order. The returned array contains
			 * deep copies of the elements.
			 *
			 * @return ElementTypePtr storing the address of the array or
			 * nullptr if collection is empty.
			 */
			ElementTypePtr ToArray(void) const override
			{
				return this->m_container->ToArray();
			}

			/**
			 * @brief Returns an array containing all the elements returned by this
			 * collection's iterator.
			 *
			 * The length of the array is equal to the number of elements returned
			 * by the iterator. If this collection makes any guarantees as to what
			 * order its elements are returned by its iterator, this method must
			 * return the elements in the same order. The returned array contains
			 * deep copies of the elements.
			 *
			 * @param[out] array_ptr The array to store this collection's elements.
			 *
			 * @return ElementTypePtr storing the address of the array or
			 * nullptr if collection is empty.
			 */
			ElementTypePtr ToArray(ElementTypePtr array_ptr) const override
			{
				return this->m_container->ToArray(array_ptr);
			}

		public:
			/**
			 * @brief Iterates through all the elements inside the collection and
			 * performs the operation provided on each element.
			 *
			 * The operation is performed in the order of iteration, and is performed
			 * until all elements have been processed or the operation throws an
			 * exception.
			 *
			 * @param[in] function The function to perform on each element.
			 */
			Void ForEach(Common::TDelegate<Void(ElementTypeRef)> function) override
			{
				this->m_container->ForEach(function);
			}

		public:
			/**
			 * @brief Returns the index of the first occurence of the specified
			 * element in this collection, or -1 if it does not contain the
			 * element or it is empty.
			 *
			 * @param[in] element The element to search for the first occurence.
			 *
			 * @return Size storing the index of the first occurrence of the
			 * specified element, or -1 if this collection does not contain the
			 * element or it is empty.
			 */
			I64 FirstIndexOf(ConstElementTypeRef element) const override
			{
				return this->m_container->FirstIndexOf(element);
			}

			/**
			 * @brief Returns the index of the last occurence of the specified
			 * element in this collection, or -1 if it does not contain the
			 * element or it is empty.
			 *
			 * @param[in] element The element to search for the last occurence.
			 *
			 * @return Size storing the index of the last occurrence of the
			 * specified element, or -1 if this collection does not contain the
			 * element or it is empty.
			 */
			I64 LastIndexOf(ConstElementTypeRef element) const override
			{
				return this->m_container->LastIndexOf(element);
			}

		public:
			/**
			 * @brief Retreives the last element in this collection.
			 *
			 * @return ConstElementTypeRef storing the last element in this
			 * collection.
			 *
			 * @Throws InvalidOperationException if this collection is empty.
			 */
			ConstElementTypeRef PeekBack() const override
			{
				return this->m_container->PeekBack();
			}

			/**
			 * @brief This collection only allows retrieval of the top most element.
			 *
			 * @throws InvalidOperationException if attempted to retrieve the first
			 * element in this collection.
			 */
			ConstElementTypeRef PeekFront() const override
			{
				// Throw Exception

				return ElementType();
			}

		public:
			/**
			 * @brief Inserts a new element at the end of this collection, after
			 * its current last element.
			 *
			 * @param[in] element The element to insert in this collection.
			 */
			Void PushBack(ElementType&& element) override
			{
				this->m_container->PushBack(std::move(element));

				this->m_count = m_container->GetCount();
			}

			/**
		     * @brief This collection only allows insertion of elements at the end.
		     *
		     * @throws InvalidOperationException if attempted to insert at the front
		     * of this collection.
		     */
			Void PushFront(ElementType&& element) override
			{
				// Throw Exception
			}

			/**
			 * @brief Inserts a new element at the end of this collection, after
			 * its current last element.
			 *
			 * @param[in] element The element to insert in this collection.
			 */
			Void PushBack(ConstElementTypeRef element) override
			{
				this->m_container->PushBack(element);

				this->m_count = m_container->GetCount();
			}

			/**
			 * @brief This collection only allows insertion of elements at the end.
			 *
			 * @throws InvalidOperationException if attempted to insert at the front
			 * of this collection.
			 */
			Void PushFront(ConstElementTypeRef element) override
			{
				// Throw Exception
			}

			/**
			 * @brief Removes the element at the end of this collection, effectivly
			 * reducing the collection count by one.
			 *
			 * This function has the same functionality as Pop
			 *
			 * @Throws InvalidOperationException if this collection is empty.
			 */
			Void PopBack(void) override
			{
				this->m_container->PopBack();

				this->m_count = m_container->GetCount();
			}

			/**
			 * @brief This collection only allows removal of elements at the end.
			 *
			 * @throws InvalidOperationException if attempted to remove at the front
			 * of this collection.
			 */
			Void PopFront(void) override
			{
				// Throw Exception
			}

		public:
			/**
			 * @brief Inserts a new element at the top of this collection.
			 *
			 * This function has the same functionality as PushBack.
			 *
			 * @param[in] element The element to insert at the top.
			 */
			Void Push(ElementType&& element)
			{
				//this->PushBack(std:move(element));
			}

			/**
			 * @brief Inserts a new element at the top of this collection.
			 *
			 * This function has the same functionality as PushBack.
			 *
			 * @param[in] element The element to insert at the top.
			 */
			Void Push(ConstElementTypeRef element)
			{
				this->PushBack(element);
			}

			/**
			 * @brief Removes the element at the top of this collection.
			 *
			 * This operation has the same functionality as PopBack.
			 */
			Void Pop(void)
			{
				this->PopBack();
			}

		public:
			/**
			 * @brief This collection does not support insertion of elements at
			 * specified indices.
			 *
			 * @throws InvalidOperationException if attempted to insert element at
			 * a specified index.
			 */
			Void InsertAt(Size index, ElementType&& element) override
			{
				// Throw Exception
			}

			/**
			 * @brief This collection does not support insertion of elements at
			 * specified indices.
			 *
			 * @throws InvalidOperationException if attempted to insert element at
			 * a specified index.
			 */
			Void InsertAt(Size index, ConstElementTypeRef element) override
			{
				// Throw Exception
			}

			/**
			 * @brief This collection does not support removal of elements at
			 * specified indices.
			 *
			 * @throws InvalidOperationException if attempted to remove element at
			 * a specified index.
			 */
			Void RemoveAt(Size index) override
			{
				// Throw Exception
			}

		public:
			/**
			 * @brief This collection does not support removal of elements at
			 * specified positions.
			 *
			 * @throws InvalidOperationException if attempted to remove element at
			 * a specified position.
			 */
			Bool Remove(ConstElementTypeRef element) override
			{
				// Throw Exception

				return false;
			}

			/**
			 * @brief Searches this collection for the specified element.
			 *
			 * @param[in] element ElementType to search for in this collection.
			 *
			 * @return True if the specified element was found in this collection.
			 */
			Bool Contains(ConstElementTypeRef element) const override
			{
				return this->m_container->Contains(element);
			}

		public:
			/**
			 * @brief Inserts all the elements in the specified collection to this
			 * collection.
			 *
			 * The order in which the elements are inserted into this collection
			 * depends on how the specified collection is iterated on.
			 *
			 * @param[in] collection The collection containing elements to be added
			 * to this collection.
			 *
			 * @return True if insertion was succesfull and collection is not empty.
			 */
			Bool InsertAll(AbstractCollection<ElementType>& collection) override
			{
				if (collection.IsEmpty())
					return false;

				if (this->m_max_capacity - collection.GetMaxCapacity() < 0)
					return false;

				collection.ForEach([this](ElementTypeRef element) -> Void
					{
						this->Push(element);
					}
				);

				return true;
			}

			/**
			 * @brief This collection does not support removal of elements at
			 * specified positions.
			 *
			 * @throws InvalidOperationException if attempted to remove element at
			 * a specified position.
			 */
			Bool RemoveAll(AbstractCollection<ElementType>& collection) override
			{
				// Throw Exception

				return false;
			}

			/**
			 * @brief Searches for all the elements in the specified collection in
			 * this collection.
			 *
			 * @param[in] collection The collection containing elements to be
			 * search for in this collection.
			 *
			 * @return True if the specified elements were found and the collection
			 * is not empty.
			 */
			Bool ContainsAll(AbstractCollection<ElementType>& collection) override
			{
				return this->m_container->ContainsAll(collection);
			}

		public:
			/**
			 * @brief Removes all the elements from this collection.
			 */
			Void Clear(void) override
			{
				this->m_container->Clear();

				this->m_count = 0;
			}
		};
	}
}

#endif // T_DYNAMIC_STACK_H
