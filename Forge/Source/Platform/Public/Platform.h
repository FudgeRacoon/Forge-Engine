#ifndef PLATFORM_H
#define PLATFORM_H

#include "Core/Public/Common/Common.h"

namespace Forge {
	namespace Platform
	{
#if defined(FORGE_PLATFORM_WINDOWS)
		#include "Windows/WindowsPlatform.h"
		typedef Forge::Platform::WindowsPlatform	Platform, *PlatformPtr;
#endif
	}
}

#endif
