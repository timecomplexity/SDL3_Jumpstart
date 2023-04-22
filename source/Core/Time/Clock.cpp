#include "Clock.h"


// == CLOCK =============
LV::Core::Time::Clock::Clock() : _now(SDL_GetPerformanceCounter())
{
}

void LV::Core::Time::Clock::UpdateClock()
{
  _last = _now;
  _now = SDL_GetPerformanceCounter();

  _deltaTime = static_cast<double>((_now - _last) * 1000.0) / static_cast<double>(SDL_GetPerformanceFrequency());
}

// == GAME CLOCK ==========
std::unique_ptr<LV::Core::Time::Clock> LV::Core::Time::GameClock::_gameClock = std::make_unique<LV::Core::Time::Clock>();

void LV::Core::Time::GameClock::Tick()
{
  _gameClock->UpdateClock();
}

double LV::Core::Time::GameClock::DeltaTime()
{
  return _gameClock->GetDeltaTime();
}
