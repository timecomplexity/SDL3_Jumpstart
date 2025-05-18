#include "SDLWindow.h"

#include "SDLState.h"


SDLPG::SDLSystem::SDLWindow::SDLWindow(const std::string& windowName)
    : _windowTitle(windowName)
{
  SDLPG::SDLSystem::SDLState::VerifyInit();

  CreateTheWindow();
}

SDLPG::SDLSystem::SDLWindow::~SDLWindow()
{
  DestroySelf();
}

bool SDLPG::SDLSystem::SDLWindow::CreateTheWindow()
{
  bool success = false;
  // TODO: Make this read from config
  //_windowWidth = SDLPG::SomeNamespace::ReadIntFromConfig("mainWindow_width", success);
  if (!success)
  {
    _windowWidth = DEFAULT_SCREEN_WIDTH;
  }

  success = false;
  // TODO: Make this read from config
  //_windowHeight = SDLPG::SomeNamespace::ReadIntFromConfig("mainWindow_height", success);
  if (!success)
  {
    _windowHeight = DEFAULT_SCREEN_HEIGHT;
  }

  success = false;
  std::string windowTitle = "";
  // TODO: Make this read from config
  //SDLPG::SomeNamespace::ReadStrFromConfig("mainWindow_title", windowTitle, success);
  if (success && !windowTitle.empty())
  {
    _windowTitle = windowTitle + " - Playground";
  }

  SDL_WindowFlags rendererFlag;
  // TODO: Make this use config instead
  rendererFlag = SDL_WINDOW_VULKAN;
  /*
  auto renderType = SDLPG::Config::SystemConfig::GetInstance().GetCurrentRenderContextType();
  if (renderType == SDLPG::Render::RenderContextType::Vulkan)
  {
      rendererFlag = SDL_WINDOW_VULKAN;
  }
  else if (renderType == SDLPG::Render::RenderContextType::OpenGL)
  {
      rendererFlag = SDL_WINDOW_OPENGL;
  }
  else
  {
      rendererFlag = SDL_WINDOW_OPENGL;
  }
  */

  // TODO: Make this able to be configured as Vulkan or OpenGL
  _mainWindow = SDL_CreateWindow(_windowTitle.c_str(), _windowWidth, _windowHeight,
      rendererFlag | SDL_WINDOW_RESIZABLE);

  if (!_mainWindow)
  {
    _windowInitValid = false;
    return false;
  }

  // TODO: Make this read from configuration
  bool startFullscreen = false;
  if (success && startFullscreen)
  {
      SDL_SetWindowFullscreen(_mainWindow, startFullscreen);
  }

#if SDLPG_DEBUG
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_DEBUG_FLAG);
#endif

  // Set and check context for window
  _context = SDL_GL_CreateContext(_mainWindow);
  if (!_context)
  {
    _windowInitValid = false;
    return false;
  }

  // Grab mouse cursor
  SDL_SetWindowMouseGrab(_mainWindow, false);

  _windowInitValid = true;

  return true;
}

void SDLPG::SDLSystem::SDLWindow::DestroySelf()
{
    if (_context)
    {
        SDL_GL_DestroyContext(_context);
        _context = nullptr;
    }

    if (_mainWindow)
    {
    SDL_DestroyWindow(_mainWindow);
    _mainWindow = nullptr;
    }
}

void SDLPG::SDLSystem::SDLWindow::GetDrawableSizeInfo(int& width, int& height)
{
    SDL_GetWindowSizeInPixels(_mainWindow, &width, &height);
}

void SDLPG::SDLSystem::SDLWindow::SwapBuffers()
{
  SDL_GL_SwapWindow(_mainWindow);
}

float SDLPG::SDLSystem::SDLWindow::GetAspectGL()
{
  int width, height;
  GetDrawableSizeInfo(width, height);

  return (float)width / (float)height;
}

void SDLPG::SDLSystem::SDLWindow::SetMinimizedState(bool newMinimized)
{
    _isMinimized = newMinimized;
}
