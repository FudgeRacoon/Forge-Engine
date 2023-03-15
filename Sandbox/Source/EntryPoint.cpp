#include <Windows.h>
#include "Platform/Public/Platform.h"
#include "../ThirdParty/GL/glew.h"

#include "GraphicsDevice/Public/OpenGL/Windows/GLWindowsGraphicsContext.h"

using namespace Forge::Platform;
using namespace Forge::Graphics;

#pragma comment (lib, "opengl32.lib")

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, INT nCmdShow)
{
	Platform::GetInstance().Initialize(hInstance);

	WindowPtr wnd = Platform::GetInstance().ConstructWindow("Forge Engine");

	GLenum err = glewInit();
	glViewport(0, 0, 800, 600);
	glClearColor(1.0, 1.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);

	SwapBuffers(((GLWindowsGraphicsContext*)(wnd->m_graphics_context))->m_device_context_handle);

	while (!wnd->IsClosing())
	{
		Platform::GetInstance().PumpMessages();
	}

}


