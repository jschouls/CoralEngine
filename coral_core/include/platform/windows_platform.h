#pragma once
#include "window.h"
#include <memory>

// Windows
#define WIN32_LEAN_AND_MEAN 
#include <Windows.h>

namespace coral
{
using namespace core;
	
namespace platform
{
	
	class WindowWin64 : public core::Window
	{
	public:
		WindowWin64(HINSTANCE instance, const WindowProperties& properties = WindowProperties());

		virtual void Init() override;
		virtual void Close() override;

		virtual void SetVSync(bool enable) override;
		virtual bool VSync() const override;

		virtual void SetFullscreen(bool enable);
		virtual bool IsFullscreen() const;

		virtual uint32_t Width() const override;
		virtual uint32_t Height() const override;

		HWND Handle();

	private:
		WindowProperties m_properties;

		// For Windows
		HINSTANCE m_hInstance;
		HWND m_WindowHandle = nullptr;
	};

	
}; // /platform
	
template<class... Types>
	static Window* Window::Create(Types ... args)
	{
		//return nullptr;
		return new platform::WindowWin64(std::forward<Types>(args)...);
	}

}; // /coral