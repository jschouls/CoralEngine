#include "application.h"
#include <vector>


using namespace coral;

static std::vector<core::Window*> g_WindowList;

Application& Application::GetInstance()
{
	static Application app;
	return app;
}

Application::Application()
{ }

Application::~Application()
{ }

void Application::Init()
{
	
}

/*void Application::RegisterWindow(core::Window&& window)
{
	window.Init();
	g_WindowList.emplace_back(std::move(window));
}

void Application::Run()
{

}*/
