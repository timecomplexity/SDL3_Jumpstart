#include "SDLPGApplication.h"

#include <SDL3/SDL.h>
#include <stdio.h>

#include <Logger.h>
#include <SDLWindow.h>
#include <RenderPipeline.h>

#if SDLPG_VULKAN
#include <vulkan/vulkan.h>
#endif

#if SDLPG_OPENGL
#include <GL/glew.h>
#endif

void SDLPG::Application::SDLPGApplication::Run()
{

#if SDLPG_VULKAN
    SDLPG_LOG_INFO << "Initialized with Vulkan.";
    // Test if we can read spv files
    SDLPG::Render::RenderPipeline{ "../../../shaders/simple_shader.vert.spv",
        "../../../shaders/simple_shader.frag.spv" };

    uint32_t extensionCount = 0;
    vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);

    SDLPG_LOG_INFO << "Number of extensions supported: " << extensionCount;
#elif SDLPG_OPENGL
    SDLPG_LOG_INFO << "Initialized with OpenGL.";
    glewExperimental = GL_TRUE;

    if (glewInit() != GLEW_OK)
    {
        SDLPG_LOG_ERROR << "GLEW could not be initialized!";
        _mainWindow.DestroySelf();
        SDL_Quit();
    }

    glViewport(0, 0, 1024, 768);
#endif

    //Hack to get window to stay up
    SDL_Event e;
    bool quit = false;
    while (quit == false)
    {
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_EVENT_QUIT)
                quit = true;
        }

#if SDLPG_OPENGL
        // Draw something to the screen
        glClearColor(0.0f, 1.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
#endif

        _mainWindow.SwapBuffers();
    }

    _mainWindow.DestroySelf();

    //Quit SDL subsystems
    SDL_Quit();
}