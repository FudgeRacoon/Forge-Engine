#include "Platform/Public/Platform.h"

using namespace Forge::Platform;

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, INT nCmdShow)
{
	Platform::GetInstance().Initialize(hInstance);

	WindowPtr wnd = Platform::GetInstance().ConstructWindow("Forge Engine");

	Platform::GetInstance().PumpMessages();
}


