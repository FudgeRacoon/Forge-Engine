#ifndef ENABLE_IF_H
#define ENABLE_IF_H

#include "../TypeDefinitions.h"

namespace Forge {
	namespace Common
	{
		/// @brief Checks whether the predicate is true, if so returns the typename
		template<Bool predicate, typename Result>
		struct TEnableIf { };

		template<typename Result>
		struct TEnableIf<true, Result> { using Type = Result; };
	}
}

#endif // ENABLE_IF_H
