#pragma once

#include <string>
#include <vector>

#include "Export.h"

#include <SDLWindow.h>

namespace LV::Application
{
	class SDLPG_APPLICATION_API LVApplication
	{
	public:
		LVApplication(const std::string& windowTitle = "Playground") : 
			_mainWindow(windowTitle) {};
		virtual ~LVApplication() {};

		void Run();

	private:
		LV::SDLSystem::SDLWindow _mainWindow;
	};
} // namespace LV::Application