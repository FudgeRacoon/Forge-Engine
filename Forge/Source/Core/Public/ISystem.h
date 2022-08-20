#ifndef ISYSTEM_H
#define ISYSTEM_H

#include "Common/Compiler.h"
#include "Common/TypeDefinitions.h"

namespace Forge
{
	class FORGE_API ISystem
	{
	public:
		virtual VOID OnInitialize() = 0;

		virtual VOID OnUpdate() = 0;

		virtual VOID OnTerminate() = 0;
	};
}

#endif // ISYSTEM_H
