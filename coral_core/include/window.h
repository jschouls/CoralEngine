#pragma once
#include <string>

namespace coral
{
	namespace core
	{
		
		// Forward decl. (Each platform independed shall this have.)
		struct WindowProperties
		{
			uint32_t Width = 1280;
			uint32_t Height = 720;
			std::wstring Title;
			bool Fullscreen = false;
		};

		class Window
		{
		public:

			virtual void Init() = 0;
			virtual void Close() = 0;

			virtual void SetVSync(bool enable) = 0;
			virtual bool VSync() const = 0;
			
			virtual void SetFullscreen(bool enable) = 0;
			virtual bool IsFullscreen() const = 0;

			virtual uint32_t Width() const = 0;
			virtual uint32_t Height() const = 0;

			// Parameter pack so we can give different parameters per platform.
			template<class... Types>
			static Window* Create(Types ... args);
			//static Window* Create(const WindowProperties& windowProperties = WindowProperties());

		protected:
			
		};
	};
};