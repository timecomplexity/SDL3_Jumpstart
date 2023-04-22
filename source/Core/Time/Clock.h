#pragma once

#include <SDL.h>
#include <memory>
#include <stdio.h>

#include "Export.h"

namespace LV
{
  namespace Core
  {
    namespace Time
    {
      class LV_CORETIME_API Clock
      {
      public:
        Clock();
        virtual ~Clock(){};

        void UpdateClock();
        double GetDeltaTime()
        {
          return _deltaTime;
        };

      private:
        Uint64 _now = 0;
        Uint64 _last = 0;
        double _deltaTime = 0.0;
      };

      class LV_CORETIME_API GameClock
      {
      public:
        static double DeltaTime();
        static void Tick();

      private:
        static std::unique_ptr<Clock> _gameClock;
      };
    } // namespace Time
  }   // namespace Core
} // namespace LV
