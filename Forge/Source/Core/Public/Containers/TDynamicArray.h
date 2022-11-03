#ifndef T_DYNAMIC_ARRAY_H
#define T_DYNAMIC_ARRAY_H

#include <stdlib.h>
#include <initializer_list>

#include "AbstractList.h"

#include "Core/Public/Common/TypeDefinitions.h"
#include "Core/Public/Common/PreprocessorUtilities.h"

#include "Core/Public/Memory/MemoryUtilities.h"

namespace Forge {
	namespace Containers
	{
		template<typename InElementType>
		class TDynamicArray : public AbstractList<InElementType>
		{
		private:
			using ElementType         = InElementType;
			using ElementTypeRef      = InElementType&;
			using ElementTypePtr      = InElementType*;
			using ConstElementType    = const InElementType;
			using ConstElementTypeRef = const InElementType&;
			using ConstElementTypePtr = const InElementType*;

		private:
			enum { CAPACITY_ALIGNMENT = 2 };

		private:
			ElementTypePtr m_mem_block;

		private:
			Size m_capacity;
			Size m_version;

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
			/**
			 * @brief Default constructor.
			 *
			 * Constructs an empty dynamic array.
			 */
			TDynamicArray(void)
				: m_version(0), AbstractList<ElementType>(0, 0) {}

			/**
			 * @brief Move element constructor.
			 *
			 * Constructs a dynamic array with a copy of an element.
			 */
			TDynamicArray(ElementType&& element, Size count)
				: m_version(0), AbstractList<ElementType>(count, ~((Size)0))
			{
				this->m_mem_block = (ElementTypePtr)malloc(this->m_count * sizeof(ElementType));

				Memory::MoveConstruct(this->m_mem_block, element, this->m_count);
			}

			/**
			 * @brief Copy element constructor.
			 *
			 * Constructs a dynamic array with a copy of an element.
			 */
			TDynamicArray(ConstElementTypeRef element, Size count)
				: m_version(0), AbstractList<ElementType>(count, ~((Size)0))
			{
				this->m_mem_block = (ElementTypePtr)malloc(this->m_count * sizeof(ElementType));
				Memory::CopyConstruct(this->m_mem_block, element, this->m_count);
			}

			/**
			 * @brief Initializer list constructor.
			 *
			 * Constructs a static array with an initializer list.
			 */
			TDynamicArray(std::initializer_list<ElementType> init_list)
				: m_version(0), AbstractList<ElementType>(init_list.size(), ~((Size)0))
			{
				this->m_mem_block = (ElementTypePtr)malloc(this->m_count * sizeof(ElementType));
				Memory::CopyConstructArray(this->m_mem_block, const_cast<ElementTypePtr>(init_list.begin()), this->m_count);
			}

		public:
			/**
			 * @brief Move constructor.
			 */
			TDynamicArray(TDynamicArray<ElementType>&& rhs)
				: AbstractList<ElementType>(rhs)
			{
				Memory::MemoryCopy(this, &rhs, sizeof(TDynamicArray<ElementType>));

				rhs.m_mem_block = nullptr;
				rhs.m_count = rhs.m_capacity = rhs.m_version = 0;
			}

			/**
			 * @brief Copy constructor.
			 */
			TDynamicArray(const TDynamicArray<ElementType>& rhs)
				: AbstractList<ElementType>(rhs)
			{
				ConstSize old_count = this->m_count;
				ConstSize new_count = rhs.m_count;

				if (new_count > old_count)
				{
					this->ReserveCapacity(new_count);

					Memory::CopyArray(this->m_mem_block, rhs.m_mem_block, old_count);
					Memory::CopyConstructArray(this->m_mem_block + old_count, rhs.m_mem_block + old_count, new_count - old_count);
				}
				else
				{
					Memory::CopyArray(this->m_mem_block, rhs.m_mem_block, new_count);
					Memory::Destruct(this->m_mem_block + new_count, old_count - new_count);
				}

				this->m_count = rhs.m_count;
				this->m_capacity = rhs.m_capacity;
			}

		public:	
			~TDynamicArray()
			{
				this->Clear();

				free(this->m_mem_block);
			}

		public:
			TDynamicArray<ElementType>& operator =(TDynamicArray<ElementType>&& rhs)
			{
				this->Clear();
				
				Memory::MemoryCopy(this, &rhs, sizeof(TDynamicArray<ElementType>));

				rhs.m_mem_block = nullptr;
				rhs.m_capacity = rhs.m_count = rhs.m_version = 0;

				return *this;
			}

			TDynamicArray<ElementType>& operator =(const TDynamicArray<ElementType>& rhs)
			{
				ConstSize old_count = this->m_count;
				ConstSize new_count = rhs.m_count;

				this->Clear();

				if (new_count > old_count)
				{
					this->ReserveCapacity(new_count);

					Memory::CopyArray(this->m_mem_block, rhs.m_mem_block, old_count);
					Memory::CopyConstructArray(this->m_mem_block + old_count, rhs.m_mem_block + old_count, new_count - old_count);
				}
				else
					Memory::CopyArray(this->m_mem_block, rhs.m_mem_block, new_count);

				this->m_count = rhs.m_count;
				this->m_capacity = rhs.m_capacity;

				return *this;
			}
		
		public:
			ElementTypeRef operator [](Size index)
			{
				FORGE_ASSERT(index >= 0 && index < this->m_count, "Index is out of range.")
				return *(this->m_mem_block + index);
			}

		public:
			/**
			 * @brief Returns a forward iterator pointing to the first element in
			 * the dynamic array.
			 *
			 * @return ForwardIterator pointing to the first element.
			 */
			Iterator GetStartItr(void) const
			{
				return Iterator(this->m_mem_block);
			}

			/**
			 * @brief Returns a forward iterator pointing to the past-end element
			 * in the dynamic array.
			 *
			 * @return ForwardIterator pointing to the past-end element element.
			 */
			Iterator GetEndItr(void) const
			{
				return Iterator(this->m_mem_block + this->m_count);
			}

			/**
			 * @brief Returns a backward iterator pointing to the last element in
			 * the dynamic array.
			 *
			 * The backward iterator moves in the reverse direction.
			 *
			 * @return BackwardIterator pointing to the last element.
			 */
			Iterator GetStartConstItr(void) const
			{
				return ConstIterator(this->m_mem_block);
			}

			/**
			 * @brief Returns a backward iterator pointing to the first element in
			 * the dynamic array.
			 *
			 * The backward iterator moves in the reverse direction.
			 *
			 * @return BackwardIterator pointing to the first element.
			 */
			Iterator GetEndConstItr(void) const
			{
				return ConstIterator(this->m_mem_block + this->m_count);
			}

		public:
			/**
			 * @brief Gets a direct pointer to the memory array managed by this
			 * collection.
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
			 * @brief Checks whether the dynamic array is equal to the specified
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
			 * @brief Returns an array containing all the elements stored in the
			 * dynamic array.
			 *
			 * The length of the array is equal to the number of elements stored in
			 * the static array. The array returned also stores the elements in the
			 * same order that it is stored in the static array and contains deep
			 * copies of the elements.
			 *
			 * @return ElementTypePtr storing the address of the new array.
			 */
			ElementTypePtr ToArray(void) const override
			{
				ElementTypePtr array_ptr = (ElementTypePtr)malloc(this->m_count * sizeof(ElementType));

				Memory::CopyConstructArray(array_ptr, this->m_mem_block, this->m_count);

				return array_ptr;
			}

			/**
			 * @brief Fills the passed array with all the elements stored in the
			 * static array.
			 *
			 * The length of the passed array must be equal to the number of
			 * elements stored in the static array. The array passed will store the
			 * elements in the same order that it is stored in the static array and
			 * will contain deep copies of the elements.
			 *
			 * @param[out] array_ptr The array to fill with elements from this
			 * array's memory block.
			 *
			 * @return ElementTypePtr storing the address of the passed array.
			 */
			ElementTypePtr ToArray(ElementTypePtr array_ptr) const override
			{
				Memory::CopyConstructArray(array_ptr, this->m_mem_block, this->m_count);

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
			Void ForEach(Common::TDelegate<Void(ElementTypeRef)> function) override
			{
				for (I32 i = 0; i < this->m_count; i++)
					function.Invoke(*(this->m_mem_block + i));
			}

		public:
			/**
			 * @brief
			 * 
			 * @param[in] capacity The minimum capacity of the dynamic array.
			 */
			Void ReserveCapacity(Size capacity)
			{
				if (this->m_capacity >= capacity)
					return;

				Size new_capacity;

				ElementTypePtr old_elements, new_elements;

				new_capacity = this->m_capacity + (this->m_capacity / 2);
				new_capacity = new_capacity > capacity ? new_capacity : capacity;
				new_capacity = new_capacity < this->m_max_capacity ? new_capacity : this->m_max_capacity;
				new_capacity = (new_capacity + (CAPACITY_ALIGNMENT - 1)) & ~(CAPACITY_ALIGNMENT - 1);
			
				old_elements = this->m_mem_block;
				new_elements = (ElementTypePtr)malloc(new_capacity * sizeof(ElementType));

				Memory::MoveConstructArray(new_elements, old_elements, this->m_count);

				free(old_elements);

				this->m_mem_block = new_elements;
				this->m_capacity = new_capacity;
				this->m_version++;
			}

		public:
			/**
			 * @brief Returns the index of the first occurence of the specified
			 * element in the static array, or -1 if it does not contain the
			 * element or it is empty.
			 *
			 * @param[in] value The element to search for the first occurence.
			 *
			 * @return Size storing the index of the first occurrence of the
			 * specified element, or -1 if the dynamic array does not contain the
			 * element or it is empty.
			 */
			I64 FirstIndexOf(ConstElementTypeRef value) const override
			{
				if (this->m_count)
				{
					ConstElementTypePtr start = this->m_mem_block;
					ConstElementTypePtr end = start + this->m_count;

					for (ConstElementTypePtr ptr = start; ptr != end; ptr++)
					{
						if (Memory::MemoryCompare(ptr, &value, sizeof(ElementType)))
							return reinterpret_cast<I64>(Memory::SubAddress(ptr, start)) / sizeof(ElementType);
					}
				}

				return -1;
			}

			/**
			 * @brief Returns the index of the last occurence of the specified
			 * element in the static array, or -1 if it does not contain the
			 * element or it is empty.
			 *
			 * @param[in] value The element to search for the last occurence.
			 *
			 * @return Size storing the index of the last occurrence of the
			 * specified element, or -1 if the dynamic array does not contain the
			 * element or it is empty.
			 */
			I64 LastIndexOf(ConstElementTypeRef value) const override
			{
				if (this->m_count > 0)
				{
					ConstElementTypePtr start = this->m_mem_block - 1;
					ConstElementTypePtr end = start + this->m_count;

					for (ConstElementTypePtr ptr = end; ptr != start; ptr--)
					{
						if (Memory::MemoryCompare(ptr, &value, sizeof(ElementType)))
							return reinterpret_cast<I64>(Memory::SubAddress(ptr, start + 1)) / sizeof(ElementType);
					}
				}

				return -1;
			}

		public:
			/**
			 * @brief Retreives the last element in the dynamic array.
			 *
			 * @return ConstElementTypeRef storing the last element in the list.
			 */
			ConstElementTypeRef PeekBack() const
			{
				if (!this->m_count)
				{
					// Throw Exception
				}

				return *(this->m_mem_block + this->m_count - 1);
			}

			/**
			 * @brief Retreives the first element in the dynamic array.
			 *
			 * @return ConstElementTypeRef storing the first element in the list.
			 */
			ConstElementTypeRef PeekFront() const
			{
				if (!this->m_count)
				{
					// throw exception
				}

				return *(this->m_mem_block);
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
				this->InsertAt(this->m_count, element);
			}

			/**
			 * @brief Inserts a new element at the start of this linked list, before
			 * its current first element.
			 *
			 * @param[in] element The element to insert in this linked list.
			 */
			Void PushFront(ElementType&& element) override
			{
				this->InsertAt(0, element);
			}

			/**
			 * @brief Inserts a new element at the end of this linked list, after
			 * its current last element.
			 *
			 * @param[in] element The element to insert in the linked list.
			 */
			Void PushBack(ConstElementTypeRef element) override
			{
				this->InsertAt(this->m_count, element);
			}

			/**
			 * @brief Inserts a new element at the start of this linked list, before
			 * its current first element.
			 *
			 * @param[in] element The element to insert in thi linked list.
			 */
			Void PushFront(ConstElementTypeRef element) override
			{
				this->InsertAt(0, element);
			}

			/**
			 * @brief Removes the element at the end of this linked list, effectivly
			 * reducing the list count by one.
			 */
			Void PopBack(void) override
			{
				this->RemoveAt(this->m_count - 1);
			}

			/**
			 * @brief Removes the element at the start of this linked list,
			 * effectivly reducing the list count by one.
			 */
			Void PopFront(void) override
			{
				this->RemoveAt(0);
			}

		public:
			/**
			* @brief Inserts the specified element in the specified index.
			*
			* This function will increase the count size by one and shift all
			* elements that preceed the newly inserted element. If the number of
			* elements overflow the capacity of the array a reallocation will occur
			* to accomodate for the increased size.
			*
			* @param[in] index The numerical index to insert the element at.
			* @param[in] element  The element to insert in the dynamic array.
			*
			* @throw IndexOutOfRangeException if index to insert element is out
			* of range.
			*/
			Void InsertAt(Size index, ElementType&& element) override
			{
				FORGE_ASSERT(index >= 0 && index <= this->m_count, "Index is out of range.")

				if (this->m_count >= this->m_max_capacity)
					return;

				this->ReserveCapacity(this->m_count + 1);

				ElementType next, prev;

				ElementTypePtr ptr = this->m_mem_block + index;

				for (I32 i = 0, prev = *ptr; i < this->m_count - index; i++)
				{
					next = *(++ptr);
					*ptr = prev;
					prev = next;
				}

				Memory::Move(this->m_mem_block + index, std::move(element), 1);

				this->m_count++;
			}

			/**
			* @brief Inserts the specified element in the specified index.
			*
			* This function will increase the count size by one and shift all
			* elements that preceed the newly inserted element. If the number of
			* elements overflow the capacity of the array a reallocation will occur
			* to accomodate for the increased size.
			*
			* @param[in] index The numerical index to insert the element at.
			* @param[in] element  The element to insert in the dynamic array.
			*
			* @throw IndexOutOfRangeException if index to insert element is out
			* of range.
			*/
			Void InsertAt(Size index, ConstElementTypeRef element) override
			{
				FORGE_ASSERT(index >= 0 && index <= this->m_count, "Index is out of range.")

				if (this->m_count >= this->m_max_capacity)
					return;

				this->ReserveCapacity(this->m_count + 1);
				
				ElementType next, prev;

				ElementTypePtr ptr = this->m_mem_block + index;
				
				for (I32 i = 0, prev = *ptr; i < this->m_count - index; i++)
				{
					next = *(++ptr);
					*ptr = prev;
					prev = next;
				}

				Memory::Copy(this->m_mem_block + index, element, 1);

				this->m_count++;
			}

			/**
			* @brief Removes an element in the specified index.
			*
			* This function will decrease the count size by one and shift all
			* elements that preceed the removed element.
			*
			* @param[in] index The numerical index to remove the element at.
			*
			* @throw IndexOutOfRangeException if index to remove element at is out
			* of range.
			*/
			Void RemoveAt(Size index) override
			{
				FORGE_ASSERT(index >= 0 && index < this->m_count, "Index is out of range.")

				if(!this->m_count)
					return;

				ElementTypePtr slow_ptr = this->m_mem_block + index;
				ElementTypePtr fast_ptr = this->m_mem_block + index + 1;

				Memory::Destruct(this->m_mem_block + index, 1);

				for (I32 i = 0; i < this->m_count - index; i++)
					*(slow_ptr++) = *(fast_ptr++);
				
				this->m_count--;
			}

		public:
			/**
			 * @brief Removes the first occurance of the specified element from the
			 * static array.
			 *
			 * This operation explicitly calls the destructor of the element
			 * but does not deallocate the memory it was stored at.
			 *
			 * @param[in] element ElementType to remove from the static array.
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
			 * @brief Searches the static array for the specified element.
			 *
			 * @param[in] element ElementType to search for in the static array.
			 *
			 * @return True if the specified element was found in the static array.
			 */
			Bool Contains(ConstElementTypeRef element) const override
			{
				return FirstIndexOf(element) != -1;
			}

		public:
			/**
			 * @brief Inserts all the elements in the specified collection to the
			 * static array.
			 *
			 * The order in which the elements are inserted into the static array
			 * depends on how the specified collection is iterated on.
			 *
			 * @param[in] collection The collection containing elements to be added
			 * to the static array.
			 *
			 * @return True if insertion was succesfull and collection is not empty.
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
			 * @brief Removes all the elements in the specified collection from the
			 * static array.
			 *
			 * This operation explicitly calls the destructor of the element
			 * but does not deallocate the memory it was stored at.
			 *
			 * @param[in] collection The collection containing elements to be
			 * removed from the static array.
			 *
			 * @return True if removal was successful, the elements were found and
			 * the collection is not empty.
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
			 * the static array.
			 *
			 * @param[in] collection The collection containing elements to be
			 * search for in the static array.
			 *
			 * @return True if the specified elements were found in the static
			 * array and the collection is not empty.
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
			 * @brief Removes all the elements from the dynamic array.
			 *
			 * The dynamic array will be empty after this operation.
			 */
			Void Clear(void) override
			{
				Memory::Destruct(this->m_mem_block, this->m_count);

				this->m_count = 0;
				this->m_version = 0;
			}
		};
	}
}

#endif // T_DYNAMIC_ARRAY_H
