#ifndef T_LINKED_LIST_H
#define T_LINKED_LIST_H

#include <utility>
#include <stdlib.h>
#include <initializer_list>

#include "AbstractList.h"

#include "Core/Public/Common/TypeDefinitions.h"
#include "Core/Public/Common/PreprocessorUtilities.h"

#include "Core/Public/Memory/PoolAllocator.h"
#include "Core/Public/Memory/MemoryUtilities.h"

namespace Forge {
	namespace Containers
	{
		template<typename InElementType>
		class TLinkedList : public AbstractList<InElementType>
		{
		private:
			using ElementType         = InElementType;
			using ElementTypeRef      = InElementType&;
			using ElementTypePtr      = InElementType*;
			using ConstElementType    = const InElementType;
			using ConstElementTypeRef = const InElementType&;
			using ConstElementTypePtr = const InElementType*;

		private:
			struct EntryNode
			{
			public:
				ElementType m_data;
				EntryNode* m_prev, *m_next;

			public:
				EntryNode(ElementType&& data)
					: m_data(std::move(data)), m_prev(nullptr), m_next(nullptr) {}
				EntryNode(ConstElementTypeRef data)
					: m_data(data), m_prev(nullptr), m_next(nullptr) {}
			};
		
		public:
			struct Iterator
			{
			private:
				EntryNode* m_ptr;

			public:
				Iterator(void)
					: m_ptr(nullptr) {}

				Iterator(EntryNode* ptr)
					: m_ptr(ptr) {}

			public:
				Iterator(Iterator&& other)
				{
					*this = std::move(other);
				}
				Iterator(const Iterator& other)
				{
					*this = other;
				}

			public:
				~Iterator() = default;

			public:
				Iterator operator =(Iterator&& other)
				{
					Memory::MemoryCopy(this, &other, sizeof(Iterator));

					other.m_ptr = nullptr;

					return *this;
				}
				Iterator operator =(const Iterator& other)
				{
					Memory::MemoryCopy(this, const_cast<Iterator*>(&other), sizeof(Iterator));

					return *this;
				}

			public:
				Iterator operator --(I32)
				{
					Iterator temp(this->m_ptr);

					this->m_ptr = this->m_ptr->m_prev;

					return temp;
				}
				Iterator operator --(void)
				{
					this->m_ptr = this->m_ptr->m_prev;

					return *this;
				}

			public:
				Iterator operator ++(I32)
				{
					Iterator temp(this->m_ptr);

					this->m_ptr = this->m_ptr->m_next;

					return temp;
				}
				Iterator operator ++(void)
				{
					this->m_ptr = this->m_ptr->m_next;

					return *this;
				}

			public:
				Bool operator ==(const Iterator& other)
				{
					return this->m_ptr == other.m_ptr;
				}
				Bool operator !=(const Iterator& other)
				{
					return this->m_ptr != other.m_ptr;
				}

			public:
				ElementTypeRef operator *()
				{
					return (this->m_ptr->m_data);
				}

			public:
				ElementTypePtr operator ->()
				{
					return this->m_ptr;
				}
			};

		private:
			EntryNode* m_head, *m_tail;

		public:
			TLinkedList(void)
				: m_head(nullptr), m_tail(nullptr), AbstractList<ElementType>(0, ~((Size)0)) {}

			TLinkedList(ElementType&& element, Size count)
				: AbstractList<ElementType>(0, ~((Size)0))
			{
				while (count > this->m_count)
					this->PushBack(element);
			}

			TLinkedList(ConstElementTypeRef element, Size count)
				: AbstractList<ElementType>(0, ~((Size)0))
			{
				while (count > this->m_count)
					this->PushBack(element);
			}

			TLinkedList(std::initializer_list<ElementType> init_list)
				: AbstractList<ElementType>(0, ~((Size)0))
			{
				ConstElementTypePtr ptr = init_list.begin();

				while (init_list.size() > this->m_count)
					this->PushBack(*(ptr + this->m_count));
			}

		public:
			TLinkedList(TLinkedList<ElementType>&& rhs)
				: AbstractList<ElementType>(rhs)
			{
				Memory::MemoryCopy(this, &rhs, sizeof(TLinkedList<ElementType>));

				rhs.m_head = rhs.m_tail = nullptr;
				rhs.m_count = 0;
			}

			TLinkedList(const TLinkedList<ElementType>& rhs)
				: AbstractList<ElementType>(rhs)
			{
				for (EntryNode* curr_node = rhs.m_head; curr_node; curr_node = curr_node->m_next)
					this->PushBack(curr_node->m_data);
			}
		
		public:
			~TLinkedList()
			{
				this->Clear();
			}

		public:
			TLinkedList<ElementType>& operator =(TLinkedList<ElementType>&& rhs)
			{
				this->Clear();

				Memory::MemoryCopy(this, &rhs, sizeof(TLinkedList<ElementType>));

				rhs.m_head = rhs.m_tail = nullptr;
				rhs.m_count = 0;

				return *this;
			}

			TLinkedList<ElementType>& operator =(const TLinkedList<ElementType>& rhs)
			{
				this->Clear();

				for (EntryNode* curr_node = rhs.m_head; curr_node; curr_node = curr_node->m_next)
					this->PushBack(curr_node->m_data);

				return *this;
			}

		public:
			/**
			 * @brief This operation is not supported by the linked list.
			 *
			 * @throws InvalidOperationException if operation not supported by
			 * list.
			 */
			ConstElementTypePtr GetRawData() const override
			{
				return nullptr;
			}

		public:
			/**
			 * @brief Returns an iterator pointing to the first element in this
			 * linked list.
			 *
			 * @return Iterator pointing to the first element.
			 */
			Iterator GetStartItr(void) const
			{
				return Iterator(this->m_head);
			}

			/**
			 * @brief Returns an iterator pointing to the past-end element in this
			 * linked list.
			 *
			 * @return Iterator pointing to the past-end element element.
			 */
			Iterator GetEndItr(void) const
			{
				return Iterator(this->m_tail->m_next);
			}

			/**
			 * @brief Returns a const iterator pointing to the first element in this
			 * linked list.
			 *
			 * @return ConstIterator pointing to the first element.
			 */
			Iterator GetStartConstItr(void) const
			{
				return ConstIterator(this->m_head);
			}

			/**
			 * @brief Returns a const iterator pointing to the past-end element in this
			 * linked list.
			 *
			 * @return ConstIterator pointing to the past-end element element.
			 */
			Iterator GetEndConstItr(void) const
			{
				return ConstIterator(this->m_tail->m_prev);
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
				if (collection.IsEmpty())
					return false;

				if (this->m_count != collection.GetCount())
					return false;

				Bool return_value;

				Iterator start_itr = this->GetStartItr();
				Iterator end_itr = this->GetEndItr();

				collection.ForEach([&return_value, &start_itr, end_itr](ElementTypeRef element) -> Void
					{
						if ((start_itr++) == end_itr)
						{
							return_value = true;
							return;
						}

						if (!Memory::MemoryCompare(&(*start_itr), &element, sizeof(ElementType)))
						{
							return_value = false;
							return;
						}
					}
				);

				return return_value;
			}
			 
		public:
			/**
			 * @brief Returns an array containing all the elements returned by this
			 * list's forward iterator.
			 *
			 * The length of the array is equal to the number of elements returned
			 * by the iterator. If this list makes any guarantees as to what order 
			 * its elements are returned by its iterator, this method must return 
			 * the elements in the same order. The returned array contains deep 
			 * copies of the elements.
			 *
			 * @return ElementTypePtr storing the address of the array.
			 */
			ElementTypePtr ToArray(void) const override
			{
				return nullptr;
			}

			/**
			 * @brief Returns an array containing all the elements returned by this
			 * collection's forward iterator.
			 *
			 * The length of the array is equal to the number of elements returned
			 * by the iterator. If this list makes any guarantees as to what order 
			 * its elements are returned by its iterator, this method must return 
			 * the elements in the same order. The returned array contains deep 
			 * copies of the elements.
			 *
			 * @param[out] array The array to store this list's elements.
			 *
			 * @return ElementTypePtr storing the address of the array.
			 */
			ElementTypePtr ToArray(ElementTypePtr array) const override
			{
				return nullptr;
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
				EntryNode* curr_node = this->m_head;
				do { function.Invoke(curr_node->m_data); } while (curr_node = curr_node->m_next);
			}


		public:
			/**
			 * @brief Returns the index of the first occurence of the specified
			 * element in the linked list, or -1 if it does not contain the element.
			 *
			 * @param[in] element The element to search for the first occurence.
			 *
			 * @return Size storing the index of the first occurrence of the
			 * specified element, or -1 if this list does not contain the element.
			 */
			I64 FirstIndexOf(ConstElementTypeRef element) const override
			{
				EntryNode* curr_node = this->m_head;

				for (I32 index = 0; curr_node; index++)
				{
					if (Memory::MemoryCompare(&curr_node->m_data, &element, sizeof(ElementType)))
						return index;
						
					curr_node = curr_node->m_next;
				}

				return -1;
			}

			/**
			 * @brief Returns the index of the last occurence of the specified
			 * element in the linked list, or -1 if it does not contain the element.
			 *
			 * @param[in] element The element to search for the first occurence.
			 *
			 * @return Size storing the index of the last occurrence of the
			 * specified element, or -1 if this list does not contain the element.
			 */
			I64 LastIndexOf(ConstElementTypeRef element) const override
			{
				EntryNode* curr_node = this->m_tail;

				for (I32 index = this->m_count - 1; curr_node; index--)
				{
					if (Memory::MemoryCompare(&curr_node->m_data, &element, sizeof(ElementType)))
						return index;

					curr_node = curr_node->m_prev;
				}

				return -1;
			}

		public:
			/**
			 * @brief Retreives the last element in the linked list.
			 *
			 * @return ConstElementTypeRef storing the last element in the list.
			 */
			ConstElementTypeRef PeekBack() const override
			{
				if (!this->m_tail)
				{
					// Throw Exception
				}

				return this->m_tail->m_data;
			}

			/**
			 * @brief Retreives the first element in the linked list.
			 *
			 * @return ConstElementTypeRef storing the first element in the list.
			 */
			ConstElementTypeRef PeekFront() const override
			{
				if (!this->m_head)
				{
					// Throw Exception
				}

				return this->m_head->m_data;
			}

		public:
			/**
			 * @brief Inserts a new element at the end of this linked list, after
			 * its current last element.
			 *
			 * @param[in] element The element to insert in this linked list.
			 */
			Void PushBack(ElementType&& element) override
			{
				EntryNode* elem_node = new EntryNode(std::move(element));

				if (!this->m_tail)
					this->m_head = this->m_tail = elem_node;
				else
				{
					elem_node->m_prev = this->m_tail;
					this->m_tail->m_next = elem_node;
					this->m_tail = elem_node;
				}

				this->m_count++;
			}

			/**
			 * @brief Inserts a new element at the start of this linked list, before
			 * its current first element.
			 *
			 * @param[in] element The element to insert in this linked list.
			 */
			Void PushFront(ElementType&& element) override
			{
				EntryNode* elem_node = new EntryNode(std::move(element));

				if (!this->m_head)
					this->m_head = this->m_tail = elem_node;
				else
				{
					elem_node->m_next = this->m_head;
					this->m_head->m_prev = elem_node;
					this->m_head = elem_node;
				}

				this->m_count++;
			}

			/**
			 * @brief Inserts a new element at the end of this linked list, after
			 * its current last element.
			 *
			 * @param[in] element The element to insert in the linked list.
			 */
			Void PushBack(ConstElementTypeRef element) override
			{
				EntryNode* elem_node = new EntryNode(element);

				if (!this->m_tail)
					this->m_head = this->m_tail = elem_node;
				else
				{
					elem_node->m_prev = this->m_tail;
					this->m_tail->m_next = elem_node;
					this->m_tail = elem_node;
				}

				this->m_count++;
			}

			/**
			 * @brief Inserts a new element at the start of this linked list, before
			 * its current first element.
			 *
			 * @param[in] element The element to insert in thi linked list.
			 */
			Void PushFront(ConstElementTypeRef element) override
			{
				EntryNode* elem_node = new EntryNode(element);

				if (!this->m_head)
					this->m_head = this->m_tail = elem_node;
				else
				{
					elem_node->m_next = this->m_head;
					this->m_head->m_prev = elem_node;
					this->m_head = elem_node;
				}

				this->m_count++;
			}

			/**
			 * @brief Removes the element at the end of this linked list, effectivly
			 * reducing the list count by one.
			 */
			Void PopBack(void) override
			{
				if (!this->m_tail)
					return;
				else if (!this->m_tail->m_prev)
				{
					free(this->m_tail);

					this->m_head = this->m_tail = nullptr;
				}
				else
				{
					EntryNode* curr_node = this->m_tail->m_prev;

					free(this->m_tail);

					this->m_tail = curr_node;
					this->m_tail->m_next = nullptr;
				}

				this->m_count--;
			}

			/**
			 * @brief Removes the element at the start of this linked list, 
			 * effectivly reducing the list count by one.
			 */
			Void PopFront(void) override
			{
				if (!this->m_head)
					return;
				else if (!this->m_head->m_next)
				{
					free(this->m_head);

					this->m_head = this->m_tail = nullptr;
				}
				else
				{
					EntryNode* curr_node = this->m_head->m_next;

					free(this->m_head);

					this->m_head = curr_node;
					this->m_head->m_prev = nullptr;
				}

				this->m_count--;
			}

		public:
			/**
			 * @brief Inserts the specified element in the specified index.
			 *
			 * This operation inserts the new element before the element in the
			 * specified index. Insertion at the start or end of the linked list
			 * is not supported, instead use PushBack and PushFront.
			 * 
			 * @param[in] index   The numerical index to insert the element at.
			 * @param[in] element The element to insert in the list.
			 *
			 * @throw IndexOutOfRangeException if index to insert element is out
			 * of range.
			 * 
			 * @throw InvalidOperationException if attempted to insert at start or
			 * end of this linked list.
			 */
			Void InsertAt(Size index, ElementType&& element) override
			{
				FORGE_ASSERT(index > 0 && index < this->m_count, "Index is out of range")

				EntryNode* elem_node = new EntryNode(std::move(element));

				EntryNode* next_node = this->m_head;

				while (next_node->m_next && (index--) > 0)
					next_node = next_node->m_next;
				
				EntryNode* prev_node = next_node->m_prev;
				
				elem_node->m_next = next_node;
				elem_node->m_prev = prev_node;
				next_node->m_prev = elem_node;
			    prev_node->m_next = elem_node;

				this->m_count++;
			}

			/**
			 * @brief Inserts the specified element in the specified index.
			 *
			 * This operation insertes the new element before the element in the
			 * specified index. Insertion at the start or end of the linked list
			 * is not supported, instead use PushBack and PushFront.
			 *
			 * @param[in] index   The numerical index to insert the element at.
			 * @param[in] element The element to insert in the list.
			 *
			 * @throw IndexOutOfRangeException if index to insert element is out
			 * of range.
			 *
			 * @throw InvalidOperationException if attempted to insert at start or
			 * end of this linked list.
			 */
			Void InsertAt(Size index, ConstElementTypeRef element) override
			{
				FORGE_ASSERT(index > 0 && index < this->m_count, "Index is out of range")

				EntryNode* elem_node = new EntryNode(element);

				EntryNode* next_node = this->m_head;

				while (next_node->m_next && (index--) > 0)
					next_node = next_node->m_next;

				EntryNode* prev_node = next_node->m_prev;

				elem_node->m_next = next_node;
				elem_node->m_prev = prev_node;
				next_node->m_prev = elem_node;
				prev_node->m_next = elem_node;

				this->m_count++;
			}

			/**
			* @brief Removes the element in the specified index.
			*
			* Removal of an element at the start or end of the linked list is not
			* supported, instead use PopBack or PopFront.
			* 
			* @param[in] index The numerical index to remove the element at.
			*
			* @throw IndexOutOfRangeException if index to remove element at is out
			* of range.
			* 
			* @throw InvalidOperationException if attempted to remove at start or
			 * end of this linked list.
			*/
			Void RemoveAt(Size index) override
			{
				FORGE_ASSERT(index > 0 && index + 1 < this->m_count, "Index is out of range")

				EntryNode* curr_node = this->m_head;

				while (curr_node->m_next && (index--) > 0)
					curr_node = curr_node->m_next;

				EntryNode* next_node = curr_node->m_next;
				EntryNode* prev_node = next_node->m_prev;

				prev_node->m_next = next_node;
				next_node->m_prev = prev_node;

				free(curr_node);

				this->m_count--;
			}

		public:
			/**
			 * @brief Removes the specified element from this linked list.
			 *
			 * @param[in] element ElementType to remove from this linked list.
			 *
			 * @return True if removal was successful.
			 */
			Bool Remove(ConstElementTypeRef element) override
			{
				if (Size index = this->FirstIndexOf(element) != -1)
				{
					this->RemoveAt(index);
					return true;
				}

				return false;
			}

			/**
			 * @brief Searches this linked list for the specified element.
			 *
			 * @param[in] element ElementType to search for in this linked list.
			 *
			 * @return True if the specified element was found.
			 */
			Bool Contains(ConstElementTypeRef element) const override
			{
				return this->FirstIndexOf(element) != -1;
			}

		public:
			/**
			 * @brief Inserts all the elements in the specified collection to this
			 * collection.
			 *
			 * @param[in] collection The collection containing elements to be added
			 * to this collection.
			 *
			 * @return True if insertion was successful.
			 */
			Bool InsertAll(AbstractCollection<ElementType>& collection) override
			{
				if (collection.IsEmpty())
					return false;

				if (this->m_max_capacity - collection.GetMaxCapacity() < 0)
					return false;

				collection.ForEach([this](ElementTypeRef element)->Void
					{
						this->PushBack(element);
					}
				);

				return true;
			}

			/**
			 * @brief Removes all the elements in the specified collection from this
			 * collection.
			 *
			 * @param[in] collection The collection containing elements to be
			 * removed from this collection.
			 *
			 * @return True if removal was successful.
			 */
			Bool RemoveAll(AbstractCollection<ElementType>& collection) override
			{
				if (!this->m_count || collection.IsEmpty())
					return false;

				Bool return_value;

				collection.ForEach([this, &return_value](ElementTypeRef element)->Void
					{
						return_value = this->Remove(element);

						if (!return_value)
							return;
					}
				);

				return return_value;
			}

			/**
			 * @brief Searches for all the elements in the specified collection in
			 * this collection.
			 *
			 * @param[in] collection The collection containing elements to be
			 * search for in this collection.
			 *
			 * @return True if the specified elements were found in this collection.
			 */
			Bool ContainsAll(AbstractCollection<ElementType>& collection) override
			{
				if (!this->m_count || collection.IsEmpty())
					return false;

				Bool return_value;

				collection.ForEach([this, &return_value](ElementTypeRef element)->Void
					{
						return_value = this->Contains(element);

						if (!return_value)
							return;
					}
				);

				return return_value;
			}

		public:
			/**
			 * @brief Removes all the elements from the linked list.
			 *
			 * The linked list will be empty after this operation.
			 */
			Void Clear(void) override
			{
				if (this->m_head)
				{
					EntryNode* curr_node = this->m_head;
					do { this->PopBack(); } while (curr_node = curr_node->m_next);
				}
			}
		};
	}
}

#endif // T_LINKED_LIST_H
