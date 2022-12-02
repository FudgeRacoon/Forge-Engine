#ifndef STRING_UTILITIES_H
#define STRING_UTILITIES_H

#include "Core/Public/Common/Compiler.h"
#include"Core/Public/Common/TypeDefinitions.h"

namespace Forge {
	namespace Algorithm
	{
		/**
		 * @brief Checks wether a given string is null and not pointing to any
		 * memory or is allocated but not storing any characters.
		 * 
		 * @param str The pointer to a null-terminated byte string.
		 * 
		 * @return True if the given given string is not null or empty. 
		 */
		FORGE_FORCE_INLINE Bool IsStringNullOrEmpty(ConstCharPtr str)
		{
			return str == nullptr || *str == '\0';
		}

		/**
		 * @brief Gets the length of a given string, the number of characters in a
		 * character array whose first element is pointed to by the string pointer
		 * up to and not including the first null character.
		 * 
		 * @param str The pointer to a null-terminated byte string.
		 * 
		 * @return ConstSize storing the length of the string.
		 * 
		 * @throw InvalidArgumentException if the given string is null.
		 */
		FORGE_FORCE_INLINE ConstSize GetStringLength(ConstCharPtr str)
		{
			if (str == nullptr)
			{
				// Throw Exception
			}

			Size count = 0;

			while (*(str++) != '\0')
				count++;

			return count;
		}
	}
}

#endif // STRING_UTILITIES_H 
