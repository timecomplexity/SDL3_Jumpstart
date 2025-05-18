#pragma once

#include <memory>
#include <stdio.h>
#include <string>
#include <glm/glm/glm.hpp>

#include <SDL.h>

#include "Export.h"

namespace LV
{
  namespace SDLSystem
  {
    class SDLPG_SDLSYSTEM_API SDLWindow
    {
    public:
      SDLWindow(const std::string& windowName = "Playground");
      virtual ~SDLWindow();

      std::string GetWindowTitle()
      {
        return _windowTitle;
      }

      bool IsWindowValid()
      {
        return _windowInitValid;
      }

      void DestroySelf();

      void GetDrawableSizeInfo(int& width, int& height);

      float GetAspectGL();

      SDL_Window* GetSDLWindow()
      {
        return _mainWindow;
      }

      SDL_GLContext GetGLContext()
      {
        return _context;
      }

      void SwapBuffers();

      int GetHeight() const
      {
        return _windowHeight;
      }

      int GetWidth() const
      {
        return _windowWidth;
      }

    private:
      bool CreateTheWindow();

    private:
      SDL_Window* _mainWindow = nullptr;
      SDL_GLContext _context = nullptr;

      std::string _windowTitle;

      int _windowHeight = -1;
      int _windowWidth = -1;

      bool _windowInitValid = false;

      const uint32_t DEFAULT_SCREEN_WIDTH = 1024;
      const uint32_t DEFAULT_SCREEN_HEIGHT = 768;
    };
  } // namespace SDLSystem
} // namespace LV
