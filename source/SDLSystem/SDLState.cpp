#include "SDLState.h"

#include "Logger.h"

uint32_t SDL_SUBSYSTEM_INIT = 0;
bool SDL_ATTRIBUTES_SET = false;
bool LV::SDLSystem::SDLState::_initHasRun = false;

void LV::SDLSystem::SDLState::VerifyInit()
{
  if (!EVERYTHING_CHECK && !_initHasRun)
  {
    RunSDLInit();
  }

  if (!SDL_ATTRIBUTES_SET)
  {
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_ATTRIBUTES_SET = true;
  }
}

int LV::SDLSystem::SDLState::HandleInitGamepad(void* ptr)
{
  if (!GAMECONTROLLER_CHECK)
  {
    LV_LOG_INFO << "(6/7) Initializing Game Controller subsystem";
    SDL_SUBSYSTEM_INIT |= SDL_Init(SDL_INIT_GAMECONTROLLER);
  }

  if (!JOYSTICK_CHECK)
  {
    LV_LOG_INFO << "(7/7) Initializing Joystick subsystem";
    SDL_SUBSYSTEM_INIT |= SDL_Init(SDL_INIT_JOYSTICK);
  }

  LV_LOG_INFO << "SDL has successfully initialized!";
  LV_LOG_INFO << "=====================================";
  return 0;
}

void LV::SDLSystem::SDLState::RunSDLInit()
{
  // Certain inits might take forever, splitting it up makes sense
  // SDL_Init(SDL_INIT_EVERYTHING);
  _initHasRun = true;
  LV_LOG_INFO << "=====================================";
  LV_LOG_INFO << "Begin initializing SDL...";

  if (!TIMER_CHECK)
  {
    LV_LOG_INFO << "(1/7) Initializing Timer subsystem";
    SDL_SUBSYSTEM_INIT |= SDL_Init(SDL_INIT_TIMER);
  }

  if (!AUDIO_CHECK)
  {
    LV_LOG_INFO << "(2/7) Initializing Audio subsystem";
    SDL_SUBSYSTEM_INIT |= SDL_Init(SDL_INIT_AUDIO);
  }

  if (!VIDEO_CHECK)
  {
    LV_LOG_INFO << "(3/7) Initializing Video subsystem";
    SDL_SUBSYSTEM_INIT |= SDL_Init(SDL_INIT_VIDEO);
  }

  if (!HAPTIC_CHECK)
  {
    LV_LOG_INFO << "(4/7) Initializing Haptics subsystem";
    SDL_SUBSYSTEM_INIT |= SDL_Init(SDL_INIT_HAPTIC);
  }

  if (!EVENTS_CHECK)
  {
    LV_LOG_INFO << "(5/7) Initializing Events subsystem";
    SDL_SUBSYSTEM_INIT |= SDL_Init(SDL_INIT_EVENTS);
  }

  // Spin up a thread for the gamepad initialization since that takes time
  SDL_Thread* thread = SDL_CreateThread(HandleInitGamepad, "HandleInitGamepad", (void*)nullptr);

  if (thread == nullptr)
  {
    LV_LOG_ERROR << "Could not initialize gamepad: " << SDL_GetError();
  }
  else
  {
    SDL_DetachThread(thread);
  }
}
