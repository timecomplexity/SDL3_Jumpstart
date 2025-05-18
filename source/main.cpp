#pragma once

#define SDL_MAIN_HANDLED
#include <stdio.h>

#include <Logger.h>
#include <LVApplication.h>

int main (int argc, char* args[])
{
    LV::Application::LVApplication app{"Playground"};

    try
    {
        app.Run();
    } 
    catch (const std::exception& e)
    {
        SDLPG_LOG_ERROR << e.what();
        return EXIT_FAILURE;
    }

    return 0;
}
