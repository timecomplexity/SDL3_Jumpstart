#include "LVApplication.h"

#include <SDL.h>
#include <stdio.h>

#include <Logger.h>
#include <SDLWindow.h>
#include <RenderPipeline.h>
#include <vulkan/vulkan.h>

void LV::Application::LVApplication::Run()
{
    // Test if we can read spv files
    LV::Render::RenderPipeline{ "../../../shaders/simple_shader.vert.spv",
        "../../../shaders/simple_shader.frag.spv" };

    uint32_t extensionCount = 0;
    vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);

    SDLPG_LOG_INFO << "Number of extensions supported: " << extensionCount;

    //Hack to get window to stay up
    SDL_Event e;
    bool quit = false;
    while (quit == false)
    {
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
                quit = true;
        }
    }

    _mainWindow.DestroySelf();

    //Quit SDL subsystems
    SDL_Quit();
}