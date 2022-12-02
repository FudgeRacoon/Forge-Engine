#include "Core/Public/Types/String/AbstractString.h"

namespace Forge {
	namespace Type
	{
		Size AbstractString::FindFirstOf(ConstChar ch, Size pos = 0) const
		{
			if (!this->m_count)
			{
				// Throw Exception
			}

			if (pos < 0 || pos >= this->m_count)
			{
				// Throw Exception
			}

			ConstCharPtr data = this->GetRawData();

			for (I32 i = pos; i < this->m_count; i++)
				if (*(data + i) == ch)
					return i;

			return -1;
		}

		Size AbstractString::FindLastOf(ConstChar ch, Size pos = 0) const
		{
			if (!this->m_count)
			{
				// Throw Exception
			}

			if (pos < 0 || pos >= this->m_count)
			{
				// Throw Exception
			}

			ConstCharPtr data = this->GetRawData();

			for (I32 i = (this->m_count - 1) - pos; i >= 0; i--)
				if (*(data + i) == ch)
					return i;

			return -1;
		}

		Size AbstractString::FindFirstNotOf(ConstChar ch, Size pos = 0) const
		{
			if (!this->m_count)
			{
				// Throw Exception
			}

			if (pos < 0 || pos >= this->m_count)
			{
				// Throw Exception
			}

			ConstCharPtr data = this->GetRawData();

			for (I32 i = pos; i < this->m_count; i++)
				if (*(data + i) != ch)
					return i;

			return -1;
		}

		Size AbstractString::FindLastNotOf(ConstChar ch, Size pos = 0) const
		{
			if (!this->m_count)
			{
				// Throw Exception
			}

			if (pos < 0 || pos >= this->m_count)
			{
				// Throw Exception
			}

			ConstCharPtr data = this->GetRawData();

			for (I32 i = (this->m_count - 1) - pos; i >= 0; i--)
				if (*(data + i) != ch)
					return i;

			return -1;
		}

		Size AbstractString::FindFirstOf(ConstCharPtr str, Size pos = 0) const
		{
			if (!this->m_count)
			{
				// Throw Exception
			}

			if (pos < 0 || pos >= this->m_count)
			{
				// Throw Exception
			}

			if (!str)
			{
				// Throw Exception
			}

			ConstCharPtr data = this->GetRawData();

			for (I32 i = pos; i < this->m_count; i++)
			{
				ConstCharPtr tmp = str;

				while (*tmp != '\0')
					if (*(data + i) == *(tmp++))
						return i;
			}

			return -1;
		}

		Size AbstractString::FindLastOf(ConstCharPtr str, Size pos = 0) const
		{
			if (!this->m_count)
			{
				// Throw Exception
			}

			if (pos < 0 || pos >= this->m_count)
			{
				// Throw Exception
			}

			if (!str)
			{
				// Throw Exception
			}

			ConstCharPtr data = this->GetRawData();

			for (I32 i = (this->m_count - 1) - pos; i >= 0; i--)
			{
				ConstCharPtr tmp = str;

				while (*tmp != '\0')
					if (*(data + i) == *(tmp++))
						return i;
			}

			return -1;
		}

		Size AbstractString::FindFirstNotOf(ConstCharPtr str, Size pos = 0) const
		{
			if (!this->m_count)
			{
				// Throw Exception
			}

			if (pos < 0 || pos >= this->m_count)
			{
				// Throw Exception
			}

			if (!str)
			{
				// Throw Exception
			}

			ConstCharPtr data = this->GetRawData();

			for (I32 i = pos; i < this->m_count; i++)
			{
				ConstCharPtr tmp = str;

				while (*tmp != '\0')
					if (*(data + i) != *(tmp++))
						return i;
			}

			return -1;
		}

		Size AbstractString::FindLastNotOf(ConstCharPtr str, Size pos = 0) const
		{
			if (!this->m_count)
			{
				// Throw Exception
			}

			if (pos < 0 || pos >= this->m_count)
			{
				// Throw Exception
			}

			if (!str)
			{
				// Throw Exception
			}

			ConstCharPtr data = this->GetRawData();

			for (I32 i = (this->m_count - 1) - pos; i >= 0; i--)
			{
				ConstCharPtr tmp = str;

				while (*tmp != '\0')
					if (*(data + i) != *(tmp++))
						return i;
			}

			return -1;
		}

		Size AbstractString::FindSubString(ConstCharPtr substr, Size pos = 0) const
		{
			if (!this->m_count)
			{
				// Throw Exception
			}

			if (pos < 0 || pos >= this->m_count)
			{
				// Throw Exception
			}

			if (!substr)
			{
				// Throw Exception
			}

			ConstCharPtr data = this->GetRawData();

			ConstSize substr_size = Algorithm::GetStringLength(substr);

			for(I32 i = 0; i < this->m_count - substr_size; i++)

		}

		Size AbstractString::FindSubString(ConstSelfTypeRef substr, Size pos = 0) const
		{
		
		
		}

		Bool AbstractString::StartsWith(ConstCharPtr substr, StringSearchCase search_case) const
		{
		
		}

		Bool AbstractString::StartsWith(ConstSelfTypeRef substr, StringSearchCase search_case) const
		{
		
		}

		Bool AbstractString::EndsWith(ConstCharPtr substr, StringSearchCase search_case) const
		{
		
		}

		Bool AbstractString::EndsWith(ConstSelfTypeRef substr, StringSearchCase search_case) const
		{
		
		}

		Bool AbstractString::LexicographicalCompare(ConstCharPtr str)
		{
		
		}

		Bool AbstractString::LexicographicalCompare(ConstSelfTypeRef str)
		{
		
		}
	}
}
