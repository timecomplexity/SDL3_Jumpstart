#pragma once

#if defined(_MSC_VER)
    //  Microsoft
#if defined(SDLPG_LOGGER_EXPORT)
    #define SDLPG_LOGGER_API __declspec(dllexport)
#else
    #define SDLPG_LOGGER_API __declspec(dllimport)
#endif
#elif defined(__GNUC__)
    //  GCC
    #define SDLPG_LOGGER_API __attribute__((visibility("default")))
#else
    //  do nothing and hope for the best?
    #define SDLPG_LOGGER_API
    #pragma warning Unknown dynamic link import/export semantics.
#endif
