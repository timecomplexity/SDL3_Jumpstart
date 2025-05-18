#include "Clock.h"


// == CLOCK =============
SDLPG::Core::Time::Clock::Clock() : _now(SDL_GetPerformanceCounter())
{
}

void SDLPG::Core::Time::Clock::UpdateClock()
{
  _last = _now;
  _now = SDL_GetPerformanceCounter();

  _deltaTime = static_cast<double>((_now - _last) * 1000.0) / static_cast<double>(SDL_GetPerformanceFrequency());
}

// == GAME CLOCK ==========
std::unique_ptr<SDLPG::Core::Time::Clock> SDLPG::Core::Time::GameClock::_gameClock = std::make_unique<SDLPG::Core::Time::Clock>();

void SDLPG::Core::Time::GameClock::Tick()
{
  _gameClock->UpdateClock();
}

double SDLPG::Core::Time::GameClock::DeltaTime()
{
  return _gameClock->GetDeltaTime();
}
