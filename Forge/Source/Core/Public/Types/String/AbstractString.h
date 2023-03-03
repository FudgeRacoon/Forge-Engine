#ifndef ABSTRACT_STRING_H
#define ABSTRACT_STRING_H

#include "Core/Public/Common/TypeDefinitions.h"

#include "Core/Public/Memory/MemoryUtilities.h"

#include "Core/Public/Algorithm/StringUtilities.h"
#include "Core/Public/Algorithm/GeneralUtilities.h"

namespace Forge {
	namespace Type
	{
		enum StringSearchCase
		{
			/**
			 * @brief Upper/Lower characters must match for strings to be considered equaL.
			 */
			CASE_SENSETIVE,

			/**
			 * @brief Upper/Lower characters does not matter when making a comparison.
			 */
			CASE_INSENSITIVE
		};

		/**
		 * @brief Abstract base class for strings which implements read-only
		 * operations.
		 * 
		 * @author Karim Hisham
		 */
		class AbstractString
		{
		private:
			using SelfType         = AbstractString;
			using SelfTypeRef      = AbstractString&;
			using SelfTypePtr      = AbstractString*;
			using ConstSelfType    = const AbstractString;
			using ConstSelfTypeRef = const AbstractString&;
			using ConstSelfTypePtr = const AbstractString*;

		protected:
			Size m_count;
			Size m_max_capacity;
		
		public:
			ConstBool operator ==(ConstSelfTypeRef other) const;
			ConstBool operator !=(ConstSelfTypeRef other) const;

		public:
			AbstractString(Size count, Size max_capacity)
				: m_count(count), m_max_capacity(max_capacity) {}

		public:
			virtual ~AbstractString() = default;

		public:
			/**
			 * @brief Checks whether the string is full and is at maximum capacity.
			 *
			 * @return True if the string is full.
			 */
			virtual ConstBool IsFull(void) const;

			/**
			 * @brief Checks whether the string is empty and not storing any
			 * characters.
			 *
			 * @return True if the string is empty.
			 */
			virtual ConstBool IsEmpty(void) const;

		public:
			/**
			 * @brief Gets the number of characters in the string.
			 * 
			 * @return ConstSize storing the number of characters in the string.
			 */
			virtual ConstSize GetCount(void) const;

			/**
			 * @brief Gets the maximum number of characters that can be stored in
			 * the string.
			 *
			 * @return ConstSize storing the maximum number of characters that can be
			 * stored in the string.
			 */
			virtual ConstSize GetMaxCapacity(void) const;

			/**
			 * @brief Gets a direct pointer to the memory array managed by the
			 * string.
			 *
			 * Characters in the memory array are guranteed to be stored in 
			 * contiguous memory locations. This allows the pointer to be
			 * offsetted to access different characters.
			 *
			 * @return ConstCharPtr storing address of the memory array.
			 */
			virtual ConstCharPtr GetRawData(void) const = 0;

		public:
			/**
			 * @brief Searches the string for the first character that matches a
			 * given character starting from a given position.
			 * 
			 * When a position is specified, the search only includes characters
			 * at or after the position, ignoring any possible occurrences before
			 * it.
			 * 
			 * @param ch  The character to search for in the string.
			 * @param pos The position to start the search from.
			 * 
			 * @return ConstSize storing the first position of the character that
			 * matches the given character, or -1 if not found.
			 * 
			 * @throws InvalidOperationException if the string is empty.
			 * 
			 * @throws InvalidArgumentException if the given position is less than
			 * zero or bigger than the character count.
			 */
			virtual ConstSize FindFirstOf(ConstChar ch, ConstSize pos = 0) const;

			/**
			 * @brief Searches the string for the last character that matches a
			 * given character starting from a given position.
			 *
			 * When a position is specified, the search only includes characters
			 * at or before the position, ignoring any possible occurrences after
			 * it.
			 *
			 * @param ch  The character to search for in the string.
			 * @param pos The position to start the search from.
			 *
			 * @return ConstSize storing the last position of the character that
			 * matches the given character, or -1 if not found.
			 *
			 * @throws InvalidOperationException if the string is empty.
			 * 
			 * @throws InvalidArgumentException if the given position is less than
			 * zero or bigger than the character count.
			 */
			virtual ConstSize FindLastOf(ConstChar ch, ConstSize pos = 0) const;

			/**
			 * @brief Searches the string for the first character that does not 
			 * match a given character starting from a given position.
			 *
			 * When a position is specified, the search only includes characters
			 * at or after the position, ignoring any possible occurrences before
			 * it.
			 *
			 * @param ch  The character to search for in the string.
			 * @param pos The position to start the search from.
			 *
			 * @return ConstSize storing the first position of the character that
			 * does not match the given character, or -1 if not found.
			 * 
			 * @throws InvalidOperationException if the string is empty.
			 * 
			 * @throws InvalidArgumentException if the given position is less than
			 * zero or bigger than the character count.
			 */
			virtual ConstSize FindFirstNotOf(ConstChar ch, ConstSize pos = 0) const;
			
			/**
			 * @brief Searches the string for the last character that does not 
			 * match a given character starting from a given position.
			 *
			 * When a position is specified, the search only includes characters
			 * at or before the position, ignoring any possible occurrences after
			 * it.
			 *
			 * @param ch  The character to search for in the string.
			 * @param pos The position to start the search from.
			 *
			 * @return ConstSize storing the last position of the character that
			 * does not match the given character, or -1 if not found.
			 * 
			 * @throws InvalidOperationException if the string is empty.
			 *  
			 * @throws InvalidArgumentException if the given position is less than
			 * zero or bigger than the character count.
			 */
			virtual ConstSize FindLastNotOf(ConstChar ch, ConstSize pos = 0) const;
			
			/**
			 * @brief Searches the string for the first character that matches a
			 * given character in an array of characters starting from a given
			 * position.
			 *
			 * When a position is specified, the search only includes characters
			 * at or after the position, ignoring any possible occurrences before
			 * it.
			 *
			 * @param str The character array to search for in the string.
			 * @param pos The position to start the search from.
			 *
			 * @return ConstSize storing the first position of the character that
			 * matches the given character in the character array, or -1 if not
			 * found.
			 * 
			 * @throws InvalidOperationException if the string is empty.
			 *  
			 * @throws InvalidArgumentException if the given position is less than
			 * zero or bigger than the character count or if given character array
			 * is null.
			 */
			virtual ConstSize FindFirstOf(ConstCharPtr str, ConstSize pos = 0) const;

			/**
			 * @brief Searches the string for the last character that matches a
			 * given character in an array of characters starting from a given
			 * position.
			 *
			 * When a position is specified, the search only includes characters
			 * at or before the position, ignoring any possible occurrences after
			 * it.
			 *
			 * @param str The character array to search for in the string.
			 * @param pos The position to start the search from.
			 *
			 * @return ConstSize storing the last position of the character that
			 * matches the given character in the character array, or -1 if not
			 * found.
			 * 
			 * @throws InvalidOperationException if the string is empty.
			 *  
			 * @throws InvalidArgumentException if the given position is less than
			 * zero or bigger than the character count or if given character array
			 * is null.
			 */
			virtual ConstSize FindLastOf(ConstCharPtr str, ConstSize pos = 0) const;

			/**
			 * @brief Searches the string for the first character that does not
			 * match a given character in an array of characters starting from a
			 * given position.
			 *
			 * When a position is specified, the search only includes characters
			 * at or after the position, ignoring any possible occurrences before
			 * it.
			 *
			 * @param str The character array to search for in the string.
			 * @param pos The position to start the search from.
			 *
			 * @return ConstSize storing the first position of the character that
			 * does not match the given character in the character array, or -1 if
			 * not found.
			 * 
			 * @throws InvalidOperationException if the string is empty.
			 *  
			 * @throws InvalidArgumentException if the given position is less than
			 * zero or bigger than the character count or if given character array
			 * is null.
			 */
			virtual ConstSize FindFirstNotOf(ConstCharPtr str, ConstSize pos = 0) const;

			/**
			 * @brief Searches the string for the last character that does not
			 * match a given character in an array of characters starting from a
			 * given position.
			 *
			 * When a position is specified, the search only includes characters
			 * at or after the position, ignoring any possible occurrences before
			 * it.
			 *
			 * @param str The character array to search for in the string.
			 * @param pos The position to start the search from.
			 *
			 * @return ConstSize storing the last position of the character that
			 * does not match the given character in the character array, or -1 if
			 * not found.
			 * 
			 * @throws InvalidOperationException if the string is empty.
			 *  
			 * @throws InvalidArgumentException if the given position is less than
			 * zero or bigger than the character count or if given character array
			 * is null.
			 */
			virtual ConstSize FindLastNotOf(ConstCharPtr str, ConstSize pos = 0) const;

		public:
			/**
			 * @brief Searches the string for a given sub-string starting from a
			 * given position.
			 * 
			 * @param substr The sub-string to search for in the string.
			 * @param pos    The position to start the search from.
			 * 
			 * @return ConstSize storing the position of the sub-string that matches
			 * the given sub-string, or -1 if not found.
			 * 
			 * @throws InvalidOperationException if the string is empty.
			 *  
			 * @throws InvalidArgumentException if the given position is less than
			 * zero or bigger than the character count or if given substring is null.
			 */
			virtual ConstSize FindSubString(ConstCharPtr substr, ConstSize pos = 0) const;

			/**
			 * @brief Searches the string for a given sub-string starting from a
			 * given position.
			 *
			 * @param substr The sub-string to search for in the string.
			 * @param pos    The position to start the search from.
			 *
			 * @return ConstSize storing the position of the sub-string that matches
			 * the given sub-string, or -1 if not found.
			 * 
			 * @throws InvalidOperationException if the string is empty.
			 *  
			 * @throws InvalidArgumentException if the given position is less than
			 * zero or bigger than the character count or if given substring is empty.
			 */
			virtual ConstSize FindSubString(ConstSelfTypeRef substr, ConstSize pos = 0) const;

		public:
			/**
			 * @brief Checks wether a given string is at the start of this string.
			 * 
			 * @param substr      The string to check if is at the start of the string.
			 * @param search_case The search case to use when comparing strings.
			 * 
			 * @return True if the given string is at the start of this string.
			 * 
			 * @throws InvalidOperationException if the string is empty.
			 *  
			 * @throws InvalidArgumentException if the given position is less than
			 * zero or bigger than the character count or if given substring is empty.
			 */
			virtual ConstBool StartsWith(ConstCharPtr substr, StringSearchCase search_case) const;

			/**
			 * @brief Checks wether a given string is at the start of this string.
			 * 
			 * @param substr      The string to check if is at the start of the string.
			 * @param search_case The search case to use when comparing strings.
			 * 
			 * @return True if the given string is at the start of this string.
			 * 
			 * @throws InvalidOperationException if the string is empty.
			 *  
			 * @throws InvalidArgumentException if the given position is less than
			 * zero or bigger than the character count or if given substring is empty.
			 */
			virtual ConstBool StartsWith(ConstSelfTypeRef substr, StringSearchCase search_case) const;

			/**
			 * @brief Checks wether a given string is at the end of this string.
			 *
			 * @param substr      The string to check if is at the end of the string.
			 * @param search_case The search case to use when comparing strings.
			 *
			 * @return True if the given string is at the end of this string.
			 * 
			 * @throws InvalidOperationException if the string is empty.
			 *  
			 * @throws InvalidArgumentException if the given position is less than
			 * zero or bigger than the character count or if given substring is empty.
			 */
			virtual ConstBool EndsWith(ConstCharPtr substr, StringSearchCase search_case) const;

			/**
			 * @brief Checks wether a given string is at the end of this string.
			 *
			 * @param substr      The string to check if is at the start of the string.
			 * @param search_case The search case to use when comparing strings.
			 *
			 * @return True if the given string is at the end of this string.
			 * 
			 * @throws InvalidOperationException if the string is empty.
			 *  
			 * @throws InvalidArgumentException if the given position is less than
			 * zero or bigger than the character count or if given substring is empty.
			 */
			virtual ConstBool EndsWith(ConstSelfTypeRef substr, StringSearchCase search_case) const;

		public:
			/**
			 * @brief Returns true if the string compares lexicographically less
			 * than another given string.
			 * 
			 * A lexicographical comparison is the kind of comparison generally
			 * used to sort words alphabetically in dictionaries; It involves
			 * comparing sequentially the elements that have the same position
			 * in both ranges against each other until one element is not 
			 * equivalent to the other. The result of comparing these first
			 * non-matching elements is the result of the lexicographical
			 * comparison.
			 * 
			 * @param str The string to compare with this string
			 * 
			 * @return True if the string compares less than the given string.
			 * 
			 * @throws InvalidOperationException if the string is empty.
			 * 
			 * @throws InvalidArgumentException if given string is empty.
			 */
			virtual ConstBool LexicographicalCompare(ConstCharPtr str);

			/**
			 * @brief Returns true if the string compares lexicographically less
			 * than another given string.
			 *
			 * A lexicographical comparison is the kind of comparison generally
			 * used to sort words alphabetically in dictionaries; It involves
			 * comparing sequentially the elements that have the same position
			 * in both ranges against each other until one element is not
			 * equivalent to the other. The result of comparing these first
			 * non-matching elements is the result of the lexicographical
			 * comparison.
			 *
			 * @param str The string to compare with this string
			 *
			 * @return True if the string compares less than the given string.
			 * 
			 * @throws InvalidOperationException if the string is empty.
			 * 
			 * @throws InvalidArgumentException if given string is empty.
			 */
			virtual ConstBool LexicographicalCompare(ConstSelfTypeRef str);
		};

		FORGE_FORCE_INLINE ConstBool AbstractString::IsFull(void) const
		{
			return this->m_count == this->m_max_capacity;
		}

		FORGE_FORCE_INLINE ConstBool AbstractString::IsEmpty(void) const
		{
			return this->m_count == 0;
		}

		FORGE_FORCE_INLINE ConstSize AbstractString::GetCount(void) const
		{
			return this->m_count;
		}

		FORGE_FORCE_INLINE ConstSize AbstractString::GetMaxCapacity(void) const
		{
			return this->m_max_capacity;
		}
	}
}

#endif // ABSTRACT_STRING_H
