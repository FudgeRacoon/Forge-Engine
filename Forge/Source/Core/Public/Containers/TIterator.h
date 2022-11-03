#ifndef T_ITERATOR_H
#define T_ITERATOR_H

#include "Core/Public/Common/Compiler.h"
#include "Core/Public/Common/TDelegate.h"
#include "Core/Public/Common/TypeDefinitions.h"

#include "Core/Public/Memory/MemoryUtilities.h"

namespace Forge {
	namespace Containers
	{
		template<typename InDataType, typename OutDataType = InDataType>
		class TIterator
		{
		private:
			using DataType         = InDataType;
			using DataTypeRef      = InDataType&;
			using DataTypePtr      = InDataType*;
			using ConstDataType    = const InDataType;
			using ConstDataTypeRef = const InDataType&;
			using ConstDataTypePtr = const InDataType*;

		private:
			using SelfType         = TIterator<InDataType, OutDataType>;
			using SelfTypeRef      = TIterator<InDataType, OutDataType>&;
			using SelfTypePtr      = TIterator<InDataType, OutDataType>*;
			using ConstSelfType    = const TIterator<InDataType, OutDataType>;
			using ConstSelfTypeRef = const TIterator<InDataType, OutDataType>&;
			using ConstSelfTypePtr = const TIterator<InDataType, OutDataType>*;

		private:
			using NextCallback = Common::TDelegate<Void(InDataType*&)>;
			using PrevCallback = Common::TDelegate<Void(InDataType*&)>;
			using DataCallback = Common::TDelegate<OutDataType&(InDataType*&)>;

		private:
			DataTypePtr m_ptr;

		private:
			NextCallback m_next_callback;
			PrevCallback m_prev_callback;
			DataCallback m_data_callback;

		public:
			TIterator(DataTypePtr ptr)
				: m_ptr(ptr) {}

		public:
			TIterator(SelfType&& rhs)
			{
				Memory::MemoryCopy(this, &rhs, sizeof(SelfType));

				rhs.m_ptr = nullptr;
			}
			TIterator(ConstSelfTypeRef rhs)
			{
				Memory::MemoryCopy(this, const_cast<SelfTypePtr>(&rhs), sizeof(SelfType));
			}
		
		public:
			~TIterator() = default;

		public:
			SelfType operator =(SelfType&& other)
			{
				Memory::MemoryCopy(this, &other, sizeof(SelfType));

				other.m_ptr = nullptr;

				return *this;
			}
			SelfType operator =(ConstSelfTypeRef other)
			{
				Memory::MemoryCopy(this, &other, sizeof(SelfType));

				return *this;
			}

		public:
			SelfType operator ++(I32)
			{
				SelfType temp(this->m_ptr);

				m_next_callback.Invoke(this->m_ptr);

				return temp;
			}
			SelfType operator ++(void)
			{
				m_next_callback.Invoke(this->m_ptr);

				return *this;
			}
	
		public:
			SelfType operator --(I32)
			{
				SelfType temp(this->m_ptr);

				m_prev_callback.Invoke(this->m_ptr);

				return temp;
			}
			SelfType operator --(void)
			{
				m_prev_callback.Invoke(this->m_ptr);

				return *this;
			}

		public:
			template<typename OtherType>
			operator TIterator<OtherType, OutDataType>()
			{

			}


		
		
		public:
			DataTypePtr GetPtr()
			{
				return this->m_ptr;
			}

			OutDataType& GetData()
			{
				return m_data_callback.Invoke(this->m_ptr);
			}
		};
	}
}

#endif // T_ITERATOR_H
