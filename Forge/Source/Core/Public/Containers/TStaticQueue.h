#ifndef T_STATIC_QUEUE_H
#define T_STATIC_QUEUE_H

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
		template<typename InElementType, Size InMaxSize>
		class TStaticQueue : public AbstractList<InElementType>
		{
		private:
			using ElementType         = InElementType;
			using ElementTypeRef      = InElementType&;
			using ElementTypePtr      = InElementType*;
			using ConstElementType    = const InElementType;
			using ConstElementTypeRef = const InElementType&;
			using ConstElementTypePtr = const InElementType*;

		private:
			ElementType m_mem_block[InMaxSize];

		public:
			struct Iterator
			{
			private:
				ElementTypePtr m_ptr;

			public:
				Iterator(void)
					: m_ptr(nullptr) {}

				Iterator(ElementTypePtr ptr)
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

					this->m_ptr++;

					return temp;
				}
				Iterator operator --(void)
				{
					this->m_ptr++;

					return *this;
				}

			public:
				Iterator operator ++(I32)
				{
					Iterator temp(this->m_ptr);

					this->m_ptr++;

					return temp;
				}
				Iterator operator ++(void)
				{
					this->m_ptr++;

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
					return *(this->m_ptr);
				}

			public:
				ElementTypePtr operator ->()
				{
					return this->m_ptr;
				}
			};

		public:
			TStaticQueue(void)
				: AbstractList<ElementType>(0, InMaxSize)
			{
				FORGE_ASSERT(this->m_max_capacity != 0 && this->m_count < this->m_max_capacity, "Array size is not large enough to store the data.")
			}

			TStaticQueue(ElementType&& element, Size count)
				: AbstractList<ElementType>(count, InMaxSize)
			{
				FORGE_ASSERT(this->m_max_capacity != 0 && this->m_count < this->m_max_capacity, "Array size is not large enough to store the data.")

				Memory::MoveConstruct(m_mem_block, element, this->m_count);
			}

			TStaticQueue(ConstElementTypeRef element, Size count)
				: AbstractList<ElementType>(count, InMaxSize)
			{
				FORGE_ASSERT(this->m_max_capacity != 0 && this->m_count < this->m_max_capacity, "Array size is not large enough to store the data.")

				Memory::CopyConstruct(m_mem_block, element, this->m_count);
			}

			TStaticQueue(std::initializer_list<ElementType> init_list)
				: AbstractList<ElementType>(init_list.size(), InMaxSize)
			{
				FORGE_ASSERT(this->m_max_capacity != 0 && this->m_count < this->m_max_capacity, "Array size is not large enough to store the data.")

				Memory::MoveConstructArray(this->m_mem_block, const_cast<ElementTypePtr>(init_list.begin()), this->m_count);
			}

		public:
			TStaticQueue(TStaticQueue<ElementType, InMaxSize>&& rhs)
			{
				Memory::MemoryCopy(this, &rhs, sizeof(TStaticQueue<ElementType, InMaxSize>));

				rhs.m_mem_block = nullptr;
				rhs.m_count = 0;
			}

			TStaticQueue(const TStaticQueue<ElementType, InMaxSize>& rhs)
			{
				Memory::CopyConstructArray(this->m_mem_block, rhs.m_mem_block, rhs.m_count);

				this->m_count = rhs.m_count;
			}

		public:
			~TStaticQueue()
			{
				this->Clear();
			}

		public:
			TStaticQueue<ElementType, InMaxSize>& operator =(TStaticQueue<ElementType, InMaxSize>&& rhs)
			{
				Memory::MemoryCopy(this, &rhs, sizeof(TStaticQueue<ElementType, InMaxSize>));

				rhs.m_mem_block = nullptr;
				rhs.m_count = 0;
			}

			TStaticQueue<ElementType, InMaxSize>& operator =(const TStaticQueue<ElementType, InMaxSize>& rhs)
			{
				Memory::CopyArray(this->m_mem_block, rhs.m_mem_block, rhs.m_count);

				this->m_count = rhs.m_count;
			}			

		public:
			/**
			 * @brief Returns an iterator pointing to the first element in this
			 * static stack.
			 *
			 * @return Iterator pointing to the first element.
			 */
			Iterator GetStartItr(void) const
			{
				return Iterator(const_cast<ElementTypePtr>(this->m_mem_block));
			}

			/**
			 * @brief Returns an iterator pointing to the past-end element in this
			 * static stack.
			 *
			 * @return Iterator pointing to the past-end element element.
			 */
			Iterator GetEndItr(void) const
			{
				return Iterator(const_cast<ElementTypePtr>(this->m_mem_block + this->m_count));
			}

			/**
			 * @brief Returns a const iterator pointing to the first element in this
			 * static stack.
			 *
			 * @return ConstIterator pointing to the first element.
			 */
			Iterator GetStartConstItr(void) const
			{
				return ConstIterator(const_cast<ElementTypePtr>(this->m_mem_block));
			}

			/**
			 * @brief Returns a const iterator pointing to the past-end element in this
			 * static.
			 *
			 * @return ConstIterator pointing to the past-end element element.
			 */
			Iterator GetEndConstItr(void) const
			{
				return ConstIterator(const_cast<ElementTypePtr>(this->m_mem_block + this->m_count));
			}

		public:
			/**
			 * @brief Gets a direct pointer to the memory array managed by the
			 * static stack.
			 *
			 * Elements in the memory array are guranteed to be stored in contiguous
			 * memory locations. This allows the pointer to be offsetted to access
			 * different elements.
			 *
			 * @return Const pointer storing address of the memory array.
			 */
			ConstElementTypePtr GetRawData() const override
			{
				return this->m_mem_block;
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
			 * collection's forward iterator.
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
				if (!this->m_count)
					return nullptr;

				ElementTypePtr array_ptr = (ElementTypePtr)malloc(this->m_count * sizeof(ElementType));

				Memory::CopyConstructArray(array_ptr, const_cast<ElementTypePtr>(this->m_mem_block), this->m_count);

				return array_ptr;
			}

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
			 * @return ElementTypePtr storing the address of the array or
			 * nullptr if collection is empty.
			 */
			ElementTypePtr ToArray(ElementTypePtr array_ptr) const override
			{
				if (!this->m_count)
					return nullptr;

				Memory::CopyConstructArray(array_ptr, const_cast<ElementTypePtr>(this->m_mem_block), this->m_count);

				return array_ptr;
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
			virtual Void ForEach(Common::TDelegate<Void(ElementTypeRef)> function) override
			{
				for (I32 i = 0; i < this->m_count; i++)
					function.Invoke(*(this->m_mem_block + i));
			}

		public:
			/**
			 * @brief Returns the index of the first occurence of the specified
			 * element in the static queue, or -1 if it does not contain the element.
			 *
			 * @param[in] element The element to search for the first occurence.
			 *
			 * @return Size storing the index of the first occurrence of the
			 * specified element, or -1 if the static queue does not contain the
			 * element.
			 */
			I64 FirstIndexOf(ConstElementTypeRef element) const override
			{
				if (!this->m_count)
					return -1;
				
				ConstElementTypePtr start = this->m_mem_block;
				ConstElementTypePtr end = start + this->m_count;

				for (ConstElementTypePtr ptr = start; ptr != end; ptr++)
				{
					if (Memory::MemoryCompare(ptr, &element, sizeof(ElementType)))
						return reinterpret_cast<I64>(Memory::SubAddress(ptr, start)) / sizeof(ElementType);
				}
				
				return -1;
			}

			/**
			 * @brief Returns the index of the last occurence of the specified
			 * element in the static queue, or -1 if it does not contain the element.
			 *
			 * @param[in] element The element to search for the first occurence.
			 *
			 * @return Size storing the index of the last occurrence of the
			 * specified element, or -1 if the static queue does not contain the
			 * element.
			 */
			I64 LastIndexOf(ConstElementTypeRef element) const override
			{
				if (!this->m_count)
					return -1;
				
				ConstElementTypePtr start = this->m_mem_block - 1;
				ConstElementTypePtr end = start + this->m_count;

				for (ConstElementTypePtr ptr = end; ptr != end; ptr--)
				{
					if (Memory::MemoryCompare(ptr, &element, sizeof(ElementType)))
						return reinterpret_cast<I64>(Memory::SubAddress(ptr, start + 1)) / sizeof(ElementType);
				}
				
				return -1;
			}

		public:
			/**
			 * @brief Retreives the top most element in the static stack.
			 *
			 * @return ConstElementTypeRef storing the top most element in the
			 * static stack.
			 */
			ConstElementTypeRef PeekBack() const override
			{
				// Throw Exception

				return ElementType();
			}

			/**
			 * @brief The static stack only allows retrieval of the top most element.
			 *
			 * @throws InvalidOperationException if attempted to retrieve the first
			 * element.
			 */
			ConstElementTypeRef PeekFront() const override
			{
				return *(this->m_mem_block);
			}

		public:
			/**
			 * @brief The static queue only allows insertion of elements at the front
			 * of the queue.
			 *
			 * @throws InvalidOperationException if attempted to insert at the back
			 * of the stack.
			 */
			Void PushBack(ElementType&& element) override
			{
				// Throw Exception
			}

			/**
			 * @brief Inserts a new element at the front of the static queue, after
			 * its current last element.
			 *
			 * This operation has the same functionality as Push.
			 *
			 * @param[in] element The element to insert in the static queue.
			 */
			Void PushFront(ElementType&& element) override
			{
				if (this->m_count >= this->m_max_capacity)
				{
					// Throw Exception
				}

				Memory::Move(this->m_mem_block + this->m_count, std::move(element), 1);

				this->m_count++;
			}

			/**
			 * @brief Inserts a new element at the end of the static stack, after
			 * its current last element.
			 *
			 * This operation has the same functionality as Push.
			 *
			 * @param[in] element The element to insert in the static stack.
			 */
			Void PushBack(ConstElementTypeRef element) override
			{
				// Throw Exception
			}

			/**
			 * @brief The static stack only allows insertion of elements at the end
			 * of the stack.
			 *
			 * @throws InvalidOperationException if attempted to insert at the front
			 * of the stack.
			 */
			Void PushFront(ConstElementTypeRef element) override
			{
				if (this->m_count >= this->m_max_capacity)
				{
					// Throw Exception
				}

				Memory::Copy(this->m_mem_block + this->m_count, element, 1);

				this->m_count++;
			}

			/**
			 * @brief Removes the element at the end of this static stack, effectivly
			 * reducing the list count by one.
			 *
			 * This operation has the same functionality as Pop.
			 */
			Void PopBack(void) override
			{
				// Throw Exception
			}

			/**
			 * @brief The static stack only allows removal of elements at the end
			 * of the stack.
			 *
			 * @throws InvalidOperationException if attempted to remove at the front
			 * of the stack.
			 */
			Void PopFront(void) override
			{
				if (!this->m_count)
				{
					// Throw Exception
				}

				ElementTypePtr slow_ptr = this->m_mem_block;
				ElementTypePtr fast_ptr = this->m_mem_block + 1;

				this->m_count--;

				for (I32 i = 0; i < this->m_count; i++)
					*(slow_ptr++) = *(fast_ptr++);

				Memory::Destruct(this->m_mem_block, 1);
			}

		public:
			/**
			 * @brief Inserts a new element at the end of the static stack, after
			 * its current last element.
			 *
			 * This operation has the same functionality as PushBack.
			 *
			 * @param[in] element The element to insert in the static stack.
			 */
			Void Push(ElementType&& element)
			{
				this->PushFront(element);
			}

			/**
			 * @brief Inserts a new element at the end of the static stack, after
			 * its current last element.
			 *
			 * This operation has the same functionality as PushBack.
			 *
			 * @param[in] element The element to insert in the static stack.
			 */
			Void Push(ConstElementTypeRef element)
			{
				this->PushFront(element);
			}

			/**
			 * @brief Removes the element at the end of this static stack, effectivly
			 * reducing the list count by one.
			 *
			 * This operation has the same functionality as PopBack.
			 */
			Void Pop(void)
			{
				this->PopFront();
			}

		public:
			/**
			 * @brief The static queue does not support insertion of elements at
			 * specified positions.
			 *
			 * @throws InvalidOperationException if attempted to insert element at
			 * a specified position
			 */
			Void InsertAt(Size index, ElementType&& element) override
			{
				// Throw Exception
			}

			/**
			 * @brief The static queue does not support insertion of elements at
			 * specified positions.
			 *
			 * @throws InvalidOperationException if attempted to insert element at
			 * a specified position
			 */
			Void InsertAt(Size index, ConstElementTypeRef element) override
			{
				// Throw Exception
			}

			/**
			 * @brief The static queue does not support removal of elements at
			 * specified positions.
			 *
			 * @throws InvalidOperationException if attempted to remove element at
			 * a specified position
			 */
			Void RemoveAt(Size index) override
			{
				// Throw Exception
			}
		public:
			/**
			 * @brief The static queue does not support removal of elements at
			 * specified positions.
			 *
			 * @throws InvalidOperationException if attempted to remove element at
			 * a specified position
			 */
			Bool Remove(ConstElementTypeRef element) override
			{
				// Throw Exception

				return false;
			}

			/**
			 * @brief Searches the static queue for the specified element.
			 *
			 * @param[in] element ElementType to search for in the static stack.
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
						this->Push(element);
					}
				);

				return true;
			}

			/**
			 * @brief The static stack does not support removal of elements at
			 * specified positions.
			 *
			 * @throws InvalidOperationException if attempted to remove element at
			 * a specified position
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
			 * @brief Removes all the elements from the static queue.
			 *
			 * The static stack will be empty after this operation.
			 */
			Void Clear(void) override
			{
				if (!this->m_count)
					return;

				Memory::Destruct(this->m_mem_block, this->m_count);

				this->m_count = 0;
			}
		};
	}
}
#endif // T_STATIC_QUEUE_H
