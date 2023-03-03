#ifndef WINDOW_H
#define WINDOW_H

#include "Core/Public/Common/Common.h"

namespace Forge {
	namespace Platform
	{
#if defined(FORGE_PLATFORM_WINDOWS)
		#include "Windows/WindowsWindow.h"
		typedef Forge::Platform::WindowsWindow			Window,		 *WindowPtr;
		typedef const Forge::Platform::WindowsWindow	ConstWindow, *ConstWindowPtr;
#endif
	}
}

#endif
