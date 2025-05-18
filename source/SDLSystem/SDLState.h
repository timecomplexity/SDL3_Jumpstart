#pragma once

#include <stdio.h>

#include <SDL3/SDL.h>

#include "Export.h"

#define SDL_ATTRIBUTES_SET SDLPG::SDLSystem::SDLState::_openGLAttributesSet
#define SDL_SUBSYSTEM_INIT SDLPG::SDLSystem::SDLState::_subsystemInit
#define AUDIO_CHECK (SDL_SUBSYSTEM_INIT & SDL_INIT_AUDIO)
#define VIDEO_CHECK (SDL_SUBSYSTEM_INIT & SDL_INIT_VIDEO)
#define HAPTIC_CHECK (SDL_SUBSYSTEM_INIT & SDL_INIT_HAPTIC)
#define GAMECONTROLLER_CHECK (SDL_SUBSYSTEM_INIT & SDL_INIT_GAMEPAD)
#define EVENTS_CHECK (SDL_SUBSYSTEM_INIT & SDL_INIT_EVENTS)
#define JOYSTICK_CHECK (SDL_SUBSYSTEM_INIT & SDL_INIT_JOYSTICK)

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

    private:
      static uint32_t _subsystemInit;
      static bool _openGLAttributesSet;
      static bool _initHasRun;
    };
  } // namespace SDLSystem
} // namespace SDLPG
