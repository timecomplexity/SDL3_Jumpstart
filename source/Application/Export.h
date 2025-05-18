#pragma once

#if defined(_MSC_VER)
    //  Microsoft
#if defined(SDLPG_APPLICATION_EXPORT)
    #define SDLPG_APPLICATION_API __declspec(dllexport)
#else
    #define SDLPG_APPLICATION_API __declspec(dllimport)
#endif
#elif defined(__GNUC__)
    //  GCC
    #define SDLPG_APPLICATION_API __attribute__((visibility("default")))
    // #define UTILITIES_IMPORT
#else
    //  do nothing and hope for the best?
    #define SDLPG_APPLICATION_API
    #pragma warning Unknown dynamic link import/export semantics.
#endif
