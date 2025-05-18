#pragma once

#define SDL_MAIN_HANDLED
#include <stdio.h>

#include <Logger.h>
#include <SDLPGApplication.h>

int main (int argc, char* args[])
{
    SDLPG::Application::SDLPGApplication app{"Playground"};

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
