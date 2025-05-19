#include "SDLState.h"

#include "Logger.h"

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
  Init_System(SDL_INIT_GAMEPAD, "(5/6) Initializing Game Controller subsystem");
  Init_System(SDL_INIT_JOYSTICK, "(6/6) Initializing Joystick subsystem");

  SDLPG_LOG_INFO << "SDL has successfully initialized!";
  SDLPG_LOG_INFO << "=====================================";
  return 0;
}

void SDLPG::SDLSystem::SDLState::RunSDLInit()
{
  // Certain inits might take forever, splitting it up makes sense
  _initHasRun = true;
  SDLPG_LOG_INFO << "=====================================";
  SDLPG_LOG_INFO << "Begin initializing SDL...";

  Init_System(SDL_INIT_AUDIO, "(1/6) Initializing Audio subsystem");
  Init_System(SDL_INIT_VIDEO, "(2/6) Initializing Video subsystem");
  Init_System(SDL_INIT_HAPTIC, "(3/6) Initializing Haptics subsystem");
  Init_System(SDL_INIT_EVENTS, "(4/6) Initializing Events subsystem");

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

void SDLPG::SDLSystem::SDLState::Init_System(Uint32 flag, const char* message)
{
  SDLPG_LOG_INFO << message;
  if(!SDL_Init(flag))
  {
    SDLPG_LOG_ERROR << "Could not initialize subsystem! Error:" << SDL_GetError();
  }
}
