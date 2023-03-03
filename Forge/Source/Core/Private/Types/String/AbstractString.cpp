#include "Core/Public/Types/String/AbstractString.h"

namespace Forge {
	namespace Type
	{
		ConstBool AbstractString::operator ==(AbstractString::ConstSelfTypeRef other) const
		{
			if (this->GetCount() != other.m_count)
				return false;

			return Memory::MemoryCompare(this->GetRawData(), other.GetRawData(), this->GetCount());
		}

		ConstBool AbstractString::operator !=(AbstractString::ConstSelfTypeRef other) const
		{
			if (this->GetCount() != other.m_count)
				return true;

			return !(Memory::MemoryCompare(this->GetRawData(), other.GetRawData(), this->GetCount()));
		}

		ConstSize AbstractString::FindFirstOf(ConstChar ch, ConstSize pos) const
		{
			/*if (this->IsEmpty())
				FORGE_EXCEPT(Debug::Exception::ERR_INVALID_OPERATION_EXCEPTION, "String must not be empty");*/

			/*if (Algorithm::IsWithinBoundsInclusive(pos, 0, this->GetCount()))
				FORGE_EXCEPT(Debug::Exception::ERR_ARGUMENT_EXCEPTION, "Position can not be less than zero or greater than string length");*/

			ConstCharPtr data = this->GetRawData();

			for (I32 i = pos; i < this->GetCount(); i++)
				if (*(data + i) == ch)
					return i;

			return -1;
		}

		ConstSize AbstractString::FindLastOf(ConstChar ch, ConstSize pos) const
		{
			/*if (this->IsEmpty())
				FORGE_EXCEPT(Debug::Exception::ERR_INVALID_OPERATION_EXCEPTION, "String must not be empty");*/

			/*if (Algorithm::IsWithinBoundsInclusive(pos, 0, this->GetCount()))
				FORGE_EXCEPT(Debug::Exception::ERR_ARGUMENT_EXCEPTION, "Position can not be less than zero or greater than string length");*/

			ConstCharPtr data = this->GetRawData();

			for (I32 i = (this->GetCount() - 1) - pos; i >= 0; i--)
				if (*(data + i) == ch)
					return i;

			return -1;
		}

		ConstSize AbstractString::FindFirstNotOf(ConstChar ch, ConstSize pos) const
		{
			/*if (this->IsEmpty())
				FORGE_EXCEPT(Debug::Exception::ERR_INVALID_OPERATION_EXCEPTION, "String must not be empty");*/

			/*if (Algorithm::IsWithinBoundsInclusive(pos, 0, this->GetCount()))
				FORGE_EXCEPT(Debug::Exception::ERR_ARGUMENT_EXCEPTION, "Position can not be less than zero or greater than string length");*/

			ConstCharPtr data = this->GetRawData();

			for (I32 i = pos; i < this->GetCount(); i++)
				if (*(data + i) != ch)
					return i;

			return -1;
		}

		ConstSize AbstractString::FindLastNotOf(ConstChar ch, ConstSize pos) const
		{
			/*if (this->IsEmpty())
				FORGE_EXCEPT(Debug::Exception::ERR_INVALID_OPERATION_EXCEPTION, "String must not be empty");*/

			/*if (Algorithm::IsWithinBoundsInclusive(pos, 0, this->GetCount()))
				FORGE_EXCEPT(Debug::Exception::ERR_ARGUMENT_EXCEPTION, "Position can not be less than zero or greater than string length");*/

			ConstCharPtr data = this->GetRawData();

			for (I32 i = (this->GetCount() - 1) - pos; i >= 0; i--)
				if (*(data + i) != ch)
					return i;

			return -1;
		}

		ConstSize AbstractString::FindFirstOf(ConstCharPtr str, ConstSize pos) const
		{
			/*if (this->IsEmpty())
				FORGE_EXCEPT(Debug::Exception::ERR_INVALID_OPERATION_EXCEPTION, "String must not be empty");*/

			/*if (Algorithm::IsWithinBoundsInclusive(pos, 0, this->GetCount()))
				FORGE_EXCEPT(Debug::Exception::ERR_ARGUMENT_EXCEPTION, "Position can not be less than zero or greater than string length");*/

			/*if (Algorithm::IStringNullOrEmpty(str))
				FORGE_EXCEPT(Debug::Exception::ERR_ARGUMENT_EXCEPTION, "Character array must not be null");*/

			ConstCharPtr data = this->GetRawData();

			for (I32 i = pos; i < this->GetCount(); i++)
			{
				ConstCharPtr tmp = str;

				while (Algorithm::IStringNullOrEmpty(tmp))
					if (*(data + i) == *(tmp++))
						return i;
			}

			return -1;
		}

		ConstSize AbstractString::FindLastOf(ConstCharPtr str, ConstSize pos) const
		{
			/*if (this->IsEmpty())
				FORGE_EXCEPT(Debug::Exception::ERR_INVALID_OPERATION_EXCEPTION, "String must not be empty");*/

			/*if (Algorithm::IsWithinBoundsInclusive(pos, 0, this->GetCount()))
				FORGE_EXCEPT(Debug::Exception::ERR_ARGUMENT_EXCEPTION, "Position can not be less than zero or greater than string length");*/

			/*if (Algorithm::IStringNullOrEmpty(str))
				FORGE_EXCEPT(Debug::Exception::ERR_ARGUMENT_EXCEPTION, "Character array must not be null");*/

			ConstCharPtr data = this->GetRawData();

			for (I32 i = (this->GetCount() - 1) - pos; i >= 0; i--)
			{
				ConstCharPtr tmp = str;

				while (Algorithm::IStringNullOrEmpty(tmp))
					if (*(data + i) == *(tmp++))
						return i;
			}

			return -1;
		}

		ConstSize AbstractString::FindFirstNotOf(ConstCharPtr str, ConstSize pos) const
		{
			/*if (this->IsEmpty())
				FORGE_EXCEPT(Debug::Exception::ERR_INVALID_OPERATION_EXCEPTION, "String must not be empty");*/

			/*if (Algorithm::IsWithinBoundsInclusive(pos, 0, this->GetCount()))
				FORGE_EXCEPT(Debug::Exception::ERR_ARGUMENT_EXCEPTION, "Position can not be less than zero or greater than string length");*/

			/*if (Algorithm::IStringNullOrEmpty(str))
				FORGE_EXCEPT(Debug::Exception::ERR_ARGUMENT_EXCEPTION, "Character array must not be null");*/

			ConstCharPtr data = this->GetRawData();

			for (I32 i = pos; i < this->GetCount(); i++)
			{
				ConstCharPtr tmp = str;

				while (Algorithm::IStringNullOrEmpty(tmp))
					if (*(data + i) != *(tmp++))
						return i;
			}

			return -1;
		}

		ConstSize AbstractString::FindLastNotOf(ConstCharPtr str, ConstSize pos) const
		{
			/*if (this->IsEmpty())
				FORGE_EXCEPT(Debug::Exception::ERR_INVALID_OPERATION_EXCEPTION, "String must not be empty");*/

			/*if (Algorithm::IsWithinBoundsInclusive(pos, 0, this->GetCount()))
				FORGE_EXCEPT(Debug::Exception::ERR_ARGUMENT_EXCEPTION, "Position can not be less than zero or greater than string length");*/

			/*if (Algorithm::IStringNullOrEmpty(str))
				FORGE_EXCEPT(Debug::Exception::ERR_ARGUMENT_EXCEPTION, "Character array must not be null");*/

			ConstCharPtr data = this->GetRawData();

			for (I32 i = (this->GetCount() - 1) - pos; i >= 0; i--)
			{
				ConstCharPtr tmp = str;

				while (Algorithm::IStringNullOrEmpty(tmp))
					if (*(data + i) != *(tmp++))
						return i;
			}

			return -1;
		}

		ConstSize AbstractString::FindSubString(ConstCharPtr substr, ConstSize pos) const
		{
			/*if (this->IsEmpty())
				FORGE_EXCEPT(Debug::Exception::ERR_INVALID_OPERATION_EXCEPTION, "String must not be empty");*/

			/*if (Algorithm::IsWithinBoundsInclusive(pos, 0, this->GetCount()))
				FORGE_EXCEPT(Debug::Exception::ERR_ARGUMENT_EXCEPTION, "Position can not be less than zero or greater than string length");*/

			/*if (Algorithm::IStringNullOrEmpty(substr))
				FORGE_EXCEPT(Debug::Exception::ERR_ARGUMENT_EXCEPTION, "Substring must not be null");*/

			ConstCharPtr data = this->GetRawData();

			ConstSize substr_size = Algorithm::GetStringLength(substr);

			for (I32 i = pos; i < this->GetCount() - substr_size; i++)
				for (I32 j = 0; j < substr_size; j++)
				{
					if (*(data + (i + j)) != *(substr + j))
						break;

					return i;
				}

			return -1;
		}

		ConstSize AbstractString::FindSubString(ConstSelfTypeRef substr, ConstSize pos) const
		{
			/*if (this->IsEmpty())
				FORGE_EXCEPT(Debug::Exception::ERR_INVALID_OPERATION_EXCEPTION, "String must not be empty");*/

			/*if (Algorithm::IsWithinBoundsInclusive(pos, 0, this->GetCount()))
				FORGE_EXCEPT(Debug::Exception::ERR_ARGUMENT_EXCEPTION, "Position can not be less than zero or greater than string length");*/

			/*if (substr.IsEmpty())
				FORGE_EXCEPT(Debug::Exception::ERR_ARGUMENT_EXCEPTION, "Substring must no be empty");*/

			ConstCharPtr data = this->GetRawData();
			ConstCharPtr substr_data = substr.GetRawData();

			ConstSize substr_size = substr.GetCount();

			for (I32 i = pos; i < this->GetCount() - substr_size; i++)
				for (I32 j = 0; j < substr_size; j++)
				{
					if (*(data + (i + j)) != *(substr_data + j))
						break;

					return i;
				}

			return -1;
		}

		ConstBool AbstractString::StartsWith(ConstCharPtr substr, StringSearchCase search_case) const
		{
			return this->FindSubString(substr) == 0;
		}

		ConstBool AbstractString::StartsWith(ConstSelfTypeRef substr, StringSearchCase search_case) const
		{
			return this->FindSubString(substr) == 0;
		}

		ConstBool AbstractString::EndsWith(ConstCharPtr substr, StringSearchCase search_case) const
		{
			ConstSize index = this->FindSubString(substr);
			ConstSize substr_size = Algorithm::GetStringLength(this->GetRawData() + index);

			return (this->GetCount() - index) == substr_size;
		}

		ConstBool AbstractString::EndsWith(ConstSelfTypeRef substr, StringSearchCase search_case) const
		{
			ConstSize index = this->FindSubString(substr);
			ConstSize substr_size = Algorithm::GetStringLength(this->GetRawData() + index);

			return this->GetCount() - index == substr_size;
		}

		ConstBool AbstractString::LexicographicalCompare(ConstCharPtr str)
		{
			/*if (this->IsEmpty())
				FORGE_EXCEPT(Debug::Exception::ERR_INVALID_OPERATION_EXCEPTION, "String must not be empty");*/

			/*if (Algorithm::IStringNullOrEmpty(str))
				FORGE_EXCEPT(Debug::Exception::ERR_ARGUMENT_EXCEPTION, "Character array must not be null");*/

			ConstCharPtr data = this->GetRawData();

			for (I32 i = 0; i < Algorithm::Max(this->GetCount(), Algorithm::GetStringLength(str)); i++)
				if (*(data + i) < *(str + i))
					return true;
				else
					return false;
		}

		ConstBool AbstractString::LexicographicalCompare(ConstSelfTypeRef str)
		{
			/*if (this->IsEmpty())
				FORGE_EXCEPT(Debug::Exception::ERR_INVALID_OPERATION_EXCEPTION, "String must not be empty");*/

			/*if (Algorithm::IStringNullOrEmpty(str))
				FORGE_EXCEPT(Debug::Exception::ERR_ARGUMENT_EXCEPTION, "Character array must not be null");*/

			ConstCharPtr data = this->GetRawData();
			ConstCharPtr str_data = str.GetRawData();

			for (I32 i = 0; i < Algorithm::Min(this->GetCount(), str.GetCount()); i++)
				if (*(data + i) < *(str_data + i))
					return true;
				else
					return false;
		}
	}
}
