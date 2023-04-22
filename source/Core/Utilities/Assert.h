#pragma once

#include <OSDL/Core/Logger/Logger.h>

#if (OSDL_DEBUG)
#define OSDL_ENABLE_ASSERTS
#endif

#ifdef OSDL_ENABLE_ASSERTS
#define OSDL_ASSERT(_x)                                                                                                            \
  if (!(_x))                                                                                                                       \
  {                                                                                                                                \
    OSDL_LOG_CRITICAL << "Assertion failed: '" << #_x << "'";                                                                      \
    /* We use std::exit instead of abort so that our program terminates normally yet still returns a non-normal return value.*/    \
    std::exit(EXIT_FAILURE);                                                                                                       \
  }

// TODO: Can't have macros with the same name but would be nice to use OSDL_ASSERT whether we wanted the additional message or not.
// TODO: It would be nice to use stream redirection syntax similar to our logger
#define OSDL_ASSERT_MSG(_x, _message)                                                                                              \
  if (!(_x))                                                                                                                       \
  {                                                                                                                                \
    OSDL_LOG_CRITICAL << "Assertion failed: '" << #_x << "'. " << _message;                                                        \
    /* We use std::exit instead of abort so that our program terminates normally yet still returns a non-normal return value.*/    \
    std::exit(EXIT_FAILURE);                                                                                                       \
  }
#else
#define OSDL_ASSERT(x)
#define OSDL_ASSERT_MSG(_x, _message)
#endif
