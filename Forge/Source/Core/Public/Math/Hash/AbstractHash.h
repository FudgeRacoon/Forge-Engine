#ifndef ABSTRACT_HASH_H
#define ABSTRACT_HASH_H

#include "Core/Public/Common/Common.h"

namespace Forge {
	namespace Math
	{
		using Hash32 = U32;
		using Hash64 = U64;

		class FORGE_API AbstractHash
		{
		public:
			virtual Hash64 ComputeHash(ConstCharPtr string) = 0;
			virtual Hash64 ComputeHash(ConstVoidPtr data, Size size) = 0;
		};
	}
}

#endif // ABSTRACT_HASH_H
