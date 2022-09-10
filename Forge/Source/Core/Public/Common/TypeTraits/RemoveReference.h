#ifndef REMOVE_REFERENCE_H
#define REMOVE_REFERENCE_H

namespace Forge {
	namespace Common
	{
		/// @brief Removes reference qualifiers from typename.
		template<typename T>
		struct TRemoveRefernce { using Type = T; };

		template<typename T>
		struct TRemoveRefernce<T&> { using Type = T; };

		template<typename T>
		struct TRemoveRefernce<T&&> { using Type = T; };
	}
}

#endif // REMOVE_REFERENCE_H
