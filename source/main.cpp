#pragma once

#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <stdio.h>

#include <Logger.h>
#include <SDLWindow.h>

int main (int argc, char* args[])
{
    //The window we'll be rendering to
    LV::SDLSystem::SDLWindow mainWindow{ "Playground" };

    //Hack to get window to stay up
    SDL_Event e;
    bool quit = false;
    while( quit == false )
    {
        while( SDL_PollEvent( &e ) )
        { 
            if( e.type == SDL_QUIT ) 
                quit = true; 
        } 
    }

    mainWindow.DestroySelf();

    //Quit SDL subsystems
    SDL_Quit();

    return 0;
}
