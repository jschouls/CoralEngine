#pragma once
#include "config.h"
#include "window.h"

namespace coral
{
	class Application
	{
	public:
		static Application& GetInstance();
		
		void Init();


		// Let application know a new window is contructed, application will take over the rest.
		//void RegisterWindow(core::Window&& window);
		

	private:
		Application();
		Application(const Application& app) = delete;
		Application(Application&& app) = delete;

		~Application();
		
	};
};