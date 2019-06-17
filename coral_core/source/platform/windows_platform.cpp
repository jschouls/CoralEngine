#include "platform/windows_platform.h"
#include "assert.h"

using namespace coral;
using namespace core;
using namespace platform;

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_SIZE:
	{
		int width = LOWORD(lParam);  // Macro to get the low-order word.
		int height = HIWORD(lParam); // Macro to get the high-order word.

		// Respond to the message
	}
	break;
	case WM_PAINT:
	{
		// Update()
		// Render()

		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hwnd, &ps);
		// All painting occurs here, between BeginPaint and EndPaint.

		FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));

		EndPaint(hwnd, &ps);
	}
	break;
	case WM_CLOSE:
		DestroyWindow(hwnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProcW(hwnd, uMsg, wParam, lParam);
		break;
	}
	return DefWindowProcW(hwnd, uMsg, wParam, lParam);
}



WindowWin64::WindowWin64(HINSTANCE instance, const WindowProperties& properties) : m_properties(properties), m_hInstance(instance), m_WindowHandle(nullptr)
{ 
	Init();
}

void WindowWin64::Init()
{
	if (m_properties.Title.empty())
	{
		m_properties.Title = L"Coral1";
	}

	WNDCLASSEXW wc = {};

	wc.cbSize = sizeof(WNDCLASSEXW);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = &WindowProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = m_hInstance;
	wc.hIcon = NULL; //  MAKEINTRESOURCE(APPLICATION_ICON));
	wc.hCursor = ::LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = m_properties.Title.c_str();
	wc.hIconSm = NULL; //  MAKEINTRESOURCE(APPLICATION_ICON));
	// Register window class.
	RegisterClassExW(&wc);


	m_WindowHandle = CreateWindowExW(
		0, // Window style
		m_properties.Title.c_str(),
		m_properties.Title.c_str(),
		WS_OVERLAPPEDWINDOW,

		// Size and position
		0, 0, m_properties.Width, m_properties.Height,

		NULL, // No parent window
		NULL, // No menu
		m_hInstance,
		NULL);

	// If handle is 0, do assertion.
	DWORD dw = 0;
	if (m_WindowHandle == NULL)
	{
		dw = GetLastError();
	}
	assert(m_WindowHandle);

	ShowWindow(m_WindowHandle, SW_SHOWNORMAL);
	OutputDebugString("Init succes.");
}

void WindowWin64::Close()
{
}

void WindowWin64::SetVSync(bool enable)
{
	
}

bool WindowWin64::VSync() const
{
	return false;
}

void WindowWin64::SetFullscreen(bool enable)
{
}

bool WindowWin64::IsFullscreen() const
{
	return false;
}

uint32_t WindowWin64::Width() const
{
	return m_properties.Width;
}

uint32_t WindowWin64::Height() const
{
	return m_properties.Height;
}

HWND WindowWin64::Handle() 
{
	return m_WindowHandle;
}