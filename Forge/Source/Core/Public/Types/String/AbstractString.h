#ifndef ABSTRACT_STRING_H
#define ABSTRACT_STRING_H

#include "Core/Public/Common/TypeDefinitions.h"

namespace Forge {
	namespace Type
	{
		enum StringSearchCase
		{
			/**
			 * Upper/Lower characters must match for strings to be considered equaL.
			 */
			CASE_SENSETIVE,

			/**
			 * Upper/Lower characters does not matter when making a comparison.
			 */
			IGNORE_CASE_SENSETIVITY
		};

		class AbstractString
		{
		private:
			using SelfType         = AbstractString;
			using SelfTypeRef      = AbstractString&;
			using SelfTypePtr      = AbstractString*;
			using ConstSelfType    = const AbstractString;
			using ConstSelfTypeRef = const AbstractString&;
			using ConstSelfTypePtr = const AbstractString*;

		public:
			Bool operator ==(ConstSelfTypeRef other) const;
			Bool operator !=(ConstSelfTypeRef other) const;

		private:
			Size m_count;
			Size m_max_capacity;

		public:
			/**
			 * @brief Checks whether the string is full and is at maximum capacity.
			 *
			 * @return True if the string is full.
			 */
			virtual Bool IsFull(void) const;

			/**
			 * @brief Checks whether the string is empty and not storing any
			 * characters.
			 *
			 * @return True if the string is empty.
			 */
			virtual Bool IsEmpty(void) const;

		public:
			/**
			 * @brief Gets the number of bytes in the string.
			 * 
			 * @return Size storing the number of bytes in the string.
			 */
			virtual Size GetSize(void) const;

			/**
			 * @brief Gets the number of characters in the string.
			 * 
			 * @return Size storing the number of characters in the string.
			 */
			virtual Size GetCount(void) const;

			/**
			 * @brief Gets the maximum number of characters that can be stored in
			 * the string.
			 *
			 * @return Size storing the maximum number of characters that can be
			 * stored in the string.
			 */
			virtual Size GetMaxCapacity(void) const;

			/**
			 * @brief Gets a direct pointer to the memory array managed by the
			 * string.
			 *
			 * Characters in the memory array are guranteed to be stored in 
			 * contiguous memory locations. This allows the pointer to be
			 * offsetted to access different characters.
			 *
			 * @return ConstCharTypePtr storing address of the memory array.
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
			 * @return Size storing the first position of the character that
			 * matches the given character, or -1 if not found.
			 */
			virtual Size FindFirstOf(ConstChar ch, Size pos = 0) const;

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
			 * @return Size storing the last position of the character that
			 * matches the given character, or -1 if not found.
			 */
			virtual Size FindLastOf(ConstChar ch, Size pos = 0) const;

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
			 * @return Size storing the first position of the character that
			 * does not match the given character, or -1 if not found.
			 */
			virtual Size FindFirstNotOf(ConstChar ch, Size pos = 0) const;
			
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
			 * @return Size storing the last position of the character that
			 * does not match the given character, or -1 if not found.
			 */
			virtual Size FindLastNotOf(ConstChar ch, Size pos = 0) const;
			
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
			 * @return Size storing the first position of the character that
			 * matches the given character in the character array, or -1 if not
			 * found.
			 */
			virtual Size FindFirstOf(ConstCharPtr str, Size pos = 0) const;

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
			 * @return Size storing the last position of the character that
			 * matches the given character in the character array, or -1 if not
			 * found.
			 */
			virtual Size FindLastOf(ConstCharPtr str, Size pos = 0) const;

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
			 * @return Size storing the first position of the character that
			 * does not match the given character in the character array, or -1 if
			 * not found
			 */
			virtual Size FindFirstNotOf(ConstCharPtr str, Size pos = 0) const;

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
			 * @return Size storing the last position of the character that
			 * does not match the given character in the character array, or -1 if
			 * not found.
			 */
			virtual Size FindLastNotOf(ConstCharPtr str, Size pos = 0) const;

		public:
			/**
			 * @brief Searches the string for a given sub-string starting from a
			 * given position.
			 * 
			 * @param substr The sub-string to search for in the string.
			 * @param pos    The position to start the search from.
			 * 
			 * @return Size storing the position of the sub-string that matches
			 * the given sub-string, or -1 if not found.
			 */
			virtual Size FindSubString(ConstCharPtr substr, Size pos = 0) const;

			/**
			 * @brief Searches the string for a given sub-string starting from a
			 * given position.
			 *
			 * @param substr The sub-string to search for in the string.
			 * @param pos    The position to start the search from.
			 *
			 * @return Size storing the position of the sub-string that matches
			 * the given sub-string, or -1 if not found.
			 */
			virtual Size FindSubString(ConstSelfTypeRef substr, Size pos = 0) const;

		public:
			/**
			 * @brief Checks wether a given string is at the start of this string.
			 * 
			 * @param substr      The string to check if is at the start of the string.
			 * @param search_case The search case to use when comparing strings.
			 * 
			 * @return True if the given string is at the start of this string.
			 */
			virtual Bool StartsWith(ConstCharPtr substr, StringSearchCase search_case) const;

			/**
			 * @brief Checks wether a given string is at the start of this string.
			 * 
			 * @param substr      The string to check if is at the start of the string.
			 * @param search_case The search case to use when comparing strings.
			 * 
			 * @return True if the given string is at the start of this string.
			 */
			virtual Bool StartsWith(ConstSelfTypeRef substr, StringSearchCase search_case) const;

			/**
			 * @brief Checks wether a given string is at the end of this string.
			 *
			 * @param substr      The string to check if is at the end of the string.
			 * @param search_case The search case to use when comparing strings.
			 *
			 * @return True if the given string is at the end of this string.
			 */
			virtual Bool EndsWith(ConstCharPtr substr, StringSearchCase search_case) const;

			/**
			 * @brief Checks wether a given string is at the end of this string.
			 *
			 * @param substr      The string to check if is at the start of the string.
			 * @param search_case The search case to use when comparing strings.
			 *
			 * @return True if the given string is at the end of this string.
			 */
			virtual Bool EndsWith(ConstSelfTypeRef substr, StringSearchCase search_case) const;

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
			 */
			virtual Bool LexicographicalCompare(ConstCharPtr str);

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
			 */
			virtual Bool LexicographicalCompare(ConstSelfTypeRef str);
		};
	}
}

#endif // ABSTRACT_STRING_H
