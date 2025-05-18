#include "SDLState.h"

#include "Logger.h"

uint32_t SDL_SUBSYSTEM_INIT = 0;
bool SDL_ATTRIBUTES_SET = false;
bool SDLPG::SDLSystem::SDLState::_initHasRun = false;

void SDLPG::SDLSystem::SDLState::VerifyInit()
{
    RunSDLInit();

  if (!SDL_ATTRIBUTES_SET)
  {
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_ATTRIBUTES_SET = true;
  }
}

int SDLPG::SDLSystem::SDLState::HandleInitGamepad(void* ptr)
{
  if (!GAMECONTROLLER_CHECK)
  {
    SDLPG_LOG_INFO << "(5/6) Initializing Game Controller subsystem";
    SDL_SUBSYSTEM_INIT |= SDL_Init(SDL_INIT_GAMEPAD);
  }

  if (!JOYSTICK_CHECK)
  {
    SDLPG_LOG_INFO << "(6/6) Initializing Joystick subsystem";
    SDL_SUBSYSTEM_INIT |= SDL_Init(SDL_INIT_JOYSTICK);
  }

  SDLPG_LOG_INFO << "SDL has successfully initialized!";
  SDLPG_LOG_INFO << "=====================================";
  return 0;
}

void SDLPG::SDLSystem::SDLState::RunSDLInit()
{
  // Certain inits might take forever, splitting it up makes sense
  // SDL_Init(SDL_INIT_EVERYTHING);
  _initHasRun = true;
  SDLPG_LOG_INFO << "=====================================";
  SDLPG_LOG_INFO << "Begin initializing SDL...";

  if (!AUDIO_CHECK)
  {
    SDLPG_LOG_INFO << "(1/6) Initializing Audio subsystem";
    SDL_SUBSYSTEM_INIT |= SDL_Init(SDL_INIT_AUDIO);
  }

  if (!VIDEO_CHECK)
  {
    SDLPG_LOG_INFO << "(2/6) Initializing Video subsystem";
    SDL_SUBSYSTEM_INIT |= SDL_Init(SDL_INIT_VIDEO);
  }

  if (!HAPTIC_CHECK)
  {
    SDLPG_LOG_INFO << "(3/6) Initializing Haptics subsystem";
    SDL_SUBSYSTEM_INIT |= SDL_Init(SDL_INIT_HAPTIC);
  }

  if (!EVENTS_CHECK)
  {
    SDLPG_LOG_INFO << "(4/6) Initializing Events subsystem";
    SDL_SUBSYSTEM_INIT |= SDL_Init(SDL_INIT_EVENTS);
  }

  // Spin up a thread for the gamepad initialization since that takes time
  SDL_Thread* thread = SDL_CreateThread(HandleInitGamepad, "HandleInitGamepad", (void*)nullptr);

  if (thread == nullptr)
  {
    SDLPG_LOG_ERROR << "Could not initialize gamepad: " << SDL_GetError();
  }
  else
  {
    SDL_DetachThread(thread);
  }
}
