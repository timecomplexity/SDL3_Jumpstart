#pragma once

#include <stdio.h>

#include <SDL3/SDL.h>

#include "Export.h"

#define SDL_ATTRIBUTES_SET SDLPG::SDLSystem::SDLState::_openGLAttributesSet

namespace SDLPG
{
  namespace SDLSystem
  {
    class SDLPG_SDLSYSTEM_API SDLState
    {
    public:
      static void VerifyInit();

    private:
      static void RunSDLInit();
      static int HandleInitGamepad(void* data);
      static void Init_System(Uint32 flag, const char* message);

    private:
      static bool _openGLAttributesSet;
      static bool _initHasRun;
    };
  } // namespace SDLSystem
} // namespace SDLPG
