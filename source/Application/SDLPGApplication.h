#pragma once

#include <string>
#include <vector>

#include "Export.h"

#include <SDLWindow.h>

namespace SDLPG::Application
{
	class SDLPG_APPLICATION_API SDLPGApplication
	{
	public:
		SDLPGApplication(const std::string& windowTitle = "Playground") : 
			_mainWindow(windowTitle) {};
		virtual ~SDLPGApplication() {};

		void Run();

	private:
		SDLPG::SDLSystem::SDLWindow _mainWindow;
	};
} // namespace SDLPG::Application