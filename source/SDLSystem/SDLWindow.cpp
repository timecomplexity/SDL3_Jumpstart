#include "SDLWindow.h"

#include "SDLState.h"

LV::SDLSystem::SDLWindow::SDLWindow(const std::string& windowName)
    : _windowTitle(windowName)
{
  LV::SDLSystem::SDLState::VerifyInit();

  CreateTheWindow();
}

LV::SDLSystem::SDLWindow::~SDLWindow()
{
  DestroySelf();
}

bool LV::SDLSystem::SDLWindow::CreateTheWindow()
{
  bool success = false;
  // TODO: Make this read from config
  //_windowWidth = LV::SomeNamespace::ReadIntFromConfig("mainWindow_width", success);
  if (!success)
  {
    _windowWidth = DEFAULT_SCREEN_WIDTH;
  }

  success = false;
  // TODO: Make this read from config
  //_windowHeight = LV::SomeNamespace::ReadIntFromConfig("mainWindow_height", success);
  if (!success)
  {
    _windowHeight = DEFAULT_SCREEN_HEIGHT;
  }

  success = false;
  std::string windowTitle = "";
  // TODO: Make this read from config
  //LV::SomeNamespace::ReadStrFromConfig("mainWindow_title", windowTitle, success);
  if (success && !windowTitle.empty())
  {
    _windowTitle = windowTitle + " - Playground";
  }

  // TODO: Make this able to be configured as Vulkan or OpenGL
  _mainWindow = SDL_CreateWindow(_windowTitle.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _windowWidth, _windowHeight,
                                 SDL_WINDOW_VULKAN | SDL_WINDOW_RESIZABLE);

  if (!_mainWindow)
  {
    _windowInitValid = false;
    return false;
  }

  // TODO: Make this read from configuration
  bool startFullscreen = false;
  if (success && startFullscreen)
  {
    SDL_SetWindowFullscreen(_mainWindow, SDL_WINDOW_FULLSCREEN_DESKTOP);
  }

  // Set and check context for window
  _context = SDL_GL_CreateContext(_mainWindow);
  if (!_context)
  {
    _windowInitValid = false;
    return false;
  }

  // Grab mouse cursor
  SDL_SetWindowGrab(_mainWindow, SDL_TRUE);

  _windowInitValid = true;

  return true;
}

void LV::SDLSystem::SDLWindow::DestroySelf()
{
  if (_context)
  {
    SDL_GL_DeleteContext(_context);
    _context = nullptr;
  }

  if (_mainWindow)
  {
    SDL_DestroyWindow(_mainWindow);
    _mainWindow = nullptr;
  }
}

void LV::SDLSystem::SDLWindow::GetDrawableSizeInfo(int& width, int& height)
{
  SDL_GL_GetDrawableSize(_mainWindow, &width, &height);
}

void LV::SDLSystem::SDLWindow::SwapBuffers()
{
  SDL_GL_SwapWindow(_mainWindow);
}

float LV::SDLSystem::SDLWindow::GetAspectGL()
{
  int width, height;
  GetDrawableSizeInfo(width, height);

  return (float)width / (float)height;
}
