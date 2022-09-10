#ifndef ARE_SAME_TYPE_H
#define ARE_SAME_TYPE_H

namespace Forge {
	namespace Common
	{
		/// @brief Tests whether two typenames are the same
		template<typename A, typename B>
		struct TAreSameType { enum { Value = false }; };

		template<typename T>
		struct TAreSameType<T, T> { enum { Value = true }; };
	}
}

#endif // ARE_SAME_TYPE_H
