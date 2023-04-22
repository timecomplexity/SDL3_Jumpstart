#pragma once

#include <stdio.h>

#include <SDL.h>

#define SDL_ATTRIBUTES_SET LV::SDLSystem::SDLState::_openGLAttributesSet
#define SDL_SUBSYSTEM_INIT LV::SDLSystem::SDLState::_subsystemInit
#define EVERYTHING_CHECK (SDL_SUBSYSTEM_INIT & SDL_INIT_EVERYTHING)
#define TIMER_CHECK (SDL_SUBSYSTEM_INIT & SDL_INIT_TIMER)
#define AUDIO_CHECK (SDL_SUBSYSTEM_INIT & SDL_INIT_AUDIO)
#define VIDEO_CHECK (SDL_SUBSYSTEM_INIT & SDL_INIT_VIDEO)
#define HAPTIC_CHECK (SDL_SUBSYSTEM_INIT & SDL_INIT_HAPTIC)
#define GAMECONTROLLER_CHECK (SDL_SUBSYSTEM_INIT & SDL_INIT_GAMECONTROLLER)
#define EVENTS_CHECK (SDL_SUBSYSTEM_INIT & SDL_INIT_EVENTS)
#define JOYSTICK_CHECK (SDL_SUBSYSTEM_INIT & SDL_INIT_JOYSTICK)

namespace LV
{
  namespace SDLSystem
  {
    class SDLState
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
} // namespace LV
