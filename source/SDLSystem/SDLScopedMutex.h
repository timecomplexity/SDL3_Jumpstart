#pragma once

#include <SDL_mutex.h>

namespace SDLPG::SDLSystem
{
  class SDLScopedMutex
  {
  public:
    SDLScopedMutex(SDL_mutex* mutex) : _mutex(mutex)
    {
      SDL_LockMutex(mutex);
    }

    ~SDLScopedMutex()
    {
      SDL_UnlockMutex(_mutex);
    }

  private:
    SDLScopedMutex();
    SDL_mutex* _mutex;
  };
} // namespace SDLPG::SDLSystem
