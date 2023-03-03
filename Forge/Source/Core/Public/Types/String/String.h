#ifndef STRING_H
#define STRING_H

#include "AbstractString.h"

#include "Core/Public/Common/Compiler.h"

namespace Forge {
	namespace Type
	{
		class FORGE_API String : public AbstractString
		{
		private:
			using SelfType         = String;
			using SelfTypeRef      = String&;
			using SelfTypePtr      = String*;
			using ConstSelfType    = const String;
			using ConstSelfTypeRef = const String&;
			using ConstSelfTypePtr = const String*;

		private:
			enum { CAPACITY_ALIGNMENT = 2};

		private:
			CharPtr m_buffer;
		
		private:
			Size m_version;
			Size m_capacity;

		public:
			String(void)
				: m_buffer(nullptr), m_version(0), m_capacity(0), AbstractString(0, ~((Size)0)) {}

			String(CharPtr str)
				: m_version(0), m_capacity(0), AbstractString(0, ~((Size)0))
			{
				this->m_count = this->m_capacity = Algorithm::GetStringLength(str);

				this->m_buffer = (CharPtr)malloc((this->GetCount() + 1) * sizeof(Char));

				Memory::MemorySet(this->m_buffer, '\0', this->GetCount() + 1);

				Memory::MemoryCopy(this->m_buffer, str, this->GetCount());
			}

			String(ConstCharPtr str)
				: m_version(0), m_capacity(0), AbstractString(0, ~((Size)0))
			{
				this->m_count = this->m_capacity = Algorithm::GetStringLength(str);

				this->m_buffer = (CharPtr)malloc((this->GetCount() + 1) * sizeof(Char));

				Memory::MemorySet(this->m_buffer, '\0', this->GetCount() + 1);

				Memory::MemoryCopy(this->m_buffer, const_cast<CharPtr>(str), this->GetCount());
			}

		public:
			String(SelfType&& other)
				: AbstractString(other)
			{
				*this = Algorithm::Move(other);
			}

			String(ConstSelfTypeRef other)
				: AbstractString(other)
			{
				*this = other;
			}
		
		public:
			String& operator =(CharPtr str)
			{
				ConstSize new_count = Algorithm::GetStringLength(str);

				this->Clear();

				if (new_count > this->GetCount())
					this->ReserveCapacity(new_count);

				Memory::MemoryCopy(this->m_buffer, str, new_count);

				this->m_count = new_count;

				return *this;
			}

			String& operator =(ConstCharPtr str)
			{
				ConstSize new_count = Algorithm::GetStringLength(str);

				this->Clear();

				if (new_count > this->GetCount())
					this->ReserveCapacity(new_count);

				Memory::MemoryCopy(this->m_buffer, const_cast<CharPtr>(str), new_count);

				this->m_count = new_count;

				return *this;
			}

			String& operator =(SelfType&& other)
			{
				this->Clear();

				Memory::MemoryCopy(this, &other, sizeof(SelfType));

				other.m_buffer = nullptr;
				other.m_count = other.m_version = other.m_capacity = 0;

				return *this;
			}

			String& operator =(ConstSelfTypeRef other)
			{
				this->Clear();

				if (other.GetCount() > this->GetCount())
					this->ReserveCapacity(other.GetCount());

				Memory::MemoryCopy(this->m_buffer, other.m_buffer, other.GetCount());

				this->m_count = other.GetCount();
				this->m_version = other.GetVersion();
				this->m_capacity = other.GetCapacity();
				this->m_max_capacity = other.GetMaxCapacity();

				return *this;
			}

		public:
			String& operator +=(Char c)
			{

			}

			String& operator +=(CharPtr str)
			{

			}

			String& operator +=(ConstCharPtr str)
			{

			}

			String& operator +=(ConstSelfTypeRef other)
			{

			}

		public:
			ConstSize GetVersion(void) const;

			ConstSize GetCapacity(void) const;

		public:
			Void Resize(Size capacity)
			{
				if (capacity)
				{
					CharPtr temp_buffer = this->m_buffer;

					this->m_buffer = (CharPtr)malloc(capacity * sizeof(Char));

					Memory::MemorySet(this->m_buffer, '\0', this->GetCapacity());

					Memory::MemoryCopy(this->m_buffer, temp_buffer, this->GetCount());

					free(temp_buffer);
				}	
			}

			Void ReserveCapacity(Size capacity)
			{
				if (!this->m_buffer)
				{
					this->m_buffer = (CharPtr)malloc(capacity * sizeof(Char));
					return;
				}

				if (capacity && capacity > this->GetCapacity())
				{
					Size new_capacity;

					new_capacity = this->GetCapacity() + (this->GetCapacity() >> 1);
					new_capacity = new_capacity > capacity ? new_capacity : capacity;
					new_capacity = new_capacity < this->GetMaxCapacity() ? new_capacity : this->GetMaxCapacity();
					new_capacity = (new_capacity + (CAPACITY_ALIGNMENT - 1)) & ~(CAPACITY_ALIGNMENT - 1);

					this->Resize(new_capacity);

					this->m_capacity = new_capacity;
					this->m_version++;
				}
			}

		public:
			Void Clear(void);
		};

		FORGE_FORCE_INLINE ConstSize String::GetVersion(void) { return this->m_version; };

		FORGE_FORCE_INLINE ConstSize String::GetCapacity(void) { return this->m_capacity; };
	}
}

#endif // STRING_H
