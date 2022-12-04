#ifndef STRING_H
#define STRING_H

#include "AbstractString.h"

#include "Core/Public/Common/Compiler.h"
#include "Core/Public/Common/TypeDefinitions.h"

namespace Forge {
	namespace Type
	{
		class FORGE_API String : public AbstractString
		{
		private:
			using SelfType         = String;
			using SelfTypeRef      = String&;
			using SelfTypePtr      = String*;
			using ConstSelfType    = const String;
			using ConstSelfTypeRef = const String&;
			using ConstSelfTypePtr = const String*;

		private:
			CharPtr m_buffer;
		};
	}
}

#endif // STRING_H
