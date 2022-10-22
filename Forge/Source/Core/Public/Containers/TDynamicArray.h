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
			enum { CAPACITY_ALIGNMENT = 2};

		private:
			ElementTypePtr m_mem_block;

		private:
			Size m_version;

		public:
			class Iterator
			{
			private:
				ElementTypePtr m_raw_ptr;

			public:
				Iterator(ElementTypePtr ptr)
					: m_raw_ptr(ptr) {}

			public:
				Iterator(Iterator&& rhs)
				{
					this->m_raw_ptr = rhs.m_raw_ptr;
					rhs.m_raw_ptr = nullptr;
				}
				Iterator(const Iterator& rhs)
				{
					this->m_raw_ptr = rhs.m_raw_ptr;
				}

			public:
				Iterator& operator =(Iterator&& rhs)
				{
					this->m_raw_ptr = rhs.m_raw_ptr;
					rhs.m_raw_ptr = nullptr;

					return *this;
				}
				Iterator& operator =(const Iterator& rhs)
				{
					this->m_raw_ptr = rhs.m_raw_ptr;

					return *this;
				}

			public:
				virtual ~Iterator() = default;

			public:
				Iterator operator ++(void) override
				{
					Iterator itr(++this->m_raw_ptr);
					return itr;
				}
				Iterator operator ++(I32 junk) override
				{
					ElementTypePtr temp = this->m_raw_ptr++;

					Iterator itr(temp);
					return itr;
				}

			public:
				Iterator operator --(void) override
				{
					Iterator itr(--this->m_raw_ptr);
					return itr;
				}
				Iterator operator --(I32 junk) override
				{
					ElementTypePtr temp = this->m_raw_ptr--;

					Iterator itr(temp);
					return itr;
				}

			public:
				Bool operator ==(const Iterator& rhs)
				{
					return this->m_raw_ptr == rhs.m_raw_ptr;
				}
				Bool operator !=(const Iterator& rhs)
				{
					return this->m_raw_ptr != rhs.m_raw_ptr;
				}

			public:
				ElementTypeRef operator *(void)
				{
					return *this->m_raw_ptr;
				}
				ElementTypePtr operator ->(void)
				{
					return this->m_raw_ptr;
				}
			};
			class ConstIterator
			{
			private:
				ElementTypePtr m_raw_ptr;

			public:
				ConstIterator(ElementTypePtr ptr)
					: m_raw_ptr(ptr) {}

			public:
				ConstIterator(ConstIterator&& rhs)
				{
					this->m_raw_ptr = rhs.m_raw_ptr;
					rhs.m_raw_ptr = nullptr;
				}
				ConstIterator(const ConstIterator& rhs)
				{
					this->m_raw_ptr = rhs.m_raw_ptr;
				}

			public:
				virtual ~ConstIterator() = default;

			public:
				ConstIterator& operator =(ConstIterator&& rhs)
				{
					this->m_raw_ptr = rhs.m_raw_ptr;
					rhs.m_raw_ptr = nullptr;

					return *this;
				}
				ConstIterator& operator =(const ConstIterator& rhs)
				{
					this->m_raw_ptr = rhs.m_raw_ptr;

					return *this;
				}

			public:
				ConstIterator operator ++(void) override
				{
					ConstIterator itr(++this->m_raw_ptr);
					return itr;
				}
				ConstIterator operator ++(I32 junk) override
				{
					ElementTypePtr temp = this->m_raw_ptr++;

					ConstIterator itr(temp);
					return itr;
				}

			public:
				ConstIterator operator --(void) override
				{
					ConstIterator itr(--this->m_raw_ptr);
					return itr;
				}
				ConstIterator operator --(I32 junk) override
				{
					ElementTypePtr temp = this->m_raw_ptr--;

					ConstIterator itr(temp);
					return itr;
				}

			public:
				Bool operator ==(const ConstIterator& rhs)
				{
					return this->m_raw_ptr == rhs.m_raw_ptr;
				}
				Bool operator !=(const ConstIterator& rhs)
				{
					return this->m_raw_ptr != rhs.m_raw_ptr;
				}

			public:
				ConstElementTypeRef operator *(void)
				{
					return *this->m_raw_ptr;
				}
				ConstElementTypePtr operator ->(void)
				{
					return this->m_raw_ptr;
				}
			};

		public:
			TDynamicArray(void)
				: m_version(0), AbstractList<ElementType>(0, 0) {}
			TDynamicArray(ElementType&& element, Size count)
				: m_version(0), AbstractList<ElementType>(count, count)
			{
				this->m_mem_block = (ElementTypePtr)malloc(this->m_capacity * sizeof(ElementType));
				Memory::MoveConstruct(this->m_mem_block, element, this->m_capacity);
			}
			TDynamicArray(ConstElementTypeRef element, Size count)
				: m_version(0), AbstractList<ElementType>(count, count)
			{
				this->m_mem_block = (ElementTypePtr)malloc(this->m_capacity * sizeof(ElementType));
				Memory::CopyConstruct(this->m_mem_block, element, this->m_capacity);
			}
			TDynamicArray(std::initializer_list<ElementType> init_list)
				: m_version(0), AbstractList<ElementType>(init_list.size(), init_list.size())
			{
				this->m_mem_block = (ElementTypePtr)malloc(this->m_capacity * sizeof(ElementType));
				Memory::CopyConstructArray(this->m_mem_block, const_cast<ElementTypePtr>(init_list.begin()), this->m_capacity);
			}

		public:
			TDynamicArray(TDynamicArray<ElementType>&& rhs)
				: AbstractList<ElementType>(rhs)
			{
				if (this->m_mem_block == rhs.m_mem_block)
					return;

				Memory::Destruct(this->m_mem_block, this->m_count);
				Memory::MemoryCopy(this, &rhs, sizeof(TDynamicArray<ElementType>));

				rhs.m_mem_block = nullptr;
				rhs.m_count = 0;
				rhs.m_capacity = 0;
				rhs.m_version = 0;
			}
			TDynamicArray(const TDynamicArray<ElementType>& rhs)
				: AbstractList<ElementType>(rhs)
			{
				if (this->m_mem_block == rhs.m_mem_block)
					return;

				ConstSize old_count = this->m_count;
				ConstSize new_count = rhs.m_count;

				if (new_count > old_count)
				{
					this->Reserve(new_count);

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
			TDynamicArray<ElementType>& operator =(TDynamicArray<ElementType>&& rhs)
			{
				if (this->m_mem_block == rhs.m_mem_block)
					return *this;

				Memory::Destruct(this->m_mem_block, this->m_capacity);
				Memory::MemoryCopy(this, &rhs, sizeof(TDynamicArray<ElementType>));

				rhs.m_mem_block = nullptr;
				rhs.m_count = 0;
				rhs.m_capacity = 0;
				rhs.m_version = 0;

				return *this;
			}
			TDynamicArray<ElementType>& operator =(const TDynamicArray<ElementType>& rhs)
			{
				if (this->m_mem_block == rhs.m_mem_block)
					return *this;

				ConstSize old_count = this->m_count;
				ConstSize new_count = rhs.m_count;

				if (new_count > old_count)
				{
					this->Reserve(new_count);

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

				return *this;
			}

		public:
			~TDynamicArray()
			{
				this->Clear();

				free(this->m_mem_block);
			}
		
		public:
			ElementTypeRef operator [](Size ui_index) override
			{
				FORGE_ASSERT(ui_index >= 0 && ui_index < this->m_count, "Index is out of range.")
				return *(this->m_mem_block + ui_index);
			}

		public:
			/**
			 * @brief Returns a forward iterator pointing to the first element in
			 * the dynamic array.
			 *
			 * @return ForwardIterator pointing to the first element.
			 */
			Iterator GetStartItr(void) override
			{
				return Iterator(this->m_mem_block);
			}

			/**
			 * @brief Returns a forward iterator pointing to the past-end element
			 * in the dynamic array.
			 *
			 * @return ForwardIterator pointing to the past-end element element.
			 */
			Iterator GetEndItr(void) override
			{
				return Iterator(this->m_mem_block + this->m_capacity);
			}

			/**
			 * @brief Returns a backward iterator pointing to the last element in
			 * the dynamic array.
			 *
			 * The backward iterator moves in the reverse direction.
			 *
			 * @return BackwardIterator pointing to the last element.
			 */
			ConstIterator GetStartConstItr(void) override
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
			ConstIterator GetEndConstItr(void) override
			{
				return ConstIterator(this->m_mem_block + this->m_capacity);
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
			Bool IsEqual(const AbstractCollection<ElementType>& collection) const override
			{
				if (collection.IsEmpty())
					return false;

				if (this->m_count != collection.GetCount())
					return false;

				Iterator start_itr = this->GetStartItr();

				Iterator other_start_itr = collection.GetStartItr();
				Iterator other_end_itr = collection.GetEndItr();

				for (; other_start_itr != other_end_itr; start_itr++, other_start_itr++)
					if (!Memory::MemoryCompare(&(*start_itr), &(*other_start_itr)))
						return false;

				return false;
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
			Void ReserveCapacity(Size ui_capacity)
			{
				if (this->m_capacity >= ui_capacity)
					return;

				Size new_capacity;
				ConstSize max_capacity = ~(Size)0;
				ElementTypePtr old_elements, new_elements;

				new_capacity = this->m_capacity + (this->m_capacity / 2);
				new_capacity = new_capacity > ui_capacity ? new_capacity : ui_capacity;
				new_capacity = new_capacity < max_capacity ? new_capacity : max_capacity;
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
						if (Memory::MemoryCompare(ptr, &value, sizeof(ElementType))
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
						if (Memory::MemoryCompare(ptr, &value, sizeof(ElementType))
							return reinterpret_cast<I64>(Memory::SubAddress(ptr, start + 1)) / sizeof(ElementType);
					}
				}

				return -1;
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
			* @param[in] ui_index The numerical index to insert the element at.
			* @param[in] element  The element to insert in the dynamic array.
			*
			* @throw IndexOutOfRangeException if index to insert element is out
			* of range.
			*/
			Void InsertAt(Size ui_index, ElementType&& element) override
			{
				FORGE_ASSERT(ui_index >= 0 && ui_index <= this->m_count, "Index is out of range.")

				this->Reserve(this->m_count + 1);

				ElementType next, prev;

				ElementTypePtr ptr = this->m_mem_block + ui_index;

				for (I32 i = 0, prev = *ptr; i < this->m_count - ui_index; i++)
				{
					next = *(++ptr);
					*ptr = prev;
					prev = next;
				}

				this->m_count++;
				Memory::Move(this->m_mem_block + ui_index, element, 1);
			}

			/**
			* @brief Inserts the specified element in the specified index.
			*
			* This function will increase the count size by one and shift all
			* elements that preceed the newly inserted element. If the number of
			* elements overflow the capacity of the array a reallocation will occur
			* to accomodate for the increased size.
			*
			* @param[in] ui_index The numerical index to insert the element at.
			* @param[in] element  The element to insert in the dynamic array.
			*
			* @throw IndexOutOfRangeException if index to insert element is out
			* of range.
			*/
			Void InsertAt(Size ui_index, ConstElementTypeRef element) override
			{
				FORGE_ASSERT(ui_index >= 0 && ui_index <= this->m_count, "Index is out of range.")

				this->Reserve(this->m_count + 1);
				
				ElementType next, prev;

				ElementTypePtr ptr = this->m_mem_block + ui_index;
				
				for (I32 i = 0, prev = *ptr; i < this->m_count - ui_index; i++)
				{
					next = *(++ptr);
					*ptr = prev;
					prev = next;
				}

				this->m_count++;
				Memory::Copy(this->m_mem_block + ui_index, element, 1);
			}

			/**
			* @brief Inserts the specified element in the specified position.
			*
			* This function will increase the count size by one and shift all
			* elements that preceed the newly inserted element. If the number of
			* elements overflow the capacity of the array a reallocation will occur
			* to accomodate for the increased size.
			*
			* @param[in] position The numerical index to insert the element at.
			* @param[in] element  The element to insert in the dynamic array.
			*
			* @throw IndexOutOfRangeException if index to insert element is out
			* of range.
			*/
			Void InsertAt(Iterator& position, ElementType&& element) override
			{
				FORGE_ASSERT(position != this->GetEndItr(), "Index is out of range.")

				this->Reserve(this->m_count + 1);

				ElementType next, prev;

				Size iteration = reinterpret_cast<Size>(Memory::SubAddress(this->m_mem_block + this->m_count - 1, &(*position)));

				for (I32 i = 0, prev = *position; i < iteration; i++)
				{
					next = *(++position);
					*position = prev;
					prev = next;
				}

				this->m_count++;
				Memory::Move(&(*position), element, 1);
			}

			/**
			* @brief Inserts the specified element in the specified position.
			*
			* This function will increase the count size by one and shift all
			* elements that preceed the newly inserted element. If the number of
			* elements overflow the capacity of the array a reallocation will occur
			* to accomodate for the increased size.
			*
			* @param[in] position The numerical index to insert the element at.
			* @param[in] element  The element to insert in the dynamic array.
			*
			* @throw IndexOutOfRangeException if index to insert element is out
			* of range.
			*/
			Void InsertAt(Iterator& position, ConstElementTypeRef element) override
			{
				FORGE_ASSERT(position != this->GetEndItr(), "Index is out of range.")

				this->Reserve(this->m_count + 1);

				ElementType next, prev;

				Size iteration = reinterpret_cast<Size>(Memory::SubAddress(this->m_mem_block + this->m_count - 1, &(*position)));

				for (I32 i = 0, prev = *position; i < iteration; i++)
				{
					next = *(++position);
					*position = prev;
					prev = next;
				}

				this->m_count++;
				Memory::Copy(&(*position), element, 1);
			}

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
			*/
			Void RemoveAt(Size ui_index) override
			{
				FORGE_ASSERT(ui_index >= 0 && ui_index < this->m_count, "Index is out of range.")

				ElementTypePtr slow_ptr = this->m_mem_block + ui_index;
				ElementTypePtr fast_ptr = this->m_mem_block + ui_index + 1;

				this->m_count--;

				for (I32 i = 0; i < this->m_count - ui_index; i++)
					*(slow_ptr++) = *(fast_ptr++);

				Memory::Destruct(this->m_mem_block + ui_index, 1);
				Memory::Destruct(this->m_mem_block + ui_index + 1, 1);
			}

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
			*/
			Void RemoveAt(Iterator& position) override
			{
				FORGE_ASSERT(position != this->GetEndItr(), "Index is out of range.")

				this->m_count--;

				Size iteration = reinterpret_cast<Size>(Memory::SubAddress(this->m_mem_block + this->m_count - 1, &(*position)));

				for (I32 i = 0; i < iteration; i++)
					*(position++) = *((position + 1)++);

				Memory::Destruct(&(*position), 1);
				Memory::Destruct(&(*position + 1), 1);
			}

		public:
			/**
			 * @brief Inserts the specified element at the end of the dynamic array.
			 *
			 * @param[in] element The element to insert in the dynamic array.
			 *
			 * @return True if insertion was successfull.
			 */
			Bool Insert(ConstElementTypeRef element) override
			{
				this->InsertAt(this->m_count, element);

				return true;
			}

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
				Size index = FirstIndexOf(element);

				if (index == -1)
					return false;

				RemoveAt(index);

				return true;
			}

			/**
			 * @brief Searches the static array for the specified element.
			 *
			 * @param[in] element ElementType to search for in the static array.
			 *
			 * @return True if the specified element was found in the static array.
			 */
			Bool Contains(ConstElementTypeRef element) override
			{
				return FirstIndexOf(element) != -1;
			}

		public:
			/**
			 * @brief Inserts all the elements in the specified collection to the
			 * dynamic array.
			 *
			 * The order in which the elements are inserted into the dynamic array
			 * depends on how the specified collection is iterated on.
			 *
			 * @param[in] collection The collection containing elements to be added
			 * to the dynamic array.
			 *
			 * @return True if insertion was succesfull and collection is not empty.
			 */
			Bool InsertAll(const AbstractCollection<ElementType>& collection) override
			{
				if (collection.IsEmpty())
					return false;

				Iterator start_itr = collection.GetStartItr();
				Iterator end_itr = collection.GetEndItr();

				for (; start_itr != end_itr; start_itr++)
					InsertAt(start_itr, *start_itr);

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
			Bool RemoveAll(const AbstractCollection<ElementType>& collection) override
			{
				if (collection.IsEmpty())
					return false;

				Iterator start_itr = collection.GetStartItr();
				Iterator end_itr = collection.GetEndItr();

				for (; start_itr != end_itr; start_itr++)
					if (!Remove(*start_itr))
						return false;

				return true;
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
			Bool ContainsAll(const AbstractCollection<ElementType>& collection) override
			{
				if (collection.IsEmpty())
					return false;

				Iterator start_itr = collection.GetStartItr();
				Iterator end_itr = collection.GetEndItr();

				for (; start_itr != end_itr; start_itr++)
					if (!Contains(*start_itr))
						return false;

				return true;
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
