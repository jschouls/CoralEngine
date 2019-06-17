//#define WIN32_LEAN_AND_MEAN 
//#include <Windows.h>
#include <stdint.h>
#include <assert.h>
#include "resources/resourcemanager.h"

#include <stdio.h>
#include <fcntl.h>
#include <io.h>


/* Window main */
#include "application.h"
#include "platform/windows_platform.h"
#include <stdio.h>
#include <fcntl.h>
#include <io.h>
#include <iostream>
#include <fstream>



using namespace std;

// maximum mumber of lines the output console should have
// From: http://www.cplusplus.com/forum/windows/58206/
static const WORD MAX_CONSOLE_LINES = 500;
void RedirectIOToConsole()
{
	AllocConsole();
	AttachConsole(GetCurrentProcessId());
	freopen("CON", "w", stdout);
}



using namespace coral;
using namespace core;
using namespace platform;

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
	coral::Application::GetInstance().Init();

	Window* window = Window::Create(hInstance);
	Window* window2 = Window::Create(hInstance, WindowProperties{1280, 720, L"Console", false});

	

	MSG msg = { 0 };
	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return 0;
	
	/* Create console window 
	RedirectIOToConsole();
	const wchar_t windowClassName[] = L"Coral";
	const wchar_t* windowTitle = windowClassName;

	CreateWindowClass(hInstance, windowClassName);
	s_windowHandle = CreateWindow(hInstance, windowClassName, windowTitle, 1280, 720);

	ShowWindow(s_windowHandle, nCmdShow);

	coral::resources::ResourceManager& rm = coral::resources::ResourceManager::GetInstance();
	rm.SetPath("./assets/");
	//rm


	MSG msg = { 0 };
	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}


	*/
}


