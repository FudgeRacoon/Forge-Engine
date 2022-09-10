#ifndef REMOVE_CONST_H
#define REMOVE_CONST_H

namespace Forge {
	namespace Common
	{
		/// @brief Removes constant qualifiers from typename
		template<typename T>
		struct TRemoveConst { using Type = T; };

		template<typename T>
		struct TRemoveConst<const T> { using Type = T; };
	}
}

#endif // REMOVE_REFERENCE_H
