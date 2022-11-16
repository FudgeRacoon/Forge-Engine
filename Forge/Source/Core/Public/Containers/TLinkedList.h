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
			using SelfType         = TLinkedList<ElementType>;
			using SelfTypeRef      = TLinkedList<ElementType>&;
			using SelfTypePtr      = TLinkedList<ElementType>*;
			using ConstSelfType    = const TLinkedList<ElementType>;
			using ConstSelfTypeRef = const TLinkedList<ElementType>&;
			using ConstSelfTypePtr = const TLinkedList<ElementType>*;

		private:
			struct EntryNode
			{
			public:
				ElementType m_data;

			public:
				EntryNode* m_prev;
				EntryNode* m_next;

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
					return this->m_ptr->m_data;
				}

			public:
				ElementTypePtr operator ->()
				{
					return this->m_ptr;
				}
			};
			struct ConstIterator
			{
			private:
				EntryNode* m_ptr;

			public:
				ConstIterator(void)
					: m_ptr(nullptr) {}

				ConstIterator(EntryNode* ptr)
					: m_ptr(ptr) {}

			public:
				ConstIterator(ConstIterator&& other)
				{
					*this = std::move(other);
				}
				ConstIterator(const ConstIterator& other)
				{
					*this = other;
				}

			public:
				~ConstIterator() = default;

			public:
				ConstIterator operator =(ConstIterator&& other)
				{
					Memory::MemoryCopy(this, &other, sizeof(ConstIterator));

					other.m_ptr = nullptr;

					return *this;
				}
				ConstIterator operator =(const ConstIterator& other)
				{
					Memory::MemoryCopy(this, const_cast<ConstIterator*>(&other), sizeof(Iterator));

					return *this;
				}

			public:
				ConstIterator operator --(I32)
				{
					ConstIterator temp(this->m_ptr);

					this->m_ptr = this->m_ptr->m_prev;

					return temp;
				}
				ConstIterator operator --(void)
				{
					this->m_ptr = this->m_ptr->m_prev;

					return *this;
				}

			public:
				ConstIterator operator ++(I32)
				{
					ConstIterator temp(this->m_ptr);

					this->m_ptr = this->m_ptr->m_next;

					return temp;
				}
				ConstIterator operator ++(void)
				{
					this->m_ptr = this->m_ptr->m_next;

					return *this;
				}

			public:
				Bool operator ==(const ConstIterator& other)
				{
					return this->m_ptr == other.m_ptr;
				}
				Bool operator !=(const ConstIterator& other)
				{
					return this->m_ptr != other.m_ptr;
				}

			public:
				ConstElementTypeRef operator *()
				{
					return this->m_ptr->m_data;
				}

			public:
				ConstElementTypePtr operator ->()
				{
					return this->m_ptr;
				}
			};

		private:
			EntryNode* m_head;
			EntryNode* m_tail;

		public:
			/**
			 * @brief Default constructor.
			 *
			 * Constructs an empty linked list.
			 */
			TLinkedList(void)
				: m_head(nullptr), m_tail(nullptr), AbstractList<ElementType>(0, ~((Size)0)) {}

			/**
			 * @brief Move element constructor.
			 *
			 * Constructs a linked list with a copy of an element.
			 */
			TLinkedList(ElementType&& element, Size count)
				: AbstractList<ElementType>(0, ~((Size)0))
			{
				while (count > this->m_count)
					this->PushBack(std::move(element));
			}

			/**
			 * @brief Copy element constructor.
			 *
			 * Constructs a linked list with a copy of an element.
			 */
			TLinkedList(ConstElementTypeRef element, Size count)
				: AbstractList<ElementType>(0, ~((Size)0))
			{
				while (count > this->m_count)
					this->PushBack(element);
			}

			/**
			 * @brief Initializer list constructor.
			 *
			 * Constructs a linked list with an initializer list.
			 */
			TLinkedList(std::initializer_list<ElementType> init_list)
				: AbstractList<ElementType>(0, ~((Size)0))
			{
				ConstElementTypePtr ptr = init_list.begin();

				while (init_list.size() > this->m_count)
					this->PushBack(*(ptr + this->m_count));
			}

		public:
			/**
			 * @brief Move constructor.
			 */
			TLinkedList(SelfType&& other)
				: AbstractList<ElementType>(other)
			{
				*this = std::move(other);
			}

			/**
			 * @brief Copy constructor.
			 */
			TLinkedList(ConstSelfTypeRef other)
				: AbstractList<ElementType>(other)
			{
				*this = other;
			}
		
		public:
			~TLinkedList()
			{
				this->Clear();
			}

		public:
			/**
			 * @brief Move constructor.
			 */
			SelfTypeRef operator =(SelfType&& other)
			{
				this->Clear();

				Memory::MemoryCopy(this, &other, sizeof(SelfType));

				other.m_head = other.m_tail = nullptr;
				other.m_count = 0;

				return *this;
			}

			/**
			 * @brief Copy constructor.
			 */
			SelfTypeRef operator =(ConstSelfTypeRef other)
			{
				this->Clear();

				for (EntryNode* curr_node = other.m_head; curr_node; curr_node = curr_node->m_next)
					this->PushBack(curr_node->m_data);

				return *this;
			}

		public:
			/**
			 * @brief Returns an iterator pointing to the first element in this
			 * collection.
			 *
			 * @return Iterator pointing to the first element.
			 */
			Iterator GetStartItr(void)
			{
				return Iterator(this->m_head);
			}

			/**
			 * @brief Returns an iterator pointing to the past-end element in this
			 * collection.
			 *
			 * @return Iterator pointing to the past-end element element.
			 */
			Iterator GetEndItr(void)
			{
				return Iterator(this->m_tail->m_next);
			}

			/**
			 * @brief Returns a const iterator pointing to the first element in this
			 * collection.
			 *
			 * @return ConstIterator pointing to the first element.
			 */
			ConstIterator GetStartConstItr(void) const
			{
				return ConstIterator(this->m_head);
			}

			/**
			 * @brief Returns a const iterator pointing to the past-end element in
			 * this collection.
			 *
			 * @return ConstIterator pointing to the past-end element element.
			 */
			ConstIterator GetEndConstItr(void) const
			{
				return ConstIterator(this->m_tail->m_next);
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
				// Throw Exception

				return nullptr;
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

				ConstIterator start_itr = this->GetStartConstItr();
				ConstIterator end_itr = this->GetEndConstItr();

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
				return nullptr;
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
			 * @brief Retreives the last element in this collection.
			 *
			 * @return ConstElementTypeRef storing the last element in this
			 * collection.
			 *
			 * @Throws InvalidOperationException if this collection is empty.
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
			 * @brief Retreives the first element in this collection.
			 *
			 * @return ConstElementTypeRef storing the first element in this
			 * collection.
			 *
			 * @Throws InvalidOperationException if this collection is empty.
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
			 * @brief Inserts a new element at the end of this collection, after
			 * its current last element.
			 *
			 * @param[in] element The element to insert in this collection.
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
			 * @brief Inserts a new element at the start of this collection. before
			 * its current first element.
			 *
			 * @param[in] element The element to insert in this collection.
			 */
			Void PushFront(ElementType&& element) override
			{
				this->InsertAt(0, std::move(element));
			}

			/**
			 * @brief Inserts a new element at the end of this collection, after
			 * its current last element.
			 *
			 * @param[in] element The element to insert in this collection.
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
			 * @brief Inserts a new element at the start of this collection. before
			 * its current first element.
			 *
			 * @param[in] element The element to insert in this collection.
			 */
			Void PushFront(ConstElementTypeRef element) override
			{
				this->InsertAt(0, element);
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
				this->RemoveAt(this->m_count - 1);
			}

			/**
			 * @brief Removes the element at the front of this collection, effectivly
			 * reducing the collection count by one.
			 *
			 * This function has the same functionality as Pop
			 *
			 * @Throws InvalidOperationException if this collection is empty.
			 */
			Void PopFront(void) override
			{
				this->RemoveAt(0);
			}

		public:
			/**
			 * @brief Inserts the specified element in the specified index in this
			 * collection.
			 *
			 * This function will increase this collection's count size by one and
			 * shift all elements that preceed the newly inserted element.
			 *
			 * @param[in] index   The index to insert the element at.
			 * @param[in] element The element to insert in this collection.
			 *
			 * @throw IndexOutOfRangeException if index to insert element is out
			 * of range.
			 *
			 * @throw MemoryOutOfBoundsException if this collection's max capacity
			 * has been reached.
			 */
			Void InsertAt(Size index, ElementType&& element) override
			{
				if (index < 0 || index >= this->m_count)
				{
					// Throw Exception
				}

				if (this->m_count >= this->m_max_capacity)
				{
					// Throw Exception
				}

				EntryNode* elem_node = new EntryNode(std::move(element));

				EntryNode* next_node = this->m_head;

				while (next_node->m_next && (index--) > 0)
					next_node = next_node->m_next;
				
				EntryNode* prev_node = next_node->m_prev;
				
				elem_node->m_next = next_node;
				elem_node->m_prev = prev_node;
				next_node->m_prev = elem_node;

				if(prev_node)
					prev_node->m_next = elem_node;

				this->m_count++;
			}

			/**
			 * @brief Inserts the specified element in the specified index in this
			 * collection.
			 *
			 * This function will increase this collection's count size by one and
			 * shift all elements that preceed the newly inserted element to the
			 * right.
			 *
			 * @param[in] index   The index to insert the element at.
			 * @param[in] element The element to insert in this collection.
			 *
			 * @throw IndexOutOfRangeException if index to insert element is out
			 * of range.
			 *
			 * @throw MemoryOutOfBoundsException if this collection's max capacity
			 * has been reached.
			 */
			Void InsertAt(Size index, ConstElementTypeRef element) override
			{
				if (index < 0 || index >= this->m_count)
				{
					// Throw Exception
				}

				if (this->m_count >= this->m_max_capacity)
				{
					// Throw Exception
				}

				EntryNode* elem_node = new EntryNode(element);
				
				EntryNode* next_node = this->m_head;

				while (next_node->m_next && (index--) > 0)
					next_node = next_node->m_next;

				EntryNode* prev_node = next_node->m_prev;

				elem_node->m_next = next_node;
				elem_node->m_prev = prev_node;
				next_node->m_prev = elem_node;

				if (!prev_node)
					this->m_head = elem_node;
				else
					prev_node->m_next = elem_node;

				this->m_count++;
			}

			/**
			 * @brief Removes the specified element after the element in the
			 * specified index in this collection.
			 *
			 * This function will decreases this collection's count by one and shift
			 * all elements that preceed the removed element to the left.
			 *
			 * This function explicitly calls the destructor of the element
			 * but does not deallocate the memory it was stored at.
			 *
			 * @param[in] index The numerical index to remove the element at.
			 *
			 * @throw IndexOutOfRangeException if index to insert element is out
			 * of range.
			 *
			 * @Throws InvalidOperationException if this collection is empty.
			 */
			Void RemoveAt(Size index) override
			{
				if (index < 0 || index >= this->m_count)
				{
					// Throw Exception
				}

				if (!this->m_count)
				{
					// Throw Exception
				}

				EntryNode* curr_node = this->m_head;

				while (curr_node->m_next && (index--) > 0)
					curr_node = curr_node->m_next;

				EntryNode* next_node = curr_node->m_next;
				EntryNode* prev_node = curr_node->m_prev;

				if (!next_node && !prev_node)
					this->m_head = this->m_tail = nullptr;
				else if (!next_node)
				{
					this->m_tail = prev_node;
					this->m_tail->m_next = nullptr;
				}
				else if (!prev_node)
				{
					this->m_head = next_node;
					this->m_head->m_prev = nullptr;
				}
				else
				{
					prev_node->m_next = next_node;
					next_node->m_prev = prev_node;
				}

				free(curr_node);

				this->m_count--;
			}

		public:
			/**
			 * @brief Removes the first occurance of the specified element from
			 * this collection.
			 *
			 * This function explicitly calls the destructor of the element
			 * but does not deallocate the memory it was stored at.
			 *
			 * @param[in] element ElementType to remove from this collection.
			 *
			 * @return True if removal was successful and the element was found.
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
			 * @brief Searches this collection for the specified element.
			 *
			 * @param[in] element ElementType to search for in this collection.
			 *
			 * @return True if the specified element was found in this collection.
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
						this->PushBack(element);
					}
				);

				return true;
			}

			/**
			 * @brief Removes all the elements in the specified collection from this
			 * collection.
			 *
			 * This function explicitly calls the destructor of the elements
			 * but does not deallocate the memory it was stored at.
			 *
			 * @param[in] collection The collection containing elements to be
			 * removed from this collection.
			 *
			 * @return True if removal was successful, the elements were found and
			 * the collection is not empty.
			 */
			Bool RemoveAll(AbstractCollection<ElementType>& collection) override
			{
				if (!this->m_count || collection.IsEmpty())
					return false;

				Bool return_value;

				collection.ForEach([this, &return_value](ElementTypeRef element) -> Void
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
			 * @return True if the specified elements were found and the collection
			 * is not empty.
			 */
			Bool ContainsAll(AbstractCollection<ElementType>& collection) override
			{
				if (!this->m_count || collection.IsEmpty())
					return false;

				Bool return_value;

				collection.ForEach([this, &return_value](ElementTypeRef element) -> Void
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
			 * @brief Removes all the elements from this collection.
			 */
			Void Clear(void) override
			{
				if (!this->m_head)
					return;
				
				while (this->m_count > 0) this->PopBack();
			}
		};
	}
}

#endif // T_LINKED_LIST_H
