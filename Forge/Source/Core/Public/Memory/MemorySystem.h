#ifndef MEMORY_SYSTEM_H
#define MEMORY_SYSTEM_H

#include "Core/Public/ISystem.h"
#include "Core/Public/Singleton.h"
#include "Core/Public/Common/Compiler.h"
#include "Core/Public/Common/TypeDefinitions.h"

namespace Forge {
	namespace Memory
	{
		class FORGE_API MemorySystem : public ISystem, public Singleton<MemorySystem>
		{
			
		};
	}
}

#endif // MEMORY_SYSTEM_H